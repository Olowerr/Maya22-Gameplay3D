#pragma once
#include "the stuff.h"

constexpr size_t MB = 1048576;

enum Headers 
{
	MESSAGE,
	MESH_NEW,
	MESH_UPDATE,
	TRANSFORM_DATA
};

struct Vertex
{
	float position[3];
	float uv[2];
	float normal[3];
};

struct SectionHeader
{
	Headers header;
	size_t messageLength;
	size_t messageID;

	// Will always be used right?
	CharString nodeName;
};

struct MeshInfoHeader
{
	unsigned int numVertex;
	//unsigned int numIndex;
};

struct MeshUpdateHeader
{
	unsigned int vertexIndex;
	Vertex newVertex;
};

struct NewMeshHeader
{
	char message[1024]{};
};

struct TransformDataHeader
{
	char message[1024]{};
	float transMtrx[4][4];
};