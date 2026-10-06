// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// BFME1 6583b3c1 WideCharStringToMultiByte.cpp provides UTF-8 conversion flow.
// Native3289AC/179 calls the same two-pass Win32 API with code page65001,
// array allocation/deletion and narrow assignment1B790; local string cleanup
// uses BFME2 game free30830 instead of the donor node-pool allocator.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int, unsigned long, const unsigned short *, int,
    char *, int, const char *, int *);
namespace WcslenIAT { extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *); }
_STL::string WideCharStringToMultiByte(const unsigned short *orig) {
    _STL::string ret;
    int len = WideCharToMultiByte(65001, 0, orig, WcslenIAT::wcslen(orig), 0, 0, 0, 0) + 1;
    if (len > 0) {
        char *dest = new char[len];
        WideCharToMultiByte(65001, 0, orig, -1, dest, len, 0, 0);
        dest[len - 1] = 0;
        ret = dest;
        delete[] dest;
    }
    return ret;
}
