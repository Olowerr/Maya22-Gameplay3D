#pragma once
#include "the stuff.h"

constexpr size_t MB = 1048576;

enum Headers 
{
	MESSAGE,
	NEW_MESH,
	MESH_DATA
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