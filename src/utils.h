#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <locale>
#include <codecvt>

#include <vector>
#include <string>

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#define SETCOLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

#define INFO(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(10); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#define WARN(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(14); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#define ERROR(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(12); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

std::string tStringToString(const tstring& tstr) {
	std::string converted_str(tstr.begin(), tstr.end());
	return converted_str;
}

// Get process list as vector of strings
std::vector<std::string> GetProcessList() {
	PROCESSENTRY32 pe32;

	// Create a snap to get the process list
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	pe32.dwSize = sizeof(PROCESSENTRY32);

	Process32First(snap, &pe32);

	std::vector<tstring> processes;

	while (Process32Next(snap, &pe32)) {
		processes.push_back(pe32.szExeFile);
	}

	CloseHandle(snap);

	std::vector<std::string> convertedProcesses;
	for (const auto& process : processes)
		convertedProcesses.push_back(tStringToString(process));

	return convertedProcesses;
}

// Get handle from process name
HANDLE GetProcessHandle(const std::string& processName) {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Create a snap to get the process list
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snap == INVALID_HANDLE_VALUE) {
		ERROR("Failed to create snapshot\n");
		return NULL;
	}

	Process32First(snap, &pe32);
	if (!processName.compare(tStringToString(pe32.szExeFile))) {
		CloseHandle(snap);
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
	}

	while (Process32Next(snap, &pe32)) {
		if (!processName.compare(tStringToString(pe32.szExeFile))) {
			CloseHandle(snap);
			return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		}
	}

	CloseHandle(snap);
	return NULL;
}

char* toLower(char* str) {
	char* newStr = new char[strlen(str) + 1];
	for (int i = 0; str[i]; i++) 
		newStr[i] = tolower(static_cast<unsigned char>(str[i]));

	newStr[strlen(str)] = '\0';

	return newStr;
}
