// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c1ad0.md plus retail only. No
// decoder source was consulted.
//
// DeringBlockStrong_C (retail 0x001C1AD0, 2030 bytes): cdecl adaptive smoothing
// of one 8x8 block. Vertical and horizontal neighbour weights come from the
// pixel differences, capped at 3 * Q (at most 32) and replaced by the sharpen
// modifier for strong edges; each output pixel blends itself with its four
// neighbours, and a row is computed into temporaries before it is stored.
// Codegen notes (see reverse/attempt_support/dering-strong-offset-20261021.md):
// the row offset is a basic induction variable (off += pitch); pixels 0 and 7
// keep centre/right pixel locals loaded before the weights while pixels 1-6
// read inline; the row store is eight explicit c = k statements.
extern "C" int g_vp6SharpenModifier[64];

extern "C" void __cdecl DeringBlockStrong_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = g_vp6SharpenModifier[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	int row;
	unsigned int c;

	if (cap > 32)
		cap = 32;

	const unsigned char *vrow = source;
	for (row = 0; row < 9; row++) {
		for (c = 0; c < 8; c++) {
			int difference = (vrow[c] - vrow[c - pitch]) > 0 ? (vrow[c] - vrow[c - pitch]) : (vrow[c - pitch] - vrow[c]);
			int weight;
			weight = quality - difference + 32;
			if (weight < -64)
				weight = sharpen;
			else if (weight < 0)
				weight = 0;
			else if (weight > cap)
				weight = cap;
			vertical[row * 8 + c] = (short)weight;
		}
		vrow += pitch;
	}
	const unsigned char *hrow = source;
	for (row = 0; row < 8; row++) {
		for (c = 0; c < 9; c++) {
			int difference = (hrow[c] - hrow[c - 1]) > 0 ? (hrow[c] - hrow[c - 1]) : (hrow[c - 1] - hrow[c]);
			int weight;
			weight = quality - difference + 32;
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			horizontal[row * 9 + c] = (short)weight;
		}
		hrow += pitch;
	}

	short *downWeights = vertical + 8 + 1;
	short *upWeights = vertical + 1;
	int off = 0;
	for (row = 0; row < 8; row++) {
		int rowValues[8];
		{
			int centerPixel = source[off + 0];
			int rightPixel = source[off + 1];
			int left = horizontal[row * 9 + 0];
			int up = upWeights[row * 8 + -1];
			int down = downWeights[row * 8 + -1];
			int right = horizontal[row * 9 + 0 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + 0] + left * source[off + -1]
				+ up * above[off + 0] + right * rightPixel + 64) >> 7;
			if (value < 0) rowValues[0] = 0;
			else if (value > 255) rowValues[0] = 255;
			else rowValues[0] = value;
		}
		{
			int left = horizontal[row * 9 + 1];
			int up = upWeights[row * 8 + 0];
			int down = downWeights[row * 8 + 0];
			int right = horizontal[row * 9 + 1 + 1];
			int value = ((128 - right - down - up - left) * source[off + 1]
				+ down * below[off + 1] + left * source[off + 0]
				+ up * above[off + 1] + right * source[off + 2] + 64) >> 7;
			if (value < 0) rowValues[1] = 0;
			else if (value > 255) rowValues[1] = 255;
			else rowValues[1] = value;
		}
		{
			int left = horizontal[row * 9 + 2];
			int up = upWeights[row * 8 + 1];
			int down = downWeights[row * 8 + 1];
			int right = horizontal[row * 9 + 2 + 1];
			int value = ((128 - right - down - up - left) * source[off + 2]
				+ down * below[off + 2] + left * source[off + 1]
				+ up * above[off + 2] + right * source[off + 3] + 64) >> 7;
			if (value < 0) rowValues[2] = 0;
			else if (value > 255) rowValues[2] = 255;
			else rowValues[2] = value;
		}
		{
			int left = horizontal[row * 9 + 3];
			int up = upWeights[row * 8 + 2];
			int down = downWeights[row * 8 + 2];
			int right = horizontal[row * 9 + 3 + 1];
			int value = ((128 - right - down - up - left) * source[off + 3]
				+ down * below[off + 3] + left * source[off + 2]
				+ up * above[off + 3] + right * source[off + 4] + 64) >> 7;
			if (value < 0) rowValues[3] = 0;
			else if (value > 255) rowValues[3] = 255;
			else rowValues[3] = value;
		}
		{
			int left = horizontal[row * 9 + 4];
			int up = upWeights[row * 8 + 3];
			int down = downWeights[row * 8 + 3];
			int right = horizontal[row * 9 + 4 + 1];
			int value = ((128 - right - down - up - left) * source[off + 4]
				+ down * below[off + 4] + left * source[off + 3]
				+ up * above[off + 4] + right * source[off + 5] + 64) >> 7;
			if (value < 0) rowValues[4] = 0;
			else if (value > 255) rowValues[4] = 255;
			else rowValues[4] = value;
		}
		{
			int left = horizontal[row * 9 + 5];
			int up = upWeights[row * 8 + 4];
			int down = downWeights[row * 8 + 4];
			int right = horizontal[row * 9 + 5 + 1];
			int value = ((128 - right - down - up - left) * source[off + 5]
				+ down * below[off + 5] + left * source[off + 4]
				+ up * above[off + 5] + right * source[off + 6] + 64) >> 7;
			if (value < 0) rowValues[5] = 0;
			else if (value > 255) rowValues[5] = 255;
			else rowValues[5] = value;
		}
		{
			int left = horizontal[row * 9 + 6];
			int up = upWeights[row * 8 + 5];
			int down = downWeights[row * 8 + 5];
			int right = horizontal[row * 9 + 6 + 1];
			int value = ((128 - right - down - up - left) * source[off + 6]
				+ down * below[off + 6] + left * source[off + 5]
				+ up * above[off + 6] + right * source[off + 7] + 64) >> 7;
			if (value < 0) rowValues[6] = 0;
			else if (value > 255) rowValues[6] = 255;
			else rowValues[6] = value;
		}
		{
			int centerPixel = source[off + 7];
			int rightPixel = source[off + 8];
			int left = horizontal[row * 9 + 7];
			int up = upWeights[row * 8 + 6];
			int down = downWeights[row * 8 + 6];
			int right = horizontal[row * 9 + 7 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + 7] + left * source[off + 6]
				+ up * above[off + 7] + right * rightPixel + 64) >> 7;
			if (value < 0) rowValues[7] = 0;
			else if (value > 255) rowValues[7] = 255;
			else rowValues[7] = value;
		}

		c = 0; destination[off + c] = (unsigned char)rowValues[c];
		c = 1; destination[off + c] = (unsigned char)rowValues[c];
		c = 2; destination[off + c] = (unsigned char)rowValues[c];
		c = 3; destination[off + c] = (unsigned char)rowValues[c];
		c = 4; destination[off + c] = (unsigned char)rowValues[c];
		c = 5; destination[off + c] = (unsigned char)rowValues[c];
		c = 6; destination[off + c] = (unsigned char)rowValues[c];
		c = 7; destination[off + c] = (unsigned char)rowValues[c];
		off += pitch;
	}
}


// Weak companion, retail 0x001C22C0..0x001C28B6 (1526 bytes).
// Clean room: specs 001c22c0 and 001c1ad0, retail and the prior clean bank only.
// Named sample, promotion and arithmetic stages are all consumed. Their explicit
// lifetimes reproduce VC7.1 temporary identities without dummy-local padding.
// Both weight grids precede output; each output pixel is stored immediately,
// preserving source/destination overlap behavior rather than staging a whole row.
static inline int ClampWeight(int weight, int sharpen, int cap)
{
	if (weight < -64)
		return sharpen;
	if (weight < 0)
		return 0;
	if (weight > cap)
		return cap;
	return weight;
}

extern "C" void __cdecl DeringBlockWeak_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = g_vp6SharpenModifier[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	unsigned int c;
	int r;

	if (cap > 24)
		cap = 24;

	const unsigned char *vrow = source;
	for (r = 0; r < 9; r++) {
		for (c = 0; c < 8; c++) {
			unsigned char sampleValue = vrow[c];
			int differencePromoted002 = sampleValue;
			unsigned int differencePromoted003 = pitch;
			unsigned int differenceDifference004 = c - differencePromoted003;
			unsigned char differenceSample005 = vrow[differenceDifference004];
			int differencePromoted006 = differenceSample005;
			int differenceDifference007 = differencePromoted002 - differencePromoted006;
			unsigned char differenceSample008 = vrow[c];
			int differencePromoted009 = differenceSample008;
			unsigned int differencePromoted010 = pitch;
			unsigned int differenceDifference011 = c - differencePromoted010;
			unsigned char differenceSample012 = vrow[differenceDifference011];
			int differencePromoted013 = differenceSample012;
			int differenceDifference014 = differencePromoted009 - differencePromoted013;
			unsigned int differencePromoted015 = pitch;
			unsigned int differenceDifference016 = c - differencePromoted015;
			unsigned char differenceSample017 = vrow[differenceDifference016];
			int differencePromoted018 = differenceSample017;
			unsigned char differenceSample019 = vrow[c];
			int differencePromoted020 = differenceSample019;
			int differenceDifference021 = differencePromoted018 - differencePromoted020;
			int difference = (differenceDifference007) > 0 ? (differenceDifference014) : (differenceDifference021);
			int weight;
			int outputValueDifference022 = 16 - difference;
			int outputValueProduct023 = 2 * (outputValueDifference022);
			int outputValueSum024 = quality + outputValueProduct023;
			weight = ClampWeight(outputValueSum024, sharpen, cap);
			int outputIndexProduct025 = r * 8;
			unsigned int outputIndexPromoted026 = outputIndexProduct025;
			unsigned int outputIndexSum027 = outputIndexPromoted026 + c;
			vertical[outputIndexSum027] = (short)weight;
		}
		vrow += pitch;
	}
	const unsigned char *hrow = source;
	for (r = 0; r < 8; r++) {
		for (unsigned int hc = 0; hc < 9; hc++) {
			int differencePromoted028 = hc;
			unsigned char differenceSample029 = hrow[(int)differencePromoted028];
			int differencePromoted030 = differenceSample029;
			int differencePromoted031 = hc;
			int differenceDifference032 = (int)differencePromoted031 - 1;
			unsigned char differenceSample033 = hrow[differenceDifference032];
			int differencePromoted034 = differenceSample033;
			int differenceDifference035 = differencePromoted030 - differencePromoted034;
			int differencePromoted036 = hc;
			unsigned char differenceSample037 = hrow[(int)differencePromoted036];
			int differencePromoted038 = differenceSample037;
			int differencePromoted039 = hc;
			int differenceDifference040 = (int)differencePromoted039 - 1;
			unsigned char differenceSample041 = hrow[differenceDifference040];
			int differencePromoted042 = differenceSample041;
			int differenceDifference043 = differencePromoted038 - differencePromoted042;
			int differencePromoted044 = hc;
			int differenceDifference045 = (int)differencePromoted044 - 1;
			unsigned char differenceSample046 = hrow[differenceDifference045];
			int differencePromoted047 = differenceSample046;
			int differencePromoted048 = hc;
			unsigned char differenceSample049 = hrow[(int)differencePromoted048];
			int difference = (differenceDifference035) > 0 ? (differenceDifference043) : (differencePromoted047 - differenceSample049);
			int weight;
			weight = quality + 2 * (16 - difference);
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			horizontal[r * 9 + (int)hc] = (short)weight;
		}
		hrow += pitch;
	}

	int off = 0;
	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int centerPixel = source[off + c];
			int rightPixel = source[off + c + 1];
			int leftPixel = source[off + c - 1];
			int left = horizontal[r * 9 + c];
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + c] + left * leftPixel
				+ right * rightPixel + up * above[off + c] + 64) >> 7;
			int pixel;
			if (value < 0) pixel = 0;
			else if (value > 255) pixel = 255;
			else pixel = (int)value;
			destination[off + c] = (unsigned char)pixel;
		}
		off += pitch;
	}
}
