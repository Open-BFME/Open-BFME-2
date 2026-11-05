// cl: /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc 
//
// AttackStateMachine::AttackStateMachine, retail 0x00346D17 (654 bytes): Zero
// Hour's AttackStateMachine constructor (AIStates.cpp). The name is a target
// fact: the vftable 0x00811A68 it installs (dtor 0x0033FAE9, deleting dtor
// 0x0034314E in slot 0) has the name getter 0x0033FAF4 in slot 2, returning
// "AttackStateMachine". Aim, fire and the BFME 2
// re-aim state, then chase/approach unless immobile (a portable structure
// that can attack gets the always-aim chase state). Object conditions are the
// normal or forced table, replaced by BFME 2's status-0x26 tables (one for a
// turreted current weapon); position attacks use the position table. Base:
// the rowed StateMachine constructor 0x004D79E1 with the name key; states
// from plain operator new and their rowed constructors.
#include <stddef.h>
#include "Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
class Object;

#include "../../../Include/Common/StateConditionInfo.h"
#include "../../../Include/Common/StateMachineClass.h"
enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};
enum WhichTurretType
{
	TURRET_INVALID = -1
};
class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
};
struct ObjectTemplateBytes
{
	unsigned char m_pad000[0x108];
	unsigned char m_kind108; // +0x108 bit 2: immobile, bit 3: can attack
	unsigned char m_pad109[0x10F - 0x109];
	unsigned char m_kind10F; // +0x10F bit 1: portable structure
};
class Object
{
public:
	Bool testStatus(ObjectStatusTypes status) const;
	unsigned char m_pad00[0x04];
	const ObjectTemplateBytes *m_template; // +0x04
	unsigned char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai; // +0x258
};
// The attack state handed in; its +0x20 base is the fire state's interface.
class Rva00346D17AttackHead
{
public:
	virtual void v00();
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva00346D17AttackInterface
{
public:
	virtual void v00();
};
class Rva00346D17Attack : public Rva00346D17AttackHead, public Rva00346D17AttackInterface
{
};
class Rva0033F3B6
{
public:
	Rva0033F3B6(StateMachine *machine, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad00[0x24];
};
class Rva0033F483
{
public:
	Rva0033F483(StateMachine *machine, int attackInterface);
private:
	unsigned char m_pad00[0x28];
};
class Rva0033F43D
{
public:
	Rva0033F43D(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva004D74AC
{
public:
	Rva004D74AC(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class Rva004D7491
{
public:
	Rva004D7491(StateMachine *machine);
private:
	unsigned char m_pad00[0x20];
};
class AIAttackPursueTargetState
{
public:
	AIAttackPursueTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad00[0x64];
};
class AIAttackApproachTargetState
{
public:
	AIAttackApproachTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad00[0x74];
};
class AttackStateMachine : public StateMachine
{
public:
	AttackStateMachine(Object *obj, Rva00346D17Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking);
	virtual ~AttackStateMachine();
};
// The conditions the tables reference (retail .rdata entries).
bool rva00343DD8(void *thisState, void *userData);	// outOfWeaponRangeObject
class Rva00343F8A; struct Rva00343EFAState;
bool wantToSquishTarget(Rva00343EFAState *thisState);	// wantToSquishTarget
bool cannotPossiblyAttackObject(Rva00343F8A *thisState, void *userData);	// cannotPossiblyAttackObject
bool rva0033FD98(Rva00343F8A *thisState, void *userData);	// outOfWeaponRangePosition
int inWeaponRangeObject(void *thisState, void *userData);	// inWeaponRangeObject
enum
{
	CHASE_TARGET = 100,
	APPROACH_TARGET = 101,
	AIM_AT_TARGET = 102,
	FIRE_WEAPON = 103,
	REAIM_TARGET = 104,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

AttackStateMachine::AttackStateMachine(Object *obj, Rva00346D17Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking) : StateMachine(obj, nameKey, false)
{
	static const StateConditionInfo objectConditionsNormal[] =
	{
		{ (bool (*)(State *, void *))rva00343DD8, CHASE_TARGET, NULL },
		{ (bool (*)(State *, void *))wantToSquishTarget, CHASE_TARGET, NULL },
		{ (bool (*)(State *, void *))cannotPossiblyAttackObject, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
		{ NULL, 0, NULL }	// keep last
	};
	static const StateConditionInfo objectConditionsForced[] =
	{
		{ (bool (*)(State *, void *))rva00343DD8, CHASE_TARGET, NULL },
		{ (bool (*)(State *, void *))cannotPossiblyAttackObject, EXIT_MACHINE_WITH_FAILURE, (void *)3 },
		{ (bool (*)(State *, void *))wantToSquishTarget, CHASE_TARGET, NULL },
		{ NULL, 0, NULL }	// keep last
	};
	const StateConditionInfo *objectConditions = forceAttacking ? objectConditionsForced : objectConditionsNormal;
	if (obj->testStatus(OBJECT_STATUS_26))
	{
		static const StateConditionInfo statusConditions[] =
		{
			{ (bool (*)(State *, void *))cannotPossiblyAttackObject, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ NULL, 0, NULL }	// keep last
		};
		static const StateConditionInfo turretConditions[] =
		{
			{ (bool (*)(State *, void *))rva00343DD8, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ (bool (*)(State *, void *))cannotPossiblyAttackObject, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ NULL, 0, NULL }	// keep last
		};
		objectConditions = statusConditions;
		if (obj->m_ai && obj->m_ai->getWhichTurretForCurWeapon() != TURRET_INVALID)
			objectConditions = turretConditions;
	}
	static const StateConditionInfo positionConditions[] =
	{
		{ (bool (*)(State *, void *))rva0033FD98, CHASE_TARGET, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	defineState( AIM_AT_TARGET, (State *)new Rva0033F3B6( this, attackingObject, forceAttacking ), FIRE_WEAPON, EXIT_MACHINE_WITH_FAILURE, attackingObject ? objectConditions : positionConditions );
	defineState( FIRE_WEAPON, (State *)new Rva0033F483( this, (int)static_cast<Rva00346D17AttackInterface *>(att) ), REAIM_TARGET, CHASE_TARGET, attackingObject ? objectConditions : positionConditions );
	defineState( REAIM_TARGET, (State *)new Rva0033F43D( this ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
	// A same-valued template expression preserves retail's separate bit tests.
	if (((this ? obj->m_template : obj->m_template)->m_kind108 & 4) == 0)
	{
		if ((obj->m_template->m_kind10F & 2) && ((this?obj->m_template:obj->m_template)->m_kind108 & 8))
		{
			static const StateConditionInfo portableStructureChaseConditions[] =
			{
				{ (bool (*)(State *, void *))inWeaponRangeObject, AIM_AT_TARGET, NULL },
				{ NULL, 0, NULL }	// keep last
			};
			defineState( CHASE_TARGET, (State *)new Rva004D74AC( this ), EXIT_MACHINE_WITH_FAILURE, EXIT_MACHINE_WITH_FAILURE, portableStructureChaseConditions );
		}
		else if (attackingObject)
		{
			defineState( CHASE_TARGET, (State *)new AIAttackPursueTargetState( this, follow, attackingObject, forceAttacking ), APPROACH_TARGET, APPROACH_TARGET );
			defineState( APPROACH_TARGET, (State *)new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
		}
		else
		{
			defineState( CHASE_TARGET, (State *)new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
			defineState( APPROACH_TARGET, (State *)new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
		}
	}
	else
	{
		defineState( CHASE_TARGET, (State *)new Rva004D7491( this ), EXIT_MACHINE_WITH_FAILURE, EXIT_MACHINE_WITH_FAILURE );
	}
}
