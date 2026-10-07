// cl: /O2 /GR- /EHsc- -Ireference/shims/nbench
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
extern "C" __declspec(dllimport) void * __stdcall GetCurrentProcess(void);
extern "C" __declspec(dllimport) void * __stdcall GetCurrentThread(void);
extern "C" __declspec(dllimport) unsigned long __stdcall GetPriorityClass(void *);
extern "C" __declspec(dllimport) int __stdcall SetPriorityClass(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall GetThreadPriority(void *);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);
#define HIGH_PRIORITY_CLASS 0x00000080
#define THREAD_PRIORITY_HIGHEST 2

#include "nbench0.c"
