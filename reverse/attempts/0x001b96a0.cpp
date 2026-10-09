// _UpdateUMVBorder
// partial score=0.8 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b96a0.md plus retail only.
// NEAR (not exact): UpdateUMVBorder retail 0x001B96A0..0x001B9AB6 (1047
// bytes). Same block structure (inlined memset/memcpy rep stos/movs; the
// border copy loops address the bottom rows as top + invariant difference;
// halved border via shr; UV stride and UV rows kept for V) but this body
// compiles to 1055 bytes: MSVC loads the buffer argument first into ECX
// and keeps the border in EDX where retail keeps the buffer in EAX and the
// border in ECX (and the left source pointer in ESI) so registers rotate
// throughout. Tried: increment orders / declaration orders / separate
// halved border / width local / single row pointer / unsigned border /
// local buffer copy / flag variants (/G5 /G7 /Ox /O1 /Oy-).
struct Vp6BorderInstance {
	unsigned char unknown0[0x78];
	int ReconYDataOffset;
	int ReconUDataOffset;
	int ReconVDataOffset;
	unsigned char unknown84[0x90 - 0x84];
	int HFragments;
	int VFragments;
	int YStride;
	int UVStride;
	unsigned char unknownA0[0xb4 - 0xa0];
	int MVBorder;
};
extern "C" void *memset(void *, int, unsigned);
extern "C" void *memcpy(void *, const void *, unsigned);
#pragma intrinsic(memset, memcpy)
extern "C" void UpdateUMVBorder(Vp6BorderInstance *pbi, unsigned char *buffer)
{
	int i;
	int rows;
	int border = pbi->MVBorder;
	int stride = pbi->YStride;
	unsigned char *srcLeft, *srcRight, *dstLeft, *dstRight;
	unsigned char *src, *last, *dstTop, *dstBottom;

	rows = pbi->VFragments * 8;
	srcLeft = buffer + pbi->ReconYDataOffset;
	srcRight = srcLeft + pbi->HFragments * 8 - 1;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], border);
		memset(dstRight, srcRight[0], border);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + border * stride;
	last = src + (pbi->VFragments * 8 - 1) * stride;
	dstTop = buffer;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}

	stride = pbi->UVStride;
	rows = pbi->VFragments * 4;
	border = (unsigned)border / 2;
	srcLeft = buffer + pbi->ReconUDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], border);
		memset(dstRight, srcRight[0], border);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + pbi->ReconUDataOffset - border;
	last = src + (pbi->VFragments * 4 - 1) * stride;
	dstTop = src - border * stride;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}

	srcLeft = buffer + pbi->ReconVDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], border);
		memset(dstRight, srcRight[0], border);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + pbi->ReconVDataOffset - border;
	last = src + (pbi->VFragments * 4 - 1) * stride;
	dstTop = src - border * stride;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}
}
