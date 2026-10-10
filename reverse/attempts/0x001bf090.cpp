// _DeblockNonFilteredBandNewFilter_C
// partial score=0.23 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bf090.md plus retail only.
// No decoder source was consulted.
// NEAR score=0.23 (structure only; ours 2020 bytes vs 2107)
// _DeblockNonFilteredBandNewFilter_C retail 0x001BF090..0x001BF8CB (2107
// bytes) cdecl; generic dispatch slot 21 (declared Rva009AE6A0 there).
// Same pointer IVs as retail (src / src-3p / src+p / dst-4p / dst+2p) but
// frame 0x88 vs 0x98: retail spills qStep and limit to slots and keeps the
// 10-sample array at 0x28; retail forms the -5p offset as p - 5p (5p only
// materialised after the entry test) where this draft folds it to -4p.

struct Vp6DeblockBandNewInstance
{
	unsigned char m_pad00[0x0C];
	int m_frameQIndex;
	unsigned char m_pad10[0x28 - 0x10];
	int *m_variance;
	unsigned char m_pad2c[0x38 - 0x2c];
	int *m_bounding;
};

extern const unsigned char g_bfmeClampTable[];
#define VABS(x) ((x) > 0 ? (x) : -(x))

extern "C" void __cdecl DeblockNonFilteredBandNewFilter_C(Vp6DeblockBandNewInstance *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, unsigned int first, const unsigned int *limits)
{
	unsigned int index;
	int x[10];
	int upper, lower, sum, filter;
	int qStep, limit;
	unsigned int row;
	int k;
	unsigned char *s;
	unsigned char *rowInput, *rowOutput;
	qStep = limits[ctx->m_frameQIndex];
	index = first;
	int p2 = 2 * stride;
	int p3 = 3 * stride;
	int p4 = 4 * stride;
	for (; index < first + count; ++index) {
		rowInput = source + 8 * (index - first);
		limit = (qStep * 3) >> 2;
		rowOutput = destination + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			x[0] = rowInput[-5 * (int)stride];
			x[1] = rowInput[-p4];
			x[2] = rowInput[-p3];
			x[3] = rowInput[-p2];
			x[4] = rowInput[-(int)stride];
			x[5] = rowInput[0];
			x[6] = rowInput[stride];
			x[7] = rowInput[p2];
			x[8] = rowInput[p3];
			x[9] = rowInput[p4];
			upper = 0;
			for (k = 0; k < 4; k++)
				upper += VABS(x[k + 1] - x[k]);
			lower = 0;
			for (k = 0; k < 4; k++)
				lower += VABS(x[k + 5] - x[k + 6]);
			ctx->m_variance[index] += upper > 255 ? 255 : upper;
			ctx->m_variance[index + count] += lower > 255 ? 255 : lower;
			if (upper < limit && lower < limit && x[5] - x[4] < qStep && x[4] - x[5] < qStep) {
				sum = x[4] + 3 * x[0] + x[3] + x[2] + 4 + x[1];
				rowOutput[-p4] = (unsigned char)((sum + x[1]) >> 3);
				sum += x[5] - x[0];
				rowOutput[-p3] = (unsigned char)((sum + x[2]) >> 3);
				sum += x[6] - x[0];
				rowOutput[-p2] = (unsigned char)((sum + x[3]) >> 3);
				sum += x[7] - x[0];
				rowOutput[-(int)stride] = (unsigned char)((sum + x[4]) >> 3);
				sum += x[8] - x[1];
				rowOutput[0] = (unsigned char)((sum + x[5]) >> 3);
				sum += x[9] - x[2];
				rowOutput[stride] = (unsigned char)((sum + x[6]) >> 3);
				sum += x[9] - x[3];
				rowOutput[p2] = (unsigned char)((sum + x[7]) >> 3);
				sum += x[9] - x[4];
				rowOutput[p3] = (unsigned char)((sum + x[8]) >> 3);
			} else {
				filter = ctx->m_bounding[(x[3] - x[6] + 3 * (x[5] - x[4]) + 4) >> 3];
				rowOutput[-(int)stride] = g_bfmeClampTable[x[4] + filter];
				rowOutput[0] = g_bfmeClampTable[x[5] - filter];
				rowOutput[-p4] = rowInput[-p4];
				rowOutput[-p3] = rowInput[-p3];
				rowOutput[-p2] = rowInput[-p2];
				rowOutput[stride] = rowInput[stride];
				rowOutput[p2] = rowInput[p2];
				rowOutput[p3] = rowInput[p3];
			}
			rowInput++;
			rowOutput++;
		}
		if (index == first)
			continue;
		rowInput = rowOutput = destination - 8 * stride + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			x[0] = rowInput[-5];
			x[1] = rowInput[-4];
			x[2] = rowInput[-3];
			x[3] = rowInput[-2];
			x[4] = rowInput[-1];
			x[5] = rowInput[0];
			x[6] = rowInput[1];
			x[7] = rowInput[2];
			x[8] = rowInput[3];
			x[9] = rowInput[4];
			upper = 0;
			for (k = 0; k < 4; k++)
				upper += VABS(x[k + 1] - x[k]);
			lower = 0;
			for (k = 0; k < 4; k++)
				lower += VABS(x[k + 5] - x[k + 6]);
			ctx->m_variance[index - 1] += upper > 255 ? 255 : upper;
			ctx->m_variance[index] += lower > 255 ? 255 : lower;
			if (upper < limit && lower < limit && x[5] - x[4] < qStep && x[4] - x[5] < qStep) {
				sum = x[4] + 3 * x[0] + x[3] + x[2] + 4 + x[1];
				rowOutput[-4] = (unsigned char)((sum + x[1]) >> 3);
				sum += x[5] - x[0];
				rowOutput[-3] = (unsigned char)((sum + x[2]) >> 3);
				sum += x[6] - x[0];
				rowOutput[-2] = (unsigned char)((sum + x[3]) >> 3);
				sum += x[7] - x[0];
				rowOutput[-1] = (unsigned char)((sum + x[4]) >> 3);
				sum += x[8] - x[1];
				rowOutput[0] = (unsigned char)((sum + x[5]) >> 3);
				sum += x[9] - x[2];
				rowOutput[1] = (unsigned char)((sum + x[6]) >> 3);
				sum += x[9] - x[3];
				rowOutput[2] = (unsigned char)((sum + x[7]) >> 3);
				sum += x[9] - x[4];
				rowOutput[3] = (unsigned char)((sum + x[8]) >> 3);
			} else {
				filter = ctx->m_bounding[(x[3] - x[6] + 3 * (x[5] - x[4]) + 4) >> 3];
				rowOutput[-1] = g_bfmeClampTable[x[4] + filter];
				rowOutput[0] = g_bfmeClampTable[x[5] - filter];
			}
			rowInput += stride;
			rowOutput += stride;
		}
	}
}
