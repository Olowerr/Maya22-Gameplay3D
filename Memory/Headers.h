#pragma once
#include "maya/MString.h"

constexpr size_t MB = 1048576;

struct CharString
{
	static const uint32_t LENGTH = 128;

	CharString() = default;
	CharString(const char* str)
	{
		copy(str);
	}
	CharString(const std::string& str)
	{
		copy(str.c_str());
	}
	CharString(const MString& str)
	{
		copy(str.asChar());
	}

	CharString& operator=(const char* str)
	{
		copy(str);
		return *this;
	}
	CharString& operator=(const std::string& str)
	{
		copy(str.c_str());
		return *this;
	}
	CharString& operator=(const MString& str)
	{
		copy(str.asChar());
		return *this;
	}
	
	bool operator==(const char* str)
	{
		return strcmp(cStr, str) == 0;
	}
	bool operator==(const std::string& str)
	{
		return strcmp(cStr, str.c_str()) == 0;
	}
	bool operator==(const MString& str)
	{
		return strcmp(cStr, str.asChar()) == 0;
	}

	void copy(const char* str)
	{
		size_t length = strlen(str);
		if (length > LENGTH)
			length = LENGTH;

		memcpy(cStr, str, length);
	}

	char cStr[LENGTH]{};
};

enum Headers 
{
	MESSAGE,
	NEW_MESH,
	MESH_DATA
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

	// Will always be used right?
	CharString nodeName;
};

struct MessageHeader
{
	char message[1024]{};
	float position[3];
};

struct MeshDataHeader
{
	int numVertex;
	// int numIndex;
};