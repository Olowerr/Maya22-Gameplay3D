#pragma once

#include <Windows.h>
#include "Headers.h"

struct ControlHeader
{
	size_t head = 0;
	size_t tail = 0;
	size_t freeMemory = 0;
};

class Memory
{
private:
	HANDLE memoryFilemap;
	HANDLE controlFilemap;

	char* memoryData;
	size_t* controlData;

	size_t bufferSize;
	size_t controlbufferSize;

	LPCWSTR bufferName;
	LPCWSTR ctrlbufferName;

public:
	Memory(LPCWSTR bufferName, size_t bufferSize);
	~Memory();
	void InitializeFilemap(LPCWSTR buffername);
	void InitializeFileview();

	char* GetMemoryBuffer() { return memoryData; }
	size_t* GetControlBuffer() { return controlData; }

	size_t GetControlBufferSize() { return this->controlbufferSize; }
	size_t GetBufferSize() { return this->bufferSize; }
};
