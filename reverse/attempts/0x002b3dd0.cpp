// ?rva002B3DD0@Rva002B4650@@QAEHXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /MD
// ?rva002B3DD0@Rva002B4650@@QAEHXZ @0x002B3DD0 20B.
// Align-up helper: ceil(pinned 0x002B3DB2 result / g_Va00DBA4E4) via
// lea eax,[eax+ecx-1] plus xor-div. Same-this thiscall passthrough to the
// pinned Rva002B4650 getter (no ecx setup); unsigned div normalizes.
// Evidence: pin 0x002B3DB2 QAEHXZ, global g_Va00DBA4E4 3HA, callers
// 0x00574306 0x005750AA, unblocks 0x00575038.
class Rva002B4650
{
public:
	int rva002B3DB2();
	int rva002B3DD0();
};

extern int g_Va00DBA4E4;

// ?rva002B3DD0@Rva002B4650@@QAEHXZ present-unmatched
int Rva002B4650::rva002B3DD0()
{
	int a = rva002B3DB2();
	unsigned int b = (unsigned int)g_Va00DBA4E4;
	return (int)(((unsigned int)a + (b - 1u)) / b);
}
