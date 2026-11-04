// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/DX8WebBrowserInitialize.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.
// BFME1 donor boundary: 0x00958F20..0x009591ED, surrounded by int3 padding.
// BFME2 target: RVA 0x001772B0, all 717 bytes verified by its ledger row.
// BrowserEngine.DLL / DllRegisterServer and the interface / class UUIDs
// identify DX8WebBrowser::Initialize. Native VS2003 COM smart-pointer code
// reproduces the complete 717-byte body. Dependency proofs:
// WW3D::Get_Window at 0x008FD170 reads the witnessed WW3D HWND global;
// _bstr_t::Data_t::Release at 0x00958BF0 independently matches the native
// 70-byte InterlockedDecrement / string-buffer destruction implementation.
// <new> declares operator delete[] before comutil.h: without it cl 7.1 lowers
// Data_t::_Free's delete [] m_str to operator delete (??3), and the emitted
// Release COMDAT is not retail's 0x00176E90 body, which calls ??_V.
#include <new>
#include <objbase.h>
#include <comip.h>
extern GUID g_bfmeIidTSA;
#include <comdef.h>
struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412")) IFEBrowserEngine2 : IDispatch {
    virtual HRESULT __stdcall raw_Initialize(long *) = 0;
    virtual void __stdcall slot08() = 0;
    virtual void __stdcall slot09() = 0;
    virtual void __stdcall slot10() = 0;
    virtual void __stdcall slot11() = 0;
    virtual void __stdcall slot12() = 0;
    virtual void __stdcall slot13() = 0;
    virtual void __stdcall slot14() = 0;
    virtual void __stdcall slot15() = 0;
    virtual void __stdcall slot16() = 0;
    virtual void __stdcall slot17() = 0;
    virtual void __stdcall slot18() = 0;
    virtual HRESULT __stdcall put_BadPageURL(BSTR) = 0;
    virtual void __stdcall slot20() = 0;
    virtual HRESULT __stdcall put_LoadingPageURL(BSTR) = 0;
    virtual void __stdcall slot22() = 0;
    virtual HRESULT __stdcall put_MouseFileName(BSTR) = 0;
    virtual void __stdcall slot24() = 0;
    virtual HRESULT __stdcall put_MouseBusyFileName(BSTR) = 0;
    void Initialize(long *device) {
        HRESULT hr=raw_Initialize(device);
        if (hr<0) _com_issue_errorex(hr,this,g_bfmeIidTSA);
    }
};
struct __declspec(uuid("2b2cc8b0-2dc0-48c6-b6fd-c07820a6477e")) FEBrowserEngine2;
template <> inline const IID &_com_IIID<IFEBrowserEngine2,&__uuidof(IFEBrowserEngine2)>::GetIID() throw()
{
    return g_bfmeIidTSA;
}
typedef _com_ptr_t<_com_IIID<IFEBrowserEngine2,&__uuidof(IFEBrowserEngine2)> > IFEBrowserEngine2Ptr;

// Preserve the VS2003 smart-pointer operation while sharing the existing
// IUnknown GUID owner with its out-of-line provider. The compiler UUID
// constant is the same value but would create a second data identity.
template <> inline HRESULT IFEBrowserEngine2Ptr::CreateInstance(
    const CLSID &classId, IUnknown *outer, DWORD context) throw()
{
    HRESULT result;
    _Release();
    if (context & (CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)) {
        IUnknown *unknown;
        result = CoCreateInstance(classId, outer, context, IID_IUnknown,
            reinterpret_cast<void **>(&unknown));
        if (SUCCEEDED(result)) {
            result = OleRun(unknown);
            if (SUCCEEDED(result)) {
                result = unknown->QueryInterface(GetIID(),
                    reinterpret_cast<void **>(&m_pInterface));
            }
            unknown->Release();
        }
    } else {
        result = CoCreateInstance(classId, outer, context, GetIID(),
            reinterpret_cast<void **>(&m_pInterface));
    }
    if (FAILED(result))
        m_pInterface = NULL;
    return result;
}

// The browser smart pointer lives at retail 0x009F7040, the global
// BfmeConv804.cpp owns as g_bfmeObjECF; this unit views it as the COM pointer.
struct BfmeObjECF;
extern BfmeObjECF *g_bfmeObjECF;
#define Rva0134B280Browser (*reinterpret_cast<IFEBrowserEngine2Ptr *>(&g_bfmeObjECF))
#include "WW3DClass.h"
struct IDirect3DDevice8;
#include "DX8WrapperClass.h"
class DX8WebBrowser {
public:
    static HWND hWnd;
    static bool Initialize(const char *,const char *,const char *,const char *);
};
bool DX8WebBrowser::Initialize(const char *badpageurl,const char *loadingpageurl,const char *mousefilename,const char *mousebusyfilename)
{
    if (Rva0134B280Browser == 0) {
        CoInitialize(0);
        HRESULT hr=Rva0134B280Browser.CreateInstance(__uuidof(FEBrowserEngine2));
        if (hr == REGDB_E_CLASSNOTREG) {
            HMODULE lib=LoadLibraryA("BrowserEngine.DLL");
            if (lib) {
                FARPROC proc=GetProcAddress(lib,"DllRegisterServer");
                if (proc) {
                    proc();
                    hr=Rva0134B280Browser.CreateInstance(__uuidof(FEBrowserEngine2));
                }
                FreeLibrary(lib);
            }
        }
        if (hr == S_OK) {
            hWnd=(HWND)WW3D::Get_Window();
            Rva0134B280Browser->Initialize((long *)DX8Wrapper::_Get_D3D_Device8());
            if (badpageurl) Rva0134B280Browser->put_BadPageURL(_bstr_t(badpageurl));
            if (loadingpageurl) Rva0134B280Browser->put_LoadingPageURL(_bstr_t(loadingpageurl));
            if (mousefilename) Rva0134B280Browser->put_MouseFileName(_bstr_t(mousefilename));
            if (mousebusyfilename) Rva0134B280Browser->put_MouseBusyFileName(_bstr_t(mousebusyfilename));
        } else {
            Rva0134B280Browser=0;
            return false;
        }
    }
    return true;
}
