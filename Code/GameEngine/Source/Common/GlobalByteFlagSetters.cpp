// Global byte flag setters: eight-byte frameless helpers with one shape:
//
//     mov byte ptr [<address>],1 / ret
//
// One global byte is set to 1. MSVC 7.1 emits `C6 05 ADDR 01` plus `C3`
// for eight bytes total. Identity is not recovered: every name is derived
// from its address, with the SetFlag verb describing the store.
// No // cl: line (defaults match the frameless eight-byte shape).
void Rva0031AB77SetFlag(void)
{
	*(volatile unsigned char *)0x00E01D0C = 1;
}
