// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5d20.md plus retail only.
// No decoder source was consulted.
// _VP6_FindNearestandNextNearest retail 0x001C5D20..0x001C5E30 (272 bytes)
// cdecl (instance / macroblock row / macroblock column / frame selector
// byte / type out pointer). Scans the twelve neighbour offsets at 0x6A8
// around row * columns(0x230) + column: a neighbour counts only when the
// mode-to-frame table (0x00BD8D00 read as dwords and indexed by the signed
// prediction mode byte at 0x6F0) maps it to the selector. The first non-zero
// motion vector (dwords at 0x6F4) becomes the nearest (type 2) and the next
// different non-zero one the near vector (type 0); type starts at 1. The
// last-frame selector (1) stores the type and the inter index/vectors at
// 0x44/0x3C/0x40; any other selector stores only the golden ones at
// 0x50/0x48/0x4C and leaves the type output untouched (retail
// 0x001C5E19..0x001C5E2F).
struct Vp6NearestInstance {
	unsigned char unknown0[0x3c];
	int nearestInter, nearInter, nearestInterIndex;
	int nearestGolden, nearGolden, nearestGoldenIndex;
	unsigned char unknown54[0x230 - 0x54];
	unsigned mbCols;
	unsigned char unknown234[0x6a8 - 0x234];
	int neighbourOffset[12];
	unsigned char unknown6d8[0x6f0 - 0x6d8];
	signed char *predictionMode;
	int *motionVector;
};
// Mode-to-frame map at 0x00BD8D00 (ledger name; dword entries here).
extern unsigned char g_bfmeVp6SelectorMap[40];
extern "C" void VP6_FindNearestandNextNearest(Vp6NearestInstance *pbi, unsigned row, unsigned col, unsigned char frame, int *type)
{
	int i;
	int base = row * pbi->mbCols + col;
	int nearest = 0;
	int nearVector = 0;
	int nearestType = 1;
	int nearestIndex;
	for (i = 0; i < 12; i++) {
		int offset = base + pbi->neighbourOffset[i];
		if (((const int *)g_bfmeVp6SelectorMap)[pbi->predictionMode[offset]] == frame) {
			int mv = pbi->motionVector[offset];
			if (mv != 0) {
				nearest = mv;
				nearestType = 2;
				break;
			}
		}
	}
	nearestIndex = i;
	for (i++; i < 12; i++) {
		int offset = base + pbi->neighbourOffset[i];
		if (((const int *)g_bfmeVp6SelectorMap)[pbi->predictionMode[offset]] == frame) {
			int mv = pbi->motionVector[offset];
			if (mv != nearest && mv != 0) {
				nearVector = mv;
				nearestType = 0;
				break;
			}
		}
	}
	if (frame == 1) {
		*type = nearestType;
		pbi->nearestInterIndex = nearestIndex;
		pbi->nearestInter = nearest;
		pbi->nearInter = nearVector;
	} else {
		pbi->nearestGoldenIndex = nearestIndex;
		pbi->nearestGolden = nearest;
		pbi->nearGolden = nearVector;
	}
}
