// cl: /O1 /G7 /arch:SSE2
// ATL 7.1 cstringt.h, supplied by the Open-BFME-1 MSVC 7.1 toolchain.
// The retail helper selects Win9x conversion or the native Unicode API once,
// then atomically installs the selected function in the string thunk table.
extern "C" __declspec(dllimport) unsigned long __stdcall GetVersion();
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(long *, long);

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
}
