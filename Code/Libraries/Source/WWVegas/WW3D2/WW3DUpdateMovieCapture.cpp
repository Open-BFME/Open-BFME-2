// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ww3d /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// Semantic donor: ZH ww3d.cpp via BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Native117AD0..117BAB (219B); Begin_Render118170 calls this capture helper.
// Donor carries the WW3D movie-copy purpose and class spellings. Native calls
// prove GetBuffer-first ordering and no trailing Grab; native loop proves
// flipped RGB rows, hoisted row offsets, and four-byte source pixels.
// Movie DEC3DC (ww3d.cpp's private static) and g_WW3D_Hwnd DEC408 use
// existing global providers.
// Target gets FrameGrab buffer first, uses D3D9 surface slots12/13,
// and releases the surface after copying RGB bytes with a flipped row order.
	// dx8wrapper.cpp's protected static at VA 0x00DEDC70.
	// dllimport: inlined at every use, so no out-of-line copy competes with retail's
	// Convert_Color (0x0006E1C0) or Set_Ambient (0x00117F50, DX8SetAmbient.cpp).
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "ww3d.h"	// the bfme2_ww3d shims must win both include guards, ww3d.h first
#include "dx8wrapper.h"	// the bfme2_ww3d shim (BFME 2 DX8Wrapper spellings) has to win the include guard
#include "framgrab.h"

// BFME2's front-buffer object is a D3D9 surface even though DX8Wrapper keeps
// the D3D8 type name. Retail GetDesc/LockRect slots are +0x30/+0x34; this
// TU-local view follows the corresponding BFME1 W3DDisplayCaptureScreen shim.
class D3D9FrontBufferView
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual unsigned long __stdcall Release(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual long __stdcall GetDesc(void *desc);
	virtual long __stdcall LockRect(void *locked_rect, const RECT *rect, unsigned long flags);
};

extern void *g_WW3D_Hwnd;

void WW3D::Update_Movie_Capture()
{
    char *image=(char *)Movie->GetBuffer();
    D3D9FrontBufferView *fb=reinterpret_cast<D3D9FrontBufferView *>(DX8Wrapper::_Get_DX8_Front_Buffer());
    char desc[32];
    fb->GetDesc(&desc);
    RECT bounds;
    GetWindowRect((HWND)g_WW3D_Hwnd,&bounds);
    D3DLOCKED_RECT lrect;
    HRESULT hr=fb->LockRect(&lrect,&bounds,D3DLOCK_READONLY);
    if (hr) Log_DX8_ErrorCode((unsigned)hr);
    unsigned x,y,index,index2,width,height;
    width=bounds.right-bounds.left;
    height=bounds.bottom-bounds.top;
    for (y=0;y<height;y++) {
        index=3*((height-y-1)*width);
        index2=y*lrect.Pitch;
        for (x=0;x<width;x++) {
            image[index]=*((char *)lrect.pBits+index2);
            image[index+1]=*((char *)lrect.pBits+index2+1);
            image[index+2]=*((char *)lrect.pBits+index2+2);
            index+=3;
            index2+=4;
        }
    }
    fb->Release();
}

