#pragma once

// some definitions for the DLL to play nice with Maya
#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)

#include <maya/MStreamUtils.h>

#include <maya/MFloatMatrix.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshFaceVertex.h>
#include <maya/MPxSurfaceShape.h>
#include <maya/MPlugArray.h>

#include <maya/MFnPlugin.h>

#include <maya/MFnMesh.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnTransform.h>

#include <maya/MFnCamera.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnLambertShader.h>
#include <maya/MFnBlinnShader.h>
#include <maya/MFnPhongShader.h>
#include <maya/MFnPointLight.h>

#include <maya/MImage.h>
#include <maya/MFloatPointArray.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MEulerRotation.h>
#include <maya/MVector.h>
#include <maya/MItDag.h>
#include <maya/M3dView.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MPlugArray.h>
#include <maya/MSelectionList.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MDagPathArray.h>

// Wrappers
#include <maya/MGlobal.h>
#include <maya/MCallbackIdArray.h>

// Messages
#include <maya/MMessage.h>
#include <maya/MTimerMessage.h>
#include <maya/MDGMessage.h>
#include <maya/MEventMessage.h>
#include <maya/MPolyMessage.h>
#include <maya/MNodeMessage.h>
#include <maya/MDagPath.h>
#include <maya/MDagMessage.h>
#include <maya/MUiMessage.h>
#include <maya/MModelMessage.h>

// Commands
#include <maya/MPxCommand.h>


#define M_OK(X) X == MS::kSuccess
#define M_OK2 status == MS::kSuccess

#define M_FAIL(X) X != MS::kSuccess
#define M_FAIL2 status != MS::kSuccess

inline void printIntArray(const MIntArray& arr)
{
	const unsigned int length = arr.length();
	std::cout << "Length: " << length << ", values: ";

	for (unsigned int i = 0; i < length; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\n";
}

inline void printFloatArray(const MFloatPointArray& arr)
{
	const unsigned int length = arr.length();
	std::cout << "Length: " << length << ", values: ";

	for (unsigned int i = 0; i < length; i++)
		std::cout << "(" << arr[i].x << ", " << arr[i].y << ", " << arr[i].z << arr[i].w << "), ";
	std::cout << "\n";
}

inline void printFloatArray(const MFloatVectorArray& arr)
{
	const unsigned int length = arr.length();
	std::cout << "Length: " << length << ", values: ";

	for (unsigned int i = 0; i < length; i++)
		std::cout << "(" << arr[i].x << ", " << arr[i].y << ", " << arr[i].z << "), ";
	std::cout << "\n";
}

inline void printFloatArray(const MFloatArray& arr)
{
	const unsigned int length = arr.length();
	std::cout << "Length: " << length << ", values: ";

	for (unsigned int i = 0; i < length; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\n";
}

inline void printNodePath(MObject& node)
{
	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dag(node);
		MDagPathArray paths;
		if (dag.getAllPaths(paths) == MS::kSuccess)
		{
			std::cout << dag.name() << " has " << paths.length() << " path(s) ";
			for (unsigned int i = 0; i < paths.length(); i++)
				std::cout << i << ": " << paths[i].fullPathName() << " ";
			std::cout << "\n\n";
		}
		else
			std::cout << "No paths found for: " << dag.name() << "...\n\n";
	}
	else
		std::cout << "Node was not a dag node...\n\n";

}

inline void printPlugPath(MPlug& plug)
{
	if (plug.node().hasFn(MFn::kDagNode))
	{
		MFnDagNode dag(plug.node());
		MDagPathArray paths;
		if (dag.getAllPaths(paths) == MS::kSuccess)
		{
			std::cout << plug.name() << " has " << paths.length() << " path(s) ";
			for (unsigned int i = 0; i < paths.length(); i++)
				std::cout << i << ": " << paths[i].fullPathName() << " ";
			std::cout << "\n";
		}
		else
			std::cout << "No paths found for: " << plug.name() << "...\n";
	}
	else
		std::cout << "Node was not a dag node...\n";
}
