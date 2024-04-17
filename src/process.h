#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

// TODO: Find a way to standardise this
// NOTE: `handle` is a `HANDLE` on Windows and a `void*` on Linux
// NOTE: `pid` is a `DWORD` on Windows and a `pid_t` on Linux
class Process {
public:
	std::string name;

#ifdef _WIN32
	DWORD pid;
	HANDLE handle;

    Process(std::string name, DWORD pid, HANDLE handle) : name(name), pid(pid), handle(handle) {}
#elif __linux__
	pid_t pid;
	void* handle;

    Process(std::string name, pid_t pid, void* handle) : name(name), pid(pid), handle(handle) {}
#endif
};
