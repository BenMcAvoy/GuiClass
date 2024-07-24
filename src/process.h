#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>

#include <string>

// NOTE: `handle` is a `HANDLE` on Windows and a `void*` on Linux
// NOTE: `pid` is a `DWORD` on Windows and a `pid_t` on Linux
class Process {
public:
	std::string name;

	DWORD pid;
	HANDLE handle;

  Process(std::string name, DWORD pid, HANDLE handle) : name(name), pid(pid), handle(handle) {}
};

#endif // PROCESS_H
