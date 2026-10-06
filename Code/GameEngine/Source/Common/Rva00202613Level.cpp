// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// ?rva00202613@Rva00202613@@QAEHM@Z @0x00202613 32B. Float-to-LOD-level lookup:
// converts the float arg to int then scans the 5-entry 16B-stride threshold
// table at +0x1C8..+0x208 from the top, returning the highest index whose
// threshold is below the value, or 0.
// Evidence: neighbour row 0x00202633 applies a level*16 table entry at
// +0x1CC; caller 0x00043FE5; /arch:SSE for retail cvttss2si.
struct LODEntry
{
	int m_threshold; // +0 compared against the converted value
	int m_a; // +4
	int m_b; // +8
	int m_c; // +12
};

class Rva00202613
{
public:
	int rva00202613(float v);

private:
	char m_pad0[0x1c8]; // +0x00..+0x1C8 unknown
	LODEntry m_lod[5]; // +0x1C8..+0x208 thresholds
	char m_pad1[0x17a0 - 0x208]; // +0x208.. end, matches sibling size
};

int Rva00202613::rva00202613(float v)
{
	int level = (int)v;
	int idx = 4;
	LODEntry *e = &m_lod[4];
	do {
		if (e->m_threshold < level)
			return idx;
		--idx;
		--e;
	} while (idx >= 0);
	return 0;
}
