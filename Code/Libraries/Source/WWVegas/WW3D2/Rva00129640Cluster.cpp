// cl: /O2 /G7 /DNDEBUG /MD
//
// Bounded array read and its cumulative push, living between the Debug_Statistics
// last-frame getters (0x00129590..0x00129680) and the SimpleDynVecClass accessor at
// 0x00129700. Count is the byte-verified g_stat10 (0x00DEE894) other matched rows
// already use; the three-entry buffer at 0x00DEE8E8 and the monotone source at
// 0x00DEE910 are address-derived. No callee or relocation, so the body is the only
// evidence for identity. /G7 is required for the retail `add reg,1` loop idiom
// (the /O2 default emits inc) and is the flags line Rva00129670Inc already proved.

extern int g_stat10;			// 0x00DEE894, number of live entries (capped at 3)
extern int g_Va00DEE8E8[];		// 0x00DEE8E8, three-entry buffer
extern int g_stat8;		// 0x00DEE910, monotone source value

// Defined here (DebugStatisticsBegin pattern for g_statN): .bss runtime
// buffer/source at distinct VAs, not the g_stat array, so no alias.
int g_Va00DEE8E8[3];

// ?Rva00129640Get@@YAHH@Z @ 0x00129640 (23B)
int Rva00129640Get(int index)
{
	if (index >= g_stat10)
		return 0;
	return g_Va00DEE8E8[index];
}

// ?Rva00129690@@YAXXZ @ 0x00129690 (86B)
void Rva00129690(void)
{
	int count = g_stat10;

	if (count >= 3)
		return;

	if (count == 0) {
		g_Va00DEE8E8[0] = g_stat8;
	} else {
		int sum = 0;

		for (int i = 0; i < count; i++)
			sum += g_Va00DEE8E8[i];

		g_Va00DEE8E8[count] = g_stat8 - sum;
	}

	g_stat10 = count + 1;
}
