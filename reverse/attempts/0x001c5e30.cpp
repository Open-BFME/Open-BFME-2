// ?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z
// partial score=0.87 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5e30.md plus retail only.
// No decoder source was consulted.
// ?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z retail
// 0x001C5E30..0x001C6130 (768 bytes) cdecl (decoder instance / 16-bit
// output block / block position 0..5); spec name VP6_PredictFilteredBlock
// and the pinned name is kept (the matched caller 0x001C6130 declares it).
// The source frame is the golden one (0x24C) when the mode (0x08) maps to
// frame 2 in g_bfmeVp6SelectorMap (read as dwords) else the last recon
// frame (0x254). With a profile (0x19D) and a loop filter mode (0x4534) the
// loop-filtered builder 0x001D8DD0 fills the 16-stride buffer at 0x290 and
// both offsets start at 34; otherwise the block moves by the whole-pel part
// of its vector (0x24 + 4 * block; mask 0x80 / shift 0x7C / frame stride
// 0x88 / recon index 0x70 / stride 0x74). The second offset steps one pixel
// and one line towards the vector's fractional part; equal offsets unpack
// the block through slot 0x00E22D18 and anything else filters it through
// slot 0x00E22D1C with doubled luma phases and a bicubic flag from the
// prediction filter mode (0x692) size threshold (0x693) and variance
// threshold (0x694 via 0x001D8A30). Chroma always uses bilinear.

extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)

struct Rva009C84D0Vp6Context;

struct Rva009B5830MotionVector
{
	short x;
	short y;
};

struct Rva009B5830State
{
	unsigned char pad0[8];
	int mode;
	unsigned char padC[0x24 - 0x0c];
	Rva009B5830MotionVector vectors[6];
	unsigned char pad3c[0x70 - 0x3c];
	int reconIndex;
	int reconStride;
	unsigned char pad78[0x7c - 0x78];
	int vectorShift;
	int vectorMask;
	unsigned char pad84[0x88 - 0x84];
	int frameStride;
	unsigned char pad8c[0x19d - 0x8c];
	unsigned char profile;
	unsigned char pad19e[0x24c - 0x19e];
	unsigned char *goldenFrame;
	unsigned char pad250[0x254 - 0x250];
	unsigned char *lastFrame;
	unsigned char pad258[0x290 - 0x258];
	unsigned char *loopFilteredBlock;
	unsigned char pad294[0x692 - 0x294];
	unsigned char filterMode;
	unsigned char sizeThreshold;
	unsigned int varianceThreshold;
	unsigned char pad698[0x4534 - 0x698];
	unsigned char loopFilterMode;
};

typedef void (__cdecl *Rva009B5530Filter)(unsigned char *, unsigned char *, void *,
	int, int, int, int);
typedef void (__cdecl *Rva009B5530Unpack)(unsigned char *, void *, int);

extern void *g_bfmeSlotB50;
extern void *g_bfmeSlotB54;
extern unsigned char g_bfmeVp6SelectorMap[40];
void Rva009C84D0Vp6Filter(Rva009C84D0Vp6Context *, void *, int, int);
int rva009C8130(const unsigned char *, int);

void __cdecl Rva009B5530Prepare(Rva009B5830State *pbi, void *output, int block)
{
	unsigned char *source;
	unsigned char *base;
	int stride;
	int offset1;
	int offset2;
	int xPhase;
	int yPhase;
	short mvx;
	short mvy;
	int x;
	int y;
	unsigned int limit;
	int mask;

	source = pbi->lastFrame;
	mask = pbi->vectorMask;
	if (((const int *)g_bfmeVp6SelectorMap)[pbi->mode] == 2)
		source = pbi->goldenFrame;

	if (pbi->profile != 0 && pbi->loopFilterMode != 0) {
		Rva009C84D0Vp6Filter((Rva009C84D0Vp6Context *)pbi, source + pbi->reconIndex,
			pbi->vectors[block].x, pbi->vectors[block].y);
		mvx = pbi->vectors[block].x;
		mvy = pbi->vectors[block].y;
		x = mvx;
		y = mvy;
		xPhase = x & pbi->vectorMask;
		yPhase = y & pbi->vectorMask;
		base = pbi->loopFilteredBlock;
		stride = 16;
		offset1 = 34;
		offset2 = 34;
	} else {
		mvx = pbi->vectors[block].x;
		mvy = pbi->vectors[block].y;
		x = mvx;
		y = mvy;
		xPhase = x & mask;
		yPhase = y & mask;
		base = source + pbi->reconIndex
			+ pbi->frameStride * ((y + ((y >> 31) & mask)) >> pbi->vectorShift)
			+ ((x + ((x >> 31) & mask)) >> pbi->vectorShift);
		stride = pbi->reconStride;
		offset1 = 0;
		offset2 = 0;
	}

	if (xPhase != 0)
		offset2 += (mvx > 0) * 2 - 1;
	if (yPhase != 0)
		offset2 += ((mvy > 0) * 2 - 1) * stride;

	if (offset1 != offset2) {
		if (block < 4) {
			xPhase <<= 1;
			yPhase <<= 1;
			if (pbi->profile == 0) {
				((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
					output, stride, xPhase, yPhase, 0);
			} else if (pbi->filterMode == 2) {
				if (pbi->sizeThreshold > 0)
					limit = (1 << (pbi->sizeThreshold - 1)) << 2;
				else
					limit = 128;
				if (pbi->sizeThreshold != 0 && (abs(x) > limit || abs(y) > limit)) {
					((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
						output, stride, xPhase, yPhase, 0);
				} else if (pbi->varianceThreshold != 0) {
					((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
						output, stride, xPhase, yPhase,
						rva009C8130(base + offset1, stride) >= pbi->varianceThreshold);
				} else {
					((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
						output, stride, xPhase, yPhase, 1);
				}
			} else {
				((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
					output, stride, xPhase, yPhase, pbi->filterMode == 1);
			}
		} else {
			((Rva009B5530Filter)g_bfmeSlotB54)(base + offset1, base + offset2,
				output, stride, xPhase, yPhase, 0);
		}
	} else {
		((Rva009B5530Unpack)g_bfmeSlotB50)(base + offset1, output, stride);
	}
}
