// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// kernel32.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as D3DX9ImportThunks.cpp does for d3dx9. VS2003
// __identifier names the actual decorated __imp__ symbol; no alias, address
// pin, inline assembly, emitted bytes or replacement datum is used.
// Signatures: the VS2003 Platform SDK headers (WinBase.h, WinNls.h, WinCon.h,
// TlHelp32.h), included with _KERNEL32_ defined (WinBase.h's own switch) so
// WINBASEAPI is empty and these definitions are not dllimport (no C4273
// /EXPORT directives).
// Each retail six-byte thunk's IAT slot names the export (row notes).
#define _KERNEL32_
#include <windows.h>
#include <tlhelp32.h>
extern "C" {
// _InterlockedExchange@8
typedef LONG (WINAPI *PFN_InterlockedExchange)(LONG volatile *, LONG);
extern PFN_InterlockedExchange __identifier("_imp__InterlockedExchange@8");
LONG WINAPI InterlockedExchange(LONG volatile * Target, LONG Value) {
 return __identifier("_imp__InterlockedExchange@8")(Target, Value);
}

// _GetACP@0
typedef UINT (WINAPI *PFN_GetACP)(VOID);
extern PFN_GetACP __identifier("_imp__GetACP@0");
UINT WINAPI GetACP(VOID) {
 return __identifier("_imp__GetACP@0")();
}

// _GetLocaleInfoA@16
typedef int (WINAPI *PFN_GetLocaleInfoA)(LCID, LCTYPE, LPSTR, int);
extern PFN_GetLocaleInfoA __identifier("_imp__GetLocaleInfoA@16");
int WINAPI GetLocaleInfoA(LCID Locale, LCTYPE LCType, LPSTR lpLCData, int cchData) {
 return __identifier("_imp__GetLocaleInfoA@16")(Locale, LCType, lpLCData, cchData);
}

// _GetThreadLocale@0
typedef LCID (WINAPI *PFN_GetThreadLocale)(VOID);
extern PFN_GetThreadLocale __identifier("_imp__GetThreadLocale@0");
LCID WINAPI GetThreadLocale(VOID) {
 return __identifier("_imp__GetThreadLocale@0")();
}

// _GetVersionExA@4
typedef BOOL (WINAPI *PFN_GetVersionExA)(LPOSVERSIONINFOA);
extern PFN_GetVersionExA __identifier("_imp__GetVersionExA@4");
BOOL WINAPI GetVersionExA(LPOSVERSIONINFOA lpVersionInformation) {
 return __identifier("_imp__GetVersionExA@4")(lpVersionInformation);
}

// _GetLastError@0
typedef DWORD (WINAPI *PFN_GetLastError)(VOID);
extern PFN_GetLastError __identifier("_imp__GetLastError@0");
DWORD WINAPI GetLastError(VOID) {
 return __identifier("_imp__GetLastError@0")();
}

// _LeaveCriticalSection@4
typedef VOID (WINAPI *PFN_LeaveCriticalSection)(LPCRITICAL_SECTION);
extern PFN_LeaveCriticalSection __identifier("_imp__LeaveCriticalSection@4");
VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
 __identifier("_imp__LeaveCriticalSection@4")(lpCriticalSection);
}

// _EnterCriticalSection@4
typedef VOID (WINAPI *PFN_EnterCriticalSection)(LPCRITICAL_SECTION);
extern PFN_EnterCriticalSection __identifier("_imp__EnterCriticalSection@4");
VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
 __identifier("_imp__EnterCriticalSection@4")(lpCriticalSection);
}

// _FreeLibrary@4
typedef BOOL (WINAPI *PFN_FreeLibrary)(HMODULE);
extern PFN_FreeLibrary __identifier("_imp__FreeLibrary@4");
BOOL WINAPI FreeLibrary(HMODULE hLibModule) {
 return __identifier("_imp__FreeLibrary@4")(hLibModule);
}

// _GetProcAddress@8
typedef FARPROC (WINAPI *PFN_GetProcAddress)(HMODULE, LPCSTR);
extern PFN_GetProcAddress __identifier("_imp__GetProcAddress@8");
FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
 return __identifier("_imp__GetProcAddress@8")(hModule, lpProcName);
}

// _LoadLibraryA@4
typedef HMODULE (WINAPI *PFN_LoadLibraryA)(LPCSTR);
extern PFN_LoadLibraryA __identifier("_imp__LoadLibraryA@4");
HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName) {
 return __identifier("_imp__LoadLibraryA@4")(lpLibFileName);
}

// _MultiByteToWideChar@24
typedef int (WINAPI *PFN_MultiByteToWideChar)(UINT, DWORD, LPCSTR, int, LPWSTR, int);
extern PFN_MultiByteToWideChar __identifier("_imp__MultiByteToWideChar@24");
int WINAPI MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar) {
 return __identifier("_imp__MultiByteToWideChar@24")(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}

// _lstrlen@4
// WinBase.h maps lstrlen to lstrlenA; retail imports the legacy undecorated
// export, declared here with the header's ANSI signature.
#undef lstrlen
int WINAPI lstrlen(LPCSTR lpString);
typedef int (WINAPI *PFN_lstrlen)(LPCSTR);
extern PFN_lstrlen __identifier("_imp__lstrlen@4");
int WINAPI lstrlen(LPCSTR lpString) {
 return __identifier("_imp__lstrlen@4")(lpString);
}

// _CloseHandle@4
typedef BOOL (WINAPI *PFN_CloseHandle)(HANDLE);
extern PFN_CloseHandle __identifier("_imp__CloseHandle@4");
BOOL WINAPI CloseHandle(HANDLE hObject) {
 return __identifier("_imp__CloseHandle@4")(hObject);
}

// _CreateMutexW@12
typedef HANDLE (WINAPI *PFN_CreateMutexW)(LPSECURITY_ATTRIBUTES, BOOL, LPCWSTR);
extern PFN_CreateMutexW __identifier("_imp__CreateMutexW@12");
HANDLE WINAPI CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName) {
 return __identifier("_imp__CreateMutexW@12")(lpMutexAttributes, bInitialOwner, lpName);
}

// _SetCurrentDirectoryW@4
typedef BOOL (WINAPI *PFN_SetCurrentDirectoryW)(LPCWSTR);
extern PFN_SetCurrentDirectoryW __identifier("_imp__SetCurrentDirectoryW@4");
BOOL WINAPI SetCurrentDirectoryW(LPCWSTR lpPathName) {
 return __identifier("_imp__SetCurrentDirectoryW@4")(lpPathName);
}

// _GetModuleFileNameW@12
typedef DWORD (WINAPI *PFN_GetModuleFileNameW)(HMODULE, LPWSTR, DWORD);
extern PFN_GetModuleFileNameW __identifier("_imp__GetModuleFileNameW@12");
DWORD WINAPI GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize) {
 return __identifier("_imp__GetModuleFileNameW@12")(hModule, lpFilename, nSize);
}

// _FindClose@4
typedef BOOL (WINAPI *PFN_FindClose)(HANDLE);
extern PFN_FindClose __identifier("_imp__FindClose@4");
BOOL WINAPI FindClose(HANDLE hFindFile) {
 return __identifier("_imp__FindClose@4")(hFindFile);
}

// _FindFirstFileW@8
typedef HANDLE (WINAPI *PFN_FindFirstFileW)(LPCWSTR, LPWIN32_FIND_DATAW);
extern PFN_FindFirstFileW __identifier("_imp__FindFirstFileW@8");
HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) {
 return __identifier("_imp__FindFirstFileW@8")(lpFileName, lpFindFileData);
}

// _GetCommandLineW@0
typedef LPWSTR (WINAPI *PFN_GetCommandLineW)(VOID);
extern PFN_GetCommandLineW __identifier("_imp__GetCommandLineW@0");
LPWSTR WINAPI GetCommandLineW(VOID) {
 return __identifier("_imp__GetCommandLineW@0")();
}

// _WideCharToMultiByte@32
typedef int (WINAPI *PFN_WideCharToMultiByte)(UINT, DWORD, LPCWSTR, int, LPSTR, int, LPCSTR, LPBOOL);
extern PFN_WideCharToMultiByte __identifier("_imp__WideCharToMultiByte@32");
int WINAPI WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar) {
 return __identifier("_imp__WideCharToMultiByte@32")(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
}

// _RaiseException@16
typedef VOID (WINAPI *PFN_RaiseException)(DWORD, DWORD, DWORD, CONST ULONG_PTR *);
extern PFN_RaiseException __identifier("_imp__RaiseException@16");
VOID WINAPI RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, CONST ULONG_PTR * lpArguments) {
 __identifier("_imp__RaiseException@16")(dwExceptionCode, dwExceptionFlags, nNumberOfArguments, lpArguments);
}

// _InitializeCriticalSection@4
typedef VOID (WINAPI *PFN_InitializeCriticalSection)(LPCRITICAL_SECTION);
extern PFN_InitializeCriticalSection __identifier("_imp__InitializeCriticalSection@4");
VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
 __identifier("_imp__InitializeCriticalSection@4")(lpCriticalSection);
}

// _DeleteCriticalSection@4
typedef VOID (WINAPI *PFN_DeleteCriticalSection)(LPCRITICAL_SECTION);
extern PFN_DeleteCriticalSection __identifier("_imp__DeleteCriticalSection@4");
VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
 __identifier("_imp__DeleteCriticalSection@4")(lpCriticalSection);
}

// _GetVersion@0
typedef DWORD (WINAPI *PFN_GetVersion)(VOID);
extern PFN_GetVersion __identifier("_imp__GetVersion@0");
DWORD WINAPI GetVersion(VOID) {
 return __identifier("_imp__GetVersion@0")();
}

// _lstrcmpi@8
// WinBase.h maps lstrcmpi to lstrcmpiA; retail imports the legacy undecorated
// export, declared here with the header's ANSI signature.
#undef lstrcmpi
int WINAPI lstrcmpi(LPCSTR lpString1, LPCSTR lpString2);
typedef int (WINAPI *PFN_lstrcmpi)(LPCSTR, LPCSTR);
extern PFN_lstrcmpi __identifier("_imp__lstrcmpi@8");
int WINAPI lstrcmpi(LPCSTR lpString1, LPCSTR lpString2) {
 return __identifier("_imp__lstrcmpi@8")(lpString1, lpString2);
}

// _lstrlenW@4
typedef int (WINAPI *PFN_lstrlenW)(LPCWSTR);
extern PFN_lstrlenW __identifier("_imp__lstrlenW@4");
int WINAPI lstrlenW(LPCWSTR lpString) {
 return __identifier("_imp__lstrlenW@4")(lpString);
}

// _lstrcmpiW@8
typedef int (WINAPI *PFN_lstrcmpiW)(LPCWSTR, LPCWSTR);
extern PFN_lstrcmpiW __identifier("_imp__lstrcmpiW@8");
int WINAPI lstrcmpiW(LPCWSTR lpString1, LPCWSTR lpString2) {
 return __identifier("_imp__lstrcmpiW@8")(lpString1, lpString2);
}

// _CompareStringA@24
typedef int (WINAPI *PFN_CompareStringA)(LCID, DWORD, LPCSTR, int, LPCSTR, int);
extern PFN_CompareStringA __identifier("_imp__CompareStringA@24");
int WINAPI CompareStringA(LCID Locale, DWORD dwCmpFlags, LPCSTR lpString1, int cchCount1, LPCSTR lpString2, int cchCount2) {
 return __identifier("_imp__CompareStringA@24")(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2);
}

// _CompareStringW@24
typedef int (WINAPI *PFN_CompareStringW)(LCID, DWORD, LPCWSTR, int, LPCWSTR, int);
extern PFN_CompareStringW __identifier("_imp__CompareStringW@24");
int WINAPI CompareStringW(LCID Locale, DWORD dwCmpFlags, LPCWSTR lpString1, int cchCount1, LPCWSTR lpString2, int cchCount2) {
 return __identifier("_imp__CompareStringW@24")(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2);
}

// _GetEnvironmentVariableA@12
typedef DWORD (WINAPI *PFN_GetEnvironmentVariableA)(LPCSTR, LPSTR, DWORD);
extern PFN_GetEnvironmentVariableA __identifier("_imp__GetEnvironmentVariableA@12");
DWORD WINAPI GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize) {
 return __identifier("_imp__GetEnvironmentVariableA@12")(lpName, lpBuffer, nSize);
}

// _GetEnvironmentVariableW@12
typedef DWORD (WINAPI *PFN_GetEnvironmentVariableW)(LPCWSTR, LPWSTR, DWORD);
extern PFN_GetEnvironmentVariableW __identifier("_imp__GetEnvironmentVariableW@12");
DWORD WINAPI GetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize) {
 return __identifier("_imp__GetEnvironmentVariableW@12")(lpName, lpBuffer, nSize);
}

// _GetStringTypeExA@20
typedef BOOL (WINAPI *PFN_GetStringTypeExA)(LCID, DWORD, LPCSTR, int, LPWORD);
extern PFN_GetStringTypeExA __identifier("_imp__GetStringTypeExA@20");
BOOL WINAPI GetStringTypeExA(LCID Locale, DWORD dwInfoType, LPCSTR lpSrcStr, int cchSrc, LPWORD lpCharType) {
 return __identifier("_imp__GetStringTypeExA@20")(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType);
}

// _GetStringTypeExW@20
typedef BOOL (WINAPI *PFN_GetStringTypeExW)(LCID, DWORD, LPCWSTR, int, LPWORD);
extern PFN_GetStringTypeExW __identifier("_imp__GetStringTypeExW@20");
BOOL WINAPI GetStringTypeExW(LCID Locale, DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc, LPWORD lpCharType) {
 return __identifier("_imp__GetStringTypeExW@20")(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType);
}

// _Sleep@4
typedef VOID (WINAPI *PFN_Sleep)(DWORD);
extern PFN_Sleep __identifier("_imp__Sleep@4");
VOID WINAPI Sleep(DWORD dwMilliseconds) {
 __identifier("_imp__Sleep@4")(dwMilliseconds);
}

// _GetFileType@4
typedef DWORD (WINAPI *PFN_GetFileType)(HANDLE);
extern PFN_GetFileType __identifier("_imp__GetFileType@4");
DWORD WINAPI GetFileType(HANDLE hFile) {
 return __identifier("_imp__GetFileType@4")(hFile);
}

// _GetFileSize@8
typedef DWORD (WINAPI *PFN_GetFileSize)(HANDLE, LPDWORD);
extern PFN_GetFileSize __identifier("_imp__GetFileSize@8");
DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh) {
 return __identifier("_imp__GetFileSize@8")(hFile, lpFileSizeHigh);
}

// _GetSystemInfo@4
typedef VOID (WINAPI *PFN_GetSystemInfo)(LPSYSTEM_INFO);
extern PFN_GetSystemInfo __identifier("_imp__GetSystemInfo@4");
VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
 __identifier("_imp__GetSystemInfo@4")(lpSystemInfo);
}

// _SetFilePointer@16
typedef DWORD (WINAPI *PFN_SetFilePointer)(HANDLE, LONG, PLONG, DWORD);
extern PFN_SetFilePointer __identifier("_imp__SetFilePointer@16");
DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) {
 return __identifier("_imp__SetFilePointer@16")(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

// _SetEndOfFile@4
typedef BOOL (WINAPI *PFN_SetEndOfFile)(HANDLE);
extern PFN_SetEndOfFile __identifier("_imp__SetEndOfFile@4");
BOOL WINAPI SetEndOfFile(HANDLE hFile) {
 return __identifier("_imp__SetEndOfFile@4")(hFile);
}

// _CreateFileA@28
typedef HANDLE (WINAPI *PFN_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
extern PFN_CreateFileA __identifier("_imp__CreateFileA@28");
HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
 return __identifier("_imp__CreateFileA@28")(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

// _ReadFile@20
typedef BOOL (WINAPI *PFN_ReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
extern PFN_ReadFile __identifier("_imp__ReadFile@20");
BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
 return __identifier("_imp__ReadFile@20")(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

// _UnmapViewOfFile@4
typedef BOOL (WINAPI *PFN_UnmapViewOfFile)(LPCVOID);
extern PFN_UnmapViewOfFile __identifier("_imp__UnmapViewOfFile@4");
BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress) {
 return __identifier("_imp__UnmapViewOfFile@4")(lpBaseAddress);
}

// _WriteFile@20
typedef BOOL (WINAPI *PFN_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
extern PFN_WriteFile __identifier("_imp__WriteFile@20");
BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
 return __identifier("_imp__WriteFile@20")(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

// _MapViewOfFile@20
typedef LPVOID (WINAPI *PFN_MapViewOfFile)(HANDLE, DWORD, DWORD, DWORD, SIZE_T);
extern PFN_MapViewOfFile __identifier("_imp__MapViewOfFile@20");
LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap) {
 return __identifier("_imp__MapViewOfFile@20")(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

// _CreateFileMappingA@24
typedef HANDLE (WINAPI *PFN_CreateFileMappingA)(HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCSTR);
extern PFN_CreateFileMappingA __identifier("_imp__CreateFileMappingA@24");
HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName) {
 return __identifier("_imp__CreateFileMappingA@24")(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

// _GetStringTypeW@16
typedef BOOL (WINAPI *PFN_GetStringTypeW)(DWORD, LPCWSTR, int, LPWORD);
extern PFN_GetStringTypeW __identifier("_imp__GetStringTypeW@16");
BOOL WINAPI GetStringTypeW(DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc, LPWORD lpCharType) {
 return __identifier("_imp__GetStringTypeW@16")(dwInfoType, lpSrcStr, cchSrc, lpCharType);
}

// _LCMapStringW@24
typedef int (WINAPI *PFN_LCMapStringW)(LCID, DWORD, LPCWSTR, int, LPWSTR, int);
extern PFN_LCMapStringW __identifier("_imp__LCMapStringW@24");
int WINAPI LCMapStringW(LCID Locale, DWORD dwMapFlags, LPCWSTR lpSrcStr, int cchSrc, LPWSTR lpDestStr, int cchDest) {
 return __identifier("_imp__LCMapStringW@24")(Locale, dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest);
}

// _GetCPInfo@8
typedef BOOL (WINAPI *PFN_GetCPInfo)(UINT, LPCPINFO);
extern PFN_GetCPInfo __identifier("_imp__GetCPInfo@8");
BOOL WINAPI GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) {
 return __identifier("_imp__GetCPInfo@8")(CodePage, lpCPInfo);
}

// _EnumSystemLocalesA@8
typedef BOOL (WINAPI *PFN_EnumSystemLocalesA)(LOCALE_ENUMPROCA, DWORD);
extern PFN_EnumSystemLocalesA __identifier("_imp__EnumSystemLocalesA@8");
BOOL WINAPI EnumSystemLocalesA(LOCALE_ENUMPROCA lpLocaleEnumProc, DWORD dwFlags) {
 return __identifier("_imp__EnumSystemLocalesA@8")(lpLocaleEnumProc, dwFlags);
}

// _LCMapStringA@24
typedef int (WINAPI *PFN_LCMapStringA)(LCID, DWORD, LPCSTR, int, LPSTR, int);
extern PFN_LCMapStringA __identifier("_imp__LCMapStringA@24");
int WINAPI LCMapStringA(LCID Locale, DWORD dwMapFlags, LPCSTR lpSrcStr, int cchSrc, LPSTR lpDestStr, int cchDest) {
 return __identifier("_imp__LCMapStringA@24")(Locale, dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest);
}

// _GetStringTypeA@20
typedef BOOL (WINAPI *PFN_GetStringTypeA)(LCID, DWORD, LPCSTR, int, LPWORD);
extern PFN_GetStringTypeA __identifier("_imp__GetStringTypeA@20");
BOOL WINAPI GetStringTypeA(LCID Locale, DWORD dwInfoType, LPCSTR lpSrcStr, int cchSrc, LPWORD lpCharType) {
 return __identifier("_imp__GetStringTypeA@20")(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType);
}

// _GetLocalTime@4
typedef VOID (WINAPI *PFN_GetLocalTime)(LPSYSTEMTIME);
extern PFN_GetLocalTime __identifier("_imp__GetLocalTime@4");
VOID WINAPI GetLocalTime(LPSYSTEMTIME lpSystemTime) {
 __identifier("_imp__GetLocalTime@4")(lpSystemTime);
}

// _GetCurrentDirectoryA@8
typedef DWORD (WINAPI *PFN_GetCurrentDirectoryA)(DWORD, LPSTR);
extern PFN_GetCurrentDirectoryA __identifier("_imp__GetCurrentDirectoryA@8");
DWORD WINAPI GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) {
 return __identifier("_imp__GetCurrentDirectoryA@8")(nBufferLength, lpBuffer);
}

// _WriteProcessMemory@20
typedef BOOL (WINAPI *PFN_WriteProcessMemory)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T *);
extern PFN_WriteProcessMemory __identifier("_imp__WriteProcessMemory@20");
BOOL WINAPI WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesWritten) {
 return __identifier("_imp__WriteProcessMemory@20")(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

// _GetCurrentProcess@0
typedef HANDLE (WINAPI *PFN_GetCurrentProcess)(VOID);
extern PFN_GetCurrentProcess __identifier("_imp__GetCurrentProcess@0");
HANDLE WINAPI GetCurrentProcess(VOID) {
 return __identifier("_imp__GetCurrentProcess@0")();
}

// _VirtualProtect@16
typedef BOOL (WINAPI *PFN_VirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
extern PFN_VirtualProtect __identifier("_imp__VirtualProtect@16");
BOOL WINAPI VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) {
 return __identifier("_imp__VirtualProtect@16")(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

// _IsBadReadPtr@8
typedef BOOL (WINAPI *PFN_IsBadReadPtr)(CONST VOID *, UINT_PTR);
extern PFN_IsBadReadPtr __identifier("_imp__IsBadReadPtr@8");
BOOL WINAPI IsBadReadPtr(CONST VOID * lp, UINT_PTR ucb) {
 return __identifier("_imp__IsBadReadPtr@8")(lp, ucb);
}

// _GetModuleHandleA@4
typedef HMODULE (WINAPI *PFN_GetModuleHandleA)(LPCSTR);
extern PFN_GetModuleHandleA __identifier("_imp__GetModuleHandleA@4");
HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) {
 return __identifier("_imp__GetModuleHandleA@4")(lpModuleName);
}

// _GetCurrentProcessId@0
typedef DWORD (WINAPI *PFN_GetCurrentProcessId)(VOID);
extern PFN_GetCurrentProcessId __identifier("_imp__GetCurrentProcessId@0");
DWORD WINAPI GetCurrentProcessId(VOID) {
 return __identifier("_imp__GetCurrentProcessId@0")();
}

// _TlsAlloc@0
typedef DWORD (WINAPI *PFN_TlsAlloc)(VOID);
extern PFN_TlsAlloc __identifier("_imp__TlsAlloc@0");
DWORD WINAPI TlsAlloc(VOID) {
 return __identifier("_imp__TlsAlloc@0")();
}

// _HeapAlloc@12
typedef LPVOID (WINAPI *PFN_HeapAlloc)(HANDLE, DWORD, SIZE_T);
extern PFN_HeapAlloc __identifier("_imp__HeapAlloc@12");
LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
 return __identifier("_imp__HeapAlloc@12")(hHeap, dwFlags, dwBytes);
}

// _HeapCreate@12
typedef HANDLE (WINAPI *PFN_HeapCreate)(DWORD, SIZE_T, SIZE_T);
extern PFN_HeapCreate __identifier("_imp__HeapCreate@12");
HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
 return __identifier("_imp__HeapCreate@12")(flOptions, dwInitialSize, dwMaximumSize);
}

// _GetCommandLineA@0
typedef LPSTR (WINAPI *PFN_GetCommandLineA)(VOID);
extern PFN_GetCommandLineA __identifier("_imp__GetCommandLineA@0");
LPSTR WINAPI GetCommandLineA(VOID) {
 return __identifier("_imp__GetCommandLineA@0")();
}

// _TlsGetValue@4
typedef LPVOID (WINAPI *PFN_TlsGetValue)(DWORD);
extern PFN_TlsGetValue __identifier("_imp__TlsGetValue@4");
LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex) {
 return __identifier("_imp__TlsGetValue@4")(dwTlsIndex);
}

// _TlsSetValue@8
typedef BOOL (WINAPI *PFN_TlsSetValue)(DWORD, LPVOID);
extern PFN_TlsSetValue __identifier("_imp__TlsSetValue@8");
BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue) {
 return __identifier("_imp__TlsSetValue@8")(dwTlsIndex, lpTlsValue);
}

// _OutputDebugStringA@4
typedef VOID (WINAPI *PFN_OutputDebugStringA)(LPCSTR);
extern PFN_OutputDebugStringA __identifier("_imp__OutputDebugStringA@4");
VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) {
 __identifier("_imp__OutputDebugStringA@4")(lpOutputString);
}

// _VirtualFree@12
typedef BOOL (WINAPI *PFN_VirtualFree)(LPVOID, SIZE_T, DWORD);
extern PFN_VirtualFree __identifier("_imp__VirtualFree@12");
BOOL WINAPI VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
 return __identifier("_imp__VirtualFree@12")(lpAddress, dwSize, dwFreeType);
}

// _VirtualAlloc@16
typedef LPVOID (WINAPI *PFN_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
extern PFN_VirtualAlloc __identifier("_imp__VirtualAlloc@16");
LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
 return __identifier("_imp__VirtualAlloc@16")(lpAddress, dwSize, flAllocationType, flProtect);
}

// _VirtualQuery@12
typedef SIZE_T (WINAPI *PFN_VirtualQuery)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
extern PFN_VirtualQuery __identifier("_imp__VirtualQuery@12");
SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
 return __identifier("_imp__VirtualQuery@12")(lpAddress, lpBuffer, dwLength);
}

// _DeleteFileA@4
typedef BOOL (WINAPI *PFN_DeleteFileA)(LPCSTR);
extern PFN_DeleteFileA __identifier("_imp__DeleteFileA@4");
BOOL WINAPI DeleteFileA(LPCSTR lpFileName) {
 return __identifier("_imp__DeleteFileA@4")(lpFileName);
}

// _GetModuleFileNameA@12
typedef DWORD (WINAPI *PFN_GetModuleFileNameA)(HMODULE, LPSTR, DWORD);
extern PFN_GetModuleFileNameA __identifier("_imp__GetModuleFileNameA@12");
DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
 return __identifier("_imp__GetModuleFileNameA@12")(hModule, lpFilename, nSize);
}

// _SetUnhandledExceptionFilter@4
typedef LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI *PFN_SetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER);
extern PFN_SetUnhandledExceptionFilter __identifier("_imp__SetUnhandledExceptionFilter@4");
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter) {
 return __identifier("_imp__SetUnhandledExceptionFilter@4")(lpTopLevelExceptionFilter);
}

// _CreateMutexA@12
typedef HANDLE (WINAPI *PFN_CreateMutexA)(LPSECURITY_ATTRIBUTES, BOOL, LPCSTR);
extern PFN_CreateMutexA __identifier("_imp__CreateMutexA@12");
HANDLE WINAPI CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
 return __identifier("_imp__CreateMutexA@12")(lpMutexAttributes, bInitialOwner, lpName);
}

// _InterlockedIncrement@4
typedef LONG (WINAPI *PFN_InterlockedIncrement)(LONG volatile *);
extern PFN_InterlockedIncrement __identifier("_imp__InterlockedIncrement@4");
LONG WINAPI InterlockedIncrement(LONG volatile * lpAddend) {
 return __identifier("_imp__InterlockedIncrement@4")(lpAddend);
}

// _ReleaseMutex@4
typedef BOOL (WINAPI *PFN_ReleaseMutex)(HANDLE);
extern PFN_ReleaseMutex __identifier("_imp__ReleaseMutex@4");
BOOL WINAPI ReleaseMutex(HANDLE hMutex) {
 return __identifier("_imp__ReleaseMutex@4")(hMutex);
}

// _InterlockedDecrement@4
typedef LONG (WINAPI *PFN_InterlockedDecrement)(LONG volatile *);
extern PFN_InterlockedDecrement __identifier("_imp__InterlockedDecrement@4");
LONG WINAPI InterlockedDecrement(LONG volatile * lpAddend) {
 return __identifier("_imp__InterlockedDecrement@4")(lpAddend);
}

// _GetCurrentThreadId@0
typedef DWORD (WINAPI *PFN_GetCurrentThreadId)(VOID);
extern PFN_GetCurrentThreadId __identifier("_imp__GetCurrentThreadId@0");
DWORD WINAPI GetCurrentThreadId(VOID) {
 return __identifier("_imp__GetCurrentThreadId@0")();
}

// _GetTimeFormatA@24
typedef int (WINAPI *PFN_GetTimeFormatA)(LCID, DWORD, CONST SYSTEMTIME *, LPCSTR, LPSTR, int);
extern PFN_GetTimeFormatA __identifier("_imp__GetTimeFormatA@24");
int WINAPI GetTimeFormatA(LCID Locale, DWORD dwFlags, CONST SYSTEMTIME * lpTime, LPCSTR lpFormat, LPSTR lpTimeStr, int cchTime) {
 return __identifier("_imp__GetTimeFormatA@24")(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime);
}

// _WaitForSingleObject@8
typedef DWORD (WINAPI *PFN_WaitForSingleObject)(HANDLE, DWORD);
extern PFN_WaitForSingleObject __identifier("_imp__WaitForSingleObject@8");
DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
 return __identifier("_imp__WaitForSingleObject@8")(hHandle, dwMilliseconds);
}

// _IsBadCodePtr@4
typedef BOOL (WINAPI *PFN_IsBadCodePtr)(FARPROC);
extern PFN_IsBadCodePtr __identifier("_imp__IsBadCodePtr@4");
BOOL WINAPI IsBadCodePtr(FARPROC lpfn) {
 return __identifier("_imp__IsBadCodePtr@4")(lpfn);
}

// _ReadProcessMemory@20
typedef BOOL (WINAPI *PFN_ReadProcessMemory)(HANDLE, LPCVOID, LPVOID, SIZE_T, SIZE_T *);
extern PFN_ReadProcessMemory __identifier("_imp__ReadProcessMemory@20");
BOOL WINAPI ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesRead) {
 return __identifier("_imp__ReadProcessMemory@20")(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

// _GetCurrentThread@0
typedef HANDLE (WINAPI *PFN_GetCurrentThread)(VOID);
extern PFN_GetCurrentThread __identifier("_imp__GetCurrentThread@0");
HANDLE WINAPI GetCurrentThread(VOID) {
 return __identifier("_imp__GetCurrentThread@0")();
}

// _GlobalUnlock@4
typedef BOOL (WINAPI *PFN_GlobalUnlock)(HGLOBAL);
extern PFN_GlobalUnlock __identifier("_imp__GlobalUnlock@4");
BOOL WINAPI GlobalUnlock(HGLOBAL hMem) {
 return __identifier("_imp__GlobalUnlock@4")(hMem);
}

// _GlobalLock@4
typedef LPVOID (WINAPI *PFN_GlobalLock)(HGLOBAL);
extern PFN_GlobalLock __identifier("_imp__GlobalLock@4");
LPVOID WINAPI GlobalLock(HGLOBAL hMem) {
 return __identifier("_imp__GlobalLock@4")(hMem);
}

// _GlobalAlloc@8
typedef HGLOBAL (WINAPI *PFN_GlobalAlloc)(UINT, SIZE_T);
extern PFN_GlobalAlloc __identifier("_imp__GlobalAlloc@8");
HGLOBAL WINAPI GlobalAlloc(UINT uFlags, SIZE_T dwBytes) {
 return __identifier("_imp__GlobalAlloc@8")(uFlags, dwBytes);
}

// _ResumeThread@4
typedef DWORD (WINAPI *PFN_ResumeThread)(HANDLE);
extern PFN_ResumeThread __identifier("_imp__ResumeThread@4");
DWORD WINAPI ResumeThread(HANDLE hThread) {
 return __identifier("_imp__ResumeThread@4")(hThread);
}

// _GetExitCodeThread@8
typedef BOOL (WINAPI *PFN_GetExitCodeThread)(HANDLE, LPDWORD);
extern PFN_GetExitCodeThread __identifier("_imp__GetExitCodeThread@8");
BOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode) {
 return __identifier("_imp__GetExitCodeThread@8")(hThread, lpExitCode);
}

// _CreateThread@24
typedef HANDLE (WINAPI *PFN_CreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
extern PFN_CreateThread __identifier("_imp__CreateThread@24");
HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
 return __identifier("_imp__CreateThread@24")(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

// _SuspendThread@4
typedef DWORD (WINAPI *PFN_SuspendThread)(HANDLE);
extern PFN_SuspendThread __identifier("_imp__SuspendThread@4");
DWORD WINAPI SuspendThread(HANDLE hThread) {
 return __identifier("_imp__SuspendThread@4")(hThread);
}

// _ExitProcess@4
typedef DECLSPEC_NORETURN VOID (WINAPI *PFN_ExitProcess)(UINT);
extern PFN_ExitProcess __identifier("_imp__ExitProcess@4");
DECLSPEC_NORETURN VOID WINAPI ExitProcess(UINT uExitCode) {
 __identifier("_imp__ExitProcess@4")(uExitCode);
}

// _CreateProcessA@40
typedef BOOL (WINAPI *PFN_CreateProcessA)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
extern PFN_CreateProcessA __identifier("_imp__CreateProcessA@40");
BOOL WINAPI CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
 return __identifier("_imp__CreateProcessA@40")(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

// _TerminateProcess@8
typedef BOOL (WINAPI *PFN_TerminateProcess)(HANDLE, UINT);
extern PFN_TerminateProcess __identifier("_imp__TerminateProcess@8");
BOOL WINAPI TerminateProcess(HANDLE hProcess, UINT uExitCode) {
 return __identifier("_imp__TerminateProcess@8")(hProcess, uExitCode);
}

// _GlobalFree@4
typedef HGLOBAL (WINAPI *PFN_GlobalFree)(HGLOBAL);
extern PFN_GlobalFree __identifier("_imp__GlobalFree@4");
HGLOBAL WINAPI GlobalFree(HGLOBAL hMem) {
 return __identifier("_imp__GlobalFree@4")(hMem);
}

// _GlobalSize@4
typedef SIZE_T (WINAPI *PFN_GlobalSize)(HGLOBAL);
extern PFN_GlobalSize __identifier("_imp__GlobalSize@4");
SIZE_T WINAPI GlobalSize(HGLOBAL hMem) {
 return __identifier("_imp__GlobalSize@4")(hMem);
}

// _GlobalReAlloc@12
typedef HGLOBAL (WINAPI *PFN_GlobalReAlloc)(HGLOBAL, SIZE_T, UINT);
extern PFN_GlobalReAlloc __identifier("_imp__GlobalReAlloc@12");
HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags) {
 return __identifier("_imp__GlobalReAlloc@12")(hMem, dwBytes, uFlags);
}

// _Beep@8
typedef BOOL (WINAPI *PFN_Beep)(DWORD, DWORD);
extern PFN_Beep __identifier("_imp__Beep@8");
BOOL WINAPI Beep(DWORD dwFreq, DWORD dwDuration) {
 return __identifier("_imp__Beep@8")(dwFreq, dwDuration);
}

// _SetNamedPipeHandleState@16
typedef BOOL (WINAPI *PFN_SetNamedPipeHandleState)(HANDLE, LPDWORD, LPDWORD, LPDWORD);
extern PFN_SetNamedPipeHandleState __identifier("_imp__SetNamedPipeHandleState@16");
BOOL WINAPI SetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpMode, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout) {
 return __identifier("_imp__SetNamedPipeHandleState@16")(hNamedPipe, lpMode, lpMaxCollectionCount, lpCollectDataTimeout);
}

// _GetComputerNameA@8
typedef BOOL (WINAPI *PFN_GetComputerNameA)(LPSTR, LPDWORD);
extern PFN_GetComputerNameA __identifier("_imp__GetComputerNameA@8");
BOOL WINAPI GetComputerNameA(LPSTR lpBuffer, LPDWORD nSize) {
 return __identifier("_imp__GetComputerNameA@8")(lpBuffer, nSize);
}

// _CopyFileA@12
typedef BOOL (WINAPI *PFN_CopyFileA)(LPCSTR, LPCSTR, BOOL);
extern PFN_CopyFileA __identifier("_imp__CopyFileA@12");
BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) {
 return __identifier("_imp__CopyFileA@12")(lpExistingFileName, lpNewFileName, bFailIfExists);
}

// _FreeConsole@0
typedef BOOL (WINAPI *PFN_FreeConsole)(VOID);
extern PFN_FreeConsole __identifier("_imp__FreeConsole@0");
BOOL WINAPI FreeConsole(VOID) {
 return __identifier("_imp__FreeConsole@0")();
}

// _GetTickCount@0
typedef DWORD (WINAPI *PFN_GetTickCount)(VOID);
extern PFN_GetTickCount __identifier("_imp__GetTickCount@0");
DWORD WINAPI GetTickCount(VOID) {
 return __identifier("_imp__GetTickCount@0")();
}

// _GetConsoleScreenBufferInfo@8
typedef BOOL (WINAPI *PFN_GetConsoleScreenBufferInfo)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO);
extern PFN_GetConsoleScreenBufferInfo __identifier("_imp__GetConsoleScreenBufferInfo@8");
BOOL WINAPI GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo) {
 return __identifier("_imp__GetConsoleScreenBufferInfo@8")(hConsoleOutput, lpConsoleScreenBufferInfo);
}

// _ReadConsoleInputA@16
typedef BOOL (WINAPI *PFN_ReadConsoleInputA)(HANDLE, PINPUT_RECORD, DWORD, LPDWORD);
extern PFN_ReadConsoleInputA __identifier("_imp__ReadConsoleInputA@16");
BOOL WINAPI ReadConsoleInputA(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead) {
 return __identifier("_imp__ReadConsoleInputA@16")(hConsoleInput, lpBuffer, nLength, lpNumberOfEventsRead);
}

// _GetNumberOfConsoleInputEvents@8
typedef BOOL (WINAPI *PFN_GetNumberOfConsoleInputEvents)(HANDLE, LPDWORD);
extern PFN_GetNumberOfConsoleInputEvents __identifier("_imp__GetNumberOfConsoleInputEvents@8");
BOOL WINAPI GetNumberOfConsoleInputEvents(HANDLE hConsoleInput, LPDWORD lpNumberOfEvents) {
 return __identifier("_imp__GetNumberOfConsoleInputEvents@8")(hConsoleInput, lpNumberOfEvents);
}

// _GetStdHandle@4
typedef HANDLE (WINAPI *PFN_GetStdHandle)(DWORD);
extern PFN_GetStdHandle __identifier("_imp__GetStdHandle@4");
HANDLE WINAPI GetStdHandle(DWORD nStdHandle) {
 return __identifier("_imp__GetStdHandle@4")(nStdHandle);
}

// _SetConsoleWindowInfo@12
typedef BOOL (WINAPI *PFN_SetConsoleWindowInfo)(HANDLE, BOOL, CONST SMALL_RECT *);
extern PFN_SetConsoleWindowInfo __identifier("_imp__SetConsoleWindowInfo@12");
BOOL WINAPI SetConsoleWindowInfo(HANDLE hConsoleOutput, BOOL bAbsolute, CONST SMALL_RECT * lpConsoleWindow) {
 return __identifier("_imp__SetConsoleWindowInfo@12")(hConsoleOutput, bAbsolute, lpConsoleWindow);
}

// _SetConsoleTitleA@4
typedef BOOL (WINAPI *PFN_SetConsoleTitleA)(LPCSTR);
extern PFN_SetConsoleTitleA __identifier("_imp__SetConsoleTitleA@4");
BOOL WINAPI SetConsoleTitleA(LPCSTR lpConsoleTitle) {
 return __identifier("_imp__SetConsoleTitleA@4")(lpConsoleTitle);
}

// _GetConsoleTitleA@8
typedef DWORD (WINAPI *PFN_GetConsoleTitleA)(LPSTR, DWORD);
extern PFN_GetConsoleTitleA __identifier("_imp__GetConsoleTitleA@8");
DWORD WINAPI GetConsoleTitleA(LPSTR lpConsoleTitle, DWORD nSize) {
 return __identifier("_imp__GetConsoleTitleA@8")(lpConsoleTitle, nSize);
}

// _SetConsoleCtrlHandler@8
typedef BOOL (WINAPI *PFN_SetConsoleCtrlHandler)(PHANDLER_ROUTINE, BOOL);
extern PFN_SetConsoleCtrlHandler __identifier("_imp__SetConsoleCtrlHandler@8");
BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, BOOL Add) {
 return __identifier("_imp__SetConsoleCtrlHandler@8")(HandlerRoutine, Add);
}

// _SetConsoleCursorInfo@8
typedef BOOL (WINAPI *PFN_SetConsoleCursorInfo)(HANDLE, CONST CONSOLE_CURSOR_INFO *);
extern PFN_SetConsoleCursorInfo __identifier("_imp__SetConsoleCursorInfo@8");
BOOL WINAPI SetConsoleCursorInfo(HANDLE hConsoleOutput, CONST CONSOLE_CURSOR_INFO * lpConsoleCursorInfo) {
 return __identifier("_imp__SetConsoleCursorInfo@8")(hConsoleOutput, lpConsoleCursorInfo);
}

// _SetConsoleMode@8
typedef BOOL (WINAPI *PFN_SetConsoleMode)(HANDLE, DWORD);
extern PFN_SetConsoleMode __identifier("_imp__SetConsoleMode@8");
BOOL WINAPI SetConsoleMode(HANDLE hConsoleHandle, DWORD dwMode) {
 return __identifier("_imp__SetConsoleMode@8")(hConsoleHandle, dwMode);
}

// _AllocConsole@0
typedef BOOL (WINAPI *PFN_AllocConsole)(VOID);
extern PFN_AllocConsole __identifier("_imp__AllocConsole@0");
BOOL WINAPI AllocConsole(VOID) {
 return __identifier("_imp__AllocConsole@0")();
}

// _CreateEventA@16
typedef HANDLE (WINAPI *PFN_CreateEventA)(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPCSTR);
extern PFN_CreateEventA __identifier("_imp__CreateEventA@16");
HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName) {
 return __identifier("_imp__CreateEventA@16")(lpEventAttributes, bManualReset, bInitialState, lpName);
}

// _SetEvent@4
typedef BOOL (WINAPI *PFN_SetEvent)(HANDLE);
extern PFN_SetEvent __identifier("_imp__SetEvent@4");
BOOL WINAPI SetEvent(HANDLE hEvent) {
 return __identifier("_imp__SetEvent@4")(hEvent);
}

// _PulseEvent@4
typedef BOOL (WINAPI *PFN_PulseEvent)(HANDLE);
extern PFN_PulseEvent __identifier("_imp__PulseEvent@4");
BOOL WINAPI PulseEvent(HANDLE hEvent) {
 return __identifier("_imp__PulseEvent@4")(hEvent);
}

// _ResetEvent@4
typedef BOOL (WINAPI *PFN_ResetEvent)(HANDLE);
extern PFN_ResetEvent __identifier("_imp__ResetEvent@4");
BOOL WINAPI ResetEvent(HANDLE hEvent) {
 return __identifier("_imp__ResetEvent@4")(hEvent);
}

// _WaitForMultipleObjects@16
typedef DWORD (WINAPI *PFN_WaitForMultipleObjects)(DWORD, CONST HANDLE *, BOOL, DWORD);
extern PFN_WaitForMultipleObjects __identifier("_imp__WaitForMultipleObjects@16");
DWORD WINAPI WaitForMultipleObjects(DWORD nCount, CONST HANDLE * lpHandles, BOOL bWaitAll, DWORD dwMilliseconds) {
 return __identifier("_imp__WaitForMultipleObjects@16")(nCount, lpHandles, bWaitAll, dwMilliseconds);
}

// _SetErrorMode@4
typedef UINT (WINAPI *PFN_SetErrorMode)(UINT);
extern PFN_SetErrorMode __identifier("_imp__SetErrorMode@4");
UINT WINAPI SetErrorMode(UINT uMode) {
 return __identifier("_imp__SetErrorMode@4")(uMode);
}

// _QueryPerformanceCounter@4
typedef BOOL (WINAPI *PFN_QueryPerformanceCounter)(LARGE_INTEGER *);
extern PFN_QueryPerformanceCounter __identifier("_imp__QueryPerformanceCounter@4");
BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER * lpPerformanceCount) {
 return __identifier("_imp__QueryPerformanceCounter@4")(lpPerformanceCount);
}

// _QueryPerformanceFrequency@4
typedef BOOL (WINAPI *PFN_QueryPerformanceFrequency)(LARGE_INTEGER *);
extern PFN_QueryPerformanceFrequency __identifier("_imp__QueryPerformanceFrequency@4");
BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER * lpFrequency) {
 return __identifier("_imp__QueryPerformanceFrequency@4")(lpFrequency);
}

// _LocalFree@4
typedef HLOCAL (WINAPI *PFN_LocalFree)(HLOCAL);
extern PFN_LocalFree __identifier("_imp__LocalFree@4");
HLOCAL WINAPI LocalFree(HLOCAL hMem) {
 return __identifier("_imp__LocalFree@4")(hMem);
}

// _LocalAlloc@8
typedef HLOCAL (WINAPI *PFN_LocalAlloc)(UINT, SIZE_T);
extern PFN_LocalAlloc __identifier("_imp__LocalAlloc@8");
HLOCAL WINAPI LocalAlloc(UINT uFlags, SIZE_T uBytes) {
 return __identifier("_imp__LocalAlloc@8")(uFlags, uBytes);
}

// _HeapFree@12
typedef BOOL (WINAPI *PFN_HeapFree)(HANDLE, DWORD, LPVOID);
extern PFN_HeapFree __identifier("_imp__HeapFree@12");
BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
 return __identifier("_imp__HeapFree@12")(hHeap, dwFlags, lpMem);
}

// _GetProcessHeap@0
typedef HANDLE (WINAPI *PFN_GetProcessHeap)(VOID);
extern PFN_GetProcessHeap __identifier("_imp__GetProcessHeap@0");
HANDLE WINAPI GetProcessHeap(VOID) {
 return __identifier("_imp__GetProcessHeap@0")();
}

// _InterlockedExchangeAdd@8
typedef LONG (WINAPI *PFN_InterlockedExchangeAdd)(LONG volatile *, LONG);
extern PFN_InterlockedExchangeAdd __identifier("_imp__InterlockedExchangeAdd@8");
LONG WINAPI InterlockedExchangeAdd(LONG volatile * Addend, LONG Value) {
 return __identifier("_imp__InterlockedExchangeAdd@8")(Addend, Value);
}

// _CreateProcessW@40
typedef BOOL (WINAPI *PFN_CreateProcessW)(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION);
extern PFN_CreateProcessW __identifier("_imp__CreateProcessW@40");
BOOL WINAPI CreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
 return __identifier("_imp__CreateProcessW@40")(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

// _GetExitCodeProcess@8
typedef BOOL (WINAPI *PFN_GetExitCodeProcess)(HANDLE, LPDWORD);
extern PFN_GetExitCodeProcess __identifier("_imp__GetExitCodeProcess@8");
BOOL WINAPI GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode) {
 return __identifier("_imp__GetExitCodeProcess@8")(hProcess, lpExitCode);
}

// _lstrcpy@8
// WinBase.h maps lstrcpy to lstrcpyA; retail imports the legacy undecorated
// export, declared here with the header's ANSI signature.
#undef lstrcpy
LPSTR WINAPI lstrcpy(LPSTR lpString1, LPCSTR lpString2);
typedef LPSTR (WINAPI *PFN_lstrcpy)(LPSTR, LPCSTR);
extern PFN_lstrcpy __identifier("_imp__lstrcpy@8");
LPSTR WINAPI lstrcpy(LPSTR lpString1, LPCSTR lpString2) {
 return __identifier("_imp__lstrcpy@8")(lpString1, lpString2);
}

// _lstrcpyn@12
// WinBase.h maps lstrcpyn to lstrcpynA; retail imports the legacy undecorated
// export, declared here with the header's ANSI signature.
#undef lstrcpyn
LPSTR WINAPI lstrcpyn(LPSTR lpString1, LPCSTR lpString2, int iMaxLength);
typedef LPSTR (WINAPI *PFN_lstrcpyn)(LPSTR, LPCSTR, int);
extern PFN_lstrcpyn __identifier("_imp__lstrcpyn@12");
LPSTR WINAPI lstrcpyn(LPSTR lpString1, LPCSTR lpString2, int iMaxLength) {
 return __identifier("_imp__lstrcpyn@12")(lpString1, lpString2, iMaxLength);
}

// _GetTempFileNameA@16
typedef UINT (WINAPI *PFN_GetTempFileNameA)(LPCSTR, LPCSTR, UINT, LPSTR);
extern PFN_GetTempFileNameA __identifier("_imp__GetTempFileNameA@16");
UINT WINAPI GetTempFileNameA(LPCSTR lpPathName, LPCSTR lpPrefixString, UINT uUnique, LPSTR lpTempFileName) {
 return __identifier("_imp__GetTempFileNameA@16")(lpPathName, lpPrefixString, uUnique, lpTempFileName);
}

// _CreateDirectoryA@8
typedef BOOL (WINAPI *PFN_CreateDirectoryA)(LPCSTR, LPSECURITY_ATTRIBUTES);
extern PFN_CreateDirectoryA __identifier("_imp__CreateDirectoryA@8");
BOOL WINAPI CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
 return __identifier("_imp__CreateDirectoryA@8")(lpPathName, lpSecurityAttributes);
}

// _GetTempPathA@8
typedef DWORD (WINAPI *PFN_GetTempPathA)(DWORD, LPSTR);
extern PFN_GetTempPathA __identifier("_imp__GetTempPathA@8");
DWORD WINAPI GetTempPathA(DWORD nBufferLength, LPSTR lpBuffer) {
 return __identifier("_imp__GetTempPathA@8")(nBufferLength, lpBuffer);
}

// _RemoveDirectoryA@4
typedef BOOL (WINAPI *PFN_RemoveDirectoryA)(LPCSTR);
extern PFN_RemoveDirectoryA __identifier("_imp__RemoveDirectoryA@4");
BOOL WINAPI RemoveDirectoryA(LPCSTR lpPathName) {
 return __identifier("_imp__RemoveDirectoryA@4")(lpPathName);
}

// _FindNextFileA@8
typedef BOOL (WINAPI *PFN_FindNextFileA)(HANDLE, LPWIN32_FIND_DATAA);
extern PFN_FindNextFileA __identifier("_imp__FindNextFileA@8");
BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
 return __identifier("_imp__FindNextFileA@8")(hFindFile, lpFindFileData);
}

// _FindFirstFileA@8
typedef HANDLE (WINAPI *PFN_FindFirstFileA)(LPCSTR, LPWIN32_FIND_DATAA);
extern PFN_FindFirstFileA __identifier("_imp__FindFirstFileA@8");
HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
 return __identifier("_imp__FindFirstFileA@8")(lpFileName, lpFindFileData);
}

// _DeleteFileW@4
typedef BOOL (WINAPI *PFN_DeleteFileW)(LPCWSTR);
extern PFN_DeleteFileW __identifier("_imp__DeleteFileW@4");
BOOL WINAPI DeleteFileW(LPCWSTR lpFileName) {
 return __identifier("_imp__DeleteFileW@4")(lpFileName);
}

// _GetEnvironmentStrings@0
typedef LPSTR (WINAPI *PFN_GetEnvironmentStrings)(VOID);
extern PFN_GetEnvironmentStrings __identifier("_imp__GetEnvironmentStrings@0");
LPSTR WINAPI GetEnvironmentStrings(VOID) {
 return __identifier("_imp__GetEnvironmentStrings@0")();
}

// _MapViewOfFileEx@24
typedef LPVOID (WINAPI *PFN_MapViewOfFileEx)(HANDLE, DWORD, DWORD, DWORD, SIZE_T, LPVOID);
extern PFN_MapViewOfFileEx __identifier("_imp__MapViewOfFileEx@24");
LPVOID WINAPI MapViewOfFileEx(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress) {
 return __identifier("_imp__MapViewOfFileEx@24")(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress);
}

// _OpenEventA@12
typedef HANDLE (WINAPI *PFN_OpenEventA)(DWORD, BOOL, LPCSTR);
extern PFN_OpenEventA __identifier("_imp__OpenEventA@12");
HANDLE WINAPI OpenEventA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) {
 return __identifier("_imp__OpenEventA@12")(dwDesiredAccess, bInheritHandle, lpName);
}

// _CreateDirectoryW@8
typedef BOOL (WINAPI *PFN_CreateDirectoryW)(LPCWSTR, LPSECURITY_ATTRIBUTES);
extern PFN_CreateDirectoryW __identifier("_imp__CreateDirectoryW@8");
BOOL WINAPI CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
 return __identifier("_imp__CreateDirectoryW@8")(lpPathName, lpSecurityAttributes);
}

// _GetDateFormatA@24
typedef int (WINAPI *PFN_GetDateFormatA)(LCID, DWORD, CONST SYSTEMTIME *, LPCSTR, LPSTR, int);
extern PFN_GetDateFormatA __identifier("_imp__GetDateFormatA@24");
int WINAPI GetDateFormatA(LCID Locale, DWORD dwFlags, CONST SYSTEMTIME * lpDate, LPCSTR lpFormat, LPSTR lpDateStr, int cchDate) {
 return __identifier("_imp__GetDateFormatA@24")(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate);
}

// _GetDateFormatW@24
typedef int (WINAPI *PFN_GetDateFormatW)(LCID, DWORD, CONST SYSTEMTIME *, LPCWSTR, LPWSTR, int);
extern PFN_GetDateFormatW __identifier("_imp__GetDateFormatW@24");
int WINAPI GetDateFormatW(LCID Locale, DWORD dwFlags, CONST SYSTEMTIME * lpDate, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate) {
 return __identifier("_imp__GetDateFormatW@24")(Locale, dwFlags, lpDate, lpFormat, lpDateStr, cchDate);
}

// _GetTimeFormatW@24
typedef int (WINAPI *PFN_GetTimeFormatW)(LCID, DWORD, CONST SYSTEMTIME *, LPCWSTR, LPWSTR, int);
extern PFN_GetTimeFormatW __identifier("_imp__GetTimeFormatW@24");
int WINAPI GetTimeFormatW(LCID Locale, DWORD dwFlags, CONST SYSTEMTIME * lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime) {
 return __identifier("_imp__GetTimeFormatW@24")(Locale, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime);
}

// _GetDiskFreeSpaceExW@16
typedef BOOL (WINAPI *PFN_GetDiskFreeSpaceExW)(LPCWSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);
extern PFN_GetDiskFreeSpaceExW __identifier("_imp__GetDiskFreeSpaceExW@16");
BOOL WINAPI GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes) {
 return __identifier("_imp__GetDiskFreeSpaceExW@16")(lpDirectoryName, lpFreeBytesAvailableToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes);
}

// _GetLocaleInfoW@16
typedef int (WINAPI *PFN_GetLocaleInfoW)(LCID, LCTYPE, LPWSTR, int);
extern PFN_GetLocaleInfoW __identifier("_imp__GetLocaleInfoW@16");
int WINAPI GetLocaleInfoW(LCID Locale, LCTYPE LCType, LPWSTR lpLCData, int cchData) {
 return __identifier("_imp__GetLocaleInfoW@16")(Locale, LCType, lpLCData, cchData);
}

// _GetTimeZoneInformation@4
typedef DWORD (WINAPI *PFN_GetTimeZoneInformation)(LPTIME_ZONE_INFORMATION);
extern PFN_GetTimeZoneInformation __identifier("_imp__GetTimeZoneInformation@4");
DWORD WINAPI GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation) {
 return __identifier("_imp__GetTimeZoneInformation@4")(lpTimeZoneInformation);
}

// _TerminateThread@8
typedef BOOL (WINAPI *PFN_TerminateThread)(HANDLE, DWORD);
extern PFN_TerminateThread __identifier("_imp__TerminateThread@8");
BOOL WINAPI TerminateThread(HANDLE hThread, DWORD dwExitCode) {
 return __identifier("_imp__TerminateThread@8")(hThread, dwExitCode);
}

// _FindNextFileW@8
typedef BOOL (WINAPI *PFN_FindNextFileW)(HANDLE, LPWIN32_FIND_DATAW);
extern PFN_FindNextFileW __identifier("_imp__FindNextFileW@8");
BOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) {
 return __identifier("_imp__FindNextFileW@8")(hFindFile, lpFindFileData);
}

// _SetThreadPriority@8
typedef BOOL (WINAPI *PFN_SetThreadPriority)(HANDLE, int);
extern PFN_SetThreadPriority __identifier("_imp__SetThreadPriority@8");
BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority) {
 return __identifier("_imp__SetThreadPriority@8")(hThread, nPriority);
}

// _GlobalMemoryStatusEx@4
typedef BOOL (WINAPI *PFN_GlobalMemoryStatusEx)(LPMEMORYSTATUSEX);
extern PFN_GlobalMemoryStatusEx __identifier("_imp__GlobalMemoryStatusEx@4");
BOOL WINAPI GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer) {
 return __identifier("_imp__GlobalMemoryStatusEx@4")(lpBuffer);
}

// _FileTimeToDosDateTime@12
typedef BOOL (WINAPI *PFN_FileTimeToDosDateTime)(CONST FILETIME *, LPWORD, LPWORD);
extern PFN_FileTimeToDosDateTime __identifier("_imp__FileTimeToDosDateTime@12");
BOOL WINAPI FileTimeToDosDateTime(CONST FILETIME * lpFileTime, LPWORD lpFatDate, LPWORD lpFatTime) {
 return __identifier("_imp__FileTimeToDosDateTime@12")(lpFileTime, lpFatDate, lpFatTime);
}

// _GetFileInformationByHandle@8
typedef BOOL (WINAPI *PFN_GetFileInformationByHandle)(HANDLE, LPBY_HANDLE_FILE_INFORMATION);
extern PFN_GetFileInformationByHandle __identifier("_imp__GetFileInformationByHandle@8");
BOOL WINAPI GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation) {
 return __identifier("_imp__GetFileInformationByHandle@8")(hFile, lpFileInformation);
}

// _SetFileTime@16
typedef BOOL (WINAPI *PFN_SetFileTime)(HANDLE, CONST FILETIME *, CONST FILETIME *, CONST FILETIME *);
extern PFN_SetFileTime __identifier("_imp__SetFileTime@16");
BOOL WINAPI SetFileTime(HANDLE hFile, CONST FILETIME * lpCreationTime, CONST FILETIME * lpLastAccessTime, CONST FILETIME * lpLastWriteTime) {
 return __identifier("_imp__SetFileTime@16")(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
}

// _DosDateTimeToFileTime@12
typedef BOOL (WINAPI *PFN_DosDateTimeToFileTime)(WORD, WORD, LPFILETIME);
extern PFN_DosDateTimeToFileTime __identifier("_imp__DosDateTimeToFileTime@12");
BOOL WINAPI DosDateTimeToFileTime(WORD wFatDate, WORD wFatTime, LPFILETIME lpFileTime) {
 return __identifier("_imp__DosDateTimeToFileTime@12")(wFatDate, wFatTime, lpFileTime);
}

// _CreateFileW@28
typedef HANDLE (WINAPI *PFN_CreateFileW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
extern PFN_CreateFileW __identifier("_imp__CreateFileW@28");
HANDLE WINAPI CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
 return __identifier("_imp__CreateFileW@28")(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

// _GetStartupInfoA@4
typedef VOID (WINAPI *PFN_GetStartupInfoA)(LPSTARTUPINFOA);
extern PFN_GetStartupInfoA __identifier("_imp__GetStartupInfoA@4");
VOID WINAPI GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo) {
 __identifier("_imp__GetStartupInfoA@4")(lpStartupInfo);
}

// _GetSystemTimeAsFileTime@4
typedef VOID (WINAPI *PFN_GetSystemTimeAsFileTime)(LPFILETIME);
extern PFN_GetSystemTimeAsFileTime __identifier("_imp__GetSystemTimeAsFileTime@4");
VOID WINAPI GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime) {
 __identifier("_imp__GetSystemTimeAsFileTime@4")(lpSystemTimeAsFileTime);
}

// _DebugBreak@0
typedef VOID (WINAPI *PFN_DebugBreak)(VOID);
extern PFN_DebugBreak __identifier("_imp__DebugBreak@0");
VOID WINAPI DebugBreak(VOID) {
 __identifier("_imp__DebugBreak@0")();
}

// _OutputDebugStringW@4
typedef VOID (WINAPI *PFN_OutputDebugStringW)(LPCWSTR);
extern PFN_OutputDebugStringW __identifier("_imp__OutputDebugStringW@4");
VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString) {
 __identifier("_imp__OutputDebugStringW@4")(lpOutputString);
}

// _WaitCommEvent@12
typedef BOOL (WINAPI *PFN_WaitCommEvent)(HANDLE, LPDWORD, LPOVERLAPPED);
extern PFN_WaitCommEvent __identifier("_imp__WaitCommEvent@12");
BOOL WINAPI WaitCommEvent(HANDLE hFile, LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped) {
 return __identifier("_imp__WaitCommEvent@12")(hFile, lpEvtMask, lpOverlapped);
}

// _GetOverlappedResult@16
typedef BOOL (WINAPI *PFN_GetOverlappedResult)(HANDLE, LPOVERLAPPED, LPDWORD, BOOL);
extern PFN_GetOverlappedResult __identifier("_imp__GetOverlappedResult@16");
BOOL WINAPI GetOverlappedResult(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait) {
 return __identifier("_imp__GetOverlappedResult@16")(hFile, lpOverlapped, lpNumberOfBytesTransferred, bWait);
}

// _SetCommMask@8
typedef BOOL (WINAPI *PFN_SetCommMask)(HANDLE, DWORD);
extern PFN_SetCommMask __identifier("_imp__SetCommMask@8");
BOOL WINAPI SetCommMask(HANDLE hFile, DWORD dwEvtMask) {
 return __identifier("_imp__SetCommMask@8")(hFile, dwEvtMask);
}

// _PurgeComm@8
typedef BOOL (WINAPI *PFN_PurgeComm)(HANDLE, DWORD);
extern PFN_PurgeComm __identifier("_imp__PurgeComm@8");
BOOL WINAPI PurgeComm(HANDLE hFile, DWORD dwFlags) {
 return __identifier("_imp__PurgeComm@8")(hFile, dwFlags);
}

// _SetCommState@8
typedef BOOL (WINAPI *PFN_SetCommState)(HANDLE, LPDCB);
extern PFN_SetCommState __identifier("_imp__SetCommState@8");
BOOL WINAPI SetCommState(HANDLE hFile, LPDCB lpDCB) {
 return __identifier("_imp__SetCommState@8")(hFile, lpDCB);
}

// _GetCommState@8
typedef BOOL (WINAPI *PFN_GetCommState)(HANDLE, LPDCB);
extern PFN_GetCommState __identifier("_imp__GetCommState@8");
BOOL WINAPI GetCommState(HANDLE hFile, LPDCB lpDCB) {
 return __identifier("_imp__GetCommState@8")(hFile, lpDCB);
}

// _SetCommConfig@12
typedef BOOL (WINAPI *PFN_SetCommConfig)(HANDLE, LPCOMMCONFIG, DWORD);
extern PFN_SetCommConfig __identifier("_imp__SetCommConfig@12");
BOOL WINAPI SetCommConfig(HANDLE hCommDev, LPCOMMCONFIG lpCC, DWORD dwSize) {
 return __identifier("_imp__SetCommConfig@12")(hCommDev, lpCC, dwSize);
}

// _GetCommConfig@12
typedef BOOL (WINAPI *PFN_GetCommConfig)(HANDLE, LPCOMMCONFIG, LPDWORD);
extern PFN_GetCommConfig __identifier("_imp__GetCommConfig@12");
BOOL WINAPI GetCommConfig(HANDLE hCommDev, LPCOMMCONFIG lpCC, LPDWORD lpdwSize) {
 return __identifier("_imp__GetCommConfig@12")(hCommDev, lpCC, lpdwSize);
}

// _SetCommTimeouts@8
typedef BOOL (WINAPI *PFN_SetCommTimeouts)(HANDLE, LPCOMMTIMEOUTS);
extern PFN_SetCommTimeouts __identifier("_imp__SetCommTimeouts@8");
BOOL WINAPI SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts) {
 return __identifier("_imp__SetCommTimeouts@8")(hFile, lpCommTimeouts);
}

// _SetupComm@12
typedef BOOL (WINAPI *PFN_SetupComm)(HANDLE, DWORD, DWORD);
extern PFN_SetupComm __identifier("_imp__SetupComm@12");
BOOL WINAPI SetupComm(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue) {
 return __identifier("_imp__SetupComm@12")(hFile, dwInQueue, dwOutQueue);
}

// _SetPriorityClass@8
typedef BOOL (WINAPI *PFN_SetPriorityClass)(HANDLE, DWORD);
extern PFN_SetPriorityClass __identifier("_imp__SetPriorityClass@8");
BOOL WINAPI SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass) {
 return __identifier("_imp__SetPriorityClass@8")(hProcess, dwPriorityClass);
}

// _GetThreadPriority@4
typedef int (WINAPI *PFN_GetThreadPriority)(HANDLE);
extern PFN_GetThreadPriority __identifier("_imp__GetThreadPriority@4");
int WINAPI GetThreadPriority(HANDLE hThread) {
 return __identifier("_imp__GetThreadPriority@4")(hThread);
}

// _GetPriorityClass@4
typedef DWORD (WINAPI *PFN_GetPriorityClass)(HANDLE);
extern PFN_GetPriorityClass __identifier("_imp__GetPriorityClass@4");
DWORD WINAPI GetPriorityClass(HANDLE hProcess) {
 return __identifier("_imp__GetPriorityClass@4")(hProcess);
}

// _GetSystemDirectoryA@8
typedef UINT (WINAPI *PFN_GetSystemDirectoryA)(LPSTR, UINT);
extern PFN_GetSystemDirectoryA __identifier("_imp__GetSystemDirectoryA@8");
UINT WINAPI GetSystemDirectoryA(LPSTR lpBuffer, UINT uSize) {
 return __identifier("_imp__GetSystemDirectoryA@8")(lpBuffer, uSize);
}

// _MulDiv@12
typedef int (WINAPI *PFN_MulDiv)(int, int, int);
extern PFN_MulDiv __identifier("_imp__MulDiv@12");
int WINAPI MulDiv(int nNumber, int nNumerator, int nDenominator) {
 return __identifier("_imp__MulDiv@12")(nNumber, nNumerator, nDenominator);
}

// _Module32Next@8
typedef BOOL (WINAPI *PFN_Module32Next)(HANDLE, LPMODULEENTRY32);
extern PFN_Module32Next __identifier("_imp__Module32Next@8");
BOOL WINAPI Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
 return __identifier("_imp__Module32Next@8")(hSnapshot, lpme);
}

// _Module32First@8
typedef BOOL (WINAPI *PFN_Module32First)(HANDLE, LPMODULEENTRY32);
extern PFN_Module32First __identifier("_imp__Module32First@8");
BOOL WINAPI Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
 return __identifier("_imp__Module32First@8")(hSnapshot, lpme);
}

// _CreateToolhelp32Snapshot@8
typedef HANDLE (WINAPI *PFN_CreateToolhelp32Snapshot)(DWORD, DWORD);
extern PFN_CreateToolhelp32Snapshot __identifier("_imp__CreateToolhelp32Snapshot@8");
HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID) {
 return __identifier("_imp__CreateToolhelp32Snapshot@8")(dwFlags, th32ProcessID);
}

// _Thread32Next@8
typedef BOOL (WINAPI *PFN_Thread32Next)(HANDLE, LPTHREADENTRY32);
extern PFN_Thread32Next __identifier("_imp__Thread32Next@8");
BOOL WINAPI Thread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte) {
 return __identifier("_imp__Thread32Next@8")(hSnapshot, lpte);
}

// _Thread32First@8
typedef BOOL (WINAPI *PFN_Thread32First)(HANDLE, LPTHREADENTRY32);
extern PFN_Thread32First __identifier("_imp__Thread32First@8");
BOOL WINAPI Thread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte) {
 return __identifier("_imp__Thread32First@8")(hSnapshot, lpte);
}

// _WriteConsoleOutputA@20
typedef BOOL (WINAPI *PFN_WriteConsoleOutputA)(HANDLE, CONST CHAR_INFO *, COORD, COORD, PSMALL_RECT);
extern PFN_WriteConsoleOutputA __identifier("_imp__WriteConsoleOutputA@20");
BOOL WINAPI WriteConsoleOutputA(HANDLE hConsoleOutput, CONST CHAR_INFO * lpBuffer, COORD dwBufferSize, COORD dwBufferCoord, PSMALL_RECT lpWriteRegion) {
 return __identifier("_imp__WriteConsoleOutputA@20")(hConsoleOutput, lpBuffer, dwBufferSize, dwBufferCoord, lpWriteRegion);
}

// _SetConsoleScreenBufferSize@8
typedef BOOL (WINAPI *PFN_SetConsoleScreenBufferSize)(HANDLE, COORD);
extern PFN_SetConsoleScreenBufferSize __identifier("_imp__SetConsoleScreenBufferSize@8");
BOOL WINAPI SetConsoleScreenBufferSize(HANDLE hConsoleOutput, COORD dwSize) {
 return __identifier("_imp__SetConsoleScreenBufferSize@8")(hConsoleOutput, dwSize);
}
}
