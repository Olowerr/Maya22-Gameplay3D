#pragma once
#include <string>

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

	bool operator==(const char* str)
	{
		return strcmp(cStr, str) == 0;
	}
	bool operator==(const std::string& str)
	{
		return strcmp(cStr, str.c_str()) == 0;
	}

	operator char*() { return cStr; }
	operator const char*() { return cStr; } const

	void copy(const char* str)
	{
		size_t length = strlen(str);
		if (length > LENGTH)
			length = LENGTH;

		memcpy(cStr, str, length);
	}

	char cStr[LENGTH]{};
};