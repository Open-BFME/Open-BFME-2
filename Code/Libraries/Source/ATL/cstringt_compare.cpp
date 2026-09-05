// ATL 7.1 cstringt.h lstrcmpiWFake with the atlconv.h W2A expansion.
// Source supplied by Open-BFME-1 toolchain; local ABI declarations replace headers.
// cl: /O1 /G7 /arch:SSE2
extern "C" void *__cdecl _alloca(unsigned int);
#pragma intrinsic(_alloca)
extern "C" __declspec(dllimport) int __stdcall lstrlenW(const unsigned short *);
extern "C" __declspec(dllimport) int __stdcall lstrcmpiA(const char *, const char *);
char *__stdcall AtlW2AHelper(char *, const unsigned short *, int, unsigned int);
namespace ATL {
typedef unsigned int (__stdcall *ATLGETTHREADACP)();
extern ATLGETTHREADACP g_pfnGetThreadACP;
int __stdcall lstrcmpiWFake(const unsigned short *a, const unsigned short *b)
{
    int convert;
    unsigned int acp = g_pfnGetThreadACP();
    const unsigned short *wide;
#define CONVERT(s) (((wide = (s)) == 0) ? 0 : (convert = (lstrlenW(wide)+1)*2, AtlW2AHelper((char *)_alloca(convert), wide, convert, acp)))
    return lstrcmpiA(CONVERT(a), CONVERT(b));
#undef CONVERT
}
}
