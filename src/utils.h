#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>

#include "logging.h"
#include "process.h"

std::string STR_LOWER(const std::string& str) {
  std::string result = str;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) -> unsigned char {
    return static_cast<unsigned char>(std::tolower(c));
	});

	return result;
}

#define WIN32_LEAN_AND_MEAN

#include <tlhelp32.h>
#include <windows.h>
#include <codecvt>
#include <locale>

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

std::vector<Process> GetProcessList() {
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snap == INVALID_HANDLE_VALUE) {
        GC_ERROR("Failed to get PROCESSENTRY32 snapshot\n");
        return {};
    }

    if (!Process32First(snap, &pe32)) {
        GC_ERROR("Failed to get first process\n");
        CloseHandle(snap);
        return {};
    }

    std::unordered_map<std::string, DWORD> firstProcesses;
    std::vector<Process> processes;

    while (Process32Next(snap, &pe32)) {
        if (firstProcesses.find(pe32.szExeFile) == firstProcesses.end()) {
            firstProcesses[pe32.szExeFile] = pe32.th32ProcessID;
            processes.push_back(Process(pe32.szExeFile, pe32.th32ProcessID, nullptr));
        }
    }

    return processes;
}

#endif // UTILS_H
