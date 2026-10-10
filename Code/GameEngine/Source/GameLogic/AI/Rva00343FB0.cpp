// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// ?rva00343FB0@@YA_NPAVObject@@@Z
//
// AIAttackApproachTargetState::onEnter, retail 0x0034CD3A (783 bytes): slot 4
// of vtable 0x00C12610 (slot-2 name getter "AIAttackApproachTargetState";
// slots 5/6 are the rowed onExit 0x0034894C and update 0x003488AF), with the
// AIStates.cpp helpers it calls:
//
//  - rva003430A3 0x003430A3 (123 bytes): the attack line-of-sight test. True
//    unless the owner's template has kind byte +0x10F mask 8 or byte +0x122
//    mask 0x40, the weapon's template is neither the +0x2C9400 byte-field
//    kind nor a contact weapon (pinned WeaponTemplate::isContactWeapon), and
//    the stack line-of-sight partition filter (vtable 0x00C07150, rowed
//    Rva002619C1Filter::allow) refuses the victim. Also called outside this
//    unit (0x0046C7A4), so it is external cdecl.
//  - rva00343FB0 0x00343FB0 (173 bytes): static, owner in ESI. False for an
//    immobile owner (kind byte +0x108 mask 4) or one whose outermost
//    container is; otherwise BFME1's rva0016B010 (contact/field weapon,
//    non-human player, no AI, state 0x3E, AI slot 143 != 2, AI byte +0x3C1,
//    owner byte +0x249).
//  - canPursue 0x00344635 (276 bytes): static, owner in ESI, victim in EDI,
//    weapon on the stack; Zero Hour's canPursue as BFME1 shaped it (status
//    0x26 with a container, crush test, weapon too-close test 0x002C9AFE,
//    locomotor speed 0x002627E8 against the victim's 0x0028AC7D).
//
// onEnter is Zero Hour's with BFME 2 target facts: the owner position is
// saved at +0x58; a destroyed goal fails; status 0x44 or AI byte +0x3CC
// takes a direct fire/fail exit through AI::rva002FE193 and the
// line-of-sight test (else the machine's slot 14 clears the goal); a victim
// rowed Rva0034311ECheck fails; the view-blocked test is rva003430A3;
// the guard-retaliate block is rva00343FB0; an AI module flag +0x24 with
// layer >= 17 and no quick path, or a non-moving owner (Object::rva002907A1,
// locomotor 0x001E46E1 speed < 0.1), waits two seconds (+0x68, flag +0x71).
// Donors: Zero Hour AIStates.cpp, BFME1 AIAttackApproachTargetState_onEnter.cpp.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

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
	OBJECT_STATUS_26 = 0x26,
	OBJECT_STATUS_44 = 0x44
};

#include "Code/Libraries/Include/Lib/Coord3D.h"

class Object;
class Weapon;

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

extern const int g_009BA4E4;
#define LOGICFRAMES_PER_SECOND g_009BA4E4

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class TAiData
{
public:
	unsigned char m_pad00[0x8C];
	Bool m_aiCrushesInfantry; // +0x8C
};

class AI
{
public:
	static Bool rva002FE193(Object *owner, Object *nemesis);
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

class Locomotor
{
public:
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS
	};
	void setUsePreciseZPos(Bool b)
	{
		if (b)
			m_flags |= (1 << PRECISE_Z_POS);
		else
			m_flags &= ~(1 << PRECISE_Z_POS);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};

// Locomotor speed for an object (0x001E46E1), rowed under this name.
class Rva001E46E1
{
public:
	Real rva001E46E1(Object *obj);
};

// AI current-locomotor speed (0x002627E8), rowed under this name.
class Rva002627E8
{
public:
	Real rva002627E8() const;
};

class AIUpdateModuleData
{
public:
	unsigned char m_pad00[0x24];
	Bool m_24; // +0x24
};

template <int N> class AIApproachAISlots : public AIApproachAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIApproachAISlots<0>
{
};

class AIUpdateInterface : public AIApproachAISlots<136>
{
public:
	virtual void slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142() = 0;
	virtual Int slot143() = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	Int rva00260DED() const;
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Bool isQuickPathAvailable(const Coord3D *destination) const;
	Real getCurLocomotorSpeed() const { return ((const Rva002627E8 *)this)->rva002627E8(); }
private:
	const AIUpdateModuleData *m_moduleData; // +0x04
	unsigned char m_pad008[0x1F0 - 0x08];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3C1 - 0x1F4];
public:
	Bool m_3c1; // +0x3C1
	unsigned char m_pad3C2[0x3CC - 0x3C2];
	Bool m_3cc; // +0x3CC
};

class ThingTemplate
{
public:
	Bool isKindOfImmobile() const { return (m_kindOf[0] & 4) != 0; }
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 2) != 0; }
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[8]; // +0x108
	unsigned char m_pad110[0x122 - 0x110];
	unsigned char m_122; // +0x122
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const Coord3D *getUnitDirectionVector2D() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Player
{
public:
	unsigned char m_pad00[0x5C];
	Int m_playerType; // +0x5C
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	Bool isKindOfImmobile() const { return getTemplate()->isKindOfImmobile(); }
	Bool isKindOfProjectile() const { return getTemplate()->isKindOfProjectile(); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	Player *getControllingPlayer() const;
	Int rva0028B511() const;
	Bool rva002907A1();
	Bool isSignificantlyAboveTerrain() const;
	Bool rva0029493F(Object *other, Int test);
	Real rva0028AC7D() const;
	unsigned char m_pad044[0x249 - 0x44];
	Bool m_249; // +0x249
	unsigned char m_pad24A[0x258 - 0x24A];
	AIUpdateInterface *m_ai; // +0x258
	void *m_physics; // +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy; // +0x274
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Rva002C9407ByteField
{
public:
	unsigned char get() const;
};

class WeaponTemplate
{
public:
	Bool isContactWeapon() const;
	unsigned char m_pad00[0x16B];
	Bool m_16b; // +0x16B
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;
	char isWithinAttackRange(Object *source, void *pos, Real extra, Int flag) const;
	Bool rva002C9AFE(const Object *source, const void *target) const;
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};

// The line-of-sight partition filter (vtable 0x00C07150).
class Rva002619C1FilterBase
{
public:
	Rva002619C1FilterBase() : m_zero(0) {}
	Int m_zero;
};

class Rva002619C1Filter : public Rva002619C1FilterBase
{
public:
	Rva002619C1Filter(Object *owner) : m_owner(owner) {}
	virtual ~Rva002619C1Filter() {}
	virtual Bool allow(Object *other);

	Object *m_owner;
};

template <int N> class StateMachineSlots : public StateMachineSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class StateMachineSlots<0>
{
};

class StateMachine : public StateMachineSlots<14>
{
public:
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

// StateMachine::isGoalObjectDestroyed (0x004D7ADD), rowed under this name.
class TurretStateMachine
{
public:
	Bool rva004D7ADD();
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void slot05();
	virtual StateReturnType update();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Bool computePath();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	Coord3D m_prevVictimPos; // +0x4C
	Coord3D m_ownerPosition; // +0x58
	Int m_approachTimestamp; // +0x64
	UnsignedInt m_waitFrame; // +0x68
	Bool m_follow; // +0x6C
	Bool m_isAttackingObject; // +0x6D
	Bool m_stopIfInRange; // +0x6E
	Bool m_isInitialApproach; // +0x6F
	Bool m_isForceAttacking; // +0x70
	Bool m_waiting; // +0x71
};

Bool Rva0034311ECheck(Object *obj);

Bool rva003430A3(Object *source, Object *victim, Weapon *weapon)
{
	if (weapon && victim && !((const Rva002C9400ByteField *)weapon->getTemplate())->get() &&
		!weapon->getTemplate()->isContactWeapon() &&
		((source->getTemplate()->m_kindOf[7] & 8) || (source->getTemplate()->m_122 & 0x40)))
	{
		Rva002619C1Filter filter(source);
		if (!filter.allow(victim))
			return false;
	}
	return true;
}

static Bool canPursue(Object *source, Weapon *weapon, Object *victim)
{
	if (!victim->m_physics)
		return false;
	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return false;
	AIUpdateInterface *ai = source->getAI();
	if (!ai)
		return false;

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (source->getControllingPlayer() &&
			source->getControllingPlayer()->m_playerType == 1 &&
			source->rva0029493F(victim, 2))
		{
			return true;
		}
	}

	if (weapon->rva002C9AFE(source, victim))
		return false;

	Real ourMaxSpeed = source->getAI()->getCurLocomotorSpeed();
	Real victimSpeed = victim->rva0028AC7D();
	if (victimSpeed >= ourMaxSpeed)
		return false;
	if (victimSpeed < ourMaxSpeed * 0.1f)
		return false;
	Real dx = victim->getPosition()->x - source->getPosition()->x;
	Real dy = victim->getPosition()->y - source->getPosition()->y;
	const Coord3D *victimDirection = victim->getUnitDirectionVector2D();
	Coord3D victimDirectionVector;
	victimDirectionVector.x = victimDirection->x;
	victimDirectionVector.y = victimDirection->y;
	if (dx * victimDirectionVector.x + dy * victimDirectionVector.y < 0)
		return false;
	return true;
}

static Bool rva00343FB0(Object *obj)
{
	if (obj->isKindOfImmobile())
		return false;
	Object *container = obj->m_containedBy;
	while (container && container->m_containedBy)
		container = container->m_containedBy;
	if (container && container->isKindOfImmobile())
		return false;

	Weapon *weapon = obj->getCurrentWeapon();
	if (weapon && (((const Rva002C9400ByteField *)weapon->getTemplate())->get() ||
			((const Rva002C9407ByteField *)weapon->getTemplate())->get()))
		return true;
	if (obj->getControllingPlayer()->m_playerType)
		return true;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return true;
	if (ai->rva00260DED() == 0x3e || ai->slot143() != 2 || ai->m_3c1 || (obj->m_249?obj->m_249:obj->m_249))
		return true;
	return false;
}

StateReturnType AIAttackApproachTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	if (source->isKindOfProjectile())
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	m_ownerPosition = *source->getPosition();

	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_FAILURE;

	m_waiting = false;
	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();

	if (source->testStatus(OBJECT_STATUS_44) || ai->m_3cc)
	{
		if (weapon && victim && AI::rva002FE193(source, victim) &&
			rva003430A3(source, victim, weapon))
			return STATE_SUCCESS;
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	m_prevVictimPos.x = 0.0f;
	m_prevVictimPos.y = 0.0f;
	m_prevVictimPos.z = 0.0f;
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;

	if (victim)
	{
		if (!weapon)
			return STATE_FAILURE;
		if (Rva0034311ECheck(victim))
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		{
			Bool viewBlocked = false;
			if (ai->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
				viewBlocked = !rva003430A3(source, victim, weapon);
			if (!viewBlocked)
				return STATE_SUCCESS;
		}
		if (!rva00343FB0(source))
			return STATE_FAILURE;
		if (canPursue(source, weapon, victim))
			return STATE_SUCCESS;
		if (ai->getAIUpdateModuleData()->m_24 && source->rva0028B511() >= 17 &&
			!ai->isQuickPathAvailable(victim->getPosition()))
		{
			m_waiting = true;
			m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
			return STATE_CONTINUE;
		}
	}
	else
	{
		if (!weapon || !weapon->getTemplate()->m_16b)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange(source, (void *)getMachineGoalPosition(), 0.0f, 1))
			return STATE_SUCCESS;
		if (!rva00343FB0(source))
			return STATE_FAILURE;
	}

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->rva002907A1())
		mobile = false;
	if (((Rva001E46E1 *)ai->getCurLocomotor())->rva001E46E1(source) < 0.1f)
		mobile = false;
	if (!mobile)
	{
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			ai->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			ai->setTurretTargetPosition(tur, getMachineGoalPosition());
	}

	if (computePath() == false)
		return STATE_FAILURE;
	if (m_waiting)
		return STATE_CONTINUE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}
