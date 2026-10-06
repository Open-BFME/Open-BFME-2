// cl: /DNDEBUG /MD
//
// WeaponSet::setWeaponLock, retail 0x002C8AAE (237 bytes).
// Identity: Zero Hour WeaponSet.cpp setWeaponLock (false for NOT_LOCKED or an
// empty slot; LOCKED_PERMANENTLY always takes the slot, LOCKED_TEMPORARILY only
// when not permanently locked; true otherwise), called with m_weaponSet as this
// by the matched Object::setWeaponLock 0x00290B24. Layout from the body:
// m_weapons at +0x08, current weapon +0x20, lock status +0x24, owner ObjectID
// +0x3C.
// BFME2 additions: look the owner up first; clear the five weapon-slot model
// conditions 0x90..0x94 on it (mask built by the matched placeholder row
// 0x000B6253 in a 0x4C-byte local, i.e. a 19-word model-condition mask, and
// applied by the matched placeholder row 0x001E42F2, whose this is the Object;
// both rows keep their placeholder class names, hence the casts) and set the
// one of the current slot (switch with literal cases; cl merges the five
// masked-word test/or tails). The false path is laid out last, which needs the
// early-out tests folded into one guarding if.

enum ObjectID
{
	INVALID_ID = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
// Placeholder rows: 0x000B6253 fills a 0x4C-byte (19-word) model-condition mask
// with up to five bits and returns it; 0x001E42F2 clears such a mask on an
// Object (its this is the Object).
class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int count, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
private:
	unsigned int m_words[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
class Weapon;
class WeaponSet
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
private:
	unsigned char m_pad00[8];
	Weapon *m_weapons[5]; // +0x08
	unsigned char m_pad1C[4];
	WeaponSlotType m_curWeapon; // +0x20
	WeaponLockType m_curWeaponLockedStatus; // +0x24
	unsigned char m_pad28[0x3C - 0x28];
	ObjectID m_ownerID; // +0x3C
};
bool WeaponSet::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (lockType != NOT_LOCKED && m_weapons[weaponSlot] != 0)
	{
		if (lockType == LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		else if (lockType == LOCKED_TEMPORARILY && m_curWeaponLockedStatus != LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		if (owner)
		{
			Rva000B6253 mask;
			((Rva001E42F2 *)owner)->rva001E42F2((const int *)mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94));
		}
		switch (m_curWeapon)
		{
		case 0:
			if (owner)
				setModelConditionBit(owner, 0x90);
			break;
		case 1:
			if (owner)
				setModelConditionBit(owner, 0x91);
			break;
		case 2:
			if (owner)
				setModelConditionBit(owner, 0x92);
			break;
		case 3:
			if (owner)
				setModelConditionBit(owner, 0x93);
			break;
		case 4:
			if (owner)
				setModelConditionBit(owner, 0x94);
			break;
		}
		return true;
	}
	return false;
}
