// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva00434969Get@@YAXPAI0@Z @0x00434969 44B: two-out stack-seeded table fetch indexed by low 2 bits of stack address; tables at 0x00DC8A3C/0x00DC8A2C; unblocks 0x00434C67 caller pushes ebp-4/ebp-8.
// g_00DC8A3C: matched references place it at VA 0xdc8a3c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A3C[4] = {
	2536442251, 1641433547, 1202787403, 1455541579,
};
// g_00DC8A2C: matched references place it at VA 0xdc8a2c; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned g_00DC8A2C[4] = {
	3752270798, 637426574, 397760014, 440508174,
};
void __cdecl Rva00434969Get(unsigned *a, unsigned *b)
{
	// inline asm is a proven codegen blocker here: plain C++ x=(unsigned)&x emits
	// lea eax,[ebp-4]; mov [ebp-4],eax (volatile) or lea eax,[ebp+8] (plain),
	// never retail's mov [ebp-4],esp. __asm mov x,esp emits it byte-exact.
	unsigned x = 0;
	__asm mov x, esp
	unsigned idx = (x & 3);
	*a = g_00DC8A3C[idx];
	*b = g_00DC8A2C[idx];
}
