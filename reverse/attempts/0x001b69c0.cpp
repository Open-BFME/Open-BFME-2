// _PlaneAddNoise_C
// partial score=0.55 date=2026-10-10
// NEAR draft (helper, clean room): reverse/vp6_cleanroom/specs/001b69c0.md
// plus retail only. _PlaneAddNoise_C retail 0x001B69C0..0x001B6B9B (475B).
// Status: compiled 444B vs 475B. Exact through the sigma / gaussian
// distribution build (inline gaussian helper with a mu parameter reproduces
// retail's duplicated x on the x87 stack and the exp/sqrt intrinsics) and the
// memset-shaped fill loops; differs from the row loop on: retail hoists the
// byte (char)-dist[0] into CL and recomputes lea edx,[esi+0xFF] per pixel,
// caches rand's IAT pointer in ESI (reloaded after the inner loop) and spills
// the row pointer to a 4-byte slot (frame 0x93C vs 0x938 here).
// Variant with `for (j = 0; j < width; j++, pos++)` and *pos (467B) caches
// rand in EBX and spills the row pointer but loses the [edi+eax] ref shape.
// Spec discrepancy: retail's upper clamp is 255 + lower bound (lea
// edx,[esi+0xff] with esi = -dist[0]) not 255 minus the lower bound.
// cl: /O2 /G6 /DNDEBUG /MD
#include <stdlib.h>
#include <math.h>
struct Vp6NoiseMath {
	static double gaussian(double sigma, double mu, double x)
	{
		return exp(-(x - mu) * (x - mu) / (sigma * sigma * 2)) / (sqrt(6.2831853) * sigma);
	}
};
extern "C" void PlaneAddNoise_C(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	unsigned i, j;
	double sigma;
	double x;
	int next;
	signed char dist[300];
	signed char noise[2048];
	sigma = 1 + 0.012698412698412698 * (63 - q);
	next = 0;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * Vp6NoiseMath::gaussian(sigma, 0, x) + 0.5);
		if (count) {
			int k;
			for (k = 0; k < count; k++)
				dist[next + k] = (signed char)(int)x;
			next += k;
		}
	}
	for (; next < 256; next++)
		dist[next] = 0;
	for (i = 0; i < 2048; i++)
		noise[i] = dist[rand() & 0xff];
	for (i = 0; i < height; i++) {
		unsigned char *pos = start + i * pitch;
		signed char *ref = &noise[rand() & 0xff];
		for (j = 0; j < width; j++) {
			if (pos[j] < -dist[0])
				pos[j] = -dist[0];
			if (pos[j] > 255 - dist[0])
				pos[j] = 255 - dist[0];
			pos[j] += ref[j];
		}
	}
}
