// ATL 7.1 cstringt.h CharLowerWFake and atlconv.h conversion macros.
// Reference: Open-BFME-1 MSVC 7.1 toolchain; local ABI declarations replace headers.
// cl: /O1 /G7 /arch:SSE2
extern "C" void *__cdecl _alloca(unsigned int);
#pragma intrinsic(_alloca)
extern "C" __declspec(dllimport) int __stdcall lstrlenW(const unsigned short *);
extern "C" __declspec(dllimport) int __stdcall lstrlenA(const char *);
extern "C" __declspec(dllimport) char *__stdcall CharLowerA(char *);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *, const unsigned short *);
char *__stdcall AtlW2AHelper(char *, const unsigned short *, int, unsigned int);
unsigned short *__stdcall AtlA2WHelper(unsigned short *, const char *, int, unsigned int);
extern "C" __declspec(dllimport) char *__stdcall CharUpperA(char *);
namespace ATL {
typedef unsigned int (__stdcall *ATLGETTHREADACP)();
extern ATLGETTHREADACP g_pfnGetThreadACP;
unsigned short *__stdcall CharLowerWFake(unsigned short *text)
{
    int convert;
    unsigned int acp = g_pfnGetThreadACP();
    const unsigned short *wide;
    const char *ansi;
#define W2A(s) (((wide = (s)) == 0) ? 0 : (convert = (lstrlenW(wide)+1)*2, AtlW2AHelper((char *)_alloca(convert), wide, convert, acp)))
#define A2W(s) (((ansi = (s)) == 0) ? 0 : (convert = lstrlenA(ansi)+1, AtlA2WHelper((unsigned short *)_alloca(convert*2), ansi, convert, acp)))
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
#define A2W(s) (((ansi = (s)) == 0) ? 0 : (convert = lstrlenA(ansi)+1, AtlA2WHelper((unsigned short *)_alloca(convert*2), ansi, convert, acp)))
    char *converted = W2A(text);
    CharUpperA(converted);
    wcscpy(text, A2W(converted));
    return text;
#undef W2A
#undef A2W
}
}
