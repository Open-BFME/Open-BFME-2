// cl: /O2 /DNDEBUG /MD
// Win32 conversion-wrapper family used by BFME1 UnicodeString/GameSpy code.
// BFME2 retail uses CP_UTF8 (65001), not the system ANSI code page.
// Descriptive function names; ABI and complete bodies independently audited
// from exported String translate callers plus named PE imports.
typedef unsigned short Wide;
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int,unsigned long,const char*,int,Wide*,int);
int BFME2Utf8ToWide(const char* source,int count,Wide* output,int capacity) {
    return MultiByteToWideChar(65001,0,source,count,output,capacity);
}
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int,unsigned long,const Wide*,int,char*,int,const char*,int*);
int BFME2WideToUtf8(const Wide* source,int count,char* output,int capacity) {
    return WideCharToMultiByte(65001,0,source,count,output,capacity,0,0);
}
int multiByteToWideChar(const char* source,int count,Wide* output,int capacity) {
    return MultiByteToWideChar(0,0,source,count,output,capacity);
}
int wideCharToMultiByte(const Wide* source,int count,char* output,int capacity) {
    return WideCharToMultiByte(0,0,source,count,output,capacity,0,0);
}
