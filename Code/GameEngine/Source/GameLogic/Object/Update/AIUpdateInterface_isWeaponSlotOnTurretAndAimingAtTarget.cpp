// cl: /O1 /DNDEBUG /MD
//
// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z,
// retail 0x002626B7, 67 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:735) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). Both TurretAI queries are direct
// (non-virtual) const calls, resolved by pins.

typedef bool Bool;

typedef int StateID;

enum
{
	INVALID_STATE_ID = 999999
};

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

// BFME2 retail layout, every offset read directly by the byte-true body:
// the state machine pointer sits at +0x14, its current-state link at +0x04,
// and the StateID four bytes into the state.
struct TurretState
{
	char m_pad[4];
	StateID m_stateID;
};

struct TurretStateMachine
{
	char m_pad[4];
	const TurretState *m_currentState;
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum
{
	MAX_TURRETS = 1
};

struct TurretAI
{
	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
	Bool isTryingToAimAtTarget(const class Object *victim) const;
	TurretTargetType friend_getTurretTarget(Object *&obj, Coord3D &pos) const;

private:
	char m_pad[0x14];
	const TurretStateMachine *m_turretStateMachine;
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[MAX_TURRETS];

public:
	Bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType wslot, const class Object *victim) const;
};

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
	const TurretStateMachine *machine = m_turretStateMachine;
	StateID sid = machine->m_currentState ? machine->m_currentState->m_stateID : INVALID_STATE_ID;

	Object *obj;
	Coord3D pos;
	if (sid == TURRETAI_AIM && friend_getTurretTarget(obj, pos) == TARGET_OBJECT && obj == victim)
		return true;
	return false;
}
