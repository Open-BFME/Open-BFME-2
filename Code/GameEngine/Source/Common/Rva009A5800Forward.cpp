// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Carried from the Open-BFME-1 donor at submodule revision 77db49c3
// (game/GameEngine/Source/Common/Rva009A5800Forward.cpp). Target evidence: the
// 477B decode body is byte-identical at BFME2 0x001B60E0 (donor b1 0x009A5620)
// and the 23B forwarder at 0x001B62C0 (donor b1 0x009A5800). Names and the
// field offsets are donor assertions. Two callees keep the names this ledger
// already gives their addresses: VP6_DecodeFrameMbs at 0x001BC9C0 and the
// d_009a8c50 stand-in at 0x001B96A0.
// The callee stays static in this TU so VC7.1 passes its data argument in EAX.
// Timestamp calls use the recovered BFME2 0x001B8E70 output-pointer helper.
#include <stdio.h>

class BfmeCursorXF;
struct BfmeBits1186;
struct Rva009A6130Context;
void __cdecl Rva001B8E70(unsigned int *result);
// Native1BD550 wrapper has a typed state argument and int Boolean result.
int __cdecl Rva001BD550ReadHeader(unsigned char *);
void bfmeReadWordXF(BfmeCursorXF *out, const unsigned char *data);
void bfmeInit1186(BfmeBits1186 *s, unsigned char *p);
struct FramePB;
extern "C" void VP6_DecodeFrameMbs(FramePB *pbi);
void __cdecl d_009a8c50(void);
extern void (__cdecl *g_bfmeToneReady)();
extern int g_0134C7D8;
// g_0134C7D8: matched references place it at VA 0xdfda50 (zero-filled .bss).
int g_0134C7D8;
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

#define U(o) (*(unsigned *)(s + (o)))
#define B(o) (*(unsigned char *)(s + (o)))
#define P(o) (*(unsigned char **)(s + (o)))

static int Rva009A5620DecodeFrame(unsigned char *s, unsigned char *data, unsigned int size)
{
	unsigned int start;
	Rva001B8E70(&start);
	U(0x1e8) = size;
	bfmeReadWordXF((BfmeCursorXF *)(s + 0x450c), data);
	if (!Rva001BD550ReadHeader(s))
		return -1;
	if (U(0x944) || !B(0x19d))
	{
		if (U(0x4520))
		{
			U(0x190) = 0;
			U(0x194) = 0;
			P(0x198) = data + U(0x451c);
		}
		else
			bfmeInit1186((BfmeBits1186 *)(s + 0x170), data + U(0x451c));
	}
	VP6_DecodeFrameMbs((FramePB *)s);
	unsigned char *swap = P(0x254);
	P(0x254) = P(0x244);
	P(0x244) = swap;
	((void (__cdecl *)(Rva009A6130Context *, unsigned char *))d_009a8c50)((Rva009A6130Context *)P(0x298), P(0x254));
	if (!B(0x1ac) || U(0x698))
		memcpy(P(0x24c), P(0x254), U(0x208) + U(0x20c) * 2);
	g_bfmeToneReady();
	if (!B(0x1ac))
		U(0x6a0) = *(unsigned int *)P(0x13c);
	else
		U(0x6a0) = (*(unsigned int *)P(0x13c) + 2 + U(0x6a0) * 3) >> 2;
	unsigned int end;
	Rva001B8E70(&end);
	unsigned int elapsed = (end - start) / U(0x1a4);
	U(0x910) = elapsed;
	if (!U(0x914))
		U(0x914) = elapsed;
	else
		U(0x914) = (U(0x914) * 7 + elapsed) >> 3;
	if (U(0x160) > U(0x1e8))
	{
		FILE *f = fopen("badframes.stt", "a");
		fprintf(f, "%8d %8d %8d \n", g_0134C7D8, U(0x160), U(0x1e8));
		fclose(f);
	}
	++g_0134C7D8;
	return 0;
}

void __cdecl Rva009A5800Forward(int s, int data, int size)
{
	Rva009A5620DecodeFrame((unsigned char *)s, (unsigned char *)data, (unsigned int)size);
}

#undef U
#undef B
#undef P
// ?g_bfmeToneReady@@3P6AXXZA: the global at VA 0xe22d10 is ?g_bfmeSlotB48@@3PAXA.
#pragma comment(linker, "/alternatename:?g_bfmeToneReady@@3P6AXXZA=?g_bfmeSlotB48@@3PAXA")
