// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118810@@YAXXZ 0x00118810 129 unlock DX8 render-state setup via Set_DX8_Render_State caller 0x00155AD0
class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
};
extern int g_00DEC4A8;
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

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DEC4A8@@3HA=?g_Va00DEC4A8@@3IA")
