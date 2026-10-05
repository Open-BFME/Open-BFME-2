// cl: /O1 /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// BFME1 6583b3c1 WideCharStringToMultiByte.cpp provides UTF-8 conversion flow.
// Native3289AC/179 calls the same two-pass Win32 API with code page65001,
// array allocation/deletion and narrow assignment1B790; local string cleanup
// uses BFME2 game free30830 instead of the donor node-pool allocator.
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
