// _DeringBlock
// partial score=0.6 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c28c0.md plus retail only.
// No decoder source was consulted.
struct Vp6DeringPostProc
{
	int pad00[2];
	int level;
};

extern "C" int Vp6FilterEdgeTagTable[];

extern "C" void DeringBlock(Vp6DeringPostProc *pp, const unsigned char *source, unsigned char *dest, int pitch, int qIndex, int *scaleTable, unsigned int spread)
{
	const unsigned char *src = source;
	unsigned char *dst = dest;
	int strength = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	int factor = 4;
	int cap;
	int row;
	unsigned int col, k;
	int neighbours[8];
	if (pp->level > 100)
		strength = pp->level - 100;
	if (spread > 32768)
		factor = 4;
	else if (spread > 2048)
		factor = 8;
	cap = 3 * strength;
	if (cap > 32)
		cap = 32;
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			int center;
			int sum;
			int centerWeight;
			int value;
			neighbours[0] = src[col - pitch - 1];
			neighbours[1] = src[col - pitch];
			neighbours[2] = src[col - pitch + 1];
			neighbours[3] = src[col - 1];
			neighbours[4] = src[col + 1];
			neighbours[5] = src[col + pitch - 1];
			neighbours[6] = src[col + pitch];
			neighbours[7] = src[col + pitch + 1];
			center = src[col];
			centerWeight = 256;
			sum = 128;
			for (k = 0; k < 8; k++) {
				int diff = center - neighbours[k];
				int weight;
				if (diff <= 0)
					diff = neighbours[k] - center;
				weight = strength - ((diff * factor) >> 2) + 32;
				if (weight < -64)
					weight = sharpen;
				else if (weight < 0)
					weight = 0;
				else if (weight > cap)
					weight = cap;
				centerWeight -= weight;
				sum += neighbours[k] * weight;
			}
			value = (center * centerWeight + sum) >> 8;
			dst[col] = (unsigned char)(value < 0 ? 0 : (value > 255 ? 255 : value));
		}
		src += pitch;
		dst += pitch;
	}
}
