#pragma once

//#include <maya/MFnMesh.h>
#include "Comlib.h"


inline bool sendMesh(const MObject& node, Comlib* pComlib)
{
	MStatus status;

	MFnMesh mesh(node, &status);
	if (M_FAIL(status))
		return false;

	// MFnTransform name is used in Gameplay3D
	MFnDagNode dag(mesh.parent(0), &status);
	if (M_FAIL(status))
		return false;

	const char* nodeName = dag.name(&status).asChar();
	if (M_FAIL(status))
		return false;

#define SWITCH 1

#if SWITCH == 0
	MItMeshFaceVertex it2(node, &status);
	if (M_FAIL2)
		return false;

	MIntArray xTrianglesPerFace, index;
	MStatus a = mesh.getTriangleOffsets(xTrianglesPerFace, index);

	printIntArray(xTrianglesPerFace);

	MFloatVectorArray tangents, biNormals;
	mesh.getTangents(tangents);
	mesh.getBinormals(biNormals);

	std::vector<Vertex> verts;
	verts.reserve(index.length());

	MPoint position;
	float2 uv;
	MVector normal;

	for (int i = 0; !it2.isDone(); it2.next(), i++)
	{
		position = it2.position();
		it2.getUV(uv);
		it2.getNormal(normal);

		verts.emplace_back();
		verts[i].position[0] = position.x;
		verts[i].position[1] = position.y;
		verts[i].position[2] = position.z;

		verts[i].uv[0]		 = uv[0];
		verts[i].uv[1]		 = uv[1];

		verts[i].normal[0]   = normal.x;
		verts[i].normal[1]   = normal.y;
		verts[i].normal[2]   = normal.z;

		verts[i].tangent[0]	 = tangents[i].x;
		verts[i].tangent[1]	 = tangents[i].y;
		verts[i].tangent[2]	 = tangents[i].z;

		verts[i].biNormal[0] = biNormals[i].x;
		verts[i].biNormal[1] = biNormals[i].y;
		verts[i].biNormal[2] = biNormals[i].z;
	}
	
	MeshInfoHeader meshInfo{ (unsigned int)verts.size(), index.length() };

	const size_t SIZE = sizeof(MeshInfoHeader) + sizeof(Vertex) * verts.size() + sizeof(int) * index.length();
	char* pData = (char*)malloc(SIZE);

	if (!pData)
		return false;

	size_t offset = 0;

	memcpy(pData, &meshInfo, sizeof(MeshInfoHeader));
	offset += sizeof(MeshInfoHeader);

	memcpy(pData + offset, verts.data(), sizeof(Vertex) * verts.size());
	offset += sizeof(Vertex) * verts.size();

	index.get((int*)(pData + offset));

	SectionHeader secHeader;
	secHeader.header = MESH_NEW;
	secHeader.name = nodeName;
	secHeader.messageLength = SIZE;

	pComlib->Send(pData, &secHeader);

	free(pData);

	return true;
	

#elif SWITCH == 1

	MItMeshFaceVertex vertexIterator(node, &status);
	if (M_FAIL(status))
		return false;


	MIntArray xTrianglesPerFace, index;
	MFloatVectorArray tangents, biNormals;
	
	MStatus triStatus = mesh.getTriangleOffsets(xTrianglesPerFace, index);
	MStatus tangStatus = mesh.getTangents(tangents);
	MStatus biNormStatus = mesh.getBinormals(biNormals);

	if (M_FAIL(triStatus) || M_FAIL(tangStatus) || M_FAIL(biNormStatus))
		return false;

	/*
		To avoid unnecessary allocations,
		such as dynamially allocating a Vertex- and int- array,
		and then copying the data from the arrays to pMessage (the memory which Comlib will send).
		We simply first allocate the total bytes needed,
		and then cast & offset the pointer to whichever type we're using.
		This way we can directly write to the memory that the Comlib will copy and send.

		The memory allocated is being used according to the following structure:
		MeshInfoHeader
		Vertex (all vertices)
		int (all indices)
	*/


	MeshInfoHeader meshHeader{ 0, index.length() };
	for (; !vertexIterator.isDone(); vertexIterator.next())
		meshHeader.numVertex++;

	const size_t SIZE = sizeof(MeshInfoHeader) + sizeof(Vertex) * meshHeader.numVertex + sizeof(int) * meshHeader.numIndex;
	char* pMessage = (char*)malloc(SIZE);
	if (!pMessage)
		return false;

	size_t offset = 0, numBytes = SIZE - (sizeof(Vertex) * meshHeader.numVertex + sizeof(int) * meshHeader.numIndex);
	memcpy(pMessage, &meshHeader, numBytes);
	offset += sizeof(MeshInfoHeader);

	MPoint position;
	float2 uv;
	MVector normal;
	Vertex* pVertex = (Vertex*)(pMessage + offset);

	vertexIterator.reset();
	for (int i = 0; !vertexIterator.isDone(); vertexIterator.next(), i++)
	{
		position = vertexIterator.position();
		vertexIterator.getUV(uv);
		vertexIterator.getNormal(normal);

		pVertex[i].position[0] = (float)position.x;
		pVertex[i].position[1] = (float)position.y;
		pVertex[i].position[2] = (float)position.z;

		pVertex[i].uv[0] = uv[0];
		pVertex[i].uv[1] = uv[1];

		pVertex[i].normal[0] = (float)normal.x;
		pVertex[i].normal[1] = (float)normal.y;
		pVertex[i].normal[2] = (float)normal.z;

		pVertex[i].tangent[0] = tangents[i].x;
		pVertex[i].tangent[1] = tangents[i].y;
		pVertex[i].tangent[2] = tangents[i].z;

		pVertex[i].biNormal[0] = biNormals[i].x;
		pVertex[i].biNormal[1] = biNormals[i].y;
		pVertex[i].biNormal[2] = biNormals[i].z;
	}

	offset += sizeof(Vertex) * meshHeader.numVertex;
	index.get((int*)(pMessage + offset));


	SectionHeader secHeader;
	secHeader.header = MESH_NEW;
	secHeader.name = nodeName;
	secHeader.messageLength = SIZE;

	pComlib->Send(pMessage, &secHeader);

	free(pMessage);

	return true;


#else


	// Indices
	MIntArray xTrianglesPerFace, indicies;
	MStatus a = mesh.getTriangleOffsets(xTrianglesPerFace, indicies);

	// Points
	MFloatPointArray points;
	MIntArray xVertexPerFace, vertexIds;
	MStatus b = mesh.getPoints(points);
	MStatus c = mesh.getVertices(xVertexPerFace, vertexIds);

	// Normals
	MFloatVectorArray normals;
	MIntArray xNormalsPerFace, normalIds;
	MStatus d = mesh.getNormals(normals);
	MStatus e = mesh.getNormalIds(xNormalsPerFace, normalIds);

	// UVs
	MFloatArray uArray, vArray;
	MIntArray xUVPerFace, uvIDs;
	MStatus f = mesh.getUVs(uArray, vArray);
	MStatus g = mesh.getAssignedUVs(xUVPerFace, uvIDs);

	/*
		mesh.getTangents()
		mesh.getBinormals()
	*/

	if (M_FAIL(a) || M_FAIL(b) || M_FAIL(c) || M_FAIL(d) || M_FAIL(e) || M_FAIL(f) || M_FAIL(g))
		return false;

	// Write to data directly? :thonk:
	std::vector<Vertex> vertices(indicies.length());
	for (unsigned int i = 0; i < indicies.length(); i++)
	{
		MFloatPoint& currPoint = points[vertexIds[indicies[i]]];
		MFloatVector& currNormal = normals[normalIds[indicies[i]]];
		float& uCoord = uArray[uvIDs[indicies[i]]];
		float& vCoord = vArray[uvIDs[indicies[i]]];

		// memcpy faster? :thonk:
		vertices[i].position[0] = currPoint.x;
		vertices[i].position[1] = currPoint.y;
		vertices[i].position[2] = currPoint.z;

		vertices[i].uv[0] = uCoord;
		vertices[i].uv[1] = vCoord;

		vertices[i].normal[0] = currNormal.x;
		vertices[i].normal[1] = currNormal.y;
		vertices[i].normal[2] = currNormal.z;
	}
	

	MeshInfoHeader meshInfo;
	meshInfo.numVertex = indicies.length();

	const size_t SIZE = sizeof(MeshInfoHeader) + sizeof(Vertex) * vertices.size();
	void* pData = malloc(SIZE);

	// Ignore warnings :]
	memcpy(pData, &meshInfo, sizeof(MeshInfoHeader));
	memcpy((char*)pData + sizeof(MeshInfoHeader), vertices.data(), SIZE - sizeof(MeshInfoHeader));

	SectionHeader secHeader;
	secHeader.header = MESH_NEW;
	secHeader.name = nodeName;
	secHeader.messageLength = SIZE;
	secHeader.messageID = 0;

	// Check if failed?
	pComlib->Send((char*)pData, &secHeader);

	free(pData);

#endif

	return true;
}

inline bool sendUpdateMesh(unsigned int index, const MObject& node, Comlib* pComlib)
{
	MStatus status;

	// temp
	return sendMesh(node, pComlib);

	MFnMesh mesh(node, &status);
	return false;

	const char* nodeName = mesh.name(&status).asChar();
	if (M_FAIL(status))
		return false;

	// first ---
	MPoint position;
	status = mesh.getPoint(index, position);
	if (M_FAIL(status))
		return false;
	
	MVector normal;
	status = mesh.getVertexNormal(index, false, normal);
	if (M_FAIL(status))
		return false;
	// --- first



	// second ---
	/*
		find and save i (in indien) when searching through vertexIds for index
		go through indien and match elements to indicies

		matching values should indicate that vertex[i] needs to be updated in gameplay3d
		right?
	*/

	MIntArray indien;
	MIntArray xTrianglesPerFace, indicies, xVertexPerFace, vertexIds;
	mesh.getTriangleOffsets(xTrianglesPerFace, indicies);
	mesh.getVertices(xVertexPerFace, vertexIds);
	
	for (unsigned int i = 0; i < vertexIds.length(); i++)
	{
		if (vertexIds[i] == index)
			indien.append(i);
	}
	// --- second

	MeshUpdateHeader header;
	header.vertexIndex = index;
	
	header.newVertex.position[0] = position.x;
	header.newVertex.position[1] = position.y;
	header.newVertex.position[2] = position.z;

	header.newVertex.uv[0] = 0.f; // temp
	header.newVertex.uv[1] = 0.f; // temp

	header.newVertex.normal[0] = normal.x;
	header.newVertex.normal[1] = normal.y;
	header.newVertex.normal[2] = normal.z;
	
	SectionHeader secHeader;
	secHeader.header = MESH_UPDATE;
	secHeader.name= nodeName;
	secHeader.messageLength = sizeof(MeshUpdateHeader);
	secHeader.messageID = 0;

	pComlib->Send((char*)&header, &secHeader);

	return true;


	//std::cout << "Indicies:\n";
	//printIntArray(indicies);
	//std::cout << "\nPoints:\n";
	//printFloatArray(points);
	//printIntArray(vertexIds);
	//std::cout <<"\nNormals:\n";
	//printFloatArray(normals);
	//printIntArray(normalIds);

}

inline bool SendTransformData(const MObject& obj, Comlib* pComlib)
{
	MStatus status;
	MFnTransform trans(obj, &status);
	if (status == MS::kSuccess)
	{
		MFnDagNode dag(obj, &status);
		if (M_FAIL(status))
			return false;

		std::string name = trans.name(&status).asChar();
		if (M_FAIL(status))
			return false;

		MDagPath path;
		status = dag.getPath(path);
		if (M_FAIL(status))
			return false;

		TransformDataHeader transHeader{};
		path.inclusiveMatrix().get(transHeader.transMtrx);

		size_t transMsgLen = sizeof(TransformDataHeader) + 1;
		char* msg = new char[transMsgLen];
		size_t offset = 0;

		memcpy(msg + offset, &transHeader, sizeof(TransformDataHeader));

		SectionHeader secHeader;
		secHeader.name = name;
		secHeader.header = TRANSFORM_DATA;
		secHeader.messageLength = transMsgLen;
		secHeader.messageID = 0;
		pComlib->Send(msg, &secHeader);

		delete[]msg;
		for (size_t i = 0; i < dag.childCount(); i++)
		{
			if (!dag.child(i).isNull())
			{
				SendTransformData(dag.child(i), pComlib);
			}
		}

		return true;
	}

	return false;
}

inline bool SendMaterialData(MFnLambertShader& shader, Comlib* pComlib, const MObject& node)
{
	MStatus status;
	MFnMesh mesh(node, &status);
	if (M_FAIL(status))
		return false;

	MFnDagNode dag(mesh.parent(0), &status);
	if (M_FAIL(status))
		return false;


	if (M_FAIL(status))
		return false;

	const char* nodeName = dag.name(&status).asChar();
	if (status == MS::kSuccess)
	{
		std::cout << nodeName << std::endl;

		MaterialDataHeader matHeader{};
		matHeader.color[0] = shader.color().r;
		matHeader.color[1] = shader.color().g;
		matHeader.color[2] = shader.color().b;
		matHeader.color[3] = shader.color().a;

		size_t matMsgLen = sizeof(MaterialDataHeader) + 1;
		char* msg = new char[matMsgLen];
		size_t offset = 0;

		memcpy(msg + offset, &matHeader, sizeof(MaterialDataHeader));

		SectionHeader secHeader;
		secHeader.name = nodeName;
		secHeader.header = MATERIAL_DATA;
		secHeader.messageLength = matMsgLen;
		secHeader.messageID = 0;
		pComlib->Send(msg, &secHeader);

		delete[]msg;

		return true;
	}

	return false;
}

inline bool sendCamera(M3dView view, Comlib* pComlib)
{
	MStatus status;

	view.updateViewingParameters();

	MDagPath camPath;
	view.getCamera(camPath);

	MFnCamera camera(camPath, &status);
	if (M_FAIL(status))
		return false;

	MFnTransform transform(camera.parent(0), &status);
	if (M_FAIL(status))
		return false;

	CameraHeader cameraData{};

	transform.transformationMatrix().get(cameraData.viewMatrix);
	cameraData.fieldOfView = camera.horizontalFieldOfView() * (180.f / M_PI);
	cameraData.perspective = !camera.isOrtho();

	if (cameraData.perspective)
	{
		cameraData.width = (float)view.portWidth();
		cameraData.height = (float)view.portHeight();
	}
	else
	{
		cameraData.width = (float)camera.orthoWidth();
		cameraData.height = cameraData.width / ((float)view.portWidth() / (float)view.portHeight());
	}

	SectionHeader secHeader;
	secHeader.name = transform.name().asChar();
	secHeader.messageLength = sizeof(CameraHeader);
	secHeader.header = Headers::CAMERA_DATA;

	pComlib->Send((char*)&cameraData, &secHeader);

	return true;
}