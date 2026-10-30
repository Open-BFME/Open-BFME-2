// cl: /MD
// Optimization flags follow reverse/retail_inventory/flag_regions.csv.
// Retail CSimpleArray::RemoveAll calls the imported CRT free through the IAT.
// platformsdk
// Microsoft Visual C++ .NET 2003 ATL 7.1 _ATL_WIN_MODULE70 and the
// CSimpleArray<ATOM> it embeds.

#define STRICT
#include <windows.h>
#include <excpt.h>
#include <stdlib.h>

namespace ATL
{

class CComCriticalSection
{
public:
    CComCriticalSection() throw();

    HRESULT Init() throw();
    HRESULT Term() throw() { DeleteCriticalSection(&m_sec); return 0; }


    CRITICAL_SECTION m_sec;
};

// CComCriticalSection::Init. The reloc sweep named it from its call site; the
// shape is read off the funclets rather than taken from the reference, because
// this engine's is not the published ATL 7.1 body.
//
// The filter does not decide anything: it saves the exception code into a
// frame slot and returns 1 unconditionally (xor eax, eax / inc eax / ret), so
// the handler always runs. The handler then picks the result branchlessly -
// setne on the saved code, dec, and 0x0006C009, add 0x80004005 - which is
// E_FAIL plus the difference to E_OUTOFMEMORY, i.e. STATUS_NO_MEMORY gives
// E_OUTOFMEMORY and anything else gives E_FAIL. Written as a filter that
// tests the code, cl folds the test into the filter and the handler stops
// matching.
//
// The saved code is the extra frame slot: __SEH_prolog takes 0x0C here where
// a filter without it takes 0x08.
inline HRESULT CComCriticalSection::Init() throw()
{
    HRESULT hRes = 0;
    unsigned long code;
    __try
    {
        InitializeCriticalSection(&m_sec);
    }
    __except (code = GetExceptionCode(), 1)
    {
        hRes = code == 0xC0000017L ? 0x8007000EL : 0x80004005L;
    }
    return hRes;
}

template <class T>
class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> >
class CSimpleArray
{
public:
    CSimpleArray() : m_aT(0), m_nSize(0), m_nAllocSize(0) {}
    ~CSimpleArray();

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
CSimpleArray<T, TEqual>::~CSimpleArray()
{
    RemoveAll();
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
    void rva0000682F();
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

bool CAtlBaseModule::m_bInitFailed;

class CAtlWinModule : public _ATL_WIN_MODULE70
{
public:
    CAtlWinModule();
    void Term();
};

HINSTANCE g_00E09E64;

CAtlWinModule::CAtlWinModule()
{
    cbSize = sizeof(_ATL_WIN_MODULE70);
    HRESULT hr = AtlWinModuleInit(this);
    if (hr < 0)
        CAtlBaseModule::m_bInitFailed = true;
}

void CAtlWinModule::Term()
{
    AtlWinModuleTerm(this, g_00E09E64);
    return m_rgWindowClassAtoms.RemoveAll();
}

template void CSimpleArray<ATOM>::RemoveAll();
template CSimpleArray<ATOM>::~CSimpleArray();
template ATOM &CSimpleArray<ATOM>::operator[](int);

// Native682F is a complete13B no-argument receiver wrapper. Its actual
// stdcallcallee58C3 takes _ATL_WIN_MODULE70* and the already-owned
// HINSTANCE globalE09E64. Original wrapper name remains unknown.
void _ATL_WIN_MODULE70::rva0000682F()
{
    AtlWinModuleTerm(this, g_00E09E64);
}

// CComCriticalSection::Term (retail 0x0000328B, 10B) is unreferenced there:
// the out-of-line copy of the header inline (DeleteCriticalSection on the
// section at +0, S_OK). The anchor (no retail counterpart) only makes this
// unit emit it.
#pragma inline_depth(0)
// ?bfmeEmitAtlCritSecTerm@ATL@@YAXPAVCComCriticalSection@1@@Z present-unmatched
void bfmeEmitAtlCritSecTerm(CComCriticalSection *comCriticalSection)
{
    comCriticalSection->Term();
}
#pragma inline_depth()

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?m@Gen_00800540@@QAEPAXXZ=??0?$CSimpleArray@GV?$CSimpleArrayEqualHelper@G@ATL@@@ATL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??0Rva00800630Owner@@QAE@XZ=??0?$CSimpleArray@GV?$CSimpleArrayEqualHelper@G@ATL@@@ATL@@QAE@XZ")
