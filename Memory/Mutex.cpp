#include "Mutex.h"

Mutex::Mutex(LPCWSTR mutexName)
{
	mutexHandle = CreateMutex(nullptr, false, mutexName);
	if (!mutexHandle)
		printf("Faild to create mutex object\n");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		printf("Mutex already exists - It's shared\n");
}

Mutex::~Mutex()
{
	CloseHandle(mutexHandle);
}

void Mutex::Lock()
{
	WaitForSingleObject(mutexHandle, INFINITE);
}

void Mutex::Unlock()
{
	ReleaseMutex(mutexHandle);
}
