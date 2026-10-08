// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118BA0@@YAXXZ @ 0x00118BA0 (118B): conditional render state always DB5FBC 7 then Has_Stencil true zeroes DEC4A4 DEC4A0 DB5FC0 with DEC4A8 2 DB5FC4 1 DB5FB0 from DB5FB4 else copies float BBB8D8 to BfmeRender2DZ with DEC4A8 0 DEC4A4 0 DEC4A0 1 DB5FC0 0 DB5FC4 1. Evidence: unlock lane siblings Rva00118B50 Rva00118C20 same flags G7 SSE Has_Stencil row callers 0xA5A56 0x1116C6 unblocks 0xA56ED.
extern int g_Va00DB5FBC;
extern int g_Va00DB5FC0;
extern int g_Va00DB5FC4;
extern int g_Va00DB5FB4;
extern int g_00DB5FB0;
extern unsigned int g_Va00DEC4A8;
extern unsigned int g_Va00DEC4A4;
extern unsigned int g_Va00DEC4A0;
extern float g_Va00BBB8D8;
extern "C" float g_BfmeRender2DZ;

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
};

void Rva00118BA0(void)
{
	if (DX8Wrapper::Has_Stencil()) {
		g_Va00DB5FBC = 7;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 0;
		g_Va00DB5FC0 = 0;
		int tmp = g_Va00DB5FB4;
		g_Va00DEC4A8 = 2;
		g_Va00DB5FC4 = 1;
		g_00DB5FB0 = tmp;
	} else {
		g_Va00DB5FBC = 7;
		float tmpF = g_Va00BBB8D8;
		g_Va00DEC4A8 = 0;
		g_Va00DEC4A4 = 0;
		g_Va00DEC4A0 = 1;
		g_Va00DB5FC0 = 0;
		g_Va00DB5FC4 = 1;
		g_BfmeRender2DZ = tmpF;
	}
}
