// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?bfmeGo940G@BfmeThing940G@@QAEXXZ
// retail 0x004B8CC9, 21 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeConv940.cpp (reference/open-bfme-1 @ 6d943426).
// Compiled /Os the donor body is byte-identical to retail once relocations are
// masked (unique hit on unclaimed .text). Only the placed body is defined here;
// the donor's other definitions are omitted.

// The callee is the rowed Object::setWeaponLock.
enum WeaponSlotType { WEAPONSLOT_UNUSED940 };
enum WeaponLockType { WEAPONLOCK_UNUSED940 };
class Object
{
public:
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
};

struct BfmeA940G
{
	char m_bfmePad[8];
	void *m_bfmeVal;
};

class BfmeB940G
{
public:
	void bfmeCall940G(void *v, int f);
};

class BfmeThing940G
{
public:
	void bfmeGo940G();
	char m_bfmePad[4];
	char m_bfmeFlag;
};

void BfmeThing940G::bfmeGo940G()
{
	BfmeA940G *a = *(BfmeA940G **)((char *)this - 0xc);
	m_bfmeFlag = 0;
	void *v = a->m_bfmeVal;
	BfmeB940G *b = *(BfmeB940G **)((char *)this - 8);
	((Object *)b)->setWeaponLock((WeaponSlotType)(int)v, (WeaponLockType)2);
}