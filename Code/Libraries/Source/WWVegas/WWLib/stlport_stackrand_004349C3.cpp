// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva004349C3Get@@YAXPAI0@Z @0x004349C3 44B: sibling of 0x00434969 same stack-seeded two-out shape; tables at 0x00DC8A7C/0x00DC8A6C; unblocks 0x00434D7A caller 0x00434D8A.
// g_00DC8A7C: matched references place it at VA 0xdc8a7c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A7C[4] = {
	92914507, 4220229963, 3165996875, 3653876043,
};
// g_00DC8A6C: matched references place it at VA 0xdc8a6c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A6C[4] = {
	1160368398, 3146484494, 2828866830, 3586763534,
};
void __cdecl Rva004349C3Get(unsigned *a, unsigned *b)
{
	// inline asm is a proven codegen blocker here: plain C++ x=(unsigned)&x emits
	// lea eax,[ebp-4]; mov [ebp-4],eax (volatile) or lea eax,[ebp+8] (plain),
	// never retail's mov [ebp-4],esp. __asm mov x,esp emits it byte-exact (see 0x00434969).
	unsigned x = 0;
	__asm mov x, esp
	unsigned idx = (x & 3);
	*a = g_00DC8A7C[idx];
	*b = g_00DC8A6C[idx];
}
