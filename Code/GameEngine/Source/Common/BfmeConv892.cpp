// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoFCD@@YAXPAVBfmeObjFCD@@PAUBfmePairFCD@@@Z
// retail 0x0046258C, 30 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv892.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
struct BfmePairFCD
{
	void *m_bfmeA;
	void *m_bfmeB;
	char m_bfmeFlag;
};

class BfmeObjFCD
{
public:
	typedef char (BfmeObjFCD::*BfmeCallFCDMember)(void *, void *);
	union BfmeCallFCDTarget
	{
		void (*asFunction)();
		BfmeCallFCDMember asMember;
	};
};

// Retail 0x00290B24: the member-function thunk this body invokes. A ghidra
// function start (FUN_00690b24, 79 bytes) with no ledger row and no pin, so
// the donor's own name is pinned for it; the address is read off retail's
// REL32 at 0x0046259B, next-instruction 0x004625A0 less displacement
// 0xFFFFE585 giving 0x004625A0 - 0x1A7B. Carried from the donor source; the
// body at the address remains unrecovered.
extern void j_0003eebe();

void bfmeGoFCD(BfmeObjFCD *o, BfmePairFCD *p)
{
	BfmeObjFCD::BfmeCallFCDTarget callFCD;
	callFCD.asFunction = j_0003eebe;
	char r = ((o->*callFCD.asMember)(p->m_bfmeA, p->m_bfmeB) == 0);
	p->m_bfmeFlag |= r;
}