#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>

#include "logging.h"
#include "process.h"

#if true // Cross-platform
std::string STR_LOWER(const std::string& str) {
  std::string result = str;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) -> unsigned char {
    return static_cast<unsigned char>(std::tolower(c));
	});

	return result;
}
#endif // Cross-platform

#ifdef _WIN32
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

#elif __linux__

#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

std::vector<Process> GetProcessList() {
    DIR *dir = opendir("/proc");

    if (!dir) {
        GC_ERROR("Failed to open /proc\n");
        return {};
    }

    std::unordered_map<std::string, pid_t> firstProcesses;
    std::vector<Process> processes;

    struct dirent *entry;

    while ((entry = readdir(dir))) {
        if (entry->d_type != DT_DIR) {
            continue;
        }

        if (entry->d_name[0] < '0' || entry->d_name[0] > '9') {
            continue;
        }

        char path[270];
        snprintf(path, sizeof(path), "/proc/%s/cmdline", entry->d_name);

        int fd = open(path, O_RDONLY);

        if (fd == -1) {
            continue;
        }

        char buffer[256];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

        if (bytesRead == -1) {
            close(fd);
            continue;
        }

        buffer[bytesRead] = '\0';

        close(fd);

        // Get executable name rather than path
        char *lastSlash = strrchr(buffer, '/');
        if (lastSlash) {
            memmove(buffer, lastSlash + 1, strlen(lastSlash));
        }

        if (strlen(buffer) == 0)
            continue;

        if (firstProcesses.find(buffer) == firstProcesses.end()) {
            firstProcesses[buffer] = atoi(entry->d_name);
            processes.push_back(Process(buffer, atoi(entry->d_name), nullptr));
        }
    }

    closedir(dir);

    return processes;
}
#endif

#endif // UTILS_H
