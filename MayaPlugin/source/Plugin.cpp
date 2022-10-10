#include "maya_includes.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Send.h"

Comlib* producerBuffer;
std::unordered_map<std::string, MCallbackId> callbacks;
MStatus status = MS::kSuccess;

#define PRINT_EXTRA 0
#define SEND 1

void addCallback(const std::string& name, MCallbackId id)
{
	if (callbacks.count(name))
		MMessage::removeCallback(callbacks[name]);

	callbacks[name] = id;
}

void removeCallback(const std::string& name)
{
	if (callbacks.find(name) == callbacks.end())
		return;

	MNodeMessage::removeCallback(callbacks[name]);
	callbacks.erase(name);
}

void meshTopoAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeEval)
	{
		MFnMesh mesh(plug.node(), &status);
		std::string nodeName = mesh.name().asChar();
		std::string plugName = plug.name().asChar();
#if PRINT_EXTRA
		printPlugPath(plug);
#endif
		if (M_OK2)
		{
			if (plugName.find(".outMesh") != -1)
			{
				std::cout << "Updating mesh: " << nodeName << "\n";
				removeCallback(nodeName + "meshTopoAttriCB");			
#if SEND
				if (!sendMesh(mesh, producerBuffer))
					std::cout << "Failed updating mesh: " << nodeName <<"\n";
#endif
			}
		}
	}
}

/*
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
	EXTRUDE NOT WORKING PLS FIX MAN
*/

void meshTopoChanged(MObject& node, void* clientData)
{
	MCallbackId callbackId = MNodeMessage::addAttributeChangedCallback(node, meshTopoAttributeChanged, nullptr, &status);
	std::string name = MFnDependencyNode(node).name().asChar();
	if (M_OK2)
		addCallback(name + "meshTopoAttriCB", callbackId);
	else
		std::cout << "Failed to add meshChanged callback...\n";
}

void meshDirtyPlug(MObject& node, MPlug& plug, void* clientData)
{
	MFnMesh mesh(node, &status);
	if (M_OK2)
	{
		std::string nodeName = mesh.name().asChar();
#if PRINT_EXTRA
		printPlugPath(plug);
#endif
		if (std::string(plug.name().asChar()).find(".inMesh") != -1)
		{
			std::cout << "Sending mesh: " << nodeName << "\n";
			removeCallback(nodeName + "DirtyPlug");
#if SEND
			if (!sendMesh(mesh, producerBuffer))
				std::cout << "Failed sending mesh: " << nodeName <<"\n";
#endif
		}
	}
}

void nodeAdded(MObject& node, void* clientData)
{
	MFnDependencyNode dgNode(node, &status);
	if (M_OK2)
	{
		MCallbackId id;
		std::string name = dgNode.name().asChar();

		if (node.hasFn(MFn::kMesh))
		{
			id = MNodeMessage::addNodeDirtyPlugCallback(node, meshDirtyPlug, nullptr, &status);
			if (M_OK2)
				addCallback(name + "DirtyPlug", id);

			id = MPolyMessage::addPolyTopologyChangedCallback(node, meshTopoChanged, nullptr, &status);
			if (M_OK2)
				addCallback(name + "TopoChanged", id);
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
	if (M_OK2)
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
