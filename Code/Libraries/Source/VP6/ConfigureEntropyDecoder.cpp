// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bbf70.md plus retail only.
// No decoder source was consulted.
// _VP6_ConfigureEntropyDecoder retail 0x001BBF70..0x001BC19B (556 bytes)
// cdecl (instance / frame type byte with 0 = key frame). Every update reads
// a bool from the primary coder at 0x150 (0x001C5100) with the table
// probability and when set reads 7 bits (0x001BCF40) doubled with 0 mapped
// to 1 (retail's branchless sete/add). An 11-entry working array starts at
// 128. DC (0x3A0) and AC (0x3B6 laid out plane/precedence/band/node) store
// the update into the working array and the field; on a key frame a field
// with no update takes the working entry. A key frame resets the 28
// zero-run probabilities (0x560) from defaults. A bool at 128 enables 4-bit
// scan band updates (0x63C positions 1..63) followed by BuildScanOrder
// (0x001BBA20). Zero-run probabilities update without the working array.
// VP6_ConfigureContexts (0x001C6DA0) runs last. The tables 0x00BD9210 /
// 0x00BD9228 / 0x00BD9268 / 0x00BD9284 / 0x00BD92A0 are address-named (the
// only ledger row there is the gap-sized blob g_rva01143064). The in-class
// read helper is what reproduces retail's register choice; spelling the
// same expression inline in each branch rotates ecx/edx/eax.
struct Rva009B4800State;
struct Rva009AAFE0Context;
struct Vp6EntropyInstance {
	unsigned char unknown0[0x150];
	unsigned char br[32];
	unsigned char unknown170[0x3a0 - 0x170];
	unsigned char DcProbs[2][11];
	unsigned char AcProbs[2][3][6][11];
	unsigned char unknown542[0x560 - 0x542];
	unsigned char ZeroRunProbs[2][14];
	unsigned char unknown57c[0x63c - 0x57c];
	unsigned char ScanBands[64];
};
int Rva009B4800DecodeBool(Rva009B4800State *, int);
int bfmeGoUSC(void *, int);
void Rva009AAFE0BuildTable(Rva009AAFE0Context *, const unsigned char *);
void Rva009B64A0BuildTone(unsigned char *);
struct Vp6ProbUpdate {
	static unsigned char Read(void *br)
	{
		unsigned char v = (unsigned char)(bfmeGoUSC(br, 7) << 1);
		return v + (v == 0);
	}
};
extern "C" void *memset(void *, int, unsigned);
extern "C" void *memcpy(void *, const void *, unsigned);
#pragma intrinsic(memset, memcpy)
extern const unsigned char g_00BD9210[2][11];
extern const unsigned char g_00BD9228[64];
extern const unsigned char g_00BD9268[2][14];
extern const unsigned char g_00BD9284[2][14];
extern const unsigned char g_00BD92A0[3][2][6][11];
extern "C" void VP6_ConfigureEntropyDecoder(Vp6EntropyInstance *pbi, unsigned char frameType)
{
	unsigned char lastProb[11];
	unsigned i, j, k;
	int prec;
	unsigned plane;
	memset(lastProb, 128, sizeof lastProb);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 11; j++) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)pbi->br, g_00BD9210[i][j])) {
				unsigned char v = Vp6ProbUpdate::Read(pbi->br);
				lastProb[j] = v;
				pbi->DcProbs[i][j] = v;
			} else if (frameType == 0) {
				pbi->DcProbs[i][j] = lastProb[j];
			}
		}
	}
	if (frameType == 0)
		memcpy(pbi->ZeroRunProbs, g_00BD9284, sizeof pbi->ZeroRunProbs);
	if (Rva009B4800DecodeBool((Rva009B4800State *)pbi->br, 128)) {
		for (i = 1; i < 64; i++) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)pbi->br, g_00BD9228[i]))
				pbi->ScanBands[i] = (unsigned char)bfmeGoUSC(pbi->br, 4);
		}
		Rva009AAFE0BuildTable((Rva009AAFE0Context *)pbi, pbi->ScanBands);
	}
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 14; j++) {
			if (Rva009B4800DecodeBool((Rva009B4800State *)pbi->br, g_00BD9268[i][j])) {
				unsigned char v = Vp6ProbUpdate::Read(pbi->br);
				pbi->ZeroRunProbs[i][j] = v;
			}
		}
	}
	for (prec = 0; prec < 3; prec++) {
		for (plane = 0; plane < 2; plane++) {
			for (j = 0; j < 6; j++) {
				for (k = 0; k < 11; k++) {
					if (Rva009B4800DecodeBool((Rva009B4800State *)pbi->br, g_00BD92A0[prec][plane][j][k])) {
						unsigned char v = Vp6ProbUpdate::Read(pbi->br);
						lastProb[k] = v;
						pbi->AcProbs[plane][prec][j][k] = v;
					} else if (frameType == 0) {
						pbi->AcProbs[plane][prec][j][k] = lastProb[k];
					}
				}
			}
		}
	}
	Rva009B64A0BuildTone((unsigned char *)pbi);
}
