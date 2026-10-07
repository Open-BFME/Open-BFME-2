struct _GUID { unsigned char bytes[16]; };
struct IUnknown;
extern _GUID g_bfmeIidTSA;
extern void __stdcall _com_issue_errorex(long, IUnknown *, const _GUID &);

struct BfmeObjECF;

struct BfmeVtblECF
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
	BfmeVtblECF *m_bfmeVtbl;
    void shutdown()
    {
        long result = m_bfmeVtbl->shutdown(this);
        if (result < 0)
            _com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
    }
};

extern BfmeObjECF *g_bfmeObjECF;

// ?bfmeGoECF@@YAXXZ
void bfmeGoECF(void)
{
	BfmeObjECF *obj = g_bfmeObjECF;
	if (obj)
		obj->m_bfmeVtbl->m_bfmeF2(obj);
}

class BfmeObjECI
{
public:
	virtual void bfmeW0(void);
	virtual void bfmeW1(void);
	virtual void bfmeW2(void);
	virtual void bfmeW3(void);
	virtual void bfmeW4(void);
	virtual void bfmeW5(void);
	virtual void bfmeW6(void);
	virtual void bfmeW7(void);
	virtual void bfmeW8(void);
	virtual void bfmeW9(void);
	virtual void bfmeW10(void);
	virtual void bfmeW11(void);
	virtual void bfmeW12(void);
	virtual void bfmeW13(void);
	virtual void bfmeW14(void);
	virtual void bfmeW15(void);
	virtual void bfmeW16(void);
	virtual void bfmeW17(void);
	virtual void bfmeW18(void);
	virtual void bfmeW19(void);
	virtual void bfmeW20(void);
	virtual void bfmeW21(void);
	virtual void bfmeW22(void);
	virtual void bfmeW23(void);
	virtual void bfmeW24(void);
	virtual void bfmeW25(void);
	virtual void bfmeW26(void);
	virtual void bfmeW27(void);
	virtual void bfmeW28(void);
	virtual void bfmeW29(void);
	virtual void bfmeW30(void);
	virtual void bfmeW31(void);
	virtual void bfmeW32(void);
	virtual void bfmeW33(void);
	virtual void bfmeW34(void);
	virtual void bfmeW35(void);
	virtual void bfmeW36(void);
	virtual void bfmeW37(void);
	virtual void bfmeW38(void);
	virtual void bfmeW39(void);
	virtual void bfmeW40(void);
	virtual void bfmeW41(void);
	virtual void bfmeW42(void);
	virtual void bfmeW43(void);
	virtual void bfmeW44(void);
	virtual void bfmeW45(void);
	virtual void bfmeW46(void);
	virtual void bfmeW47(void);
	virtual void bfmeW48(void);
	virtual void bfmeW49(void);
	virtual void bfmeW50(void);
	virtual void bfmeW51(void);
	virtual void bfmeW52(void);
	virtual void bfmeW53(void);
	virtual bool bfmeAsk54ECI(void);
};

extern BfmeObjECI *g_bfmeObjECI;

// ?bfmeGoECI@@YA_NXZ
// Retail tail-jmps vtable slot 54; the BFME1 class stops at slot 46,
// so BFME2 grew eight convention virtuals ahead of the ask.
bool bfmeGoECI(void)
{
	BfmeObjECI *obj = g_bfmeObjECI;
	if (!obj)
		return false;
	return obj->bfmeAsk54ECI();
}

// ?g_bfmeObjECF@@3PAUBfmeObjECF@@A: matched references place it at VA 0xdf7040; also referenced as ?Rva00959410Dispatch@@3URva00959410Ptr@@A, ?g_bfmeObjECF@@3VBfmeObjECFPtr@@A.
BfmeObjECF * g_bfmeObjECF = 0;
#pragma comment(linker, "/alternatename:?Rva00959410Dispatch@@3URva00959410Ptr@@A=?g_bfmeObjECF@@3PAUBfmeObjECF@@A")
#pragma comment(linker, "/alternatename:?g_bfmeObjECF@@3VBfmeObjECFPtr@@A=?g_bfmeObjECF@@3PAUBfmeObjECF@@A")
// ?g_bfmeObjECI@@3PAVBfmeObjECI@@A: the global at VA 0xdfe958 is ?g_Va009FE958@@3PAUGlobal009FE958@@A.
#pragma comment(linker, "/alternatename:?g_bfmeObjECI@@3PAVBfmeObjECI@@A=?g_Va009FE958@@3PAUGlobal009FE958@@A")

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
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();
struct HWND__;
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
            browser->m_bfmeVtbl->m_bfmeF2(browser);
        }
        hWnd = 0;
        CoUninitialize();
    }
}
