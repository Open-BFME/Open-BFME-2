// cl: /O2 /G6 /Z7 /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4840.md plus retail only.
// No decoder source was consulted. Native 1C4840..1C4A6A, cdecl with a
// 16-byte realigned frame: forward quantisation of one block. The SSE2 pre-pass
// (eight coefficients per step) is inline asm because the retail function keeps
// every local in memory around it; the DC and AC dead-zone logic is plain C.
// Debug info (/Z7) selects retail's return-address-copying realign prologue.
#include <stdlib.h>

extern unsigned char g_Rva01142608[8];
extern int g_Rva009B7B28[64];

struct Vp6Quantizer
{
	unsigned char pad0[8];
	short rounding[8];
	short multiplier[8];
};

// A plane row: the quantiser instance advanced by 256 bytes per plane; the
// multiplier, rounding, zero-bin and zero-run tables sit 0x190/0x390/0x590/
// 0x790 bytes into it.
struct Vp6QuantRow
{
	unsigned char pad0[0x190];
	int quant[64];
	int pad100[64];
	int round[64];
	int pad300[64];
	int zeroBin[64];
	int pad500[64];
	int runBias[64];
};

extern "C" void __cdecl VP6_quantize_wmt(Vp6Quantizer *q, short *coeffs, short *out, unsigned char position)
{
	__declspec(align(16)) unsigned short candidate[64];
	int plane = g_Rva01142608[position];
	Vp6QuantRow *row = (Vp6QuantRow *)((char *)q + plane * 256);
	int dcMul = ((int *)((char *)q + 0x190))[plane * 64];
	int run;
	unsigned i;
	short *dst;

	{
		short *roundingPtr = q->rounding;
		short *multiplierPtr = q->multiplier;
		run = 0;
		__asm {
			mov esi, coeffs
			xor ecx, ecx
			mov edi, roundingPtr
			movdqu xmm2, [edi]
			mov edi, multiplierPtr
			movdqu xmm3, [edi]
			lea edi, candidate
			mov eax, out
			pxor xmm7, xmm7
		again:
			movdqa xmm0, [esi+ecx]
			movdqa xmm1, xmm0
			psraw xmm1, 15
			pxor xmm0, xmm1
			psubw xmm0, xmm1
			paddw xmm0, xmm2
			pmulhuw xmm0, xmm3
			pxor xmm0, xmm1
			psubw xmm0, xmm1
			movdqa [edi+ecx], xmm0
			movdqa [eax+ecx], xmm7
			add ecx, 16
			cmp ecx, 128
			jl again
		}
	}
	{
		int dc = coeffs[0];
		if (dc >= row->zeroBin[0])
			out[0] = (short)(((dc + row->round[0]) * dcMul) >> 16);
		else if (dc <= -row->zeroBin[0])
			out[0] = (short)(((dc - row->round[0]) * dcMul + 0xFFFF) >> 16);
		else
			run = 1;
	}
	dst = out + 3;
	for (i = 4; i < 256; i += 12, dst += 3) {
		int k, c, mag;
		k = *(int *)((char *)g_Rva009B7B28 + i);
		c = candidate[k];
		if (c == 0) run++;
		else {
			mag = abs(coeffs[k]);
			if (mag < row->runBias[run] + row->zeroBin[k]) run++;
			else { run = 0; dst[-2] = (short)c; }
		}
		k = *(int *)((char *)g_Rva009B7B28 + i + 4);
		c = candidate[k];
		if (c == 0) run++;
		else {
			mag = abs(coeffs[k]);
			if (mag < row->runBias[run] + row->zeroBin[k]) run++;
			else { run = 0; dst[-1] = (short)c; }
		}
		k = *(int *)((char *)g_Rva009B7B28 + i + 8);
		c = candidate[k];
		if (c == 0) run++;
		else {
			mag = abs(coeffs[k]);
			if (mag < row->runBias[run] + row->zeroBin[k]) run++;
			else { run = 0; dst[0] = (short)c; }
		}
	}
}
