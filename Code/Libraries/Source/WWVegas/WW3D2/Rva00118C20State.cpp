// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118C20@@YAXXZ @ 0x00118C20 (116B): conditional render state sets DB5FC4 5 DB5FC0 2 always then Has_Stencil true sets DEC4A4 0 DEC4A0 0 DEC4A8 1 DB5FBC 7 DB5FB0 from DB5FB4 else copies float VA007C26F0 to BfmeRender2DZ and zeroes DEC4A8 4A4 4A0 with DB5FBC 3. Evidence: unlock lane prev Rva00118B50 pattern flags G7 arch SSE Has_Stencil row callers 0xA5A9E 0x1116D2 unblocks 0xA56ED.
extern int G00DB5FC4;
extern int G00DB5FC0;
extern int G00DB5FBC;
extern int g_Va00DB5FB4;
extern int g_00DB5FB0;
extern unsigned int g_Va00DEC4A8;
extern unsigned int g_Va00DEC4A4;
extern unsigned int g_Va00DEC4A0;
extern float g_Va007C26F0;
extern float g_Va00DEC49C;

#include "DX8WrapperClass.h"

void Rva00118C20(void)
{
	if (DX8Wrapper::Has_Stencil()) {
		G00DB5FC0 = 2;
		G00DB5FC4 = 5;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 0;
		int tmp = g_Va00DB5FB4;
		g_Va00DEC4A8 = 1;
		G00DB5FBC = 7;
		g_00DB5FB0 = tmp;
	} else {
		G00DB5FC0 = 2;
		G00DB5FC4 = 5;
		g_Va00DEC49C = g_Va007C26F0;
		g_Va00DEC4A8 = 0;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 0;
		G00DB5FBC = 3;
	}
}
