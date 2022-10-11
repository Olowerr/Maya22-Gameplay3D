#pragma once

constexpr size_t MB = 1048576;

enum Headers 
{
	MESSAGE,
	NEW_MESH,
	MESH_DATA,
	TRANSFORM_DATA
};

struct Vertex
{
	float position[3];
	//float uv[3];
	//float normal[3];
};

struct SectionHeader
{
	Headers header;
	size_t messageLength;
	size_t messageID;
};

struct MessageHeader
{
	char message[1024]{};
	float position[3];
};

struct MeshDataHeader
{
	int numVertex;
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