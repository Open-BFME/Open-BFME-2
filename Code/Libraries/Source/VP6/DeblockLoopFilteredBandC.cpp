// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bd980.md plus retail only.
// No decoder source was consulted.
//
// DeblockLoopFilteredBand_C (retail 0x001BD980, 1976 bytes): generic band
// deblocker for the loop-filtered profile. Pass 1 filters the horizontal
// edge at the top of the band column by column (q from the fragment below
// the edge), writing the source band to the destination; pass 2 filters the
// vertical edges between adjacent fragments in place on the destination one
// band up (q from the right-hand fragment). Each side's spread measure is
// accumulated into the per-fragment variance array, and a line is smoothed
// only when both measures are under the limit and the edge step is under q.

struct Vp6LoopFilteredBandInstance
{
	unsigned char m_pad00[0x24];
	unsigned int *m_tableIndex;
	int *m_variance;
};

extern "C" void __cdecl DeblockLoopFilteredBand_C(Vp6LoopFilteredBandInstance *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, unsigned int first, const unsigned int *limits)
{
	unsigned int index;
	int samples[10];
	int sumLeft, sumRight, varianceLeft, varianceRight, rolling;
	int limit, varianceLimit;
	int left, right;
	unsigned int row;
	unsigned char *rowInput, *rowOutput;
	index = first;
	int rowOffset1 = stride;
	int p2 = 2 * stride;
	int p3 = 3 * stride;
	int p4 = 4 * stride;
	int p5 = 5 * stride;
	for (; index < first + count; ++index) {
		rowInput = source + 8 * (index - first);
		limit = limits[ctx->m_tableIndex[index + count]];
		varianceLimit = (limit * limit * 3) >> 5;
		rowOutput = destination + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			samples[1] = rowInput[-p4];
			samples[2] = rowInput[-p3];
			samples[3] = rowInput[-p2];
			samples[4] = rowInput[-rowOffset1];
			samples[5] = rowInput[0];
			samples[6] = rowInput[stride];
			samples[7] = rowInput[p2];
			samples[8] = rowInput[p3];
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
			ctx->m_variance[index + count] += varianceRight;
			if (varianceLeft < varianceLimit && varianceRight < varianceLimit && samples[5] - samples[4] < limit && samples[4] - samples[5] < limit) {
				if (((rowInput[-p4] - rowInput[-p5]) > 0 ? (rowInput[-p4] - rowInput[-p5]) : (rowInput[-p5] - rowInput[-p4])) < limit) left = rowInput[-p5];
				else left = rowInput[-p4];
				if (((rowInput[p3] - rowInput[p4]) > 0 ? (rowInput[p3] - rowInput[p4]) : (rowInput[p4] - rowInput[p3])) < limit) right = rowInput[p4];
				else right = rowInput[p3];
				rolling = samples[4] + 3*left + samples[3] + samples[2] + 4 + samples[1];
				rowOutput[-p4] = (unsigned char)(((rolling+samples[1])*2-samples[4]+samples[5])>>4);
				rolling += samples[5]-left;
				rowOutput[-p3] = (unsigned char)(((rolling+samples[2])*2-samples[5]+samples[6])>>4);
				rolling += samples[6]-left;
				rowOutput[-p2] = (unsigned char)(((rolling+samples[3])*2-samples[6]+samples[7])>>4);
				rolling += samples[7]-left;
				rowOutput[-(int)stride] = (unsigned char)(((rolling+samples[4])*2-samples[7]-samples[1]+left+samples[8])>>4);
				rolling += samples[8]-samples[1];
				rowOutput[0] = (unsigned char)(((rolling+samples[5])*2-samples[8]-samples[2]+right+samples[1])>>4);
				rolling += right-samples[2];
				rowOutput[stride] = (unsigned char)(((rolling+samples[6])*2-samples[3]+samples[2])>>4);
				rolling += right-samples[3];
				rowOutput[p2] = (unsigned char)(((rolling+samples[7])*2-samples[4]+samples[3])>>4);
				rowOutput[p3] = (unsigned char)(((rolling+right+samples[8])*2-samples[5] - samples[4])>>4);
			} else {
				rowOutput[-p4] = rowInput[-p4];
				rowOutput[-p3] = rowInput[-p3];
				rowOutput[-p2] = rowInput[-p2];
				rowOutput[-(int)stride] = rowInput[-(int)stride];
				rowOutput[0] = rowInput[0];
				rowOutput[stride] = rowInput[stride];
				rowOutput[p2] = rowInput[p2];
				rowOutput[p3] = rowInput[p3];
			}
			rowInput++;
			rowOutput++;
		}
	}
	for (index = first; index < first + count - 1; ++index) {
		limit = limits[ctx->m_tableIndex[index + 1]];
		varianceLimit = (limit * limit * 3) >> 5;
		rowInput = rowOutput = destination - 8 * stride + 8 * (index - first + 1);
		for (row = 0; row < 8; ++row) {
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
				if (((rowInput[-4] - rowInput[-5]) > 0 ? (rowInput[-4] - rowInput[-5]) : (rowInput[-5] - rowInput[-4])) < limit) left = rowInput[-5];
				else left = rowInput[-4];
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
			}
			rowInput += stride;
			rowOutput += stride;
		}
	}
}
