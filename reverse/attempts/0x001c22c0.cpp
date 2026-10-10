// _DeringBlockWeak_C
// partial score=0.44 date=2026-10-10
// _DeringBlockWeak_C
// partial score=0.44 (structure ratio 0.66) date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c22c0.md plus retail only.
// No decoder source was consulted.
// Retail 0x001C22C0..0x001C28B6 (1526 bytes) cdecl. Frame size (0x160) and
// the 4x unrolled weight loops come out; retail walks the weight loops with
// pointer IVs and a down-counter (inner count 2) where this draft indexes,
// and the prologue loads Q / sharpen into other registers. The output loop
// still needs retail's pointer set (above row + pitch / 2*pitch / dst-src).
extern "C" int Vp6FilterEdgeTagTable[];

extern "C" void __cdecl DeringBlockWeak_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	int r;
	unsigned int c;

	if (cap > 24)
		cap = 24;

	for (r = 0; r < 9; r++) {
		for (c = 0; c < 8; c++) {
			int difference = source[(r - 1) * pitch + c + pitch] - source[(r - 1) * pitch + c];
			int weight;
			if (difference <= 0)
				difference = source[(r - 1) * pitch + c] - source[(r - 1) * pitch + c + pitch];
			weight = quality + 2 * (16 - difference);
			if (weight < -64)
				weight = sharpen;
			else if (weight < 0)
				weight = 0;
			else if (weight > cap)
				weight = cap;
			vertical[r * 8 + c] = (short)weight;
		}
	}

	for (r = 0; r < 8; r++) {
		for (c = 0; c < 9; c++) {
			int difference = source[r * pitch + c] - source[r * pitch + c - 1];
			int weight;
			if (difference <= 0)
				difference = source[r * pitch + c - 1] - source[r * pitch + c];
			weight = quality + 2 * (16 - difference);
			if (weight < -64)
				weight = sharpen;
			else if (weight < 0)
				weight = 0;
			else if (weight > cap)
				weight = cap;
			horizontal[r * 9 + c] = (short)weight;
		}
	}

	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int left = horizontal[r * 9 + c];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * source[r * pitch + c]
				+ down * below[r * pitch + c] + left * source[r * pitch + c - 1]
				+ right * source[r * pitch + c + 1] + up * above[r * pitch + c] + 64) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[r * pitch + c] = (unsigned char)value;
		}
	}
}
