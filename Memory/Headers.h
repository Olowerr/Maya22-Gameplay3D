#pragma once
#include "the stuff.h"

constexpr size_t MB = 1048576;

enum Headers 
{
	MESSAGE,
	MESH_NEW,
	MESH_UPDATE,
	TRANSFORM_DATA,
	MATERIAL_DATA
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
	CharString name;
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

struct TransformDataHeader
{
	float transMtrx[4][4];
};

struct MaterialDataHeader
{
	float color[3];
};