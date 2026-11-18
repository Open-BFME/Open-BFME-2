// cl: /DNDEBUG /MD
//
// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z,
// retail 0x002626B7, 67 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:735) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). Both TurretAI queries are direct
// (non-virtual) const calls, resolved by pins.

#include "../../../../Include/Common/ScalarTypes.h"

enum TurretTargetType
{
	TARGET_NONE = 0,
	TARGET_OBJECT = 1,
	TARGET_POSITION = 2
};

enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

#include "../../../../Include/GameLogic/Module/TurretStateMachine.h"

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum
{
	MAX_TURRETS = 1
};

#include "../../../../Include/GameLogic/Module/TurretAI.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z
Bool AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType wslot, const class Object *victim) const
{
	for (int i = 0; i < MAX_TURRETS; ++i)
	{
		if (m_turretAI[i] && m_turretAI[i]->isWeaponSlotOnTurret(wslot))
		{
			return m_turretAI[i]->isTryingToAimAtTarget(victim);
		}
	}
	return false;
}

// ?isTryingToAimAtTarget@TurretAI@@QBE_NPBVObject@@@Z
Bool TurretAI::isTryingToAimAtTarget(const Object *victim) const
{
	StateID sid = m_turretStateMachine->getCurrentStateID();

	Object *obj;
	Coord3D pos;
	if (sid == TURRETAI_AIM && friend_getTurretTarget(obj, pos) == TARGET_OBJECT && obj == victim)
		return true;
	return false;
}
