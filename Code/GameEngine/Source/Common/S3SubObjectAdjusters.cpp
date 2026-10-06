// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3SubObjectAdjusters.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only this one placed
// body is defined here; the donor's Gen_002DB3C0::bfmeForward stays out, so the
// unmatched-definition gate passes.
//
// This is one of two sub-object adjusters (DevastateSpecialPower's and
// PlayerHealSpecialPower's moved to their own doSpecialPowerAtObject TUs).
//
// It rewrites one pointer argument IN PLACE -- add 0x38, store it back into
// the same stack slot -- and then tail-jumps through a virtual slot. Rewriting
// the slot rather than pushing a new frame is what makes the tail jump
// possible: the callee sees the same argument count in the same positions.
//
// In source that adjustment is not arithmetic but a member address: the
// argument points at a whole object and the virtual takes the sub-object that
// lives at +0x38 of it.

struct BfmeSub
{
	char m_bfmeBytes[4];
};

struct BfmeWhole
{
	char m_bfmeHead[0x38];
	BfmeSub m_bfmeSub;					// +0x38
};

class Gen_002DE910
{
public:
	void bfmeForward(void *first, BfmeWhole *whole);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeVirtual(void *first, BfmeSub *sub);		// slot 6, vtable+0x18
};

// ?bfmeForward@Gen_002DE910@@QAEXPAXPAUBfmeWhole@@@Z 0x0050B97B
void Gen_002DE910::bfmeForward(void *first, BfmeWhole *whole)
{
	bfmeVirtual(first, &whole->m_bfmeSub);
}
