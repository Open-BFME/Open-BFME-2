// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// onEnter/onExit overrides of BFME 2 states, each named by its vtable's
// slot-2 name getter (the state's own name literal):
//
//  - AIFollowPathAsTeamState::onExit, retail 0x00349E15 (95 bytes): slot 5
//    of 0x00C121E8. Sets the team machine at +0x5C (when present) to state 0
//    through StateMachine slot 8, then Zero Hour's AIFollowPathState::onExit
//    tail on the AIInternalMoveToState base (0x003473A4): path-through-units
//    off, precise-z off, the pinned AIUpdateInterface::setDesiredSpeed with
//    999999.0 (FAST_AS_POSSIBLE, .rdata 0x00C10DE0) and goal path index -1.
//  - AIChargeTargetState::onExit, retail 0x0034BEC3 (93 bytes): slot 5 of
//    0x00C130A8. With an owner and its AI: clears model-condition bit 132
//    (word +0x11C of the bits at +0x10C, notifying through the rowed
//    Object::rva0028AE6D), calls AI slot 142 with 0, releases the weapon
//    lock (pinned Object::releaseWeaponLock, LOCKED_TEMPORARILY), clears the
//    machine byte +0x3A and runs the base onExit.
//  - AIMoveToPositionAndEnterState::onExit, retail 0x0034C035 (99 bytes):
//    slot 5 of 0x00C136A0. When the owner has object status 0x4E, clears it
//    and status 3, and for a template with kind byte +0x115 mask 0x20 also
//    clears status 3 through the pinned Object::rva00346C53; then clears
//    status 0x5D and runs the base onExit.
//  - AIAttackMeleeEngageState::onExit, retail 0x00349D26 (103 bytes): slot 5
//    of 0x00C12150. Nothing for an owner with byte +0x94 bit 0; otherwise
//    full speed (setDesiredSpeed FAST_AS_POSSIBLE), clears status 0x4B
//    through rva00346C53 and setStatus unless status 0x26 is set, then the
//    base onExit.
//  - AIAttackPositionAimAtTargetState::onExit, retail 0x0034A809 (104
//    bytes): slot 5 of 0x00C11068. AI slot 136 when both flags +0x20/+0x21
//    are set; AI slot 142 with 0 when the template real +0x53C is below
//    360.0 (.rdata 0x00BC6254); clears status 0x19. No base call.
//  - AIMoveAwayAndCowerState::onEnter, retail 0x0034CBAB (85 bytes): slot 4
//    of 0x00C12FF0. Fails (-2) without a goal object (the pinned
//    StateMachine::getGoalObject) or AI; else AI slot 142 with 4, +0x4C = 1,
//    +0x50 = true, the pinned AI member 0x00263EA2 with the goal's id (+0x74)
//    and the pinned AIInternalMoveToState::onEnter as a tail call.
//
// Layout and callees as in AIFollowPathStateOnExit.cpp and
// AIStatesDerivedOnExit.cpp; the meaning of the status, condition and kind
// bits is not recovered.

typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
typedef unsigned int StateID;
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3 = 3,
	OBJECT_STATUS_BFME_19 = 0x19,
	OBJECT_STATUS_BFME_26 = 0x26,
	OBJECT_STATUS_BFME_4B = 0x4B,
	OBJECT_STATUS_BFME_4E = 0x4E,
	OBJECT_STATUS_BFME_5D = 0x5D
};
enum ObjectID
{
	INVALID_ID = 0
};
enum
{
	STATE_FAILURE = -2
};
enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};
#define FAST_AS_POSSIBLE 999999.0f

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

template <int N> class AIStateAISlots : public AIStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIStateAISlots<0>
{
};

class AIUpdateInterface : public AIStateAISlots<136>
{
public:
	virtual void rva0034A82DSlot136() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void rva0034BEF9Slot142(int value) = 0;
	void rva00263EA2(ObjectID id);
	void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void friend_setCurrentGoalPathIndex(int index) { m_currentGoalPathIndex = index; }
	void setDesiredSpeed(Real speed);
private:
	unsigned char m_pad004[0x194 - 0x04];
	int m_currentGoalPathIndex; // +0x194
	unsigned char m_pad198[0x1F0 - 0x198];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3BA - 0x1F4];
	Bool m_canPathThroughUnits; // +0x3BA
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class ThingTemplate
{
public:
	Bool testKindByte115() const { return (m_kindOf[1] & 0x20) != 0; }
	Real getBfmeReal53C() const { return m_bfmeReal53C; }
private:
	unsigned char m_pad00[0x114];
	unsigned char m_kindOf[4]; // +0x114
	unsigned char m_pad118[0x53C - 0x118];
	Real m_bfmeReal53C; // +0x53C
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Bool testBfmeFlag94() const { return (m_bfmeFlags94 & 1) != 0; }
	Bool testStatus(ObjectStatusTypes status) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	void rva00346C53(ObjectStatusTypes status, Bool set);
	void releaseWeaponLock(WeaponLockType lockType);
	void rva0028AE6D();
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x74 - 0x08];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x94 - 0x78];
	unsigned char m_bfmeFlags94; // +0x94
	unsigned char m_pad095[0x10C - 0x95];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	void rva0034BF11ClearByte3A() { m_bfmeFlag3A = false; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3A - 0x18];
	Bool m_bfmeFlag3A; // +0x3A
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
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x5C - 0x1C];
	StateMachine *m_teamMachine; // +0x5C
};

void AIFollowPathAsTeamState::onExit(StateExitType status)
{
	if (m_teamMachine)
		m_teamMachine->setState(0);

	AIInternalMoveToState::onExit(status);

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai)
		return;
	ai->setCanPathThroughUnits(false);
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);
	ai->setDesiredSpeed(FAST_AS_POSSIBLE);
	ai->friend_setCurrentGoalPathIndex(-1);
}

class AIChargeTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIChargeTargetState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return;
	owner->clearModelConditionBit(132);
	ai->rva0034BEF9Slot142(0);
	owner->releaseWeaponLock(LOCKED_TEMPORARILY);
	getMachine()->rva0034BF11ClearByte3A();
	AIInternalMoveToState::onExit(status);
}

class AIMoveToPositionAndEnterState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIMoveToPositionAndEnterState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (owner && owner->testStatus(OBJECT_STATUS_BFME_4E))
	{
		owner->setStatus(OBJECT_STATUS_BFME_4E, false);
		owner->setStatus(OBJECT_STATUS_BFME_3, false);
		if (owner->getTemplate()->testKindByte115())
			owner->rva00346C53(OBJECT_STATUS_BFME_3, false);
	}
	owner->setStatus(OBJECT_STATUS_BFME_5D, false);
	AIInternalMoveToState::onExit(status);
}

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeEngageState::onExit(StateExitType status)
{
	Object *owner = getMachineOwner();
	if (owner->testBfmeFlag94())
		return;
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
		ai->setDesiredSpeed(FAST_AS_POSSIBLE);
	if (!owner->testStatus(OBJECT_STATUS_BFME_26))
	{
		getMachineOwner()->rva00346C53(OBJECT_STATUS_BFME_4B, false);
		getMachineOwner()->setStatus(OBJECT_STATUS_BFME_4B, false);
	}
	AIInternalMoveToState::onExit(status);
}

class AIAttackPositionAimAtTargetState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_bfmeFlag20; // +0x20
	Bool m_bfmeFlag21; // +0x21
};

void AIAttackPositionAimAtTargetState::onExit(StateExitType status)
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (m_bfmeFlag20 && ai && m_bfmeFlag21)
		ai->rva0034A82DSlot136();
	if (ai && getMachineOwner()->getTemplate()->getBfmeReal53C() < 360.0f)
		ai->rva0034BEF9Slot142(0);
	getMachineOwner()->setStatus(OBJECT_STATUS_BFME_19, false);
}

class AIMoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x4C - 0x1C];
	int m_bfmeValue4C; // +0x4C
	Bool m_bfmeFlag50; // +0x50
};

StateReturnType AIMoveAwayAndCowerState::onEnter()
{
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!goal || !ai)
		return (StateReturnType)STATE_FAILURE;
	ai->rva0034BEF9Slot142(4);
	m_bfmeValue4C = 1;
	m_bfmeFlag50 = true;
	ai->rva00263EA2(goal->getID());
	return AIInternalMoveToState::onEnter();
}
