// cl: /O2 /G6 /MD
// Native 000AC63F..000AC6A6, cdecl: MMX lane blend used by the terrain tile
// blender (callee of the matched WorldHeightMap blendTile at 0x000ADDCE). For
// each of `count` four-byte pixels it computes
//   (source * alpha - destination * (alpha - 255)) >> 8, saturated to bytes,
// with the alpha taken from a 16-bit stride and stepped by two bytes.
//
// Inline asm because intrinsics cannot reproduce it: the intrinsic form
// compiles to 124 bytes with extra MOVQ copies and allocates mm0..mm4,
// where retail fixes mm7 (zero), mm6 (0x01010101 lane constant) and mm5 and
// loads through ordinary GPRs. Recorded in reverse/re_attempts.log.
void __cdecl Rva000AC63FBlendPixels(unsigned char *source, unsigned char *destination, unsigned char *alpha, int count)
{
	__asm {
		mov esi, source
		mov edi, destination
		mov edx, alpha
		mov ecx, count
		pxor mm7, mm7
		mov eax, 01010101h
		movd mm6, eax
		mov eax, 0FFFFFFFFh
		movd mm5, eax
		punpcklbw mm6, mm5
	again:
		movd mm0, [esi]
		movd mm1, [edi]
		punpcklbw mm0, mm7
		punpcklbw mm1, mm7
		movzx eax, byte ptr [edx]
		movd mm2, eax
		punpcklwd mm2, mm2
		punpcklwd mm2, mm2
		pmullw mm0, mm2
		paddw mm2, mm6
		pmullw mm2, mm1
		psubw mm0, mm2
		psrlw mm0, 8
		packuswb mm0, mm0
		movd [edi], mm0
		add esi, 4
		add edi, 4
		add edx, 2
		dec ecx
		jne again
		emms
	}
}
