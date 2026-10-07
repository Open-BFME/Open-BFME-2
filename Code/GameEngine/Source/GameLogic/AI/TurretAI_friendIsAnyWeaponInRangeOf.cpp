// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/turretai -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
#include "PreRTS.h"

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
class Weapon
{
public:
	Bool isWithinAttackRange(const Object* source, const Object* target,
		Real rangeAdjustment, int options) const;
};

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

Bool TurretAI::friend_isAnyWeaponInRangeOf(const Object* o) const
{
	for (Int i = 0; i < 6; ++i)
	{
		const Weapon* w = ((WeaponSet*)((char*)getOwner() + 0x330))->getWeaponInWeaponSlot((WeaponSlotType)i);
		if (w == NULL || !isWeaponSlotOnTurret((WeaponSlotType)i))
			continue;

		if (w->isWithinAttackRange(getOwner(), o, 0.0f, TRUE))
			return TRUE;
	}

	return FALSE;
}
