// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00118990@@YAXXZ @ 0x00118990 (48B): global initializer with xor-first
// xor eax,eax; mov [0x00DEC4A8],eax; mov [0x00DEC4A4],eax;
// mov [0x00DEC4A0],eax; mov [0x00DB5FBC],7; mov [0x00DB5FC0],2;
// mov [0x00DB5FC4],5; ret. Zeroes three DEC4A globals via the xorred eax and
// sets three DB5F globals to 7,2,5. No calls so the gate has no REL32 to
// resolve. Prev 0x001188C0/202 ?Set_Coordinate_Range@Render2DClass
// (render2d.cpp) and next 0x00118CA0/11 ?free@Rva00118CA0 (just landed) are
// different files so not a gap; boundary proven by ret (ghidra 48 correct;
// true 245 reaches the next ledger row across unclaimed code). Callers are
// 2 calls in UNCLAIMED FUN_004a8f98 and FUN_004a9071. Identity unproven so the
// function keeps an honest Rva name. Flags: /O1 is load-bearing for the
// xor-first triple store (defaults would still use xor here but /O1 documents
// the size-optimal triple reuse per the HasFlag shard precedent).
extern unsigned int g_Va00DEC4A8;
extern unsigned int g_Va00DEC4A4;
// g_Va00DEC4A4: matched references place it at VA 0xdec4a4 (zero-filled .bss).
unsigned int g_Va00DEC4A4;
extern unsigned int g_Va00DEC4A0;
// g_Va00DEC4A0: matched references place it at VA 0xdec4a0 (zero-filled .bss).
unsigned int g_Va00DEC4A0;
extern int g_Va00DB5FBC;
// g_Va00DB5FBC: matched references place it at VA 0xdb5fbc (retail .data initial value 7).
int g_Va00DB5FBC = 7;
extern int g_Va00DB5FC0;
// g_Va00DB5FC0: matched references place it at VA 0xdb5fc0 (retail .data initial value 2).
int g_Va00DB5FC0 = 2;
extern int g_Va00DB5FC4;
// g_Va00DB5FC4: matched references place it at VA 0xdb5fc4 (retail .data initial value 5).
int g_Va00DB5FC4 = 5;

void Rva00118990(void)
{
	g_Va00DEC4A8 = 0;
	g_Va00DEC4A4 = 0;
	g_Va00DEC4A0 = 0;
	g_Va00DB5FBC = 7;
	g_Va00DB5FC0 = 2;
	g_Va00DB5FC4 = 5;
}

// ?rva00118A15@@YAXXZ @ 0x00118A15 (11B). State setter for the
// DB5FC4 global above: stores 5 (its .data initial value) then ret. No
// callers found. Honest address name.
void rva00118A15(void)
{
	g_Va00DB5FC4 = 5;
}

// ?rva00118A45@@YAXXZ @ 0x00118A45 (11B). State setter for the
// DB5FC4 global above: stores 1 then ret. No callers found. Honest address
// name.
void rva00118A45(void)
{
	g_Va00DB5FC4 = 1;
}

// ?rva00118A7A@@YAXXZ @ 0x00118A7A (11B). State setter for the
// DB5FC4 global above: stores 5 then ret. No callers found. Honest address
// name.
void rva00118A7A(void)
{
	g_Va00DB5FC4 = 5;
}
