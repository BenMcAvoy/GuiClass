#ifndef LOGGING_H
#define LOGGING_H

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>

#define SETCOLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

#define GC_INFO(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(10); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#define GC_WARN(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(14); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#ifndef DEBUG
    #define GC_ERROR(...) { \
        SYSTEMTIME st; \
        GetLocalTime(&st); \
        char message[256]; \
        sprintf_s(message, "[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); \
        strcat_s(message, __VA_ARGS__); \
        MessageBox(NULL, message, "Error", MB_OK); \
    }
#else
    #define GC_ERROR(...) { \
        SYSTEMTIME st; \
        GetLocalTime(&st); \
        SETCOLOR(12); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
        printf(__VA_ARGS__); \
    }
#endif

#elif __linux__

#include <stdio.h>
#include <time.h>

#define SETCOLOR(color) printf("\033[%dm", color)

#define GC_INFO(...) { \
    time_t rawtime; \
    struct tm *timeinfo; \
    time(&rawtime); \
    timeinfo = localtime(&rawtime); \
    SETCOLOR(32); printf("[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); SETCOLOR(0); \
    printf(__VA_ARGS__); \
}

#define GC_WARN(...) { \
    time_t rawtime; \
    struct tm *timeinfo; \
    time(&rawtime); \
    timeinfo = localtime(&rawtime); \
    SETCOLOR(33); printf("[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); SETCOLOR(0); \
    printf(__VA_ARGS__); \
}

#define GC_ERROR(...) { \
    time_t rawtime; \
    struct tm *timeinfo; \
    time(&rawtime); \
    timeinfo = localtime(&rawtime); \
    SETCOLOR(31); printf("[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); SETCOLOR(0); \
    printf(__VA_ARGS__); \
}
#endif // _WIN32

#endif // LOGGING_H
