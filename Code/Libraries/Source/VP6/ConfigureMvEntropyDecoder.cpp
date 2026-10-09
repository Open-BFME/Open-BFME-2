// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c6ef0.md plus retail only.
// No decoder source was consulted.
// _VP6_ConfigureMvEntropyDecoder retail 0x001C6EF0..0x001C703B (331 bytes)
// cdecl (instance / frame type unused). Every update reads a bool from the
// primary coder at 0x150 with the table probability (0x001C4F00) and when
// set replaces the field by a 7-bit value (0x001BCF40) doubled with 0
// mapped to 1. Per component the table's first two entries update the
// is-short (0x706) and sign (0x704) probabilities; entries 2..8 then the
// seven short probabilities (0x708) and entries 9..16 the eight long
// probabilities (0x71C) of each component. The update table is the
// 2 x 17 bytes at 0x00BD94A8 (address-named: no ledger row). The separate
// table column counter reproduces retail's distinct table pointer.
struct Vp6MvEntropyInstance {
	unsigned char unknown0[0x150];
	unsigned char br[32];
	unsigned char unknown170[0x704 - 0x170];
	unsigned char MvSignProbs[2];
	unsigned char IsMvShortProb[2];
	unsigned char MvShortProbs[2][7];
	unsigned char unknown716[6];
	unsigned char MvSizeProbs[2][8];
};
int Rva009B4600DecodeBool(void *, int);
int bfmeGoUSC(void *, int);
extern const unsigned char g_00BD94A8[2][17];
extern "C" void VP6_ConfigureMvEntropyDecoder(Vp6MvEntropyInstance *pbi, unsigned char frameType)
{
	int i;
	unsigned j;
	for (i = 0; i < 2; i++) {
		if (Rva009B4600DecodeBool(pbi->br, g_00BD94A8[i][0])) {
			pbi->IsMvShortProb[i] = bfmeGoUSC(pbi->br, 7) << 1;
			if (!pbi->IsMvShortProb[i])
				pbi->IsMvShortProb[i] = 1;
		}
		if (Rva009B4600DecodeBool(pbi->br, g_00BD94A8[i][1])) {
			pbi->MvSignProbs[i] = bfmeGoUSC(pbi->br, 7) << 1;
			if (!pbi->MvSignProbs[i])
				pbi->MvSignProbs[i] = 1;
		}
	}
	for (i = 0; i < 2; i++) {
		int k = 2;
		for (j = 0; j < 7; j++, k++) {
			if (Rva009B4600DecodeBool(pbi->br, g_00BD94A8[i][k])) {
				pbi->MvShortProbs[i][j] = bfmeGoUSC(pbi->br, 7) << 1;
				if (!pbi->MvShortProbs[i][j])
					pbi->MvShortProbs[i][j] = 1;
			}
		}
	}
	for (i = 0; i < 2; i++) {
		int k = 9;
		for (j = 0; j < 8; j++, k++) {
			if (Rva009B4600DecodeBool(pbi->br, g_00BD94A8[i][k])) {
				pbi->MvSizeProbs[i][j] = bfmeGoUSC(pbi->br, 7) << 1;
				if (!pbi->MvSizeProbs[i][j])
					pbi->MvSizeProbs[i][j] = 1;
			}
		}
	}
}
