#include "Memory.h"
#include <iostream>

Memory::Memory(LPCWSTR bufferName, size_t bufferSize)
	:bufferSize(bufferSize * MB), bufferName(bufferName)
	, controlbufferSize(sizeof(ControlHeader))
	, ctrlbufferName(L"CtrlMap")
{   
	InitializeFilemap(bufferName);
	InitializeFileview();
}

Memory::~Memory()
{
	UnmapViewOfFile(memoryData);
	CloseHandle(memoryFilemap);

	UnmapViewOfFile(controlData);
	CloseHandle(controlFilemap);
}

void Memory::InitializeFilemap(LPCWSTR buffername)
{
	memoryFilemap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, bufferSize, buffername);
	if (!memoryFilemap)
		printf("Failed to create file mapping object\n");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		printf("File mapping object already exists - it's shared\n");


	controlFilemap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, controlbufferSize, ctrlbufferName);
	if (!controlFilemap)
		printf("Failed to create file mapping object\n");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		printf("File mapping object already exists - it's shared\n");
}

void Memory::InitializeFileview()
{
	memoryData = (char*)MapViewOfFile(memoryFilemap, FILE_MAP_ALL_ACCESS, 0, 0, bufferSize);
	if (!memoryData)
		printf("View of the mapping object for memoryData failed");

	controlData = (size_t*)MapViewOfFile(controlFilemap, FILE_MAP_ALL_ACCESS, 0, 0, controlbufferSize);
	if (!controlData)
		printf("View of the mapping object for memoryData failed");
}