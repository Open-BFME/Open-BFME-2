// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C1CC@Object@@QBE_NXZ @0x0028C1CC 67B
// Object weapon-or-recent-frame predicate. Evidence: thiscall via callers
// 0x00493645 0x00438152 0x002610C6 0x00294422 (ecx=Object); rowed callees
// getCurrentWeapon 0x0028AEBD and computeStatus 0x002CC422 both with NULL
// plus rva0028AF76 0x0028AF76; globals LogicFramesPerSecond 0x00DBA4E4 (=5)
// and TheGameLogic frame 0x00DFE78C+0x40; bool return via al; name stays
// address-derived (Object owner proven by callers, identity unproven).
extern int BfmeLogicFramesPerSecond;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	WEAPON_STATUS_5
};

#include "../../../Include/GameLogic/Weapon.h"

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	int rva0028AF76() const;
	bool rva0028C1CC() const;
};

#include "../../Common/GameLogicObjectLookupView.h"

extern class GameLogic *TheGameLogic;
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

bool Object::rva0028C1CC() const
{
	const Weapon *weapon = getCurrentWeapon((WeaponSlotType *)0);
	if (weapon != 0)
	{
		if (weapon->computeStatus((bool *)0) != READY_TO_FIRE)
			return true;
		unsigned value = (unsigned)rva0028AF76();
		if (value > 2u)
		{
			if (value + (unsigned)LogicFramesPerSecond * 2u > TheGameLogic->getFrame())
				return true;
		}
	}
	return false;
}
