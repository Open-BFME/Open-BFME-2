// cl: /O2 /G6 /Z7 /MD
// Clean room: reverse/vp6_cleanroom/specs/001d1330.md plus retail only.
// No decoder source was consulted. Native 1D1330..1D153B, cdecl with a
// 16-byte realigned frame (/Z7 selects that prologue): builds the Gaussian
// sample table and a 2048-byte noise buffer, then adds the noise to each row
// sixteen pixels at a time. The row stage is an SSE2 inline asm block inside
// otherwise plain C, which is why retail keeps its locals in memory.
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>

// Normal density, matched at 0x001B6970.
double bfmeGaussPdf(double sigma, double mu, double x);

extern "C" void __cdecl PlaneAddNoise_wmt(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	unsigned i;
	double sigma;
	double x;
	int next;
	signed char dist[300];
	unsigned char noise[2048];
	__declspec(align(16)) unsigned char clampBoth[16];
	__declspec(align(16)) unsigned char clampLow[16];
	__declspec(align(16)) unsigned char clampHigh[16];
	unsigned char *row;
	unsigned rows;

	_mm_empty();
	sigma = 1 + 0.012698412698412698 * (63 - q);
	next = 0;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * bfmeGaussPdf(sigma, 0, x) + 0.5);
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
	signed char first = dist[0];
	signed char negFirst = -first;
	for (i = 0; i < 16; i++)
		clampBoth[i] = first * -2;
	for (i = 0; i < 16; i++)
		clampHigh[i] = negFirst;
	for (i = 0; i < 16; i++)
		clampLow[i] = negFirst;
	if (height > 0) {
		for (row = start, rows = height; rows; rows--) {
			unsigned char *src = row;
			unsigned char *noisePtr = &noise[rand() & 0xff];
			__asm {
				mov ecx, width
				mov esi, src
				mov edi, noisePtr
				xor eax, eax
			again:
				movdqu xmm1, [esi+eax]
				psubusb xmm1, xmmword ptr clampLow
				paddusb xmm1, xmmword ptr clampBoth
				psubusb xmm1, xmmword ptr clampHigh
				movdqu xmm2, [edi+eax]
				paddb xmm1, xmm2
				movdqu [esi+eax], xmm1
				add eax, 16
				cmp eax, ecx
				jl again
			}
			row += pitch;
		}
	}
}
