// cl: /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva0033A453@Rva0033A453@@QBE_NPBX0@Z @0x0033A453 66B
// 128-byte dual-mask tester: exempt mask disjoint plus required mask subset,
// one dword at a time over 32 dwords. Same 66B shape as Rva0026157ETestMasks
// at 0x0026157E (4 dwords) and BitFlags<116>::testSetAndClear at 0x0030A146
// (7 dwords); only the loop bound differs (0x20 vs 4 vs 7). Callers pass
// Object upgrade masks at +0x284 and Player masks at +0x13c ORed into a tmp
// (0x00507558) plus required/forbidden pairs at +0x04/+0x84 (0x0033A8D9,
// 0x00507558), +0x48/+0xC8 (0x00373EC6), +0xC4/+0x144 (0x004A3A20).
// Opaque Rva name: the BitFlags size behind the 128 bytes is unproven.
class Rva0033A453
{
public:
	bool rva0033A453(const void *required, const void *exempt) const;
};

bool Rva0033A453::rva0033A453(const void *required, const void *exempt) const
{
	const unsigned long *self = (const unsigned long *)this;
	const unsigned long *need = (const unsigned long *)required;
	const unsigned long *ban = (const unsigned long *)exempt;
	for (unsigned i = 0; i < 32; i++) {
		if ((ban[i] & self[i]) != 0)
			return false;
		if ((need[i] & self[i]) != need[i])
			return false;
	}
	return true;
}
