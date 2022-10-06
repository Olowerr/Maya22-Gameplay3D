#include "maya_includes.h"
#include <maya/MTimer.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Comlib.h"

Comlib* producerBuffer;
std::unordered_map<std::string, MCallbackId> callbacks;
MStatus status = MS::kSuccess;

#define M_OK status == MS::kSuccess
#define M_FAIL status != MS::kSuccess

void addCallback(std::string& name, MCallbackId id)
{
	static int i = 0;

	if (callbacks.find(name) != callbacks.end())
		name += std::to_string(i++);

	callbacks[name] = id;
}

void addCallbackDelOld(std::string& name, MCallbackId id)
{
	if (callbacks.count(name))
		MMessage::removeCallback(callbacks[name]);

	callbacks[name] = id;
}

void nodeAdded(MObject& node, void* clientData)
{
	MFnDependencyNode dgNode(node, &status);
	if (M_OK)
	{
		if (node.hasFn(MFn::kTransform))
		{
			std::string name = dgNode.name(&status).asChar();	

			std::cout << "Transform nodeeeeeeeeeee\n";
			std::cout << name << "\n";

			NewMeshHeader header{};
			memcpy(header.message, name.c_str(), strlen(name.c_str()));

			SectionHeader secHeader;
			secHeader.header = NEW_MESH;
			secHeader.messageLength = sizeof(NewMeshHeader);
			secHeader.messageID = 0;
			producerBuffer->Send((char*)&header, &secHeader);

			/*msgHeader.position[0] = 1.f;
			msgHeader.position[1] = 2.f;
			msgHeader.position[2] = 3.f;

			size_t msgLength = sizeof(MessageHeader) + 1;
			char* msg = new char[msgLength];
			size_t offset = 0;

			memcpy(msg + offset, &msgHeader, sizeof(MessageHeader));

			SectionHeader secHeader;
			secHeader.header = MESSAGE;
			secHeader.messageLength = msgLength;
			secHeader.messageID = 0;
			producerBuffer->Send(msg, &secHeader);

			delete[]msg;*/
		}
	}
}


EXPORT MStatus initializePlugin(MObject obj) {

	MStatus res = MS::kSuccess;

	MFnPlugin myPlugin(obj, "level editor", "1.0", "Any", &res);

	if (MFAIL(res)) {
		CHECK_MSTATUS(res);
		return res;
	}

	std::cout.set_rdbuf(MStreamUtils::stdOutStream().rdbuf());
	std::cerr.set_rdbuf(MStreamUtils::stdErrorStream().rdbuf());
	std::cout << "\n\n\n\nPlugin successfully loaded\n"
		"=======================================================\n\n\n\n";

	// register callbacks here for
	MCallbackId callBackId;

	callBackId = MDGMessage::addNodeAddedCallback(nodeAdded, "dependNode", NULL, &status);
	if (M_OK)
		callbacks.insert({ "nodeCreationCB", callBackId });

	producerBuffer = new Comlib(L"Filemap",150, ProcessType::Producer);

	return res;
}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	for (auto& id : callbacks)
	{
		std::cout << "Unloading \"" << id.first << "\" with ID: " << id.second << std::endl;
		MMessage::removeCallback(id.second);
	}

	delete producerBuffer;

	std::cout << "Plugin unloaded\n"
		"=======================================================" << std::endl;

	return MS::kSuccess;
}
