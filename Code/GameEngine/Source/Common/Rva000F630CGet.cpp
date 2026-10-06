// cl: /MD
// ?Rva000F630CGet@@YAHXZ @0x000F630C 20B; two-global availability check.
// Retail: xor eax,eax / cmp [0x009E1F64],eax / je ret / cmp [0x009E1F6C],eax / je ret / inc eax / ret.
// Target facts: reads VA 0x009E1F64 and VA 0x009E1F6C, returns 1 only when both are nonzero.
// Callers test al (0x000FD4B3 0x000FDCD7 0x000FB9D4 0x000F9D94 0x000FA935); callees: none.
// Not established: owning TU/class and global identities; names are address-derived.
extern unsigned int g_Va009E1F64;
// g_Va009E1F64: matched references place it at VA 0xde1f64 (zero-filled .bss).
unsigned int g_Va009E1F64;
extern unsigned int g_Va009E1F6C;
// g_Va009E1F6C: matched references place it at VA 0xde1f6c (zero-filled .bss).
unsigned int g_Va009E1F6C;

int Rva000F630CGet(void)
{
	return (g_Va009E1F64 && g_Va009E1F6C) ? 1 : 0;
}
