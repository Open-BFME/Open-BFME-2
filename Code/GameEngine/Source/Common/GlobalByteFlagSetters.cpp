// Global byte flag setters: eight-byte frameless helpers with one shape:
//
//     mov byte ptr [<address>],1 / ret
//
// One global byte is set to 1. MSVC 7.1 emits `C6 05 ADDR 01` plus `C3`
// for eight bytes total. Identity is not recovered: every name is derived
// from its address, with the SetFlag verb describing the store.
// No // cl: line (defaults match the frameless eight-byte shape).
// Each address is one zero-filled .data/bss byte in the retail image.
unsigned char g_Va00E0302C;
unsigned char g_Va00E1770C;

void Rva004128E8SetFlag(void)
{
	g_Va00E0302C = 1;
}
void Rva006CD200SetFlag(void)
{
	g_Va00E1770C = 1;
}
