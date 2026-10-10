// cl: /O2 /G6 /Ob1 /DNDEBUG /MD
#include <string.h>
// Clean room: reverse/vp6_cleanroom/specs/001c61f0.md plus retail only.
// No decoder source was consulted. Native 1C61F0..1C63EE, cdecl; the token
// reader result (end-of-block count) selects the 1-, 10- or 63-entry inverse
// transform from the table at 0x00E22D40 and the matching coefficient clear.
struct Vp6BlockContext
{
	unsigned char pad0[4];
	int mode;
	short frame;
	short dc;
};

struct Vp6Quantizer
{
	unsigned char pad0[0x180];
	short *dequant[4];
};

struct PB_INSTANCE
{
	unsigned char pad0[4];
	unsigned char *coefficients;
	int mode;
	int blockModes[0x6C / 4];
	int plane;
	unsigned char pad7C[0xBC - 0x7C];
	Vp6BlockContext *above;
	Vp6BlockContext *left;
	short *lastDC;
	unsigned char padC8[0x13C - 0xC8];
	Vp6Quantizer *quantizer;
	unsigned char pad140[0x270 - 0x140];
	short *reconstruction;
	unsigned char pad274[0x4520 - 0x274];
	int useHuffman;
};

typedef void (__cdecl *Vp6InverseTransform)(unsigned char *, short *, short *);

extern unsigned char g_Rva01142608[];
extern int g_bfmeVp6SelectorMapDw[];
extern Vp6InverseTransform g_Vp6IdctTable[];
extern "C" unsigned char __cdecl VP6_ReadHuffTokens(PB_INSTANCE *, unsigned char *, int);
extern "C" unsigned char __cdecl VP6_ReadTokens(PB_INSTANCE *, unsigned char *, int, Vp6BlockContext *, Vp6BlockContext *);
struct Rva009B4880State;
struct Rva009B4880Neighbor;
struct Rva009B5830State;
void Rva009B4880PredictValue(Rva009B4880State *, int, short *, const Rva009B4880Neighbor *, const Rva009B4880Neighbor *);
void Rva009B5830ReconstructBlock(Rva009B5830State *, int);

#define VP6_COEFS (pbi->coefficients + position * 128)
extern "C" void __cdecl VP6_DecodeBlock(PB_INSTANCE *pbi, int row, int column, int position)
{
	int count = pbi->useHuffman ? VP6_ReadHuffTokens(pbi, VP6_COEFS, pbi->plane != 0) : VP6_ReadTokens(pbi, VP6_COEFS, pbi->plane != 0, pbi->above, pbi->left);
	Rva009B4880PredictValue((Rva009B4880State *)pbi, position, pbi->lastDC, (const Rva009B4880Neighbor *)pbi->above, (const Rva009B4880Neighbor *)pbi->left);
	pbi->left->mode = pbi->blockModes[position];
	pbi->above->mode = pbi->left->mode;
	pbi->left->dc = *(short *)VP6_COEFS;
	pbi->above->dc = pbi->left->dc;
	pbi->left->frame = (short)g_bfmeVp6SelectorMapDw[pbi->mode];
	pbi->above->frame = pbi->left->frame;
	if ((int)count <= 1) {
		g_Vp6IdctTable[1](VP6_COEFS, pbi->quantizer->dequant[g_Rva01142608[position]], pbi->reconstruction);
		*(short *)VP6_COEFS = 0;
	} else if ((int)count <= 10) {
		g_Vp6IdctTable[9](VP6_COEFS, pbi->quantizer->dequant[g_Rva01142608[position]], pbi->reconstruction);
		memset(VP6_COEFS, 0, 16);
		memset(VP6_COEFS + 0x10, 0, 8);
		memset(VP6_COEFS + 0x20, 0, 8);
		memset(VP6_COEFS + 0x30, 0, 8);
		*(short *)(VP6_COEFS + 0x40) = 0;
	} else {
		g_Vp6IdctTable[63](VP6_COEFS, pbi->quantizer->dequant[g_Rva01142608[position]], pbi->reconstruction);
		memset(VP6_COEFS, 0, 128);
	}
	Rva009B5830ReconstructBlock((Rva009B5830State *)pbi, position);
}
