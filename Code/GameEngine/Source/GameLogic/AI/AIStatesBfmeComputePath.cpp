// cl: /DNDEBUG /MD
//
// Small computePath (slot 17), onExit (slot 5) and other overrides of AI
// states, each named by its vtable's own slot-2 name getter (the state's name
// literal). BFME 2 logs a numbered "CritterDesync" line from computePath
// when the desync log is on (g_00E03745, file g_00DFEFF0):
//
//  - AIMoveAndTightenState::computePath 0x00340158 (34 bytes; 0x00C124D8,
//    whose constructor 0x00342843 builds on AIInternalMoveToState directly):
//    "ComputePath4", then keeps the existing path (true).
//  - AIMoveAwayAndCowerState::computePath 0x003403DC (53 bytes; 0x00C12FF0)
//    and AIBackAwayState::computePath 0x0034042C (53 bytes; 0x00C13050):
//    "ComputePath8" / "ComputePath9", then spend one of the repath tries at
//    +0x4C (Zero Hour's m_okToRepathTimes) or fail.
//  - AIPickUpCrateState::computePath 0x00345B5F (42 bytes; 0x00C128D0) and
//    AIFollowPathState::computePath 0x00345B89 (42 bytes; 0x00C12BC8):
//    "ComputePath30" / "ComputePath31", then the base
//    AIInternalMoveToState::computePath (pinned 0x003441F7) as a tail call.
//  - AIWaitUntilFinishedFiringState::onExit 0x00341391 (16 bytes;
//    0x00C11120): releases the owner's weapon lock (pinned
//    Object::releaseWeaponLock, LOCKED_TEMPORARILY); no base call.
//  - AIAttackMeleeSquishState::onExit 0x003497C7 (31 bytes; 0x00C12868):
//    base onExit, then object status 0x1C cleared.
//  - AIMoveAwayAndCowerState::onExit 0x00347F48 (46 bytes): base onExit,
//    then AI slot 142 with 0.
//  - AIBackAwayState::onExit 0x00347FFE (80 bytes): base onExit, then
//    model-condition bit 65 cleared (notifying through the rowed
//    Object::rva0028AE6D), AI slot 142 with 0 and the AI byte +0x3C8 cleared.
//  - AIBackAwayState::onEnter 0x0034CC00 (314 bytes; slot 4 of 0x00C13050):
//    "setAdjustDestination(FALSE) 16", fails without a goal or an AI, calls
//    AI slot 142 with 9. Without the AI byte +0x3C8 the state is done at
//    once (+0x54); otherwise it allows one repath, arms the path-end retarget
//    (+0x50) that AIBackAwayState::update consumes, calls the rowed
//    Object::rva0028AD32 and requests a path 40 units from the goal along
//    the normalized goal-to-owner offset (rowed Coord3D::normalize,
//    AIUpdateInterface::requestPath), then the pinned base onEnter. The
//    scaled offset is a member-wise copy so /arch:SSE batches its stores.
//
//  - AIWaitUntilFinishedFiringState::update 0x0034133E (83 bytes): fails
//    without a current weapon (rowed Object::getCurrentWeapon); continues
//    while the weapon's frame (+0x2C) plus its template delay (+0x78, when
//    not negative) is ahead of TheGameLogic's frame or its rowed
//    Weapon::getStatus is 5; then succeeds for a negative delay, else fails.
//  - AIMoveToStateSA::onEnter 0x0034C8C5 (207 bytes; slot 4 of 0x00C11F00):
//    Zero Hour's AIMoveToState::onEnter with "setAdjustDestination" log
//    lines 4/5: adjust on, off again when the goal object is the AI's
//    ignored obstacle (pinned getter 0x0006E009, +0x164), goal position from
//    the goal object or the machine, the pinned base onEnter, then AI slot
//    136 when +0x50 is set and the AI is moving (pinned isMoving).
//  - AIMoveToStateSA::update 0x00347A51 (91 bytes; 0x00C11F00): while +0x50
//    is set, fails once TheGameLogic's frame passes +0x4C and otherwise
//    clears condition bit 61 and continues; else follows the machine goal
//    object's position and runs the pinned AIInternalMoveToState::update.
//  - AIGoingIdleState::onEnter 0x00341E48 (40 bytes; 0x00C11798): pokes the
//    owner's StancesBehavior module (rowed Object::findModule with the
//    StancesBehavior key, pinned member 0x0045F235) and fails.
//
// The meaning of the status, condition and AI bytes is not recovered.

typedef bool Bool;
typedef float Real;
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
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	WEAPON_STATUS_BFME_5 = 5
};

struct Coord3D
{
	Real x, y, z;
	void normalize();
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

struct WeaponTemplateView
{
	unsigned char m_pad00[0x78];
	int m_bfmeDelay78; // +0x78
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	const WeaponTemplateView *m_template04() const { return m_template; }
	unsigned int m_bfmeFrame2C() const { return m_frame; }
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplateView *m_template; // +0x04
	unsigned char m_pad08[0x2C - 0x08];
	unsigned int m_frame; // +0x2C
};

class StancesBehavior
{
public:
	void rva0045F235();
};

NameKeyType Rva0045EE2CGet();
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_1C = 0x1C
};
enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};

extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, text);
	}
}

template <int N> class AIComputePathAISlots : public AIComputePathAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIComputePathAISlots<0>
{
};

enum ObjectID
{
	INVALID_ID = 0
};

class AIUpdateInterface : public AIComputePathAISlots<136>
{
public:
	virtual void rva0034C988Slot136() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void rva00347F6BSlot142(int value) = 0;
	ObjectID getIgnoredObstacleID() const;
	Bool isMoving() const;
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	unsigned char m_pad004[0x3C8 - 0x04];
	Bool m_bfmeFlag3C8; // +0x3C8
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

class Module;

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
	Module *findModule(NameKeyType key) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	void releaseWeaponLock(WeaponLockType lockType);
	void rva0028AE6D();
	void rva0028AD32();
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
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
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
protected:
	virtual Bool computePath();
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
	virtual StateReturnType update();
protected:
	virtual Bool computePath();
	void setAdjustsDestination(Bool b) { m_adjustDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};

class AIMoveAndTightenState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIMoveAndTightenState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath4");
	return true;
}

class AIMoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
};

Bool AIMoveAwayAndCowerState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath8");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIMoveAwayAndCowerState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (owner && owner->getAI())
		owner->getAI()->rva00347F6BSlot142(0);
}

class AIBackAwayState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
	Bool m_retargetToPathEnd; // +0x50
	unsigned char m_pad51[0x54 - 0x51];
	Bool m_done; // +0x54
};

StateReturnType AIBackAwayState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 16");
	setAdjustsDestination(false);
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (goal == 0 || ai == 0)
		return STATE_FAILURE;
	ai->rva00347F6BSlot142(9);
	if (ai->m_bfmeFlag3C8)
	{
		m_okToRepathTimes = 1;
		m_retargetToPathEnd = true;
		m_done = false;
		owner->rva0028AD32();

		// Back away 40 units from the goal along the goal-to-owner direction.
		Coord3D dest;
		Coord3D dir;
		Real ox = owner->getPosition()->x;
		Real oy = owner->getPosition()->y;
		Real oz = owner->getPosition()->z;
		dest.x = ox;
		dest.y = oy;
		dest.z = oz;
		dir.x = ox - goal->getPosition()->x;
		dir.y = oy - goal->getPosition()->y;
		dir.z = oz - goal->getPosition()->z;
		dir.normalize();
		Coord3D offset;
		offset.x = dir.x;
		offset.y = dir.y;
		offset.z = dir.z;
		offset.x *= 40.0f;
		offset.y *= 40.0f;
		offset.z *= 40.0f;
		dest.x += offset.x;
		dest.y += offset.y;
		dest.z += offset.z;
		ai->requestPath(&dest, true);
		return AIInternalMoveToState::onEnter();
	}
	m_retargetToPathEnd = false;
	m_done = true;
	return STATE_CONTINUE;
}

Bool AIBackAwayState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath9");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIBackAwayState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	owner->clearModelConditionBit(65);
	if (owner->getAI())
	{
		owner->getAI()->rva00347F6BSlot142(0);
		owner->getAI()->m_bfmeFlag3C8 = false;
	}
}

class AIPickUpCrateState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIPickUpCrateState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath30");
	return AIInternalMoveToState::computePath();
}

class AIFollowPathState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIFollowPathState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath31");
	return AIInternalMoveToState::computePath();
}

class AIWaitUntilFinishedFiringState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

StateReturnType AIWaitUntilFinishedFiringState::update()
{
	const Weapon *weapon = getMachineOwner()->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	int delay = weapon->m_template04()->m_bfmeDelay78;
	if (delay >= 0)
	{
		if (weapon->m_bfmeFrame2C() + delay > TheGameLogic->getFrame())
			return STATE_CONTINUE;
	}
	if (weapon->getStatus() == WEAPON_STATUS_BFME_5)
		return STATE_CONTINUE;
	if (weapon->m_template04()->m_bfmeDelay78 < 0)
		return STATE_SUCCESS;
	return STATE_FAILURE;
}

void AIWaitUntilFinishedFiringState::onExit(StateExitType status)
{
	getMachineOwner()->releaseWeaponLock(LOCKED_TEMPORARILY);
}

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeSquishState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	getMachineOwner()->setStatus(OBJECT_STATUS_BFME_1C, false);
}

class AIMoveToStateSA : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned int m_bfmeFrame4C; // +0x4C
	Bool m_bfmeFlag50; // +0x50
};

StateReturnType AIMoveToStateSA::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 4");
	setAdjustsDestination(true);

	// If we have a goal object and are trying to ignore it as an obstacle...
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (getMachine()->getGoalObject())
	{
		if (ai && getMachine()->getGoalObject()->getID() == ai->getIgnoredObstacleID())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 5");
			setAdjustsDestination(false);
		}
	}

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();

	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (m_bfmeFlag50 && ai && ai->isMoving())
		ai->rva0034C988Slot136();
	return ret;
}

StateReturnType AIMoveToStateSA::update()
{
	if (m_bfmeFlag50)
	{
		if (TheGameLogic->getFrame() > m_bfmeFrame4C)
			return STATE_FAILURE;
		getMachineOwner()->clearModelConditionBit(61);
		return STATE_CONTINUE;
	}
	Object *goal = getMachine()->getGoalObject();
	if (goal)
		m_goalPosition = *goal->getPosition();
	return AIInternalMoveToState::update();
}

class AIGoingIdleState : public State
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIGoingIdleState::onEnter()
{
	Object *owner = getMachineOwner();
	if (owner)
	{
		StancesBehavior *stances = (StancesBehavior *)owner->findModule(Rva0045EE2CGet());
		if (stances)
			stances->rva0045F235();
	}
	return STATE_FAILURE;
}
