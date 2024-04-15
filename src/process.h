#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>

class Process {
public:
	std::string name;
	DWORD pid;

	HANDLE handle;

    Process(std::string name, DWORD pid, HANDLE handle) : name(name), pid(pid), handle(handle) {}
};

#endif