// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoESB@BfmeThingESB@@QAE_NPAVBfmeObjESA@@@Z
// retail 0x00260E2A, 26 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv884.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
class Player;

// The ledger names bfmeGoESB's parameter BfmeObjESA, so the body-facing
// stand-in keeps that spelling; the call this body makes is retail's real
// Object::getControllingPlayer (0x001BE3F0, pinned), named on the retail type
// through a no-op pointer cast.
class Object
{
public:
	Player *getControllingPlayer() const;
};

class BfmeObjESA
{
};

struct BfmeThingESB
{
	bool bfmeGoESB(BfmeObjESA *o);
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

bool BfmeThingESB::bfmeGoESB(BfmeObjESA *o)
{
	return m_bfmeP == ((Object *)o)->getControllingPlayer();
}