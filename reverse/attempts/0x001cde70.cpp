// _ClampLevels_mmx
// partial score=0.9 date=2026-10-10
// _ClampLevels_mmx
// partial score=0.9
// 232B (size exact) with the /Z7 realigned frame, C vector splats and an inline MMX row loop; 25 lines differ only in register choice/scheduling:
// retail delays the dst row store and loads white into EAX where cl loads it into ECX. ~70 declaration-order and parameter-type variants unchanged.
// cl: /O2 /G6 /Z7 /MD
struct Vp6PostProc
{
	unsigned char pad0[0x78];
	int lumaOffset;
	unsigned char pad7C[0x90 - 0x7C];
	int blocksAcross;
	int blocksDown;
	int stride;
};

extern "C" void __cdecl ClampLevels_mmx(Vp6PostProc *pp, int black, int white, unsigned char *src, unsigned char *dst)
{
	__declspec(align(8)) unsigned char blackVec[16];
	__declspec(align(8)) unsigned char whiteVec[16];
	__declspec(align(8)) unsigned char bothVec[16];
	int width = pp->blocksAcross * 8;
	unsigned char *srcRow = src + pp->lumaOffset;
	unsigned char *dstRow = dst + pp->lumaOffset;
	int height = pp->blocksDown * 8;
	int stride = pp->stride;
	int rows;
	int i;

	unsigned char blackByte = (unsigned char)black;
	unsigned char whiteByte = (unsigned char)white;
	unsigned char sumByte = whiteByte + blackByte;
	for (i = 0; i < 8; i++)
		bothVec[i] = sumByte;
	for (i = 0; i < 8; i++)
		whiteVec[i] = whiteByte;
	for (i = 0; i < 8; i++)
		blackVec[i] = blackByte;
	if (height > 0) {
		for (rows = height; rows; rows--) {
			__asm {
				mov ecx, width
				mov esi, srcRow
				mov edi, dstRow
				xor eax, eax
			again:
				movq mm1, [esi+eax]
				psubusb mm1, qword ptr blackVec
				paddusb mm1, qword ptr bothVec
				psubusb mm1, qword ptr whiteVec
				movq [edi+eax], mm1
				add eax, 8
				cmp eax, ecx
				jl again
			}
			srcRow += stride;
			dstRow += stride;
		}
	}
}
