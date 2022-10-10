#pragma once

//#include <maya/MFnMesh.h>
#include "Comlib.h"


inline bool sendMesh(const MFnMesh& mesh, Comlib* pComlib)
{
	MStatus status;
	const char* nodeName = mesh.name(&status).asChar();
	if (M_FAIL(status))
		return false;

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
	secHeader.header = NEW_MESH;
	secHeader.nodeName = nodeName;
	secHeader.messageLength = SIZE;
	secHeader.messageID = 0;

	// Check if failed?
	pComlib->Send((char*)pData, &secHeader);

	free(pData);

	return true;

}
