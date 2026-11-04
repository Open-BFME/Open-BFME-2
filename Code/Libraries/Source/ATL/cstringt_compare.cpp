// platformsdk
// ATL 7.1 cstringt.h lstrcmpiWFake with the atlconv.h W2A expansion.
// Retail uses the legacy unsuffixed ANSI kernel32 lstrcmpi export, which
// WinBase.h only spells as a macro for lstrcmpiA, so that one declaration
// stays local.
// Source supplied by Open-BFME-1 toolchain.
// flags: region default (reverse/retail_inventory/flag_regions.csv)
#include <windows.h>
#include <malloc.h>
#pragma intrinsic(_alloca)
#undef lstrcmpi
extern "C" __declspec(dllimport) int __stdcall lstrcmpi(const char *, const char *);
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
    return lstrcmpi(CONVERT(a), CONVERT(b));
#undef CONVERT
}
}
