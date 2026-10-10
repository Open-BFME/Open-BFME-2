// cl: /O2 /G6 /Z7 /MD
// Clean room: reverse/vp6_cleanroom/specs/001d89c0.md plus retail only.
// No decoder source was consulted. Native 1D89C0..1D8A21, cdecl, no frame:
// DC-only inverse transform for the SSE2 path. Multiply the first four input
// and table words, add 15, shift right 5, broadcast lane 0 and store the
// 16-byte vector eight times.
//
// Inline asm is used because compiler intrinsics cannot reproduce it: the
// intrinsic form (_mm_loadl_epi64 / _mm_mullo_epi16 / _mm_srai_epi16 /
// _mm_unpacklo_*) compiles to 108 bytes with an ebp frame and an aligned-stack
// prologue under /O2 and /Z7, where retail is a frameless 98-byte leaf that
// alternates xmm0/xmm1 for the stores. Recorded in reverse/re_attempts.log.
extern "C" void __cdecl Wmt_idct1(const short *input, const short *table, short *output)
{
	__asm {
		mov eax, input
		mov edx, 15
		movd xmm2, edx
		mov ecx, table
		mov edx, output
		movq xmm0, qword ptr [eax]
		movq xmm1, qword ptr [ecx]
		pmullw xmm0, xmm1
		paddw xmm0, xmm2
		psraw xmm0, 5
		punpcklwd xmm0, xmm0
		punpckldq xmm0, xmm0
		punpcklqdq xmm0, xmm0
		movdqa xmm1, xmm0
		movdqa [edx], xmm0
		movdqa [edx+10h], xmm1
		movdqa [edx+20h], xmm0
		movdqa [edx+30h], xmm1
		movdqa [edx+40h], xmm0
		movdqa [edx+50h], xmm1
		movdqa [edx+60h], xmm0
		movdqa [edx+70h], xmm1
	}
}
