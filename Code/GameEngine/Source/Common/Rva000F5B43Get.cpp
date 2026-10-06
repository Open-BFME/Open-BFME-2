// cl: /MD
// ?Rva000F5B43Get@@YAHXZ @0x000F5B43 19B; two-global init.
// Retail: xor eax,eax / inc eax / mov [0x00DE1F28],0x00DB5A34 / mov [0x00DE1F20],eax / ret.
// Target facts: sets data 0x009E1F28 to data 0x009B5A34 and data 0x009E1F20 to 1 then returns 1.
// Callers: none; callees: none.
// Not established: owning TU/class and global identities; names are address-derived.
extern unsigned int g_Va00DE1F28;
// g_Va00DE1F28: matched references place it at VA 0xde1f28 (zero-filled .bss).
unsigned int g_Va00DE1F28;
extern unsigned int g_Va00DE1F20;
// g_Va00DE1F20: matched references place it at VA 0xde1f20 (zero-filled .bss).
unsigned int g_Va00DE1F20;

int Rva000F5B43Get(void)
{
	g_Va00DE1F28 = 0x00DB5A34;
	g_Va00DE1F20 = 1;
	return 1;
}
