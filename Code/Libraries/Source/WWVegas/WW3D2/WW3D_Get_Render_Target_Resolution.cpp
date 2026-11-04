// cl: /DNDEBUG /MD /EHsc /G7
// dxsdk
// platformsdk
//
// ?Get_Render_Target_Resolution@DX8Wrapper@@KAXAAH00AA_N@Z, retail 0x00121860,
// 195 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/WW3D_Get_Render_Target_Resolution.cpp):
// SEH frame with a scope guard around the device branch (lock in the
// constructor, release in the destructor). The device virtual at slot 0x30
// fills the mode struct at esp+4 (width at +0x18, height at +0x1C); both
// exits share the bit-depth and windowed globals. BFME2 globals and the
// DX8 lock pair replace the reference names; every global rides a DIR32
// relocation copied from retail.

#include <stddef.h>
#include <d3d9.h>

typedef int Int;
typedef bool Bool;

void BFME_DX8_Thread_Lock(void); // retail 0x0011F520
bool BFME_DX8_Thread_Assert(void); // retail 0x00120F50

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// The render target surface. DX8Wrapper keeps the BFME 1 spelling of the
// member; the native object is a Direct3D 9 surface, whose GetDesc (vtable
// +0x30) fills the D3DSURFACE_DESC on the stack (Width +0x18, Height +0x1C).
struct IDirect3DSurface8;

// the WW3D forwarder lives at 0x00116FF0 (5B thunk, already claimed);
// this TU recovers the DX8Wrapper body it jumps to (private static, hence
// the CAX mangling). The globals it reads are DX8Wrapper's protected static
// members, defined in dx8wrapper.cpp.
class DX8Wrapper
{
	static void Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed);
protected:
	static IDirect3DSurface8 *CurrentRenderTarget; // 0x00DEDA38
	static Int ResolutionWidth;                    // 0x00DB5FD4
	static Int ResolutionHeight;                   // 0x00DB5FD8
	static Int BitDepth;                           // 0x00DB5FDC
	static Bool IsWindowed;                        // 0x00DEDA06
};

// ?Get_Render_Target_Resolution@DX8Wrapper@@CAXAAH00AA_N@Z
void DX8Wrapper::Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed)
{
	if (CurrentRenderTarget != NULL)
	{
		BFMEDX8DeviceLock guard;
		D3DSURFACE_DESC info;

		reinterpret_cast<IDirect3DSurface9 *>(CurrentRenderTarget)->GetDesc(&info);

		width = info.Width;
		height = info.Height;
		bitDepth = BitDepth;
		windowed = IsWindowed;
	}
	else
	{
		width = ResolutionWidth;
		height = ResolutionHeight;
		bitDepth = BitDepth;
		windowed = IsWindowed;
	}
}
