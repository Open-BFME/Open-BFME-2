// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c7040.md plus retail only.
// No decoder source was consulted.
// ?Rva009B6740BuildTable@@YAXPAE@Z retail 0x001C7040..0x001C7241 (514 bytes)
// (spec name VP6_BuildModeTree; the name is the existing pin that the
// matched caller Rva009B6A30LoadTables.cpp already calls). cdecl taking the
// decoder instance. For each previous mode (outer) and context type (inner)
// it weights every mode by 100 times the type's first transmitted row at
// 0x72C (the previous mode itself counts 0) then stores the same-mode
// probability at 0x77C (signed division 0x001C70BC) and the nine mode-tree
// probabilities at 0x7A4 (unsigned divisions of the grouped counts). The
// instance is reached through the byte-pointer argument itself: a separate
// typed local lets MSVC reuse the argument slot and drops retail's frame
// slot at [esp+0x10].
struct Vp6ModeTreeInstance {
	unsigned char unknown0[0x72c];
	unsigned char probXmitted[3][2][10];
	unsigned char unknown768[0x77c - 0x768];
	unsigned char probModeSame[3][10];
	unsigned char unknown79a[0x7a4 - 0x79a];
	unsigned char probMode[3][10][9];
};
#define pbi ((Vp6ModeTreeInstance *)instance)
void Rva009B6740BuildTable(unsigned char *instance)
{
	unsigned count[10];
	int prev, type, mode;
	for (prev = 0; prev < 10; prev++) {
		for (type = 0; type < 3; type++) {
			unsigned total = 0;
			for (mode = 0; mode < 10; mode++) {
				if (prev == mode)
					count[mode] = 0;
				else
					count[mode] = 100 * pbi->probXmitted[type][0][mode];
				total += count[mode];
			}
			pbi->probModeSame[type][prev] = 255 - 255 * pbi->probXmitted[type][1][prev] /
				(1 + pbi->probXmitted[type][1][prev] + pbi->probXmitted[type][0][prev]);
			pbi->probMode[type][prev][0] = 1 + 255 * (count[0] + count[2] + count[3] + count[4]) / (1 + total);
			pbi->probMode[type][prev][1] = 1 + 255 * (count[0] + count[2]) / (1 + count[0] + count[2] + count[3] + count[4]);
			pbi->probMode[type][prev][2] = 1 + 255 * (count[1] + count[7]) / (1 + count[1] + count[5] + count[6] + count[7] + count[8] + count[9]);
			pbi->probMode[type][prev][3] = 1 + 255 * count[0] / (1 + count[0] + count[2]);
			pbi->probMode[type][prev][4] = 1 + 255 * count[3] / (1 + count[3] + count[4]);
			pbi->probMode[type][prev][5] = 1 + 255 * count[1] / (1 + count[1] + count[7]);
			pbi->probMode[type][prev][6] = 1 + 255 * (count[5] + count[6]) / (1 + count[5] + count[6] + count[8] + count[9]);
			pbi->probMode[type][prev][7] = 1 + 255 * count[5] / (1 + count[5] + count[6]);
			pbi->probMode[type][prev][8] = 1 + 255 * count[8] / (1 + count[8] + count[9]);
		}
	}
}
#undef pbi
