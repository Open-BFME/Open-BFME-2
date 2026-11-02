// cl: C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Rva00118AC0@@YAXXZ
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118AC0@@YAXXZ @ 0x00118AC0 (138B): stencil-gated Clear unlock.
// Sets the unlock flag, and when Has_Stencil (rowed in dx8wrapper.cpp) is true
// decrements the gate counter 0x00DB5FB4, wrapping to 0xFF when it drops below
// one, leaving early unless the counter now reads 0xFF; then issues a
// stencil-only Clear. When Has_Stencil is false it issues a z+stencil Clear.
// Sibling lane landings: Rva00118A90Stencil / Rva00118BA0State.
// The predecrement form `--g_Va00DB5FB4` is load-bearing: `g - 1` makes VC7.1
// emit `add eax,0xFFFFFFFF` where retail emits `sub eax,1`.
// WWMath's Vector3 is a class with three float components. The native
// 0x11D330 Clear provider consumes this same 12B view (class-tagged ABI).
#include "../WWMath/Vector3Data.h"

#include "DX8WrapperClass.h"
extern unsigned char g_Va00DB5FB8;
extern int g_Va00DB5FB4;
void __cdecl Rva00118AC0()
{
	g_Va00DB5FB8 = 1;
	if (DX8Wrapper::Has_Stencil())
	{
		int v = --g_Va00DB5FB4;
		if (v < 1)
			g_Va00DB5FB4 = 0xff;
		else if (v != 0xff)
			return;
		Vector3 black(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(false, false, true, black, 0.0f, 0.0f, 0);
	}
	else
	{
		Vector3 black(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(false, true, true, black, 0.0f, 0.0f, 0);
	}
}
