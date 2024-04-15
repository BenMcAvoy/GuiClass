#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

#include <unordered_map>
#include <tlhelp32.h>
#include <windows.h>
#include <codecvt>
#include <locale>

#include <vector>
#include <string>

#include "logging.h"
#include "process.h"

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

std::vector<Process> GetProcessList() {
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snap == INVALID_HANDLE_VALUE) {
        ERROR("Failed to get PROCESSENTRY32 snapshot\n");
        return {};
    }

    if (!Process32First(snap, &pe32)) {
        ERROR("Failed to get first process\n");
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

DWORD GetParentPIDByName(const std::string &processName) {
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snap == INVALID_HANDLE_VALUE) {
        ERROR("Failed to get PROCESSENTRY32 snapshot\n");
        return 0;
    }

    if (!Process32First(snap, &pe32)) {
        ERROR("Failed to get first process\n");
        CloseHandle(snap);
        return 0;
    }

    DWORD parentPid = 0;

    while (Process32Next(snap, &pe32)) {
        if (std::string(pe32.szExeFile) == processName) {
            if (pe32.th32ParentProcessID == 0) {
                parentPid = pe32.th32ProcessID;
                break;
            }

            parentPid = pe32.th32ParentProcessID;
            break;
        }
    }

    CloseHandle(snap);

    return parentPid;
}

#endif
