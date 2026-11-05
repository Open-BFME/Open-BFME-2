// platformsdk
#include <windows.h>
#include <comdef.h>

extern _GUID g_bfmeIidTSA;

struct BfmeObjECF;

struct IFEBrowserEngine2Vtbl
{
	void (__stdcall *m_bfmeF0)(BfmeObjECF *obj);
	void (__stdcall *m_bfmeF1)(BfmeObjECF *obj);
	void (__stdcall *m_bfmeF2)(BfmeObjECF *obj);
    // IDispatch slots +0x0c..+0x1c are unused by this partial view.
    void *slot0C, *slot10, *slot14, *slot18, *slot1C;
    long (__stdcall *shutdown)(BfmeObjECF *obj);
};

struct BfmeObjECF
{
	IFEBrowserEngine2Vtbl *m_vtable;
    void shutdown()
    {
        long result = m_vtable->shutdown(this);
        if (result < 0)
            _com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
    }
};

extern BfmeObjECF *g_bfmeObjECF;

// ?releaseBrowser@@YAXXZ
void releaseBrowser(void)
{
	BfmeObjECF *obj = g_bfmeObjECF;
	if (obj)
		obj->m_vtable->m_bfmeF2(obj);
}

class LANAPI;


// ?g_bfmeObjECF@@3PAUBfmeObjECF@@A: matched references place it at VA 0xdf7040; also referenced as ?g_bfmeObjECF@@3VBfmeObjECFPtr@@A.
BfmeObjECF * g_bfmeObjECF = 0;
// ?g_bfmeObjECI@@3PAVBfmeObjECI@@A: the global at VA 0xdfe958 is ?g_Va009FE958@@3PAUGlobal009FE958@@A.

// Donor: GeneralsMD dx8webbrowser.cpp, DX8WebBrowser::Shutdown, through
// reference/open-bfme-1 revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20.
// Target evidence: complete 0x00176FA0..0x00176FED boundary, COM slot +0x20,
// same browser IID as Initialize and the existing dispatch wrappers, Release
// at +8, named window global reset, and CoUninitialize tail import. The
// structural queue's 34-byte candidate ended at the interior error call;
// this 77-byte body includes the release and both return paths.
// Use the existing global's canonical pointer spelling; clear it before
// Release as VS2003's comip.h smart-pointer assignment does. Defining the
// already identified hWnd also supplies the browser units' missing owner.
class DX8WebBrowser
{
public:
    static HWND__ *hWnd;
    static void Shutdown();
};
HWND__ *DX8WebBrowser::hWnd = 0;

void DX8WebBrowser::Shutdown()
{
    if (g_bfmeObjECF)
    {
        g_bfmeObjECF->shutdown();
        if (g_bfmeObjECF)
        {
            BfmeObjECF *browser = g_bfmeObjECF;
            g_bfmeObjECF = 0;
            browser->m_vtable->m_bfmeF2(browser);
        }
        hWnd = 0;
        CoUninitialize();
    }
}
