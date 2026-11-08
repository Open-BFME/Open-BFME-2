// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001be770.md plus retail only.
// No decoder source was consulted.
//
// DeblockNonFilteredBand_C (retail 0x001BE770, 2324 bytes): generic band
// deblocker for the profile without the in-loop filter. Pass 1 filters the
// horizontal edge at the top of each fragment column by column (q from the
// fragment below the edge), writing the source band to the destination;
// pass 2 filters the vertical edge left of every fragment but the first in
// place on the destination one band up (q from the right-hand fragment).
// Lines that are not smoothed get the bounded two-tap filter through the
// clamp table. Reached only through the generic dispatch slot 13
// (BfmeCodecCpuDispatch declares it as Rva009ADD80), so it keeps its plain C
// name.
// Retail behaviour the spec omits: after the first fragment retail skips the
// next fragment entirely (double index/pointer advance at
// 0x001BECBD..0x001BED20 then 0x001BF02B), reproduced by 'index++; continue;'.
// The one-site stride copy p1 gives retail's base/index order on the
// -2*pitch loads at 0x001BE90A and 0x001BEC49.

struct Vp6DeblockBandInstance
{
	unsigned char m_pad00[0x24];
	unsigned int *m_tableIndex;
	int *m_variance;
	unsigned char m_pad2c[0x38 - 0x2c];
	int *m_bounding;
};

extern unsigned char g_bfmeClampTable[];
#define VABS(x) ((x) > 0 ? (x) : -(x))

extern "C" void __cdecl DeblockNonFilteredBand_C(Vp6DeblockBandInstance *ctx,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int count, unsigned int first, const unsigned int *limits)
{
	unsigned int index;
	int samples[10];
	int sumLeft, sumRight, varianceLeft, varianceRight, rolling;
	int limit, varianceLimit, filter;
	int left, right;
	unsigned int row;
	unsigned char *rowInput, *rowOutput;
	index = first;
	int rowOffset1 = stride;
	int rowOffset2 = 2 * stride;
	int rowOffset3 = 3 * stride;
	int rowOffset4 = 4 * stride;
	int rowOffset5 = 5 * stride;
	for (; index < first + count; ++index) {
		rowInput = source + 8 * (index - first);
		limit = limits[ctx->m_tableIndex[index + count]];
		varianceLimit = (limit * limit * 3) >> 5;
		rowOutput = destination + 8 * (index - first);
		for (row = 0; row < 8; ++row) {
			samples[1] = rowInput[-rowOffset4];
			samples[2] = rowInput[-rowOffset3];
			samples[3] = rowInput[-rowOffset2];
			samples[4] = rowInput[-rowOffset1];
			samples[5] = rowInput[0];
			samples[6] = rowInput[rowOffset1];
			samples[7] = rowInput[rowOffset2];
			samples[8] = rowInput[rowOffset3];
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
				if (((rowInput[-rowOffset4] - rowInput[-rowOffset5]) > 0 ? (rowInput[-rowOffset4] - rowInput[-rowOffset5]) : (rowInput[-rowOffset5] - rowInput[-rowOffset4])) < limit) left = rowInput[-rowOffset5];
				else left = rowInput[-rowOffset4];
				if (((rowInput[rowOffset3] - rowInput[rowOffset4]) > 0 ? (rowInput[rowOffset3] - rowInput[rowOffset4]) : (rowInput[rowOffset4] - rowInput[rowOffset3])) < limit) right = rowInput[rowOffset4];
				else right = rowInput[rowOffset3];
				rolling = samples[4] + 3*left + samples[3] + samples[2] + 4 + samples[1];
				rowOutput[-rowOffset4] = (unsigned char)(((rolling+samples[1])*2-samples[4]+samples[5])>>4);
				rolling += samples[5]-left;
				rowOutput[-rowOffset3] = (unsigned char)(((rolling+samples[2])*2-samples[5]+samples[6])>>4);
				rolling += samples[6]-left;
				rowOutput[-rowOffset2] = (unsigned char)(((rolling+samples[3])*2-samples[6]+samples[7])>>4);
				rolling += samples[7]-left;
				rowOutput[-rowOffset1] = (unsigned char)(((rolling+samples[4])*2-samples[7]-samples[1]+left+samples[8])>>4);
				rolling += samples[8]-samples[1];
				rowOutput[0] = (unsigned char)(((rolling+samples[5])*2-samples[8]-samples[2]+right+samples[1])>>4);
				rolling += right-samples[2];
				rowOutput[stride] = (unsigned char)(((rolling+samples[6])*2-samples[3]+samples[2])>>4);
				rolling += right-samples[3];
				rowOutput[rowOffset2] = (unsigned char)(((rolling+samples[7])*2-samples[4]+samples[3])>>4);
				rowOutput[rowOffset3] = (unsigned char)(((rolling+right+samples[8])*2-samples[5] - samples[4])>>4);
			} else {
				filter = ctx->m_bounding[(samples[3] - samples[6] + 3 * (samples[5] - samples[4]) + 4) >> 3];
				rowOutput[-(int)stride] = g_bfmeClampTable[samples[4] + filter];
				rowOutput[0] = g_bfmeClampTable[samples[5] - filter];
				rowOutput[-rowOffset4] = rowInput[-rowOffset4];
				rowOutput[-rowOffset3] = rowInput[-rowOffset3];
				rowOutput[-rowOffset2] = rowInput[-rowOffset2];
				rowOutput[stride] = rowInput[stride];
				rowOutput[rowOffset2] = rowInput[rowOffset2];
				rowOutput[rowOffset3] = rowInput[rowOffset3];
			}
			rowInput++;
			rowOutput++;
		}
		if (index == first) {
			index++;
			continue;
		}
		rowInput = rowOutput = destination - 8 * stride + 8 * (index - first);
		limit = limits[ctx->m_tableIndex[index]];
		varianceLimit = (limit * limit * 3) >> 5;
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
			ctx->m_variance[index - 1] += varianceLeft;
			ctx->m_variance[index] += varianceRight;
			if (varianceLeft < varianceLimit && varianceRight < varianceLimit && samples[5] - samples[4] < limit && samples[4] - samples[5] < limit) {
				if (VABS(rowInput[-4] - rowInput[-5]) < limit) left = rowInput[-5];
				else left = rowInput[-4];
				if (VABS(rowInput[3] - rowInput[4]) < limit) right = rowInput[4];
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
