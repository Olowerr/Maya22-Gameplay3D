#pragma once
#include "CharString.h"

constexpr size_t MB = 1048576;

enum Headers : unsigned int
{
	INVALID = 0,
	MESH_NEW,
	MESH_UPDATE,
	TRANSFORM_DATA,
	MATERIAL_DATA,
	CAMERA_DATA,
	NODE_DELETE,
	NAME_CHANGE,
	COLOR_TEXTURE,
	NORMAL_TEXTURE,
	MESH_MATERIAL
};

struct Vertex
{
	float position[3];
	float uv[2];
	float normal[3];
	float tangent[3];
	float biNormal[3];
};

struct SectionHeader
{
	Headers header = Headers::INVALID;
	size_t messageLength = 0;
	size_t messageID = 0;

	// Name of node or material we're affecting
	CharString name{};
};

struct MeshInfoHeader
{
	unsigned int numVertex;
	unsigned int numIndex;
};

struct TransformDataHeader
{
	float transMtrx[4][4];
};

struct MaterialDataHeader
{
	float color[4];
};

struct TextureDataHeader
{
	CharString path;
};

struct MeshMaterialHeader
{
	CharString materialName;
};

struct CameraHeader
{
	bool perspective;

	float viewMatrix[4][4];

	// ratio = width / height
	float width;
	float height;
	float fieldOfView;
};

struct NameChangeHeader
{
	CharString newName;
};
