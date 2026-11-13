// Target update boundary: 0x0034F758..0x0034FB77; full 1055 bytes RET 0.
// The existing onExit body and its original inline accessor are retained.
// A compiler fence after isEnemy preserves the target's value scheduling.
// Identical failure tails on the two OR paths are cross-jumped by VC7.1,
// producing MOV ECX before PUSH 0 at 0x0034F920 without changing evaluation.
// Save the machine-update result once: retail makes exactly one virtual call.
// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1 /G7 /arch:SSE
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
// turret 0 is reset; the goal reset is the rowed AIUpdateInterface::friend_setGoalObject.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0,
	OBJECT_STATUS_01 = 0x01,
	OBJECT_STATUS_1C = 0x1C,
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_3C = 0x3C
};

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
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/GameLogic/Module/ContainModule.h"
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/Common/ThingTemplate.h"
#include "../../../Include/Common/Rva002C9400ByteField.h"
#include "../../../Include/GameLogic/WeaponTemplate.h"
#include "../../../Include/GameLogic/Weapon.h"
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
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
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
	// Inlined at its call sites; the out-of-line body is the matched row in
	// AIInternalMoveToStateOnExit.cpp, so this view must not emit a copy.
	__declspec(dllimport) __forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__declspec(dllimport) __forceinline void clearModelConditionState(unsigned int mc)
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
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

// State-machine calls use the target's slot 4/8 interface. Keep this separate
// from the canonical StateMachine that AIAttackState::onExit deletes.
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
#include "../../../Include/Common/AttackExitConditionsInterface.h"
class AIAttackState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Bool rva003413B2();	// ZH chooseWeapon
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

	AIUpdateInterface *ai = Object::getAI(obj);
	if (ai)
	{
		ai->setCurrentVictim(0);
		ai->setTurretTargetObject(TURRET_MAIN, 0, false);
		ai->friend_setGoalObject(0);
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
	if (sourceAI && sourceAI->rva002697FC())
		return STATE_CONTINUE;
	if (source->isOutOfAmmo() && !(source->getTemplate()->m_kindof[0] & (1U << 25)))
		return STATE_FAILURE;

	if (m_isAttackingObject)
	{
		if (!victim || victim->isEffectivelyDeadBfme() || victim->testStatus(OBJECT_STATUS_32))
		{
			source->getAI()->notifyVictimIsDead();
			if (source->getTemplate()->m_kindof[4] & (1U << 23))
				return STATE_SUCCESS;
			Int result = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->updateStateMachine(); return result > STATE_CONTINUE ? STATE_CONTINUE : (StateReturnType)result;
		}
		AIUpdateInterface *ai = source->getAI();
		Int lastCommandSource = ai->vslot143();
		Bool status1C = source->testStatus(OBJECT_STATUS_1C);
		Bool isEnemy = source->getRelationship(victim) == ENEMIES; _ReadWriteBarrier();
		if (!isEnemy && m_49 && (lastCommandSource & 2) && !status1C &&
			!(victim->getTemplate()->m_kindof[2] & (1U << 30)))
		{
			ai->friend_setGoalObject(0);
			if (victim == source->getTeam()->getTeamTargetObject())
				source->getTeam()->setTeamTargetObject(0);
			ai->notifyVictimIsDead();
			return STATE_FAILURE;
		}
		source->getAI()->setCurrentVictim(victim);
		if (victim->getTeam() != m_victimTeam)
		{
if (sourceAI && !victim->testStatus(OBJECT_STATUS_01) && victim->getContain() && victim->getContain()->isGarrisonable() && victim->getContain()->getContainCount(0) == 0 && source->getRelationship(victim) == NEUTRAL) {
				sourceAI->friend_setGoalObject(0);
				if (victim == source->getTeam()->getTeamTargetObject())
					source->getTeam()->setTeamTargetObject(0);
				sourceAI->notifyVictimIsDead();
				return STATE_FAILURE;
 } else if (source->getRelationship(victim) != ENEMIES) {
				sourceAI->friend_setGoalObject(0);
				if (victim == source->getTeam()->getTeamTargetObject())
					source->getTeam()->setTeamTargetObject(0);
				sourceAI->notifyVictimIsDead();
				return STATE_FAILURE;
 }
		}
		if (victim != m_attackMachine->getGoalObject())
			reinterpret_cast<StateMachineCallView *>(m_attackMachine)->setGoalObject(victim);
	}

	if (source->getContainedBy() && source->getContainedBy()->getContain() &&
		source->getContainedBy()->getContain()->slot48(source, victim))
		return STATE_FAILURE;
	if (!rva003413B2())
		return STATE_FAILURE;
	const Weapon *curWeapon = source->getCurrentWeapon();
	if (!((const StringBase<char> *)&m_weaponName)->isEmpty())
	{
		if (!curWeapon)
			return STATE_FAILURE;
		if (((const StringBase<char> *)&m_weaponName)->compare(((const StringBase<char> *)&curWeapon->getTemplate()->m_field08)->str()) != 0 &&
			((const StringBase<char> *)&source->getTemplate()->m_nameString)->compare("GondorTrebuchet") != 0)
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
			sourceAI->friend_setGoalObject(victim);
			reinterpret_cast<StateMachineCallView *>(getMachine())->setGoalObject(victim);
		}
		StateReturnType entered=onEnter(); _ReadWriteBarrier(); return entered;
	}

	Int stateID = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()
		? reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()->m_id : 999999;
	if (stateID == 0xE4)
	{
		source->clearModelConditionState(1 * 32 + 5);
		source->clearModelConditionState(1 * 32 + 6);
		source->clearModelConditionState(1 * 32 + 7);
	}
	else
	{
		source->setModelConditionState(1 * 32 + 5);
		if (victim && (victim->getTemplate()->m_kindof[0] & (1U << 7)))
			source->setModelConditionState(1 * 32 + 6);
		if (!m_isAttackingObject)
			source->setModelConditionState(1 * 32 + 7);
	}
	Bool runState = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()
		? reinterpret_cast<StateMachineCallView *>(m_attackMachine)->getCurrentState()->m_tail1C : true;
	if (runState && reinterpret_cast<StateMachineCallView *>(m_attackMachine)->rva0034FB52Slot8(
		reinterpret_cast<StateMachineCallView *>(m_attackMachine)->m_1cState()) == STATE_FAILURE)
		return STATE_FAILURE;
	Int result = reinterpret_cast<StateMachineCallView *>(m_attackMachine)->updateStateMachine(); return result > STATE_CONTINUE ? STATE_CONTINUE : (StateReturnType)result;
}
