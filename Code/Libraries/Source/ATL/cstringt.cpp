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
extern "C" __declspec(dllimport) unsigned long __stdcall GetEnvironmentVariableW(
    const unsigned short *, unsigned short *, unsigned long);

typedef const char *LPCSTR;
typedef char *LPSTR;
typedef const unsigned short *LPCWSTR;
typedef unsigned int UINT;
typedef unsigned long LCID;
typedef long HRESULT;

#define NULL 0
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define _ATL_SAFE_ALLOCA_DEF_THRESHOLD 1024

extern "C" __declspec(dllimport) int __stdcall lstrlenW(LPCWSTR);
extern "C" __declspec(dllimport) int __stdcall CompareStringA(
    LCID, unsigned long, LPCSTR, int, LPCSTR, int);
extern "C" void *__cdecl _alloca(unsigned int);

extern LPSTR __stdcall AtlW2AHelper(LPSTR, LPCWSTR, int, UINT);

#define USES_ATL_SAFE_ALLOCA_EX(x) \
    ATL::_ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<x> _AtlSafeAllocaManager
#define USES_ATL_SAFE_ALLOCA USES_ATL_SAFE_ALLOCA_EX(ATL::CCRTAllocator)
#define _ATL_SAFE_ALLOCA(nRequestedSize, nThreshold) \
    ((nRequestedSize <= nThreshold && \
      ATL::_ATL_SAFE_ALLOCA_IMPL::_AtlVerifyStackAvailable(nRequestedSize)) ? \
        _alloca(nRequestedSize) : \
        _AtlSafeAllocaManager.Allocate(nRequestedSize))

#define USES_CONVERSION_EX \
    int _convert_ex; (_convert_ex); \
    UINT _acp_ex = ATL::_AtlGetConversionACP(); (_acp_ex); \
    LPCWSTR _lpw_ex; (_lpw_ex); \
    LPCSTR _lpa_ex; (_lpa_ex); \
    USES_ATL_SAFE_ALLOCA

#define W2A_EX(lpw, nChars) ( \
    ((_lpw_ex = lpw) == NULL) ? NULL : ( \
        _convert_ex = (lstrlenW(_lpw_ex) + 1) * sizeof(unsigned short), \
        AtlW2AHelper( \
            (LPSTR)_ATL_SAFE_ALLOCA(_convert_ex, _ATL_SAFE_ALLOCA_DEF_THRESHOLD), \
            _lpw_ex, \
            _convert_ex, \
            _acp_ex)))

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
typedef unsigned long (__stdcall *ATLGETENVIRONMENTVARIABLEW)(
    const unsigned short *, unsigned short *, unsigned long);
struct _AtlStringThunks
{
    ATLCOMPARESTRINGW pfnCompareStringW;
    ATLGETSTRINGTYPEEXW pfnGetStringTypeExW;
    ATLLSTRCMPIW pfnlstrcmpiW;
    ATLCHARCASEW pfnCharLowerW;
    ATLCHARCASEW pfnCharUpperW;
    ATLGETENVIRONMENTVARIABLEW pfnGetEnvironmentVariableW;
};
extern _AtlStringThunks _strthunks;
typedef UINT (__stdcall *ATLGETTHREADACP)();
extern ATLGETTHREADACP g_pfnGetThreadACP;

inline UINT __stdcall _AtlGetConversionACP() throw()
{
    return g_pfnGetThreadACP();
}

class CCRTAllocator;

namespace _ATL_SAFE_ALLOCA_IMPL
{
bool __cdecl _AtlVerifyStackAvailable(unsigned int);

template <class Allocator>
class CAtlSafeAllocBufferManager
{
private:
    void *m_pHead;

public:
    CAtlSafeAllocBufferManager() : m_pHead(0) {}
    void *Allocate(unsigned int);
    ~CAtlSafeAllocBufferManager() throw();
};
}

__declspec(noreturn) void __stdcall AtlThrow(HRESULT);

int __stdcall CompareStringWFake(LCID lcid, unsigned long dwFlags,
    LPCWSTR pszString1, int nLength1, LPCWSTR pszString2, int nLength2)
{
    USES_CONVERSION_EX;

    LPCSTR pszAString1 = NULL;
    if (pszString1 != NULL)
    {
        pszAString1 = W2A_EX(pszString1, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
        if (pszAString1 == NULL)
            AtlThrow(E_OUTOFMEMORY);
    }

    LPCSTR pszAString2 = NULL;
    if (pszString2 != NULL)
    {
        pszAString2 = W2A_EX(pszString2, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
        if (pszAString2 == NULL)
            AtlThrow(E_OUTOFMEMORY);
    }

    return ::CompareStringA(lcid, dwFlags, pszAString1, nLength1,
        pszAString2, nLength2);
}

int __stdcall GetStringTypeExWFake(unsigned long, unsigned long,
    const unsigned short *, int, unsigned short *);
int __stdcall lstrcmpiWFake(const unsigned short *, const unsigned short *);
unsigned short *__stdcall CharLowerWFake(unsigned short *);
unsigned short *__stdcall CharUpperWFake(unsigned short *);
unsigned long __stdcall GetEnvironmentVariableWFake(
    const unsigned short *, unsigned short *, unsigned long);

unsigned long __stdcall GetEnvironmentVariableWThunk(
    const unsigned short *name, unsigned short *buffer, unsigned long size)
{
    _AtlInstallStringThunk(reinterpret_cast<void **>(&_strthunks.pfnGetEnvironmentVariableW),
        GetEnvironmentVariableWFake, ::GetEnvironmentVariableW);
    return _strthunks.pfnGetEnvironmentVariableW(name, buffer, size);
}

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
