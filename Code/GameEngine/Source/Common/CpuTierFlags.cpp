// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// CPU-tier flags at 0x001C4390, calling the feature probe at 0x001D5470
// with three int* output slots. Ported from the Open-BFME-1 conversion of
// its twin (Code/GameEngine/Source/Common/BfmeCpuTierFlags.cpp): the
// 140-byte executable ends where its compiler-generated four-entry jump
// table begins. Spell out the original selector cases so MSVC regenerates
// both tables.

extern int __cdecl Rva001D5470_CpuFeatureProbe(void);

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB,
	int *pTierC)
{
	unsigned int subsystem = 1;
	if (Rva001D5470_CpuFeatureProbe())
		subsystem = 0xc;
	switch (subsystem)
	{
	case 0: case 2: case 4: case 5: case 8: case 9: case 10:
		*pTierA = 0;
		*pTierB = 0;
		*pTierC = 0;
		break;
	case 1: case 3: case 6: case 7:
		*pTierA = 1;
		*pTierB = 0;
		*pTierC = 0;
		break;
	case 11:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 0;
		break;
	case 12:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 1;
		break;
	}
}
