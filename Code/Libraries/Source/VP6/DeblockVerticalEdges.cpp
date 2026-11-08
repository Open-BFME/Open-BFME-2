// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001be140.md plus retail only.
// No decoder source was consulted.
// _DeblockVerticalEdgesInNonFilteredBand retail 0x001BE140..0x001BE490
// (848 bytes) cdecl (post-processor instance / source band / destination
// band / line step / fragments across / first fragment index / 64-entry
// scale table); reached only through the address DeblockPlane
// (0x001BF8D0) stores at 0x001BF8ED so it keeps its plain C name. For each
// of the across - 1 vertical edges (the first 8 pixels into the band) the
// quantizer step is the scale entry for the right fragment's Q index
// (0x24) and the spread limit is step squared times 3 shifted right 5.
// Each of the 8 lines forms the four-sample spread measure on both sides
// and adds it to the two fragments' accumulators (0x28). Below the limit
// on both sides with a small edge step the eight run samples take the
// 1 1 2 2 4 2 2 1 1 sum over sixteen with the guards one beyond the run
// (kept only when within the step); otherwise the two edge samples move by
// the bounding entry (centre pointer 0x38) through g_bfmeClampTable. The
// loop-filtered sibling at 0x001BD670 (DeblockVerticalEdgesLoopFiltered.cpp) is the same
// walk without the second branch and supplies the shape.

struct Rva009AD750Context
{
	unsigned char m_pad00[0x24];
	unsigned int *m_tableIndex;
	int *m_variance;
	unsigned char m_pad2c[0x38 - 0x2c];
	int *m_bounding;
};

extern unsigned char g_bfmeClampTable[];

extern "C" void __cdecl DeblockVerticalEdgesInNonFilteredBand(Rva009AD750Context *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, int first, const unsigned int *limits)
{
	unsigned int index;
	int samples[10];
	int sumLeft, sumRight, varianceLeft, varianceRight, rolling;
	int limit, varianceLimit, filter;
	unsigned char *rowInput, *rowOutput;
	for (index = first; index < first + count - 1; ++index) {
		limit = limits[ctx->m_tableIndex[index + 1]];
		rowInput = source + 8 * (index - first + 1);
		varianceLimit = (limit * limit * 3) >> 5;
		rowOutput = destination + 8 * (index - first + 1);
		for (unsigned int row = 0; row < 8; ++row) {
			samples[1] = rowInput[-4];
			samples[2] = rowInput[-3];
			samples[3] = rowInput[-2];
			samples[4] = rowInput[-1];
			samples[5] = rowInput[0];
			samples[6] = rowInput[1];
			samples[7] = rowInput[2];
			samples[8] = rowInput[3];
			sumLeft = sumRight = varianceLeft = varianceRight = 0;
			for (unsigned int k = 1; k <= 4; ++k) {
				sumLeft += samples[k];
				varianceLeft += samples[k] * samples[k];
				sumRight += samples[k + 4];
				varianceRight += samples[k + 4] * samples[k + 4];
			}
			varianceLeft -= ((sumLeft + 1) >> 1) * (sumLeft >> 1);
			varianceRight -= ((sumRight + 1) >> 1) * (sumRight >> 1);
			ctx->m_variance[index] += varianceLeft;
			ctx->m_variance[index + 1] += varianceRight;
			if (varianceLeft < varianceLimit && varianceRight < varianceLimit && samples[5] - samples[4] < limit && samples[4] - samples[5] < limit) {
				int left;
				if (((rowInput[-4] - rowInput[-5]) > 0 ? (rowInput[-4] - rowInput[-5]) : (rowInput[-5] - rowInput[-4])) < limit) left = rowInput[-5];
				else left = rowInput[-4];
				int right;
				if (((rowInput[3] - rowInput[4]) > 0 ? (rowInput[3] - rowInput[4]) : (rowInput[4] - rowInput[3])) < limit) right = rowInput[4];
				else right = rowInput[3];
				rolling = samples[4] + 3*left + samples[3] + samples[2] + 4 + samples[1];
				rowOutput[-4] = (unsigned char)(((rolling+samples[1])*2-samples[4]+samples[5])>>4);
				rolling += samples[5]-left;
				rowOutput[-3] = (unsigned char)(((rolling+samples[2])*2-samples[5]+samples[6])>>4);
				rolling += samples[6]-left;
				rowOutput[-2] = (unsigned char)(((rolling+samples[3])*2-samples[6]+samples[7])>>4);
				rolling += samples[7]-left;
				rowOutput[-1] = (unsigned char)(((rolling+samples[4])*2-samples[7]-samples[1]+left+samples[8])>>4);
				rolling += samples[8]-samples[1];
				rowOutput[0] = (unsigned char)(((rolling+samples[5])*2-samples[8]-samples[2]+right+samples[1])>>4);
				rolling += right-samples[2];
				rowOutput[1] = (unsigned char)(((rolling+samples[6])*2-samples[3]+samples[2])>>4);
				rolling += right-samples[3];
				rowOutput[2] = (unsigned char)(((rolling+samples[7])*2-samples[4]+samples[3])>>4);
				rowOutput[3] = (unsigned char)(((rolling+right+samples[8])*2-samples[5] - samples[4])>>4);
			} else {
				filter = ctx->m_bounding[(samples[3] - samples[6] + 3 * (samples[5] - samples[4]) + 4) >> 3];
				rowOutput[-1] = g_bfmeClampTable[samples[4] + filter];
				rowOutput[0] = g_bfmeClampTable[samples[5] - filter];
			}
			rowInput += stride;
			rowOutput += stride;
		}
	}
}

// _DeblockVerticalEdgesInNonFilteredBandNewFilter retail
// 0x001BE490..0x001BE76A (730 bytes) cdecl. Clean room:
// reverse/vp6_cleanroom/specs/001be490.md plus retail only. The matched band
// driver DeblockPlaneNew calls it directly. The quantizer step is the scale-table entry for the frame Q
// index (0x0C) and the activity limit is step squared times 3 shifted
// right 5. For each of the across - 1 vertical edges (the first 8 pixels
// into the band) and each of the 8 lines ten source samples straddle the
// edge. When both sums of neighbour differences (four per side) are below
// the limit and the edge step is below the quantizer step in both
// directions the eight run samples take the flat 3 + 2 + 3 sum (rounded
// shift by 3) with the outer samples five before and four after the edge
// standing in outside the run; otherwise only the two edge samples move by
// the bounding entry (centre pointer 0x38) through g_bfmeClampTable. The
// outer right sample is read once into a scalar for the last three window
// steps: retail keeps every x[] load after the preceding store there.

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x38 - 0x10];
	int *m_bounding;
};

#define VP6_ABS(v) ((v) > 0 ? (v) : -(v))

extern "C" void __cdecl DeblockVerticalEdgesInNonFilteredBandNewFilter(Rva009AF200Context *ctx, unsigned char *src, unsigned char *dst,
	unsigned int step, unsigned int across, int index, const unsigned int *table)
{
	int qStep;
	int limit;
	unsigned int i;
	int j, k;
	unsigned char *s;
	unsigned char *d;
	int x[10];
	int outerRight;
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
				outerRight = x[9];
				sum += outerRight - x[2];
				d[1] = (unsigned char)((sum + x[6]) >> 3);
				sum += outerRight - x[3];
				d[2] = (unsigned char)((sum + x[7]) >> 3);
				sum += outerRight - x[4];
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
