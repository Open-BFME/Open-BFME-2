// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118BA0@@YAXXZ @ 0x00118BA0 (118B): conditional render state always DB5FBC 7 then Has_Stencil true zeroes DEC4A4 DEC4A0 DB5FC0 with DEC4A8 2 DB5FC4 1 DB5FB0 from DB5FB4 else copies float BBB8D8 to BfmeRender2DZ with DEC4A8 0 DEC4A4 0 DEC4A0 1 DB5FC0 0 DB5FC4 1. Evidence: unlock lane siblings Rva00118B50 Rva00118C20 same flags G7 SSE Has_Stencil row callers 0xA5A56 0x1116C6 unblocks 0xA56ED.
extern int G00DB5FBC;
extern int G00DB5FC0;
extern int G00DB5FC4;
extern int g_Va00DB5FB4;
extern int g_00DB5FB0;
extern unsigned int g_Va00DEC4A8;
extern unsigned int g_Va00DEC4A4;
extern unsigned int g_Va00DEC4A0;
extern float g_Va00BBB8D8;
extern float g_Va00DEC49C;

#include "DX8WrapperClass.h"

void Rva00118BA0(void)
{
	if (DX8Wrapper::Has_Stencil()) {
		G00DB5FBC = 7;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 0;
		G00DB5FC0 = 0;
		int tmp = g_Va00DB5FB4;
		g_Va00DEC4A8 = 2;
		G00DB5FC4 = 1;
		g_00DB5FB0 = tmp;
	} else {
		G00DB5FBC = 7;
		float tmpF = g_Va00BBB8D8;
		g_Va00DEC4A8 = 0;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 1;
		G00DB5FC0 = 0;
		G00DB5FC4 = 1;
		g_Va00DEC49C = tmpF;
	}
}
