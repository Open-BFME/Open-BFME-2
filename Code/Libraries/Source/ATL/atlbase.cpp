// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 _ATL_WIN_MODULE70 and the
// CSimpleArray<ATOM> it embeds.

typedef unsigned short ATOM;
typedef int BOOL;
typedef long HRESULT;
typedef unsigned int size_t;

struct HINSTANCE__;
typedef HINSTANCE__ *HINSTANCE;

typedef unsigned long DWORD;
typedef const char *LPCSTR;

extern "C" __declspec(dllimport) void __cdecl free(void *memory);
extern "C" __declspec(dllimport) __declspec(noreturn) void __stdcall RaiseException(
    DWORD code, DWORD flags, DWORD argumentCount, const DWORD *arguments);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *section);
extern "C" __declspec(dllimport) BOOL __stdcall UnregisterClassA(LPCSTR className, HINSTANCE instance);

namespace ATL
{

class CComCriticalSection
{
public:
    CComCriticalSection() throw();

    HRESULT Init() throw();
    HRESULT Term() throw() { DeleteCriticalSection(&m_sec); return 0; }

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

    int GetSize() const { return m_nSize; }
    T &operator[](int nIndex);
    void RemoveAll();

    T *m_aT;
    int m_nSize;
    int m_nAllocSize;
};

inline __declspec(noreturn) void _AtlRaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags = 1)
{
    RaiseException(dwExceptionCode, dwExceptionFlags, 0, 0);
}

template <class T, class TEqual>
T &CSimpleArray<T, TEqual>::operator[](int nIndex)
{
    if (nIndex < 0 || nIndex >= m_nSize)
    {
        _AtlRaiseException(0xC000008CL);
    }
    return m_aT[nIndex];
}

template <class T, class TEqual>
void CSimpleArray<T, TEqual>::RemoveAll()
{
    if (m_aT != 0)
    {
        free(m_aT);
        m_aT = 0;
    }
    m_nSize = 0;
    m_nAllocSize = 0;
}

struct _ATL_WIN_MODULE70
{
    unsigned int cbSize;
    CComCriticalSection m_csWindowCreate;
    void *m_pCreateWndList;
    CSimpleArray<ATOM> m_rgWindowClassAtoms;

    _ATL_WIN_MODULE70();
};

_ATL_WIN_MODULE70::_ATL_WIN_MODULE70()
{
}

extern "C" HRESULT __stdcall AtlWinModuleInit(_ATL_WIN_MODULE70 *pWinModule)
{
    if (pWinModule == 0)
        return 0x80070057L;
    if (pWinModule->cbSize != sizeof(_ATL_WIN_MODULE70))
        return 0x80070057L;

    pWinModule->m_pCreateWndList = 0;
    return pWinModule->m_csWindowCreate.Init();
}

extern "C" HRESULT __stdcall AtlWinModuleTerm(_ATL_WIN_MODULE70 *pWinModule, HINSTANCE hInst)
{
    if (pWinModule == 0)
        return 0x80070057L;
    if (pWinModule->cbSize == 0)
        return 0;
    if (pWinModule->cbSize != sizeof(_ATL_WIN_MODULE70))
        return 0x80070057L;

    for (int i = 0; i < pWinModule->m_rgWindowClassAtoms.GetSize(); i++)
        UnregisterClassA((LPCSTR)pWinModule->m_rgWindowClassAtoms[i], hInst);
    pWinModule->m_rgWindowClassAtoms.RemoveAll();
    pWinModule->m_csWindowCreate.Term();
    pWinModule->cbSize = 0;
    return 0;
}

class CAtlBaseModule
{
public:
    static bool m_bInitFailed;
};

class CAtlWinModule : public _ATL_WIN_MODULE70
{
public:
    CAtlWinModule();
};

CAtlWinModule::CAtlWinModule()
{
    cbSize = sizeof(_ATL_WIN_MODULE70);
    HRESULT hr = AtlWinModuleInit(this);
    if (hr < 0)
        CAtlBaseModule::m_bInitFailed = true;
}

template void CSimpleArray<ATOM>::RemoveAll();
template ATOM &CSimpleArray<ATOM>::operator[](int);

}
