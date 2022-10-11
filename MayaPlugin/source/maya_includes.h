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

#pragma region
#define PRINT_MSG_IND(msg, X) if (msg & MNodeMessage::AttributeMessage::X) std::cout << #X << ", "

#define PRINT_MSG(msg)							\
std::cout << "Messages: ";						\
PRINT_MSG_IND(msg, kConnectionMade);			\
PRINT_MSG_IND(msg, kConnectionBroken);			\
PRINT_MSG_IND(msg, kAttributeEval);				\
PRINT_MSG_IND(msg, kAttributeSet);				\
PRINT_MSG_IND(msg, kAttributeLocked);			\
PRINT_MSG_IND(msg, kAttributeUnlocked);			\
PRINT_MSG_IND(msg, kAttributeAdded);			\
PRINT_MSG_IND(msg, kAttributeRemoved);			\
PRINT_MSG_IND(msg, kAttributeRenamed);			\
PRINT_MSG_IND(msg, kAttributeKeyable);			\
PRINT_MSG_IND(msg, kAttributeUnkeyable);		\
PRINT_MSG_IND(msg, kIncomingDirection);			\
PRINT_MSG_IND(msg, kAttributeArrayAdded);		\
PRINT_MSG_IND(msg, kAttributeArrayRemoved);		\
PRINT_MSG_IND(msg, kOtherPlugSet);				\
PRINT_MSG_IND(msg, kLast);						\
std::cout << " | "

#define M_OK(X) X == MS::kSuccess
#define M_OK2 status == MS::kSuccess

#define M_FAIL(X) X != MS::kSuccess
#define M_FAIL2 status != MS::kSuccess
#pragma endregion Defines

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
			std::cout << " | ";
		}
		else
			std::cout << "No paths found for: " << dag.name() << "... | ";
	}
	else
		std::cout << "Node was not a dag node... | ";

}

inline void printPlugPath(MPlug& plug)
{
	MString name = plug.name();

	if (plug.node().hasFn(MFn::kDependencyNode))
	{
		if (plug.node().hasFn(MFn::kDagNode))
		{
			MFnDagNode dag(plug.node());
			MDagPathArray paths;
			if (dag.getAllPaths(paths) == MS::kSuccess)
			{
				std::cout << name << " has " << paths.length() << " path(s) ";
				for (unsigned int i = 0; i < paths.length(); i++)
					std::cout << i << ": " << paths[i].fullPathName() << " ";
				std::cout << " | ";
			}
			else
				std::cout << "Failed to get paths for \"" << name << "\"... | ";
		}
		else
			std::cout << "Plug: \"" << name <<"\" was not a dag node... | ";
	}
	else
		std::cout << "Plug: \"" << name <<"\" was not a dependency node... | ";
}

inline void printMatrix(const MMatrix& matrix)
{
	float values[4][4];
	matrix.get(values);
	std::cout << "[(" << values[0][0] << ", " << values[0][1] << ", " << values[0][2] << ", " << values[0][3] << "), ";
	std::cout << "(" << values[1][0] << ", " << values[1][1] << ", " << values[1][2] << ", " << values[1][3] << "), ";
	std::cout << "(" << values[2][0] << ", " << values[2][1] << ", " << values[2][2] << ", " << values[2][3] << "), ";
	std::cout << "(" << values[3][0] << ", " << values[3][1] << ", " << values[3][2] << ", " << values[3][3] << ")]\n";
}

inline void printVector(const MPoint& vector)
{
	std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
}

inline void printVector(const MVector& vector)
{
	std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
}

inline void printVector(const float2& vector)
{
	std::cout << "(" << vector[0] << ", " << vector[1] << ")\n";
}