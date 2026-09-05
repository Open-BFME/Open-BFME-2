// cl: /O1 /G7 /arch:SSE2
// ATL 7.1 cstringt.h, supplied by the Open-BFME-1 MSVC 7.1 toolchain.
// The retail helper selects Win9x conversion or the native Unicode API once,
// then atomically installs the selected function in the string thunk table.
extern "C" __declspec(dllimport) unsigned long __stdcall GetVersion();
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(long *, long);
extern "C" __declspec(dllimport) int __stdcall CompareStringW(
    unsigned long, unsigned long, const unsigned short *, int, const unsigned short *, int);
extern "C" __declspec(dllimport) int __stdcall GetStringTypeExW(
    unsigned long, unsigned long, const unsigned short *, int, unsigned short *);
extern "C" __declspec(dllimport) int __stdcall lstrcmpiW(
    const unsigned short *, const unsigned short *);
extern "C" __declspec(dllimport) unsigned short *__stdcall CharLowerW(unsigned short *);
extern "C" __declspec(dllimport) unsigned short *__stdcall CharUpperW(unsigned short *);

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
typedef int (__stdcall *ATLGETSTRINGTYPEEXW)(unsigned long, unsigned long,
    const unsigned short *, int, unsigned short *);
typedef int (__stdcall *ATLLSTRCMPIW)(const unsigned short *, const unsigned short *);
typedef unsigned short *(__stdcall *ATLCHARCASEW)(unsigned short *);
struct _AtlStringThunks
{
    ATLCOMPARESTRINGW pfnCompareStringW;
    ATLGETSTRINGTYPEEXW pfnGetStringTypeExW;
    ATLLSTRCMPIW pfnlstrcmpiW;
    ATLCHARCASEW pfnCharLowerW;
    ATLCHARCASEW pfnCharUpperW;
    void *pfnGetEnvironmentVariableW;
};
extern _AtlStringThunks _strthunks;
int __stdcall CompareStringWFake(unsigned long, unsigned long,
    const unsigned short *, int, const unsigned short *, int);
int __stdcall GetStringTypeExWFake(unsigned long, unsigned long,
    const unsigned short *, int, unsigned short *);
int __stdcall lstrcmpiWFake(const unsigned short *, const unsigned short *);
unsigned short *__stdcall CharLowerWFake(unsigned short *);
unsigned short *__stdcall CharUpperWFake(unsigned short *);

unsigned short *__stdcall CharUpperWThunk(unsigned short *text)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnCharUpperW),
        CharUpperWFake, ::CharUpperW);
    return _strthunks.pfnCharUpperW(text);
}

unsigned short *__stdcall CharLowerWThunk(unsigned short *text)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnCharLowerW),
        CharLowerWFake, ::CharLowerW);
    return _strthunks.pfnCharLowerW(text);
}

int __stdcall lstrcmpiWThunk(const unsigned short *first, const unsigned short *second)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnlstrcmpiW),
        lstrcmpiWFake, ::lstrcmpiW);
    return _strthunks.pfnlstrcmpiW(first, second);
}

int __stdcall CompareStringWThunk(unsigned long lcid, unsigned long flags,
    const unsigned short *string1, int length1, const unsigned short *string2, int length2)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnCompareStringW),
        CompareStringWFake, ::CompareStringW);
    return _strthunks.pfnCompareStringW(lcid, flags, string1, length1, string2, length2);
}

int __stdcall GetStringTypeExWThunk(unsigned long lcid, unsigned long infoType,
    const unsigned short *source, int length, unsigned short *charType)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnGetStringTypeExW),
        GetStringTypeExWFake, ::GetStringTypeExW);
    return _strthunks.pfnGetStringTypeExW(lcid, infoType, source, length, charType);
}
}
