// cl: /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// Dedicated TU for the 16-byte dual-mask tester at retail 0x0026157E
// (66 bytes, leaf, no calls). Tests that the exempt mask is disjoint from
// this mask and the required mask is a subset of it, one dword at a time
// over four dwords, returning false on the first failure. Same role as
// BitFlags testSetAndClear (mustBeSet subset plus mustBeClear disjoint,
// pure test, no writes), but retail walks raw dwords where BFME1 calls
// bitset members, so the loop is written out explicitly. Callers pass the
// object status at +0x94 with DieMuxData required/exempt masks (see
// Object::isDieAbleToAttack-class users like DieMuxData::isDieApplicable).
// Opaque Rva name: the BitFlags size behind the 16 bytes is unproven.
class Rva0026157E
{
public:
	bool testMasks(const void *required, const void *exempt) const;
};

bool Rva0026157E::testMasks(const void *required, const void *exempt) const
{
	const unsigned long *self = (const unsigned long *)this;
	const unsigned long *need = (const unsigned long *)required;
	const unsigned long *ban = (const unsigned long *)exempt;
	for (unsigned i = 0; i < 4; i++) {
		if ((ban[i] & self[i]) != 0)
			return false;
		if ((need[i] & self[i]) != need[i])
			return false;
	}
	return true;
}
