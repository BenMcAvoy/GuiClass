#ifndef LOGGING_H
#define LOGGING_H

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

#endif // LOGGING_H
