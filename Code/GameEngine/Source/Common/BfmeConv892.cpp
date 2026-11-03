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
	void *m_weaponSlot;
	void *m_bfmeB;
	char m_bfmeFlag;
};

class BfmeObjFCD;

// Retail 0x00290B24, the callee this body invokes on o, is rowed as
// Object::setWeaponLock(WeaponSlotType, WeaponLockType)
// (ObjectWeaponSetFlags.cpp); the pair's two words are its arguments.
enum WeaponSlotType { WEAPON_SLOT_INVALID = -1 };
enum WeaponLockType { WEAPON_LOCK_INVALID = -1 };
#include "../GameLogic/Object/object.h"

void bfmeGoFCD(BfmeObjFCD *o, BfmePairFCD *p)
{
	char r = (((Object *)o)->setWeaponLock((WeaponSlotType)(int)p->m_weaponSlot,
		(WeaponLockType)(int)p->m_bfmeB) == 0);
	p->m_bfmeFlag |= r;
}