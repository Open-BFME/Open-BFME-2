// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001ba3c0.md and 001ba460.md plus
// retail only. No decoder source was consulted.
// Both are cdecl one-line resamplers taking (source pointer, source step in
// bytes, source scale, source length, destination pointer, destination step
// in bytes, destination scale, destination length). Retail holds no direct
// call: their absolute addresses are stored at 0x001B9B1E and 0x001B9B66.

// RVA 0x001BA3C0..0x001BA45B (155 bytes): linear interpolation at the
// rational rate source scale : destination scale. The bracketing pair is
// advanced while the remainder exceeds the destination scale; the earlier
// sample is weighted by the destination scale minus the remainder and the
// later by the remainder with half the destination scale added before the
// unsigned division. The source length is unused.
extern "C" void Scale1D_c(const unsigned char *source, unsigned sourceStep, unsigned sourceScale, unsigned sourceLength, unsigned char *dest, unsigned destStep, unsigned destScale, unsigned destLength)
{
	unsigned round = destScale >> 1;
	unsigned weight = destScale;
	unsigned rem = 0;
	unsigned char left = source[0];
	unsigned char right = source[sourceStep];
	unsigned i;
	for (i = 0; i < destStep * destLength; i += destStep) {
		dest[i] = (left * weight + right * rem + round) / destScale;
		rem += sourceScale;
		while (rem > destScale) {
			source += sourceStep;
			left = source[0];
			right = source[sourceStep];
			rem -= destScale;
		}
		weight = destScale - rem;
	}
}

// RVA 0x001BA460..0x001BA4C2 (98 bytes): 2-to-1 downsampler with the 3/10/3
// filter over samples two source steps apart (interlace-aware variant).
// Output 0 copies source[0]. Source scale and length and destination scale
// are unused.
extern "C" void Scale1D_2t1_i(const unsigned char *source, unsigned sourceStep, unsigned sourceScale, unsigned sourceLength, unsigned char *dest, unsigned destStep, unsigned destScale, unsigned destLength)
{
	unsigned i, j;
	unsigned step = sourceStep * 2;
	dest[0] = source[0];
	for (i = destStep, j = step; i < destStep * destLength; i += destStep, j += step)
		dest[i] = (unsigned)(3 * source[j - step] + 10 * source[j] + 3 * source[j + step] + 8) >> 4;
}
