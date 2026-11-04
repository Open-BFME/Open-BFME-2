// cl: /MD
// platformsdk
// ATL 7.1 cstringt.h CharLowerWFake and atlconv.h conversion macros.
// Retail imports wcscpy from the DLL CRT (/MD) and uses the legacy unsuffixed
// ANSI kernel32 lstrlen export, which WinBase.h only spells as a macro for
// lstrlenA, so that one declaration stays local.
// Reference: Open-BFME-1 MSVC 7.1 toolchain.
// flags: region default (reverse/retail_inventory/flag_regions.csv)
#include <windows.h>
#include <malloc.h>
#include <string.h>
#undef lstrlen
extern "C" __declspec(dllimport) int __stdcall lstrlen(const char *);
char *__stdcall AtlW2AHelper(char *, const unsigned short *, int, unsigned int);
unsigned short *__stdcall AtlA2WHelper(unsigned short *, const char *, int, unsigned int);
namespace ATL {
typedef unsigned int (__stdcall *ATLGETTHREADACP)();
unsigned int __stdcall _AtlGetThreadACPThunk();
ATLGETTHREADACP g_pfnGetThreadACP = _AtlGetThreadACPThunk;
unsigned short *__stdcall CharLowerWFake(unsigned short *text)
{
    int convert;
    unsigned int acp = g_pfnGetThreadACP();
    const unsigned short *wide;
    const char *ansi;
#define W2A(s) (((wide = (s)) == 0) ? 0 : (convert = (lstrlenW(wide)+1)*2, AtlW2AHelper((char *)_alloca(convert), wide, convert, acp)))
#define A2W(s) (((ansi = (s)) == 0) ? 0 : (convert = lstrlen(ansi)+1, AtlA2WHelper((unsigned short *)_alloca(convert*2), ansi, convert, acp)))
    char *converted = W2A(text);
    CharLowerA(converted);
    wcscpy(text, A2W(converted));
    return text;
#undef W2A
#undef A2W
}
unsigned short *__stdcall CharUpperWFake(unsigned short *text)
{
    int convert;
    unsigned int acp = g_pfnGetThreadACP();
    const unsigned short *wide;
    const char *ansi;
#define W2A(s) (((wide = (s)) == 0) ? 0 : (convert = (lstrlenW(wide)+1)*2, AtlW2AHelper((char *)_alloca(convert), wide, convert, acp)))
#define A2W(s) (((ansi = (s)) == 0) ? 0 : (convert = lstrlen(ansi)+1, AtlA2WHelper((unsigned short *)_alloca(convert*2), ansi, convert, acp)))
    char *converted = W2A(text);
    CharUpperA(converted);
    wcscpy(text, A2W(converted));
    return text;
#undef W2A
#undef A2W
}
}
