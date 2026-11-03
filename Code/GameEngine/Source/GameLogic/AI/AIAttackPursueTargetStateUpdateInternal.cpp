// cl: /DNDEBUG /MD
//
// ?updateInternal@AIAttackPursueTargetState@@AAE?AW4StateReturnType@@XZ @0x0034939E 515B
// Evidence: pinned name; callers 0x003495A9 (rowed update); donor ZH AIStates.cpp:3025
// plus BFME1 game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp;
// retail CritterDesync ComputePath14 log, testStatus 0x33, TurretStateMachine goal checks.

typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WhichTurretType
{
	TURRET_INVALID = -1
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

enum ObjectStatusTypes
{
	STATUS_33 = 0x33
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class Player;
class Weapon;
class Pathfinder;
class Locomotor;
class AI;

class Rva0008BB38FloatField
{
public:
	Real get() const;
};

#include "../../../Include/GameLogic/LocomotorClass.h"

class AIUpdateInterface;

#include "../../../Include/GameLogic/AI.h"

extern class AI *TheAI;
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" void __cdecl fprintf(void *stream, const char *format, ...);

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/Weapon.h"

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *p);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Bool isSignificantlyAboveTerrain() const;
	Real rva0028AC7D() const;
	Bool rva0029493F(Object *other, int kind);
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;
	void *m_physics;
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed() const;
	Object *getGoalObject();
	unsigned char m_pad00[0x14];
	Object *m_owner;
};

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AIUpdateInterface : public AIUpdateSlots<136>
{
public:
	virtual void slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142() = 0;
	virtual void slot143() = 0;
	virtual void notifyVictimIsDead() = 0;
	void setCurrentVictim(const Object *victim);
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool force);
	void setDesiredSpeed(Real speed);
	unsigned char m_pad04[0x1F0 - 0x04];
	Locomotor *m_curLocomotor;
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07();
	virtual Bool isIdle() const;
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Bool computePath();
public:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual Bool computePath();
};

class AIAttackPursueTargetState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();
	unsigned char m_pad1C[0x5E - 0x1C];
	Bool m_stopIfInRange;
	Bool m_isInitialApproach;
	Bool m_isForceAttacking;
};

StateReturnType AIAttackPursueTargetState::updateInternal()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (m_machine->isGoalObjectDestroyed())
	{
		ai->notifyVictimIsDead();
		ai->setCurrentVictim(0);
		return STATE_FAILURE;
	}
	m_stopIfInRange = false;

	Object *source = m_machine->m_owner;
	StateReturnType code = STATE_FAILURE;
	Object *victim = m_machine->getGoalObject();
	if (victim)
	{
		if (victim->testStatus((ObjectStatusTypes)0x33))
			return STATE_FAILURE;
		if (victim->rva002943B2(source->getControllingPlayer()))
			return STATE_FAILURE;
		ai->setCurrentVictim(victim);
		if (g_00E03745)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "CritterDesync: ComputePath14");
		}
		if (!computePath())
			return STATE_FAILURE;
		code = AIInternalMoveToState::update();
		if (code != STATE_CONTINUE)
			return STATE_SUCCESS;
		const Weapon *weapon = source->getCurrentWeapon(0);
		if (!weapon)
			return STATE_FAILURE;
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur == TURRET_INVALID)
			return STATE_SUCCESS;
		Bool viewBlocked = false;
		if (ai->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
		{
			Pathfinder *pf = TheAI->m_pathfinder;
			viewBlocked = pf->isAttackViewBlockedByObstacle(source, source->m_position, victim, victim->m_position);
		}
		if (!viewBlocked && victim->m_physics && weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		{
			ai->setTurretTargetObject(tur, victim, m_isForceAttacking);
			m_isInitialApproach = false;
			Real victimSpeed = victim->rva0028AC7D();
			if (((Weapon *)weapon)->isWithinAttackRange(source, &source->m_position, victim, &victim->m_position, 0.0f, true))
				victimSpeed *= 0.95f;
			if (source->rva0029493F(victim, 2))
				victimSpeed = 999999.0f;
			ai->setDesiredSpeed(victimSpeed);
			Locomotor *locomotor = ai->m_curLocomotor;
			if (locomotor && ((Rva0008BB38FloatField *)locomotor)->get() == 0.0f)
				return STATE_SUCCESS;
		}
		else
		{
			ai->setDesiredSpeed(999999.0f);
		}
	}
	return code;
}
