// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9185917865846435 date=2026-10-10
// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-10-09
// cl: /I. /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1
// AIAttackState::update, retail 0x0034F758..0x0034FB77 (1055 bytes).
// Target identity: the 0x00C13B78 vtable name getter returns AIAttackState;
// its matched onExit is 0x0034B889. Zero Hour GeneralsMD AIStates.cpp
// supplies the update-state behavior. BFME2-specific gates and fields below
// follow target bytes and rowed providers; retail keeps the victim local at
// [EBP-8] on the dead-victim path.
//
// AIAttackState::onExit, retail 0x0034B889 (201 bytes): slot 5 of vtable
// 0x00C13B78, whose slot-2 name getter returns AIAttackState.
// Donor: BFME1 game/GameEngine/Source/GameLogic/AI/AIAttackStateOnExitClean.cpp
// (open-bfme-1 068db38bb4) and the Zero Hour AIStates.cpp onExit: delete the
// attack machine, clear object statuses 13/25/22/27/28, clear the attacking
// model conditions, release the weapon lock, then reset the AI victim, turret
// target and goal.
// BFME2 deltas (target evidence): the attack machine is at +0x24 and is deleted
// with a global-scope delete (vslot 0 with flag 0, then ::operator delete);
// the statuses go through the rowed setStatus(ObjectStatusTypes, bool); the
// conditions are bits 1*32+5..7 of the Object+0x10C words; the weapon-lock
// release is the Object +0x330 forwarder 0x0028BC4D (pinned by address); only
// turret 0 is reset; the goal reset is the rowed AIUpdateInterface::rva00262B0F.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0,
	OBJECT_STATUS_01 = 0x01,
	OBJECT_STATUS_1C = 0x1C,
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_3C = 0x3C
};
#define CONVERT_SLEEP_TO_CONTINUE(x) ((x) > STATE_CONTINUE ? STATE_CONTINUE : (x))

enum KindOfType
{
	KINDOF_81 = 0x81
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0
};
class Object;
template <int N> class AttackSlots : public AttackSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AttackSlots<0>
{
};
class AIUpdateInterface : public AttackSlots<143>
{
public:
	virtual Int getLastCommandSource() = 0;
	virtual void notifyVictimIsDead() = 0;
	virtual void slot145() = 0; virtual void slot146() = 0; virtual void slot147() = 0;
	virtual void slot148() = 0; virtual void slot149() = 0; virtual void slot150() = 0;
	virtual void slot151() = 0;
	virtual Bool slot152() = 0;
	void setCurrentVictim(const Object *nemesis);
	void setTurretTargetObject(WhichTurretType tur, Object *o, bool isForceAttacking);
	void rva00262B0F(int x);
};
class ContainModuleInterface : public AttackSlots<4>
{
public:
	virtual Bool isGarrisonable() = 0;
	virtual void s05() = 0; virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0; virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0;
	virtual void s13() = 0; virtual void s14() = 0; virtual void s15() = 0; virtual void s16() = 0;
	virtual void s17() = 0; virtual void s18() = 0; virtual void s19() = 0; virtual void s20() = 0;
	virtual void s21() = 0; virtual void s22() = 0; virtual void s23() = 0; virtual void s24() = 0;
	virtual void s25() = 0; virtual void s26() = 0; virtual void s27() = 0; virtual void s28() = 0;
	virtual void s29() = 0; virtual void s30() = 0; virtual void s31() = 0; virtual void s32() = 0;
	virtual void s33() = 0; virtual void s34() = 0; virtual void s35() = 0; virtual void s36() = 0;
	virtual void s37() = 0; virtual void s38() = 0; virtual void s39() = 0; virtual void s40() = 0;
	virtual void s41() = 0; virtual void s42() = 0; virtual void s43() = 0; virtual void s44() = 0;
	virtual void s45() = 0; virtual void s46() = 0; virtual void s47() = 0;
	virtual Bool rva0034F981Slot48(Object *obj, Object *victim) = 0;
	virtual void s49() = 0; virtual void s50() = 0; virtual void s51() = 0; virtual void s52() = 0;
	virtual void s53() = 0; virtual void s54() = 0; virtual void s55() = 0; virtual void s56() = 0;
	virtual void s57() = 0; virtual void s58() = 0; virtual void s59() = 0; virtual void s60() = 0;
	virtual void s61() = 0; virtual void s62() = 0; virtual void s63() = 0; virtual void s64() = 0;
	virtual void s65() = 0; virtual void s66() = 0; virtual void s67() = 0; virtual void s68() = 0;
	virtual Int getContainCount(Int kind) = 0;
};
class Team
{
public:
	Object *getTeamTargetObject();
	void rva0039D84A(Object *obj);
};
class ThingTemplate
{
public:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad68[0x108 - 0x68];
	unsigned char m_kindOf[0x14]; // +0x108
};
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class WeaponTemplate
{
public:
	unsigned char m_pad00[0x08];
	AsciiString m_name; // +0x08
};
class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
	unsigned char m_pad08[0x34 - 0x08];
	Int m_maxShotCount; // +0x34
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	void rva0028BC4D();
	void setStatus(ObjectStatusTypes status, bool set);
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf(KindOfType t) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isOutOfAmmo() const;
	Relationship getRelationship(const Object *that) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot = 0) const;
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *getContainedBy() const { return m_containedBy; }
	Team *getTeam() const { return m_team; }
	Bool isEffectivelyDeadBfme() const { return (m_438 & 1) != 0; }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 0x08];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned int m_438; // +0x438
};
class State;
class StateMachine
{
public:
	virtual ~StateMachine();
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};

// State-machine calls use the target's slot 4/8 interface. Keep this separate
// from StateMachine's virtual destructor view used by AIAttackState::onExit.
class StateMachineCallView : public AttackSlots<4>
{
public:
	virtual StateReturnType updateStateMachine();
	virtual void s05(); virtual void s06(); virtual void s07();
	virtual StateReturnType rva0034FB52Slot8(Int stateID);
	virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void setGoalObject(const Object *obj);
	State *getCurrentState() const { return m_currentState; }
	Int m_1cState() const { return m_1c; }
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x1C - 0x18];
	Int m_1c; // +0x1C
};
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
class Rva003413B2
{
public:
	Bool rva003413B2();
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
	Int getID() const { return m_id; }
	Bool getByte1C() const { return m_1c; }
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	Int m_id; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
	Bool m_1c; // +0x1C
};
class AIAttackState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad20[0x24 - 0x20];
	StateMachine *m_attackMachine; // +0x24
	AttackExitConditionsInterface *m_attackParameters; // +0x28
	Team *m_victimTeam; // +0x2C
	unsigned char m_pad30[0x3C - 0x30];
	AsciiString m_weaponName; // +0x3C
	unsigned char m_pad40[0x41 - 0x40];
	Bool m_isAttackingObject; // +0x41
	unsigned char m_pad42[0x48 - 0x42];
	Bool m_48; // +0x48
	Bool m_49; // +0x49
};
void AIAttackState::onExit(StateExitType status)
{
	// destroy the attack machine
	if (m_attackMachine)
	{
		::delete m_attackMachine;
		m_attackMachine = 0;
	}

	Object *obj = getMachineOwner();
	obj->setStatus((ObjectStatusTypes)0x0D, false);
	obj->setStatus((ObjectStatusTypes)0x19, false);
	obj->setStatus((ObjectStatusTypes)0x16, false);
	obj->setStatus((ObjectStatusTypes)0x1B, false);
	obj->setStatus((ObjectStatusTypes)0x1C, false);
	obj->clearModelConditionState(1 * 32 + 5);
	obj->clearModelConditionState(1 * 32 + 6);
	obj->clearModelConditionState(1 * 32 + 7);
	obj->rva0028BC4D();

	AIUpdateInterface *ai = obj->getAI();
	if (ai)
	{
		ai->setCurrentVictim(0);
		ai->setTurretTargetObject(TURRET_MAIN, 0, false);
		ai->rva00262B0F(0);
	}
}

StateReturnType AIAttackState::update()
{
	Object *source = getMachineOwner();
	Object *victim = getMachineGoalObject();
	if (m_attackParameters && m_attackParameters->shouldExit(getMachine()))
		return STATE_SUCCESS;
	if (source->isKindOf(KINDOF_81))
		return STATE_FAILURE;
	if (victim && victim->testStatus(OBJECT_STATUS_3C))
	{
		if (getMachine())
			reinterpret_cast<StateMachineCallView *>(getMachine())->setGoalObject(0);
		return STATE_FAILURE;
	}
	AIUpdateInterface *sourceAI = source->getAI();
	if (sourceAI && sourceAI->slot152())
		return STATE_CONTINUE;
	if (source->isOutOfAmmo() && !(source->getTemplate()->m_kindOf[3] & 2))
		return STATE_FAILURE;

	if (m_isAttackingObject)
	{
		if (!victim || victim->isEffectivelyDeadBfme() || victim->testStatus(OBJECT_STATUS_32))
		{
			source->getAI()->notifyVictimIsDead();
			if (source->getTemplate()->m_kindOf[0x12] & 0x80)
				return STATE_SUCCESS;
			return CONVERT_SLEEP_TO_CONTINUE(
					reinterpret_cast<StateMachineCallView *>(m_attackMachine)->updateStateMachine());
		}
		AIUpdateInterface *ai = source->getAI();
		Int lastCommandSource = ai->getLastCommandSource();
		Bool status1C = source->testStatus(OBJECT_STATUS_1C);
		Bool isEnemy = source->getRelationship(victim) == ENEMIES;
		if (!isEnemy && m_49 && (lastCommandSource & 2) && !status1C &&
			!(victim->getTemplate()->m_kindOf[0xB] & 0x40))
		{
			ai->rva00262B0F(0);
			if (victim == source->getTeam()->getTeamTargetObject())
				source->getTeam()->rva0039D84A(0);
			ai->notifyVictimIsDead();
			return STATE_FAILURE;
		}
		source->getAI()->setCurrentVictim(victim);
		if (victim->getTeam() != m_victimTeam)
		{
			if ((sourceAI && !victim->testStatus(OBJECT_STATUS_01) && victim->getContain() &&
					victim->getContain()->isGarrisonable() && victim->getContain()->getContainCount(0) == 0 &&
					source->getRelationship(victim) == NEUTRAL) ||
				source->getRelationship(victim) != ENEMIES)
			{
				sourceAI->rva00262B0F(0);
				if (victim == source->getTeam()->getTeamTargetObject())
					source->getTeam()->rva0039D84A(0);
				sourceAI->notifyVictimIsDead();
				return STATE_FAILURE;
			}
		}
		if (victim != m_attackMachine->getGoalObject())
			reinterpret_cast<StateMachineCallView *>(m_attackMachine)->setGoalObject(victim);
	}

	if (source->getContainedBy() && source->getContainedBy()->getContain() &&
		source->getContainedBy()->getContain()->rva0034F981Slot48(source, victim))
		return STATE_FAILURE;
	if (!((Rva003413B2 *)this)->rva003413B2())
		return STATE_FAILURE;
	const Weapon *curWeapon = source->getCurrentWeapon();
	if (!((const StringBase<char> *)&m_weaponName)->isEmpty())
	{
		if (!curWeapon)
			return STATE_FAILURE;
		if (((const StringBase<char> *)&m_weaponName)->compare(((const StringBase<char> *)&curWeapon->getTemplate()->m_name)->str()) != 0 &&
			((const StringBase<char> *)&source->getTemplate()->m_name)->compare("GondorTrebuchet") != 0)
			return STATE_FAILURE;
	}
	if (!curWeapon || curWeapon->m_maxShotCount <= 0)
		return STATE_FAILURE;

	if (((const Rva002C9400ByteField *)curWeapon->getTemplate())->get() != m_48)
	{
		onExit(EXIT_NORMAL);
		if (sourceAI)
		{
			sourceAI->setCurrentVictim(victim);
			sourceAI->rva00262B0F((int)victim);
			reinterpret_cast<StateMachineCallView *>(getMachine())->setGoalObject(victim);
		}
		return onEnter();
	}

	Int stateID = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()
		? reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()->getID() : 999999;
	if (stateID == 0xE4)
	{
		source->clearModelConditionState(1 * 32 + 5);
		source->clearModelConditionState(1 * 32 + 6);
		source->clearModelConditionState(1 * 32 + 7);
	}
	else
	{
		source->setModelConditionState(1 * 32 + 5);
		if (victim && (victim->getTemplate()->m_kindOf[0] & 0x80))
			source->setModelConditionState(1 * 32 + 6);
		if (!m_isAttackingObject)
			source->setModelConditionState(1 * 32 + 7);
	}
	Bool runState = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()
		? reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()->getByte1C() : true;
	if (runState && reinterpret_cast<StateMachineCallView *>(m_attackMachine)->rva0034FB52Slot8(
		reinterpret_cast<StateMachineCallView *>(m_attackMachine)->m_1cState()) == STATE_FAILURE)
		return STATE_FAILURE;
	return CONVERT_SLEEP_TO_CONTINUE(
		reinterpret_cast<StateMachineCallView *>(m_attackMachine)->updateStateMachine());
}
