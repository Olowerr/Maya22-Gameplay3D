#pragma once
#include <string>
#include "Memory.h"
#include "Headers.h"
#include "Mutex.h"

enum ProcessType {Producer, Consumer};

class Comlib
{
private:
	Mutex* mutex;
	Memory* sharedMemory;
	char* messageData;

	size_t* head;
	size_t* tail;
	size_t* freeMemory;

	ControlHeader* ctrler;
	ProcessType type;

public:
	Comlib(LPCWSTR bufferName, size_t bufferSize, ProcessType type);
	~Comlib();

	Memory* GetSharedMemory() { return sharedMemory; }
	//bool Send(char* message, MessageHeader* secHeader);
	bool Send(char* message, SectionHeader* secHeader);
	bool Recieve(char*& message, SectionHeader*& secHeader);
};