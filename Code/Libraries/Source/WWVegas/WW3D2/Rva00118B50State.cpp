// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118B50@@YAXXZ @ 0x00118B50 (68B): conditional float plus triple stores
// call ?Has_Stencil@DX8Wrapper@@SA_NXZ; test al,al;
// mov [0x00DB5FC4],5; mov [0x00DB5FC0],2; mov [0x00DB5FBC],7; jne;
// xorps xmm0,xmm0; movss [0x00DEC49C],xmm0; xor eax,eax;
// mov [0x00DEC4A8],eax; mov [0x00DEC4A4],eax; mov [0x00DEC4A0],eax; ret.
// Always sets the three DB5F ints to 5,2,7 and zeroes the three DEC4A dwords;
// zeroes the float at DEC49C only when Has_Stencil is false. The three movs
// sit between test and jne (mov preserves flags) via /G7 scheduling. Callee
// Has_Stencil is rowed in dx8wrapper.cpp. Prev 0x00118A90/36 ?Rva00118A90
// (Rva00118A90Stencil.cpp // cl: /O1) and next 0x00118CA0/11 ?free@Rva00118CA0
// are our own landings in the same 00118xxx page; boundary proven by ret plus
// int3 pad (ghidra 68 matches true 68). Callers are 2 calls in UNCLAIMED
// FUN_004a56ed and FUN_00511319. Identity unproven so the function keeps an
// honest Rva name. Flags: /G7 gives cmp/test plus add scheduling and
// /arch:SSE gives xorps plus movss for the 0.0f store (defaults give mov plus
// test and x87 or integer zeroing).
extern int g_Va00DB5FC4;
extern int g_Va00DB5FC0;
extern int g_Va00DB5FBC;
extern float g_Va00DEC49C;
extern unsigned int g_Va00DEC4A8;
extern unsigned int g_Va00DEC4A4;
extern unsigned int g_Va00DEC4A0;

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
};

void Rva00118B50(void)
{
	if (DX8Wrapper::Has_Stencil()) {
		g_Va00DB5FBC = 7;
		g_Va00DB5FC0 = 2;
		g_Va00DB5FC4 = 5;
	} else {
		g_Va00DB5FBC = 7;
		g_Va00DB5FC0 = 2;
		g_Va00DB5FC4 = 5;
		g_Va00DEC49C = 0.0f;
	}
	g_Va00DEC4A8 = 0;
	g_Va00DEC4A4 = 0;
	g_Va00DEC4A0 = 0;
}

// ?g_Va00DEC49C@@3MA: matched references place it at VA 0xdec49c; also referenced as _g_BfmeRender2DZ.
float g_Va00DEC49C;
#pragma comment(linker, "/alternatename:_g_BfmeRender2DZ=?g_Va00DEC49C@@3MA")
