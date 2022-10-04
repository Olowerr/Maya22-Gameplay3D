#pragma once

// Header for sending information about next message

constexpr size_t MB = 1048576;

enum Headers 
{
	MESSAGE
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