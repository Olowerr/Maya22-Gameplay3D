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

void SendTransformData(MObject obj)
{
	MFnTransform trans(obj, &status);
	if (status == MS::kSuccess)
	{
		MFnDagNode dag(obj);
		cout << trans.name() << " new translation: " << trans.getTranslation(MSpace::kObject, &status) << endl;
		cout << trans.name() << " new transformation Matrix: " << trans.transformationMatrix() << endl;

		std::string name = dag.name(&status).asChar();

		TransformDataHeader transHeader{};
		memcpy(transHeader.message, name.c_str(), strlen(name.c_str()));

		trans.transformationMatrix().get(transHeader.transMtrx);

		size_t transMsgLen = sizeof(TransformDataHeader) + 1;
		char* msg = new char[transMsgLen];
		size_t offset = 0;

		memcpy(msg + offset, &transHeader, sizeof(TransformDataHeader));

		SectionHeader secHeader;
		secHeader.header = TRANSFORM_DATA;
		secHeader.messageLength = transMsgLen;
		secHeader.messageID = 0;
		producerBuffer->Send(msg, &secHeader);

		delete[]msg;
		if (!dag.child(1).isNull())
		{
			SendTransformData(dag.child(1));
		}
	}
}

void nodeAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* x)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
	{
		MObject obj(plug.node());
		if (obj.hasFn(MFn::kTransform))
		{
			SendTransformData(obj);
		}
	}
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

			size_t transMsgLen = sizeof(TransformDataHeader) + 1;
			msg = new char[transMsgLen];

			memcpy(msg + offset, &transHeader, sizeof(TransformDataHeader));

			secHeader.header = TRANSFORM_DATA;
			secHeader.messageLength = transMsgLen;
			secHeader.messageID = 0;
			producerBuffer->Send(msg, &secHeader);

			delete[]msg;

			MCallbackId transformID = MNodeMessage::addAttributeChangedCallback(node, nodeAttributeChanged, NULL, &status);
			if (status == MS::kSuccess)
			{
				std::string extra = "transformChanged";
				auto iterator = callbacks.find(name + extra);
				if (iterator != callbacks.end())
				{
					cout << "Callback erased: " << iterator->first << endl;
					MMessage::removeCallback(iterator->second);
					callbacks.erase(iterator);
				}
				callbacks.insert({ name + extra, transformID });
			}
			else
			{
				cout << "Something went wrong when added callbacks to a node: " << name << endl;
			}
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
