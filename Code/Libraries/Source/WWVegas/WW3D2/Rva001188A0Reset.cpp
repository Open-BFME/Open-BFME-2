// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva001188A0@@YAXXZ @ 0x001188A0 (22B): conditional DX8 render-state reset
// cmp dword [0x00DEC4A8],0; je; push 0; push 0x34; call
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z; add esp,8; ret. Sets state 0x34 to
// 0 when the global at 0x00DEC4A8 is nonzero. Callee is rowed in
// DX8WrapperSetDX8States.cpp. Prev 0x00118800/12 ??1TextureStatisticsStruct
// (TextureStatisticsVector.cpp) and next 0x001188C0/202
// ?Set_Coordinate_Range@Render2DClass (render2d.cpp) are different files so not
// a gap; boundary proven by ret plus int3 pad (ghidra 22 matches true 22).
// Caller is a jmp at 0x00155AFA in UNCLAIMED FUN_00555AD0. Identity unproven so
// the function keeps an honest Rva name. Flags: base /O2 plus /G7 is
// load-bearing (defaults give mov eax plus test while /O1 gives pop-pop for
// the 8-byte cleanup; /G7 gives cmp plus add exact).
extern unsigned int g_Va00DEC4A8;
// g_Va00DEC4A8: matched references place it at VA 0xdec4a8 (zero-filled .bss).
unsigned int g_Va00DEC4A8;

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
};

void Rva001188A0(void)
{
	if (g_Va00DEC4A8 != 0) {
		DX8Wrapper::Set_DX8_Render_State(0x34, 0);
	}
}
