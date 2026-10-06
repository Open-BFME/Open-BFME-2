// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118A90@@YAXXZ @ 0x00118A90 (36B): conditional stencil flag reset
// cmp byte [0x00DB5FB8],0; je; call ?Has_Stencil@DX8Wrapper@@SA_NXZ;
// test al,al; je; mov dword [0x00DB5FB4],0x100; mov byte [0x00DB5FB8],0; ret.
// When the flag byte is set it queries Has_Stencil (rowed in dx8wrapper.cpp)
// and stores 0x100 on true then clears the flag. Prev 0x00118990/48
// ?Rva00118990 (Rva00118990Init.cpp // cl: /O1) and next 0x00118CA0/11
// ?free@Rva00118CA0 (Rva00118CA0Free.cpp defaults) are our own landings in the
// same 00118xxx page; boundary proven by ret plus int3 pad (ghidra 36 matches
// true 36). Caller is 1 call at 0x0008FF15 in UNCLAIMED FUN_0048ff12. Identity
// unproven so the function keeps an honest Rva name. Flags: /O1 is load-bearing
// for the cmp-byte guard (defaults give mov al plus test).
extern unsigned char g_Va00DB5FB8;
// g_Va00DB5FB8: matched references place it at VA 0xdb5fb8 (retail .data initial value 1).
unsigned char g_Va00DB5FB8 = 1;
extern int g_Va00DB5FB4;
// g_Va00DB5FB4: matched references place it at VA 0xdb5fb4 (retail .data initial value 256).
int g_Va00DB5FB4 = 256;

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
};

void Rva00118A90(void)
{
	if (g_Va00DB5FB8 == 0)
		return;
	if (DX8Wrapper::Has_Stencil()) {
		g_Va00DB5FB4 = 0x100;
	}
	g_Va00DB5FB8 = 0;
}
