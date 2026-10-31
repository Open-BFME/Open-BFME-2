// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os
// stlport
typedef bool Bool;
typedef int Int;

// The TU's six-slot WeaponSlotType.
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

// BFME1 donor: TurretAI::friend_isAnyWeaponInRangeOf, TurretAI.cpp:1014.
// Retail's 0x4D8310 body confirms the loop and the BFME2 deltas: six slots
// (rather than the donor's WEAPONSLOT_COUNT) and the range overload called
// with owner, target, 0.0f, and 1. These minimal TU-local views avoid the
// unrelated TurretAIData layout used by adjacent recovery work.
class Object;
class Weapon;

class WeaponSet
{
public:
	Weapon* getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

// Retail forms owner + 0x330 before calling WeaponSet. This access offset
// is established by this caller; it does not define an Object accessor.
#include "../../../Include/GameLogic/Weapon.h"

class TurretAI
{
public:
	Object* getOwner() const { return m_owner; }
	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
	Bool friend_isAnyWeaponInRangeOf(const Object* o) const;

private:
	char m_prefix[0x10];
	Object* m_owner;
};

Bool TurretAI::friend_isAnyWeaponInRangeOf(const Object* object) const
{
	for (Int i = 0; i < 6; ++i)
	{
		const Weapon* weapon = ((WeaponSet*)((char*)getOwner() + 0x330))->getWeaponInWeaponSlot((WeaponSlotType)i);
		if (weapon == 0 || !isWeaponSlotOnTurret((WeaponSlotType)i))
			continue;

		if (weapon->isWithinAttackRange(getOwner(), object, 0.0f, 1))
			return true;
	}

	return false;
}
