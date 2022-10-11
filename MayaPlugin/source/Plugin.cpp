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

			MessageHeader header{};
			memcpy(header.message, name.c_str(), strlen(name.c_str()));
			header.position[0] = 1.f;
			header.position[1] = 2.f;
			header.position[2] = 3.f;

			size_t msgLength = sizeof(MessageHeader) + 1;
			char* msg = new char[msgLength];
			size_t offset = 0;

			memcpy(msg + offset, &header, sizeof(MessageHeader));

			SectionHeader secHeader;
			secHeader.header = MESSAGE;
			secHeader.messageLength = msgLength;
			secHeader.messageID = 0;
			producerBuffer->Send(msg, &secHeader);

			delete[]msg;

			TransformDataHeader transHeader{};
			memcpy(transHeader.message, name.c_str(), strlen(name.c_str()));

			MFnTransform transform(node);
			transform.transformationMatrix().get(transHeader.transMtrx);
			//std::cout << "[(" << transHeader.transMtrx[0][0] << ", " << transHeader.transMtrx[0][1] << ", " << transHeader.transMtrx[0][2] << ", " << transHeader.transMtrx[0][3] << "), ";
			//std::cout << "(" << transHeader.transMtrx[1][0] << ", " << transHeader.transMtrx[1][1] << ", " << transHeader.transMtrx[1][2] << ", " << transHeader.transMtrx[1][3] << "), ";
			//std::cout << "(" << transHeader.transMtrx[2][0] << ", " << transHeader.transMtrx[2][1] << ", " << transHeader.transMtrx[2][2] << ", " << transHeader.transMtrx[2][3] << "), ";
			//std::cout << "(" << transHeader.transMtrx[3][0] << ", " << transHeader.transMtrx[3][1] << ", " << transHeader.transMtrx[3][2] << ", " << transHeader.transMtrx[3][3] << ")]\n";

			size_t anotherMsgLength = sizeof(TransformDataHeader) + 1;
			char* anotherMsg = new char[anotherMsgLength];
			size_t anotherOffset = 0;

			memcpy(anotherMsg + anotherOffset, &transHeader, sizeof(TransformDataHeader));

			SectionHeader anotherSecHeader;
			anotherSecHeader.header = NEW_TRANSFORM;
			anotherSecHeader.messageLength = anotherMsgLength;
			anotherSecHeader.messageID = 0;
			producerBuffer->Send(anotherMsg, &anotherSecHeader);

			delete[]anotherMsg;
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
