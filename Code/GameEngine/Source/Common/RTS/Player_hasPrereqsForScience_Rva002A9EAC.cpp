// cl: /MD /DNDEBUG
//
// ?hasPrereqsForScience@Player@@QBE_NW4ScienceType@@@Z
// retail 0x002A9EAC, 30 bytes (Ghidra FUN_006a9eac).
//
// Target evidence: pinned from the byte-verified
// Player::isCapableOfPurchasingScience (REL32 at 0x002ABEA0) between its
// hasScience and getSciencePurchaseCost checks, Zero Hour's order. The body
// is Zero Hour's one-liner, TheScienceStore->playerHasPrereqsForScience(this,
// st); BFME 2's store takes the player's science-holder base at +4 (the
// null-checked `this ? this+4 : 0`), the same Rva0043D3A8 view the rowed
// ScienceStore neighbour 0x001FF4D3 is pinned with.

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Rva0043D3A8
{
public:
	virtual void s00();
};

class PlayerSnapshotBase
{
public:
	virtual void s00();
};

class Player : public PlayerSnapshotBase, public Rva0043D3A8
{
public:
	bool hasPrereqsForScience(ScienceType t) const;
};

class ScienceStore
{
public:
	bool playerHasPrereqsForScience(const Rva0043D3A8 *player, ScienceType st) const;
};

extern ScienceStore *TheScienceStore;	// retail [0x00DFE0E0]

bool Player::hasPrereqsForScience(ScienceType t) const
{
	return TheScienceStore->playerHasPrereqsForScience(this, t);
}
