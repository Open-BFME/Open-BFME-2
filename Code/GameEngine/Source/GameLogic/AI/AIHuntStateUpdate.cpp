// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// AIHuntState::update, retail 0x003464D1 (828 bytes): slot 6 of the
// AIHuntState vtable 0x00C118B0 (its slot-2 name getter returns
// "AIHuntState"; the rowed onExit 0x003421F4 is slot 5). The BFME 2 version
// of Zero Hour's AIStates.cpp body. Layout: the hunt sub-machine at +0x20
// and m_nextEnemyScanTime at +0x24 (Zero Hour's order).
//
// BFME 2 additions to Zero Hour's body:
//  - A goal ID on the owning machine that the hunt machine lacks is handed
//    down first (or cleared when the object is gone), attacking from idle.
//  - Status 0x1C, or a contained owner whose template has kind byte +0x115
//    bit 5 when the contain's slot-31 interface accepts the hunt goal
//    (slot 88; goals with kind byte +0x108 bit 7 never count), skips the
//    scan.
//  - The scan rate is three times the int global g_00DBA4E4.
//  - AI slot 90 with a busy hunt state (state byte +0x1C clear and state
//    slot 8 false) delays the next scan without searching.
//  - AI::findClosestEnemy takes two more arguments and the team-target
//    priorities are the float AttackPriorityInfo::getPriority(owner, obj,
//    true). A new victim on an empty hunt machine plays the attack voice.

#include "../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateID
{
	AI_IDLE = 0,
	AI_ATTACK_OBJECT = 10,
	AI_PICK_UP_CRATE = 0x27,
	INVALID_STATE_ID = 999999
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_1C = 0x1C
};

class Object;
class AttackPriorityInfo;
class PartitionFilter;

// Int global tripled into the enemy scan interval.
extern int g_00DBA4E4;
#define ENEMY_SCAN_RATE (g_00DBA4E4 * 3)

template <int N> class AIHuntSlots : public AIHuntSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIHuntSlots<0>
{
};

class AttackPriorityInfo
{
public:
	Real getPriority(const Object *obj, const Object *target, Bool b) const;
};

class AIHuntState;

class AIUpdateInterface : public AIHuntSlots<90>
{
	friend class AIHuntState;
public:
	virtual Bool slot90() = 0;

	Object *checkForCrateToPickup();
	const AttackPriorityInfo *getAttackInfo() const { return m_attackInfo; }
protected:
	void playAttackVoiceResponse(Object *victim);
private:
	unsigned char m_pad004[0x70 - 0x04];
	const AttackPriorityInfo *m_attackInfo; // +0x70
};

// The contain's slot-31 interface; slot 88 accepts a hunt goal.
class AIHuntContainTarget : public AIHuntSlots<88>
{
public:
	virtual Bool slot88(Object *goal) = 0;
};

class ContainModuleInterface : public AIHuntSlots<31>
{
public:
	virtual AIHuntContainTarget *slot31() = 0;
};

class ThingTemplate
{
public:
	Bool testKind108() const { return (m_kind[0x108 - 0x108] & 0x80) != 0; }
	Bool testKind10B() const { return (m_kind[0x10B - 0x108] & 0x02) != 0; }
	Bool testKind115() const { return (m_kind[0x115 - 0x108] & 0x20) != 0; }
private:
	unsigned char m_pad000[0x108];
	unsigned char m_kind[0x18]; // +0x108
};

struct TeamTemplateInfo
{
	unsigned char m_pad000[0x216];
	Bool m_attackCommonTarget; // +0x216
};

struct TeamPrototype
{
	const TeamTemplateInfo *getTemplateInfo() const { return &m_info; }
	TeamTemplateInfo m_info;
};

class Team
{
public:
	const TeamPrototype *getPrototype() const { return m_proto; }
	Object *getTeamTargetObject();
	void rva0039D84A(Object *target);
private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};

class Player
{
public:
	Bool getUnitsShouldHunt() const { return m_unitsShouldHunt; }
private:
	unsigned char m_pad000[0x33D];
	Bool m_unitsShouldHunt; // +0x33D
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isOutOfAmmo() const;
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() { return m_team; }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x250 - 0x08];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
};

class AI
{
public:
	enum
	{
		CAN_ATTACK_BFME = 0x4A
	};
	Object *findClosestEnemy(const Object *me, Real range, UnsignedInt qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int bfmeArg);
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;

class State
{
public:
	virtual ~State();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void slot05();
	virtual StateReturnType update();
	virtual void slot07();
	virtual Bool slot08(); // the idle test StateMachine::isInIdleState reads

	StateID getID() const { return m_ID; }
	Bool getFlag1C() const { return m_flag1C; }
protected:
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	class StateMachine *m_machine; // +0x18
	Bool m_flag1C; // +0x1C
	unsigned char m_pad1D[0x20 - 0x1D];
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType updateStateMachine(); // slot 4
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual StateReturnType setState(StateID newStateID); // slot 8
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *obj); // slot 14

	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	ObjectID getGoalObjectID() const { return m_goalObjectID; }
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
	Bool isInIdleState() const { return m_currentState ? m_currentState->slot08() : true; }
	Bool getCurrentFlag1C() const { return m_currentState ? m_currentState->getFlag1C() : true; }
	void lock() { m_locked = true; }
	void unlock() { m_locked = false; }
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x20 - 0x18];
	ObjectID m_goalObjectID; // +0x20
	unsigned char m_pad24[0x38 - 0x24];
	Bool m_locked; // +0x38
};

class AIHuntState : public State
{
public:
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
private:
	StateMachine *m_huntMachine; // +0x20
	UnsignedInt m_nextEnemyScanTime; // +0x24
};

StateReturnType AIHuntState::update()
{
	if (getMachine()->getGoalObjectID() != INVALID_OBJECT_ID &&
		m_huntMachine->getGoalObjectID() != getMachine()->getGoalObjectID())
	{
		Object *goal = getMachine()->getGoalObject();
		if (goal == 0)
		{
			getMachine()->setGoalObject(0);
		}
		else
		{
			m_huntMachine->setGoalObject(goal);
			if (m_huntMachine->getCurrentStateID() == AI_IDLE)
				m_huntMachine->setState(AI_ATTACK_OBJECT);
			m_nextEnemyScanTime = TheGameLogic->getFrame() + ENEMY_SCAN_RATE;
		}
	}

	// look around for better victims every so often
	UnsignedInt now = TheGameLogic->getFrame();
	Object *owner = getMachineOwner();
	Bool holdTarget = owner->testStatus(OBJECT_STATUS_BFME_1C);
	Object *huntGoal = m_huntMachine->getGoalObject();
	if (owner->getTemplate()->testKind115())
	{
		ContainModuleInterface *contain = owner->getContain();
		if (contain)
		{
			AIHuntContainTarget *target = contain->slot31();
			if (target && huntGoal && !huntGoal->getTemplate()->testKind108() && target->slot88(huntGoal))
				holdTarget = true;
		}
	}

	if (!holdTarget && now >= m_nextEnemyScanTime)
	{
		// if all of our weapons are out of ammo, can't hunt.
		if (owner->isOutOfAmmo() && !owner->getTemplate()->testKind10B())
			return STATE_FAILURE;

		// Check to see if we have created a crate we need to pick up.
		AIUpdateInterface *ai = owner->getAI();
		Object *crate = ai->checkForCrateToPickup();
		if (crate)
		{
			m_huntMachine->setGoalObject(crate);
			m_huntMachine->setState(AI_PICK_UP_CRATE);
			return STATE_CONTINUE;
		}

		Bool scan = true;
		if (ai->slot90() && !m_huntMachine->getCurrentFlag1C() && !m_huntMachine->isInIdleState())
			scan = false;

		m_nextEnemyScanTime = now + ENEMY_SCAN_RATE;

		if (scan)
		{
			const AttackPriorityInfo *info = ai->getAttackInfo();

			// Check if team auto targets same victim.
			Object *teamVictim = 0;
			if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
			{
				teamVictim = owner->getTeam()->getTeamTargetObject();
			}
			Object *victim = 0;
			if (teamVictim && info == 0)
			{
				victim = teamVictim;
			}
			else
			{
				// do NOT do line of sight check - we want to find everything
				victim = TheAI->findClosestEnemy(owner, 9999.9f, AI::CAN_ATTACK_BFME, info, 0, 0);
				if (victim == 0 && owner->getControllingPlayer() && owner->getControllingPlayer()->getUnitsShouldHunt())
				{
					// If we are doing an all hunt, try hunting without the attack priority info.
					victim = TheAI->findClosestEnemy(owner, 9999.9f, AI::CAN_ATTACK_BFME, 0, 0, 0);
				}
				if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
				{
					// Check priorities.
					if (teamVictim && info)
					{
						if (victim == 0)
							victim = teamVictim;
						Real teamVictimPriority = info->getPriority(owner, teamVictim, true);
						Real victimPriority = info->getPriority(owner, victim, true);
						if (teamVictimPriority >= victimPriority)
							victim = teamVictim;
					}
					owner->getTeam()->rva0039D84A(victim);
				}
			}

			Object *oldGoal = m_huntMachine->getGoalObject();
			Bool newVictim = victim != oldGoal;
			if (newVictim)
			{
				m_huntMachine->setGoalObject(victim);
				if (oldGoal == 0)
					ai->playAttackVoiceResponse(victim);
			}
			if (newVictim || (m_huntMachine->isInIdleState() && victim))
			{
				m_huntMachine->setState(AI_ATTACK_OBJECT);
			}
			if (owner->getControllingPlayer() && !owner->getControllingPlayer()->getUnitsShouldHunt())
			{
				// If we are not doing an all hunt, then exit hunt state - no more victims.
				if (m_huntMachine->getCurrentStateID() == AI_IDLE && victim == 0)
					return STATE_SUCCESS;
			}
		}
	}

	getMachine()->lock();
	StateReturnType ret = m_huntMachine->updateStateMachine();
	if (ret > 0)
		ret = STATE_CONTINUE;
	getMachine()->unlock();
	return ret;
}
