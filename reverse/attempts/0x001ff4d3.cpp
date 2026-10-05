// ?rva001FF4D3@ScienceStore@@QBE_NPAVRva0043D3A8@@W4ScienceType@@@Z
// partial score=0.9 date=2026-10-05
// cl: /Os /DNDEBUG /MD /EHsc
// ?rva001FF4D3@ScienceStore@@QBE_NPAVRva0043D3A8@@W4ScienceType@@@Z @0x001FF4D3 (58B).
// Purchasability check: pin-only playerHasPrereqsForScience 0x001FF47D, then
// holder vslot 1 against rowed getSciencePurchaseCost 0x001FF3DC. Caller is
// AptSpellStore::OnBttnSpell 0x0043D65F in parseSpellIndex_Thunk.cpp.
// Prev 0x001FF449 ScienceStoreNameDescription, next 0x001FF50D IsValidScience.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Rva0043D3A8
{
public:
	virtual bool v00(ScienceType science);
	virtual int v01();
};

class ScienceStore
{
public:
	bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType science) const;
	int getSciencePurchaseCost(ScienceType science) const;
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
};

// ?rva001FF4D3@ScienceStore@@QBE_NPAVRva0043D3A8@@W4ScienceType@@@Z
bool ScienceStore::rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const
{
	if (!playerHasPrereqsForScience(holder, science))
		return false;
	int points = holder->v01();
	int cost = getSciencePurchaseCost(science);
	if (cost <= points)
		return true;
	return false;
}
