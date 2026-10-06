// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?allow@Rva00260E2AFilter@@UAE_NPAVObject@@@Z (BFME1 donor ?bfmeGoESB@BfmeThingESB)
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

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// Partition filter vftable 0x00BFAD04 slot 1, built inline by RespawnUpdate
// 0x004AF1CE and 5 more matched users under this address-derived name: is
// the candidate controlled by the +0x08 player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *o);
	void *m_bfmeP;
};

bool Rva00260E2AFilter::allow(Object *o)
{
	return m_bfmeP == o->getControllingPlayer();
}