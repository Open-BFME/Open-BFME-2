// ?Rva009ADAA0@@YAXPAURva009AF200Context@@PAE1IIHPBI@Z
// partial score=0.91 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001be490.md plus retail only.
// No decoder source was consulted.
// ?Rva009ADAA0@@YAXPAURva009AF200Context@@PAE1IIHPBI@Z retail
// 0x001BE490..0x001BE76A (730 bytes) cdecl; spec name
// DeblockVerticalEdgesInNonFilteredBandNewFilter and the pinned name is
// kept (the matched band driver copyPlane009AF0D0 calls it with this
// signature). The quantizer step is the scale-table entry for the frame Q
// index (0x0C) and the activity limit is step squared times 3 shifted
// right 5. For each of the across - 1 vertical edges (the first 8 pixels
// into the band) and each of the 8 lines ten source samples straddle the
// edge. When both sums of neighbour differences (four per side) are below
// the limit and the edge step is below the quantizer step in both
// directions the eight run samples take the flat 3 + 2 + 3 sum (rounded
// shift by 3) with the outer samples five before and four after the edge
// standing in outside the run; otherwise only the two edge samples move by
// the bounding entry (centre pointer 0x38) through g_bfmeClampTable.

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x38 - 0x10];
	int *m_bounding;
};

extern const unsigned char g_bfmeClampTable[];

#define VP6_ABS(v) ((v) > 0 ? (v) : -(v))

void __cdecl Rva009ADAA0(Rva009AF200Context *ctx, unsigned char *src, unsigned char *dst,
	unsigned int step, unsigned int across, int index, const unsigned int *table)
{
	int qStep;
	int limit;
	unsigned int i;
	int j, k;
	unsigned char *s;
	unsigned char *d;
	int x[10];
	int left, right, sum, filter;

	qStep = table[ctx->m_tableIndex];
	for (i = index; i < index + across - 1; i++) {
		limit = (qStep * qStep * 3) >> 5;
		s = src + 8 * (i - index) + 8;
		d = dst + 8 * (i - index) + 8;
		for (j = 0; j < 8; j++) {
			x[0] = s[-5];
			x[1] = s[-4];
			x[2] = s[-3];
			x[3] = s[-2];
			x[4] = s[-1];
			x[5] = s[0];
			x[6] = s[1];
			x[7] = s[2];
			x[8] = s[3];
			x[9] = s[4];
			left = 0;
			for (k = 0; k < 4; k++)
				left += VP6_ABS(x[k + 1] - x[k]);
			right = 0;
			for (k = 0; k < 4; k++)
				right += VP6_ABS(x[k + 5] - x[k + 6]);
			if (left < limit && right < limit && x[5] - x[4] < qStep && x[4] - x[5] < qStep) {
				sum = x[0] + x[0] + x[0] + x[1] + x[2] + x[3] + x[4] + 4;
				d[-4] = (unsigned char)((sum + x[1]) >> 3);
				sum += x[5] - x[0];
				d[-3] = (unsigned char)((sum + x[2]) >> 3);
				sum += x[6] - x[0];
				d[-2] = (unsigned char)((sum + x[3]) >> 3);
				sum += x[7] - x[0];
				d[-1] = (unsigned char)((sum + x[4]) >> 3);
				sum += x[8] - x[1];
				d[0] = (unsigned char)((sum + x[5]) >> 3);
				sum += x[9] - x[2];
				d[1] = (unsigned char)((sum + x[6]) >> 3);
				sum += x[9] - x[3];
				d[2] = (unsigned char)((sum + x[7]) >> 3);
				sum += x[9] - x[4];
				d[3] = (unsigned char)((sum + x[8]) >> 3);
			} else {
				filter = ctx->m_bounding[(x[3] - x[6] + 3 * (x[5] - x[4]) + 4) >> 3];
				d[-1] = g_bfmeClampTable[x[4] + filter];
				d[0] = g_bfmeClampTable[x[5] - filter];
			}
			s += step;
			d += step;
		}
	}
}
