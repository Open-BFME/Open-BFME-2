// cl: /O2 /G6 /DNDEBUG /MD
// Clean-room recovery of retail 001BF090..001BF8CB (2107 bytes).
// Approved spec: reverse/vp6_cleanroom/specs/001bf090.md; retail evidence only.
// The post-processor view and the clamp-table origin follow the spec.
// All ten samples are captured before output stores; the final input sample
// stays live through activity calculation and flat smoothing. The rolling sum
// is assigned before each use, with no unnecessary loop-entry initialization.
// Whole bytes/relocations and differential execution are recorded under
// reverse/attempt_support/deblock-newfilter-exact-20261019/.

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

extern "C" void __cdecl DeblockNonFilteredBandNewFilter_C(Vp6DeblockBandNewInstance *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, unsigned int first, const unsigned int *limits)
{
	unsigned int index;
	int samples[10];
	int k;
	int upper, lower, sum, filter;
	int qStep, limit;
	unsigned int row;
	unsigned char *rowInput, *rowOutput;
	index = first;
	int twoStride = 2 * stride;
	int threeStride = 3 * stride;
	int fourStride = 4 * stride;
	int fiveStride = 5 * stride;
	qStep = limits[ctx->m_frameQIndex];
	while (index < first + count) {
		rowInput = source + 8 * (index - first);
		rowOutput = destination + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			samples[0] = rowInput[-fiveStride];
			samples[1] = rowInput[-fourStride];
			samples[2] = rowInput[-threeStride];
			samples[3] = rowInput[-twoStride];
			samples[4] = rowInput[-(int)stride];
			samples[5] = rowInput[0];
			samples[6] = rowInput[stride];
			samples[7] = rowInput[twoStride];
			samples[8] = rowInput[threeStride];
			samples[9] = rowInput[fourStride];
			int tailSample = samples[9];
			upper = lower = 0;
			for (k = 0; k < 4; k++) {
				upper += (samples[k + 1] - samples[k]) > 0 ? (samples[k + 1] - samples[k]) : (samples[k] - samples[k + 1]);
			}
			for (k = 0; k < 4; k++) {
				lower += (samples[k + 5] - samples[k + 6]) > 0 ? (samples[k + 5] - samples[k + 6]) : (samples[k + 6] - samples[k + 5]);
			}
			ctx->m_variance[index] += upper > 255 ? 255 : upper;
			ctx->m_variance[index + count] += lower > 255 ? 255 : lower;
			limit = ((qStep * 3) >> 2);
			if (upper < limit && lower < limit && samples[5] - samples[4] < qStep && samples[4] - samples[5] < qStep) {
				sum = samples[4] + 3 * samples[0] + samples[3] + samples[2] + 4 + samples[1];
				rowOutput[-fourStride] = (unsigned char)((sum + samples[1]) >> 3);
				sum += samples[5] - samples[0];
				rowOutput[-threeStride] = (unsigned char)((sum + samples[2]) >> 3);
				sum += samples[6] - samples[0];
				rowOutput[-twoStride] = (unsigned char)((sum + samples[3]) >> 3);
				sum += samples[7] - samples[0];
				rowOutput[-(int)stride] = (unsigned char)((sum + samples[4]) >> 3);
				sum += samples[8] - samples[1];
				rowOutput[0] = (unsigned char)((sum + samples[5]) >> 3);
				sum += tailSample - samples[2];
				rowOutput[stride] = (unsigned char)((sum + samples[6]) >> 3);
				sum += tailSample - samples[3];
				rowOutput[twoStride] = (unsigned char)((sum + samples[7]) >> 3);
				sum += tailSample - samples[4];
				rowOutput[threeStride] = (unsigned char)((sum + samples[8]) >> 3);
			} else {
				const unsigned char *clamp = g_bfmeClampTable;
				filter = ctx->m_bounding[(samples[3] - samples[6] + 3 * (samples[5] - samples[4]) + 4) >> 3];
				rowOutput[-(int)stride] = clamp[samples[4] + filter];
				rowOutput[0] = clamp[samples[5] - filter];
				rowOutput[-fourStride] = rowInput[-fourStride];
				rowOutput[-threeStride] = rowInput[-threeStride];
				rowOutput[-twoStride] = rowInput[-twoStride];
				rowOutput[stride] = rowInput[stride];
				rowOutput[twoStride] = rowInput[twoStride];
				rowOutput[threeStride] = rowInput[threeStride];
			}
			rowInput++;
			rowOutput++;
		}
		if (index == first) {
			index++;
			continue;
		}
		{
		unsigned int secondOffset = index - first;
		rowInput = rowOutput = destination - 8 * stride + 8 * secondOffset;
		}
		for (row = 0; row < 8; ++row) {
			samples[0] = rowInput[-5];
			samples[1] = rowInput[-4];
			samples[2] = rowInput[-3];
			samples[3] = rowInput[-2];
			samples[4] = rowInput[-1];
			samples[5] = rowInput[0];
			samples[6] = rowInput[1];
			samples[7] = rowInput[2];
			samples[8] = rowInput[3];
			samples[9] = rowInput[4];
			upper = lower = 0;
			for (k = 0; k < 4; k++) {
				upper += (samples[k + 1] - samples[k]) > 0 ? (samples[k + 1] - samples[k]) : (samples[k] - samples[k + 1]);
			}
			for (k = 0; k < 4; k++) {
				lower += (samples[k + 5] - samples[k + 6]) > 0 ? (samples[k + 5] - samples[k + 6]) : (samples[k + 6] - samples[k + 5]);
			}
			ctx->m_variance[index - 1] += upper > 255 ? 255 : upper;
			ctx->m_variance[index] += lower > 255 ? 255 : lower;
			limit = (qStep * 3) >> 2;
			if (upper < limit && lower < limit && samples[5] - samples[4] < qStep && samples[4] - samples[5] < qStep) {
				int a0 = samples[0], a1 = samples[1], a2 = samples[2], a3 = samples[3];
				int a4 = samples[4], a5 = samples[5], a6 = samples[6], a7 = samples[7];
				int a8 = samples[8], a9 = samples[9];
				sum = a4 + 3 * a0 + a3 + a2 + 4 + a1;
				rowOutput[-4] = (unsigned char)((sum + a1) >> 3);
				sum += a5 - a0;
				rowOutput[-3] = (unsigned char)((sum + a2) >> 3);
				sum += a6 - a0;
				rowOutput[-2] = (unsigned char)((sum + a3) >> 3);
				sum += a7 - a0;
				rowOutput[-1] = (unsigned char)((sum + a4) >> 3);
				sum += a8 - a1;
				rowOutput[0] = (unsigned char)((sum + a5) >> 3);
				sum += a9 - a2;
				rowOutput[1] = (unsigned char)((sum + a6) >> 3);
				sum += a9 - a3;
				rowOutput[2] = (unsigned char)((sum + a7) >> 3);
				sum += a9 - a4;
				rowOutput[3] = (unsigned char)((sum + a8) >> 3);
			} else {
				filter = ctx->m_bounding[(samples[3] - samples[6] + 3 * (samples[5] - samples[4]) + 4) >> 3];
				rowOutput[-1] = g_bfmeClampTable[samples[4] + filter];
				rowOutput[0] = g_bfmeClampTable[samples[5] - filter];
			}
			rowInput += stride;
			rowOutput += stride;
		}
		index++;
	}
}
