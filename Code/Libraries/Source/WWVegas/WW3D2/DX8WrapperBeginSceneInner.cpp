// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// Retail 0x00904230: DX8CALL(BeginScene()) wrapped by a matching enter/leave helper.

// The device keeps its D3D8 type name but is a Direct3D 9 device: GetBackBuffer
// slot 18, BeginScene slot 41, and the back buffer is an IDirect3DSurface9
// (LockRect slot 13, UnlockRect 14, Release 2), all from the vendored SDK.
#include <d3d9.h>

struct IDirect3DDevice8;
#define DEVICE9 (reinterpret_cast<IDirect3DDevice9 *>(D3DDevice))

// Retail 0x009588E0 is the error-reporting inline COM wrapper reached from
// Begin_Scene_Inner's enter and leave edges.  The browser dispatch object is
// shared with the WOL wrapper family; this view only supplies the slot that
// this body actually calls.
extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);

// The interface id this dispatch reports: the data ledger's GUID at
// 0x007D4E3C (WebBrowserComCreateInstance.cpp).
extern GUID g_bfmeIidTSA;

class Rva00958D30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0c;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1c;
		void *slot20;
		void *slot24;
		void *slot28;
		void *slot2c;
		void *slot30;
		void *slot34;
		void *slot38;
		long (__stdcall *slot3c)(Rva00958D30 *self);
	};

	long invoke()
	{
		long result = vtable->slot3c(this);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this,
				g_bfmeIidTSA);
		return result;
	}

	Vtable *vtable;
};

// The dispatch object: the data ledger's g_bfmeObjECF at 0x009F7040
// (BfmeConv804.cpp), read through this unit's Rva00958D30 view.
struct BfmeObjECF;
extern BfmeObjECF *g_bfmeObjECF;

// ?bfmeDebugTouch009588e0@@YAXXZ
__declspec(noinline) void bfmeDebugTouch009588e0(void)
{
	if (g_bfmeObjECF)
		((Rva00958D30 *)g_bfmeObjECF)->invoke();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
#include "DX8WrapperClass.h"

// Retail's D3D call counter: the data ledger's number_of_DX8_calls
// (dx8wrapper.cpp), a plain global.
extern unsigned number_of_DX8_calls;

// ?Begin_Scene_Inner@DX8Wrapper@@SAXXZ
void DX8Wrapper::Begin_Scene_Inner(void)
{
	bfmeDebugTouch009588e0();
	DEVICE9->BeginScene();
	++number_of_DX8_calls;
	bfmeDebugTouch009588e0();
}

// Retail 0x0011D2D0 (87 B), between Begin_Scene_Inner and Clear: when a
// device exists, fetch back buffer 0 (GetBackBuffer, vtable +0x48), lock it
// (LockRect +0x34, flags 0x800 = D3DLOCK_NOSYSLOCK), unlock it if the
// lock succeeded (+0x38) and release the surface (+0x08). A lock of the back
// buffer stalls until the GPU has drained, so this reads as a frame sync.
// It has no direct caller or data reference and no Zero Hour counterpart:
// the name is address-derived.
void DX8Wrapper::Rva0011D2D0WaitForBackBuffer(void)
{
	if (D3DDevice) {
		IDirect3DSurface9 *surface = 0;
		if (DEVICE9->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface) >= 0) {
			D3DLOCKED_RECT locked;
			if (surface->LockRect(&locked, 0, D3DLOCK_NOSYSLOCK) >= 0) {
				surface->UnlockRect();
			}
			surface->Release();
		}
	}
}
