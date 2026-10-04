// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// onExit overrides of BFME 2 move states, each named by its vtable's slot-2
// name getter (the state's own name literal):
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
	OBJECT_STATUS_BFME_4E = 0x4E,
	OBJECT_STATUS_BFME_5D = 0x5D
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

class AIUpdateInterface : public AIStateAISlots<142>
{
public:
	virtual void rva0034BEF9Slot142(int value) = 0;
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
private:
	unsigned char m_pad00[0x114];
	unsigned char m_kindOf[4]; // +0x114
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
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
	unsigned char m_pad008[0x10C - 0x08];
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
