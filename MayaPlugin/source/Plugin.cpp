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

void meshDirtyPlug(MObject& node, MPlug& plug, void* clientData)
{
	MFnMesh mesh(node, &status);
	if (M_OK)
	{
		const char* nodeName = mesh.name().asChar();

		if (std::string(plug.name().asChar()).find(".inMesh") != -1)
		{
			MPointArray mayaVerts;
			status = mesh.getPoints(mayaVerts);
			if (M_OK)
			{
				std::cout << "Mesh: " << mesh.name() << ", " << mayaVerts.length() << " vertices: ";

				for (unsigned int i = 0; i < mayaVerts.length(); i++)
					std::cout << "(" << mayaVerts[i].x << ", " << mayaVerts[i].y << ", " << mayaVerts[i].z << "), ";
				std::cout << "\n";

				MIntArray trianglesPerFace, indicies;
				mesh.getTriangles(trianglesPerFace, indicies);

				for (unsigned int i = 0; i < trianglesPerFace.length(); i++)
					std::cout << trianglesPerFace[i] << ", ";
				std::cout << "\n";

				for (unsigned int i = 0; i < indicies.length(); i++)
					std::cout << indicies[i] << ", ";
				std::cout << "\n";

				// Optimize
				std::vector<Vertex> vertices(indicies.length());
				for (unsigned int i = 0; i < indicies.length(); i++)
				{
					MPoint& currVertex = mayaVerts[indicies[i]];
					vertices[i].position[0] = currVertex.x;
					vertices[i].position[1] = currVertex.y;
					vertices[i].position[2] = currVertex.z;
				}

				return;

				const size_t SIZE = sizeof(MeshDataHeader); // + sizeof(verts);
				void* data = malloc(SIZE);
				
				SectionHeader secHeader;
				secHeader.header = NEW_MESH;
				secHeader.nodeName = nodeName;
				secHeader.messageLength = SIZE;
				secHeader.messageID = 0;

				producerBuffer->Send((char*)data, &secHeader);

				free(data);
			}
		}
	}
}

void nodeAdded(MObject& node, void* clientData)
{
	MFnDependencyNode dgNode(node, &status);
	if (M_OK)
	{
		std::string name = dgNode.name().asChar();

		if (node.hasFn(MFn::kTransform))
		{
		}

		if (node.hasFn(MFn::kMesh))
		{
			MCallbackId id = MNodeMessage::addNodeDirtyPlugCallback(node, meshDirtyPlug, nullptr, &status);
			if (M_OK)
				addCallback(name, id);
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
