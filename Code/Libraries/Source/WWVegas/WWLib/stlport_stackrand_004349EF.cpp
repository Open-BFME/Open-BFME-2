// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva004349EFGet@@YAXPAI0@Z @0x004349EF 46B: rdtsc-seeded two-out table fetch sibling of 0x00434995; tables at 0x00DC8A9C/0x00DC8A8C; unblocks 0x00434E07 caller 0x00434E17.
// g_00DC8A8C: matched references place it at VA 0xdc8a8c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A8C[4] = {
	2723132174, 3752270798, 637426574, 397760014,
};
// The matched fetch masks the low counter bits with 3, selecting these four
// DWORDs; the values match the 16-byte .data window at VA 0x00DC8A9C.
unsigned g_00DC8A9C[4] = {
	0xA26FA14B, 0x972F098B, 0x61D649CB, 0x47B1144B,
};
void __cdecl Rva004349EFGet(unsigned *a, unsigned *b)
{
	unsigned x = 0;
	__asm rdtsc
	__asm mov x, eax
	unsigned idx = (x & 3);
	*a = g_00DC8A9C[idx];
	*b = g_00DC8A8C[idx];
}
