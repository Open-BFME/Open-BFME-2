#pragma once
// Minimal declarations for the Win32 lstr* string helpers rendobj.cpp calls.
// Retail links the unsuffixed ANSI exports from kernel32; we only need declarations to
// compile to object. Signatures match <winbase.h> so codegen (stdcall IAT call)
// is identical.
#ifndef WINBASE_SHIM_H
#define WINBASE_SHIM_H
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
typedef long LONG;
typedef unsigned long DWORD;
#ifndef _LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; };
    __int64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
#define _LARGE_INTEGER_DEFINED
#endif
extern "C" __declspec(dllimport) char * __stdcall lstrcpy(char *, const char *);
extern "C" __declspec(dllimport) int    __stdcall lstrlen(const char *);
extern "C" __declspec(dllimport) int    __stdcall lstrcmpi(const char *, const char *);
extern "C" __declspec(dllimport) char * __stdcall lstrcpyn(char *, const char *, int);
#define lstrcpyA lstrcpy
#define lstrlenA lstrlen
#define lstrcmpiA lstrcmpi
#define lstrcpynA lstrcpyn
#ifndef __max
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#endif
