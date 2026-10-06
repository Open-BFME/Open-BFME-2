// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva00434995Get@@YAXPAI0@Z @0x00434995 46B: sibling of 0x00434969/0x004349C3 but rdtsc-seeded two-out table fetch; tables at 0x00DC8A5C/0x00DC8A4C; unblocks 0x00434CF4 caller 0x00434D04.
// g_00DC8A5C: matched references place it at VA 0xdc8a5c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A5C[4] = {
	1662712139, 92914507, 4220229963, 3165996875,
};
// g_00DC8A4C: matched references place it at VA 0xdc8a4c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A4C[4] = {
	1738205966, 1160368398, 3146484494, 2828866830,
};
void __cdecl Rva00434995Get(unsigned *a, unsigned *b)
{
	unsigned x = 0;
	__asm rdtsc
	__asm mov x, eax
	unsigned idx = (x & 3);
	*a = g_00DC8A5C[idx];
	*b = g_00DC8A4C[idx];
}
