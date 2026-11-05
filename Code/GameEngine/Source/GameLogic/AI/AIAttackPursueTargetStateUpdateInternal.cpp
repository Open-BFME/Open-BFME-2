// cl: /DNDEBUG /MD
//
// ?updateInternal@AIAttackPursueTargetState@@AAE?AW4StateReturnType@@XZ @0x0034939E 515B
// Evidence: pinned name; callers 0x003495A9 (rowed update); donor ZH AIStates.cpp:3025
// plus BFME1 game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp;
// retail CritterDesync ComputePath14 log, testStatus 0x33, TurretStateMachine goal checks.

typedef bool Bool;
typedef float Real;


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

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"



#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AIAttackPursueTargetState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();
	unsigned char m_pad4C[0x5E - 0x4C];
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
