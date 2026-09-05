// cl: /O1 /G7 /arch:SSE2
// ATL 7.1 cstringt.h, supplied by the Open-BFME-1 MSVC 7.1 toolchain.
// The retail helper selects Win9x conversion or the native Unicode API once,
// then atomically installs the selected function in the string thunk table.
extern "C" __declspec(dllimport) unsigned long __stdcall GetVersion();
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(long *, long);
extern "C" __declspec(dllimport) int __stdcall CompareStringW(
    unsigned long, unsigned long, const unsigned short *, int, const unsigned short *, int);

namespace ATL
{
void _AtlInstallStringThunk(void **ppThunk, void *pfnWin9x, void *pfnNT) throw()
{
    static bool s_bWin9x = (GetVersion() & 0x80000000) != 0;
    void *pfn;
    if (s_bWin9x)
        pfn = pfnWin9x;
    else
        pfn = pfnNT;
    InterlockedExchange(reinterpret_cast<long *>(ppThunk), reinterpret_cast<long>(pfn));
}

typedef int (__stdcall *ATLCOMPARESTRINGW)(unsigned long, unsigned long,
    const unsigned short *, int, const unsigned short *, int);
struct _AtlStringThunks
{
    ATLCOMPARESTRINGW pfnCompareStringW;
    void *pfnGetStringTypeExW;
    void *pfnlstrcmpiW;
    void *pfnCharLowerW;
    void *pfnCharUpperW;
    void *pfnGetEnvironmentVariableW;
};
extern _AtlStringThunks _strthunks;
int __stdcall CompareStringWFake(unsigned long, unsigned long,
    const unsigned short *, int, const unsigned short *, int);

int __stdcall CompareStringWThunk(unsigned long lcid, unsigned long flags,
    const unsigned short *string1, int length1, const unsigned short *string2, int length2)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnCompareStringW),
        CompareStringWFake, ::CompareStringW);
    return _strthunks.pfnCompareStringW(lcid, flags, string1, length1, string2, length2);
}
}
