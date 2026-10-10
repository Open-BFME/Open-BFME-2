// cl: /O2 /G6 /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7df0.md plus retail only.
// No decoder source was consulted. Native 1D7DF0..1D7FC0, cdecl, ebp frame
// with a 256-byte block buffer: picks the 2-tap (bilinear) or 4-tap (bicubic)
// sub-pixel filter from the distance between the two reference pointers. The
// bicubic path widens its byte block to int16 into the output with an SSE2
// inline asm loop; the bilinear path lets the callees write int16 directly.
// Filter banks: bilinear at 0x00DB84E0 (32 bytes per phase), bicubic at
// 0x00DB85E0 (64 bytes per phase), both inside the 768-byte table that
// Rva009C7380BinkSse.cpp owns.
#include <emmintrin.h>

extern const unsigned char g_00DB84E0[];

#define BILINEAR_BANK(phase) (g_00DB84E0 + (phase) * 32)
#define BICUBIC_BANK(phase) (g_00DB84E0 + 0x100 + (phase) * 64)

void __cdecl rva009C6F20BinkSse(const void *, void *, int, int, int, int, const void *);
void __cdecl rva009C6FC0BinkSse(const void *, void *, int, int, int, int, const void *);
void __cdecl rva009C7490BinkSse(const unsigned char *, unsigned char *, int, const void *, const void *);
void __cdecl rva009C72C0BinkSse(const void *, void *, int, int, int, int, const void *);
void __cdecl rva009C7320BinkSse(const void *, void *, int, int, int, int, const void *);
void __cdecl rva009C7200BinkSse(const void *, void *, int, const void *, const void *);

extern "C" void __cdecl FilterBlock_wmt(const unsigned char *a, const unsigned char *b, short *out, int pixelsPerLine, int horizontalPhase, int verticalPhase, int bicubic)
{
	unsigned char block[256];
	int diff = b - a;
	if (diff < 0) {
		const unsigned char *t = a;
		a = b;
		b = t;
		diff = b - a;
	}
	if (diff == 0)
		return;
	if (bicubic) {
		if (diff == 1)
			rva009C6F20BinkSse(a, block, pixelsPerLine, 1, 8, 8, BICUBIC_BANK(horizontalPhase));
		else if (diff == pixelsPerLine)
			rva009C6FC0BinkSse(a, block, pixelsPerLine, pixelsPerLine, 8, 8, BICUBIC_BANK(verticalPhase));
		else if (diff == pixelsPerLine - 1)
			rva009C7490BinkSse(a - 1, block, pixelsPerLine, BICUBIC_BANK(horizontalPhase), BICUBIC_BANK(verticalPhase));
		else if (diff == pixelsPerLine + 1)
			rva009C7490BinkSse(a, block, pixelsPerLine, BICUBIC_BANK(horizontalPhase), BICUBIC_BANK(verticalPhase));
		{
			int srcStride = 8;
			const unsigned char *src = block;
			__asm {
				mov edi, out
				mov esi, src
				mov ecx, 8
				mov eax, 16
				pxor xmm0, xmm0
			again:
				movdqu xmm3, [esi]
				punpcklbw xmm3, xmm0
				movdqu [edi], xmm3
				add esi, srcStride
				add edi, eax
				dec ecx
				jne again
			}
		}
		return;
	}
	if (diff == 1)
		rva009C72C0BinkSse(a, out, pixelsPerLine, 1, 8, 16, BILINEAR_BANK(horizontalPhase));
	else if (diff == pixelsPerLine)
		rva009C7320BinkSse(a, out, pixelsPerLine, pixelsPerLine, 8, 16, BILINEAR_BANK(verticalPhase));
	else if (diff == pixelsPerLine - 1)
		rva009C7200BinkSse(a - 1, out, pixelsPerLine, BILINEAR_BANK(horizontalPhase), BILINEAR_BANK(verticalPhase));
	else if (diff == pixelsPerLine + 1)
		rva009C7200BinkSse(a, out, pixelsPerLine, BILINEAR_BANK(horizontalPhase), BILINEAR_BANK(verticalPhase));
}
