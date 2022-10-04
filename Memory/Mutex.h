#pragma once
#include <Windows.h>
#include <iostream>

class Mutex
{
private:
	HANDLE mutexHandle;

public:
	Mutex(LPCWSTR mutexName);
	~Mutex();

	void Lock();
	void Unlock();
};
