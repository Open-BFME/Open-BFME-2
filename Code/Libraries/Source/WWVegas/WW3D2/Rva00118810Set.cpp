// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118810@@YAXXZ 0x00118810 129 unlock DX8 render-state setup via Set_DX8_Render_State caller 0x00155AD0
#include "DX8WrapperClass.h"
extern unsigned int g_Va00DEC4A8;
#define g_00DEC4A8 g_Va00DEC4A8
// Native RVA 0x009B5FB0 is a mutable four-byte render-state value initially
// equal to 1. Rva00118BA0 and Rva00118C20 write it; this setup reads it for
// state 0x39. Retain the established symbol as their single storage owner.
int g_00DB5FB0 = 1;
void __cdecl Rva00118810()
{
	if (g_00DEC4A8 == 0)
		return;
	DX8Wrapper::Set_DX8_Render_State(0x34, 1);
	DX8Wrapper::Set_DX8_Render_State(0x39, g_00DB5FB0);
	DX8Wrapper::Set_DX8_Render_State(0x3a, -1);
	DX8Wrapper::Set_DX8_Render_State(0x3b, -1);
	DX8Wrapper::Set_DX8_Render_State(0x36, 1);
	DX8Wrapper::Set_DX8_Render_State(0x35, 1);
	if (g_00DEC4A8 == 2)
	{
		DX8Wrapper::Set_DX8_Render_State(0x38, 8);
		DX8Wrapper::Set_DX8_Render_State(0x37, 3);
		return;
	}
	if (g_00DEC4A8 == 1)
	{
		DX8Wrapper::Set_DX8_Render_State(0x38, 3);
		DX8Wrapper::Set_DX8_Render_State(0x37, 1);
		return;
	}
}
