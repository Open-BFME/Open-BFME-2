// ??0Rva00346D17@@QAE@PAVObject@@PAVRva00346D17Attack@@I_N22@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Rva00346D17::Rva00346D17, retail 0x00346D17 (654 bytes): Zero Hour's
// AttackStateMachine constructor (AIStates.cpp): aim, fire and the BFME 2
// re-aim state, then chase/approach unless immobile (a portable structure
// that can attack gets the always-aim chase state). Object conditions are the
// normal or forced table, replaced by BFME 2's status-0x26 tables (one for a
// turreted current weapon); position attacks use the position table. Base:
// the rowed StateMachine constructor 0x004D79E1 with the name key; states
// from plain operator new and their rowed constructors.
#include "../../../Code/Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
#define NULL 0
class Object;

struct StateConditionInfo
{
	void *m_test;
	StateID m_toStateID;
	void *m_userData;
};
struct State
{
public:
	virtual ~State();
};
class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}
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
class Rva0033F3B6 : public State
{
public:
	Rva0033F3B6(StateMachine *machine, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int attackInterface);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F43D : public State
{
public:
	Rva0033F43D(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva004D74AC : public State
{
public:
	Rva004D74AC(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva004D7491 : public State
{
public:
	Rva004D7491(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class AIAttackPursueTargetState : public State
{
public:
	AIAttackPursueTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad04[0x64 - 0x04];
};
class AIAttackApproachTargetState : public State
{
public:
	AIAttackApproachTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	unsigned char m_pad04[0x74 - 0x04];
};
class Rva00346D17 : public Rva004D759C
{
public:
	Rva00346D17(Object *obj, Rva00346D17Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking);
	virtual ~Rva00346D17();
};
// The conditions the tables reference (retail .rdata entries).
Bool rva00343DD8(State *thisState, void *userData);	// outOfWeaponRangeObject
Bool rva00343EFA(State *thisState, void *userData);	// wantToSquishTarget
Bool rva0033FDEB(State *thisState, void *userData);	// cannotPossiblyAttackObject
Bool rva0033FD98(State *thisState, void *userData);	// outOfWeaponRangePosition
Bool rva00343EE5(State *thisState, void *userData);	// inWeaponRangeObject
enum
{
	CHASE_TARGET = 100,
	APPROACH_TARGET = 101,
	AIM_AT_TARGET = 102,
	FIRE_WEAPON = 103,
	REAIM_TARGET = 104,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

Rva00346D17::Rva00346D17(Object *obj, Rva00346D17Attack *att, UnsignedInt nameKey, Bool follow, Bool attackingObject, Bool forceAttacking) : Rva004D759C(obj, nameKey, false)
{
	static const StateConditionInfo objectConditionsNormal[] =
	{
		{ (void *)rva00343DD8, CHASE_TARGET, NULL },
		{ (void *)rva00343EFA, CHASE_TARGET, NULL },
		{ (void *)rva0033FDEB, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
		{ NULL, 0, NULL }	// keep last
	};
	static const StateConditionInfo objectConditionsForced[] =
	{
		{ (void *)rva00343DD8, CHASE_TARGET, NULL },
		{ (void *)rva0033FDEB, EXIT_MACHINE_WITH_FAILURE, (void *)3 },
		{ (void *)rva00343EFA, CHASE_TARGET, NULL },
		{ NULL, 0, NULL }	// keep last
	};
	const StateConditionInfo *objectConditions = forceAttacking ? objectConditionsForced : objectConditionsNormal;
	if (obj->testStatus(OBJECT_STATUS_26))
	{
		static const StateConditionInfo statusConditions[] =
		{
			{ (void *)rva0033FDEB, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ NULL, 0, NULL }	// keep last
		};
		static const StateConditionInfo turretConditions[] =
		{
			{ (void *)rva00343DD8, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ (void *)rva0033FDEB, EXIT_MACHINE_WITH_FAILURE, (void *)2 },
			{ NULL, 0, NULL }	// keep last
		};
		objectConditions = statusConditions;
		if (obj->m_ai && obj->m_ai->getWhichTurretForCurWeapon() != TURRET_INVALID)
			objectConditions = turretConditions;
	}
	static const StateConditionInfo positionConditions[] =
	{
		{ (void *)rva0033FD98, CHASE_TARGET, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	defineState( AIM_AT_TARGET, new Rva0033F3B6( this, attackingObject, forceAttacking ), FIRE_WEAPON, EXIT_MACHINE_WITH_FAILURE, attackingObject ? objectConditions : positionConditions );
	defineState( FIRE_WEAPON, new Rva0033F483( this, (int)static_cast<Rva00346D17AttackInterface *>(att) ), REAIM_TARGET, CHASE_TARGET, attackingObject ? objectConditions : positionConditions );
	defineState( REAIM_TARGET, new Rva0033F43D( this ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
	if ((obj->m_template->m_kind108 & 4) == 0)
	{
		if ((obj->m_template->m_kind10F & 2) && (obj->m_template->m_kind108 & 8))
		{
			static const StateConditionInfo portableStructureChaseConditions[] =
			{
				{ (void *)rva00343EE5, AIM_AT_TARGET, NULL },
				{ NULL, 0, NULL }	// keep last
			};
			defineState( CHASE_TARGET, new Rva004D74AC( this ), EXIT_MACHINE_WITH_FAILURE, EXIT_MACHINE_WITH_FAILURE, portableStructureChaseConditions );
		}
		else if (attackingObject)
		{
			defineState( CHASE_TARGET, new AIAttackPursueTargetState( this, follow, attackingObject, forceAttacking ), APPROACH_TARGET, APPROACH_TARGET );
			defineState( APPROACH_TARGET, new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
		}
		else
		{
			defineState( CHASE_TARGET, new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
			defineState( APPROACH_TARGET, new AIAttackApproachTargetState( this, follow, attackingObject, forceAttacking ), AIM_AT_TARGET, EXIT_MACHINE_WITH_FAILURE );
		}
	}
	else
	{
		defineState( CHASE_TARGET, new Rva004D7491( this ), EXIT_MACHINE_WITH_FAILURE, EXIT_MACHINE_WITH_FAILURE );
	}
}
