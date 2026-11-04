// cl: /GS
// platformsdk
// Microsoft Visual C++ .NET 2003 ATL 7.1 CAtlBaseModule constructor, from
// atls.lib's atlbase.obj (src/atl/atls/atlbase.cpp), and the compiler-generated
// _ATL_BASE_MODULE70 constructor it calls.
//
// Identity: atls.lib's ??0CAtlBaseModule and ??0_ATL_BASE_MODULE70 COMDATs
// place uniquely at 0x00628E28 and 0x00628CFE. The OSVERSIONINFO local is why
// the constructor carries a /GS cookie.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

#define _ATL_VER 0x0710

// Linker-provided image base; _vcclrit.h also defines managed CRT startup state.
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace ATL
{

extern "C" const GUID GUID_ATLVer70 = { 0x394c3de0, 0x3c6f, 0x11d2, { 0x81, 0x7b, 0x0, 0xc0, 0x4f, 0x79, 0x7a, 0xb7 } };

class CComCriticalSection
{
public:
    CComCriticalSection() throw();
    HRESULT Init() throw();

    unsigned char m_sec[0x18];
};

template <class T>
class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> >
class CSimpleArray
{
public:
    CSimpleArray() : m_aT(0), m_nSize(0), m_nAllocSize(0) {}

    T *m_aT;
    int m_nSize;
    int m_nAllocSize;
};

struct _ATL_BASE_MODULE70
{
    UINT cbSize;
    HINSTANCE m_hInst;
    HINSTANCE m_hInstResource;
    bool m_bNT5orWin98;
    DWORD dwAtlBuildVer;
    const GUID *pguidVer;
    CComCriticalSection m_csResource;
    CSimpleArray<HINSTANCE> m_rgResourceInstance;
};
typedef _ATL_BASE_MODULE70 _ATL_BASE_MODULE;

class CAtlBaseModule : public _ATL_BASE_MODULE
{
public:
    static bool m_bInitFailed;
    CAtlBaseModule() throw();
};

CAtlBaseModule::CAtlBaseModule() throw()
{
    cbSize = sizeof(_ATL_BASE_MODULE);

    m_hInst = m_hInstResource = reinterpret_cast<HINSTANCE>(&__ImageBase);

    m_bNT5orWin98 = false;
    OSVERSIONINFO version;
    memset(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(version);
    ::GetVersionExA(&version);
    if(version.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if(version.dwMajorVersion >= 5)
        {
            m_bNT5orWin98 = true;
        }
    }
    else if(version.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        if((version.dwMajorVersion > 4) || ((version.dwMajorVersion == 4) &&
            (version.dwMinorVersion > 0)))
        {
            m_bNT5orWin98 = true;
        }
    }

    dwAtlBuildVer = _ATL_VER;
    pguidVer = &GUID_ATLVer70;

    if (FAILED(m_csResource.Init()))
    {
        CAtlBaseModule::m_bInitFailed = true;
    }
}

}
