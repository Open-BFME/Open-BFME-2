// cl: /O1 /DNDEBUG /MD
//
// Small AI state bodies ported from Zero Hour's GameEngine/Source/GameLogic/
// AI/AIStates.cpp (GeneralsMD tree vendored under reference/open-bfme-1/
// inputs/reference). Each vtable is named by its slot-2 name getter:
//  - AIMoveAndDeleteState::onExit, retail 0x0034A0CB (12 bytes): slot 5 of
//    0x00C12C88 (unlock, then the pinned base onExit as a tail jump).
//  - AIAttackAreaState::onExit, retail 0x0034234C (34 bytes): slot 5 of
//    0x00C11900; attack machine +0x20.
//  - AIHuntState::onExit, retail 0x003421F4 (51 bytes): slot 5 of 0x00C118B0;
//    hunt machine +0x20, then releaseWeaponLock(LOCKED_TEMPORARILY) (pinned
//    Object::releaseWeaponLock 0x0028D8B6: contain vslot then the +0x330
//    weapon set).
//  - AIAttackPursueTargetState::onExit, retail 0x003495FD (20 bytes): slot 5
//    of 0x00C12730; m_isInitialApproach +0x5F.
//  - AIAttackMoveToState::onEnter, retail 0x0034EC7B (96 bytes): slot 4 of
//    0x00C13548 (slot 5 is the rowed onExit). ZH body over the pinned
//    AIMoveToState::onEnter 0x0034C7BD (slot 4 of AIMoveToState's vtable
//    0x00C11EB8); BFME 2 then records the machine's goal object id (+0x20)
//    at +0x6C or, with none, the machine goal position (+0x24) at +0x60
//    (both unnamed). Layout: m_commandSrc +0x50, attack-move machine +0x54
//    (clear vslot 5, setState vslot 8), m_frameToSleepUntil +0x58,
//    m_retryCount +0x5C; getLastCommandSource is AI vslot 143.
//  - AIMoveAndDeleteState::onEnter, retail 0x0034ECDB (160 bytes): slot 4 of
//    0x00C12C88. ZH body (setAdjustsDestination(false) with the CritterDesync
//    log, lock, goal object or goal position, m_appendGoalPosition +0x4C);
//    BFME 2 then sets owner model conditions 1*32+29 and 7*32+28 (the
//    Object+0x10C condition words, as in AIAttackStateOnExit.cpp), each
//    followed by the rowed notifier Object::rva0028AE6D when it changes.
//  - AIBackAwayAndCowerState::onExit, retail 0x0034025E (31 bytes), and
//    ::update, retail 0x0034022F (47 bytes): slots 5 and 6 of 0x00C10EE0.
//    BFME 2 state with a sub-machine at +0x20 (AIAttackState's pattern):
//    onExit deletes it when present; update fails without it, succeeds once
//    it reports EXIT_MACHINE_WITH_SUCCESS (999998) and otherwise runs its
//    updateStateMachine (StateMachine vslot 4).
//  - AIMoveToPositionAndDieState::onEnter, retail 0x0034FFBE (98 bytes):
//    slot 4 of 0x00C12CE8. AIMoveAndDeleteState::onEnter's shape (log line
//    60) without the model conditions, the base onEnter as a tail jump.
//  - GiantBirdDieState::onEnter, retail 0x00367914 (21 bytes): slot 4 of
//    0x00C175A8. Destroys the owner through TheGameLogic (rowed
//    GameLogic::destroyObject) and succeeds.
// None of these four starts is in the Ghidra inventory; each is reached
// only from its vtable slot.
// The sub-machines are deleted with a global-scope delete (vslot 0 with flag
// 0, then ::operator delete).
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#define NULL 0
#define ATTACK_RETRY_COUNT 5
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
enum
{
	EXIT_MACHINE_WITH_SUCCESS = 999998,
	INVALID_STATE_ID = 999999
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
enum
{
	AI_IDLE = 0
};
struct Coord3D
{
	Real x, y, z;
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
class AIUpdateInterface : public VSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0;
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
private:
	unsigned int m_words[19];
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	void releaseWeaponLock(WeaponLockType lockType);
	void rva0028AE6D();
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x10C - 0x44];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
class State;
class GameLogic
{
public:
	void destroyObject(Object *obj);
};
extern GameLogic *TheGameLogic;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType updateStateMachine();
	virtual void clear();
	virtual void slot06(); virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void lock(const char *msg) { m_locked = true; }
	void unlock() { m_locked = false; }
	StateID getCurrentStateID() const;
	State *m_currentState; // +0x04
	UnsignedInt m_pad08[3];
	Object *m_owner; // +0x14
	UnsignedInt m_pad18[2];
	UnsignedInt m_goalObjectID; // +0x20
	Coord3D m_goalPosition; // +0x24
	UnsignedInt m_pad30[2];
	Bool m_locked; // +0x38
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
	StateID getID() const { return m_ID; }
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};

// ?StateMachine::getCurrentStateID absent-from-retail
inline StateID StateMachine::getCurrentStateID() const
{
	return m_currentState ? m_currentState->getID() : INVALID_STATE_ID;
}
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	__forceinline void setAdjustsDestinationFalse50()
	{
		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log)
				fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 50");
		}
		m_adjustsDestination = false;
	}
	__forceinline void setAdjustsDestinationFalse60()
	{
		if (g_00E03745)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log)
				fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 60");
		}
		m_adjustsDestination = false;
	}
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};
class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};
class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	Bool m_appendGoalPosition; // +0x4C
};
class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	Bool m_appendGoalPosition; // +0x4C
};
class GiantBirdDieState : public State
{
public:
	virtual StateReturnType onEnter();
};
class AIAttackAreaState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_attackMachine; // +0x20
};
class AIHuntState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_huntMachine; // +0x20
};
class AIBackAwayAndCowerState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_backAwayMachine; // +0x20
};
class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad4C[0x5F - 0x4C];
	Bool m_isInitialApproach; // +0x5F
};
class AIAttackMoveToState : public AIMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad4C[0x50 - 0x4C];
	CommandSourceType m_commandSrc; // +0x50
	StateMachine *m_attackMoveMachine; // +0x54
	UnsignedInt m_frameToSleepUntil; // +0x58
	int m_retryCount; // +0x5C
	Coord3D m_bfmeGoalPosition60; // +0x60
	UnsignedInt m_bfmeGoalObjectID6C; // +0x6C
};

StateReturnType AIMoveAndDeleteState::onEnter()
{
	setAdjustsDestinationFalse50();
	getMachine()->lock("AIMoveAndDeleteState::onEnter");
	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	m_appendGoalPosition = true; // We may be moving off the map.
	Object *owner = getMachineOwner();
	if (owner)
	{
		owner->setModelConditionState(1 * 32 + 29);
		owner->setModelConditionState(7 * 32 + 28);
	}
	return AIInternalMoveToState::onEnter();
}

void AIMoveAndDeleteState::onExit( StateExitType status )
{
	getMachine()->unlock();
	AIInternalMoveToState::onExit( status );
}

void AIAttackAreaState::onExit( StateExitType status )
{
	// destroy the hunt machine
	::delete m_attackMachine;
	m_attackMachine = NULL;
}

void AIHuntState::onExit( StateExitType status )
{
	// destroy the hunt machine
	::delete m_huntMachine;
	m_huntMachine = NULL;

	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->releaseWeaponLock(LOCKED_TEMPORARILY);	// release any temporary locks.
	}
}

void AIAttackPursueTargetState::onExit( StateExitType status )
{
	// contained by AIAttackState, so no separate timer
	AIInternalMoveToState::onExit( status );

	m_isInitialApproach = false;	// We only want to allow turreted things to fire at enemies during their
																// first approach
}

StateReturnType AIAttackMoveToState::onEnter()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	m_attackMoveMachine->clear();
	m_attackMoveMachine->setState( AI_IDLE );
	m_commandSrc = ai->getLastCommandSource();
	m_retryCount = ATTACK_RETRY_COUNT;
	m_frameToSleepUntil = 0;

	StateReturnType ret = AIMoveToState::onEnter();
	StateMachine *machine = getMachine();
	if (machine->m_goalObjectID)
	{
		m_bfmeGoalObjectID6C = machine->m_goalObjectID;
	}
	else
	{
		m_bfmeGoalObjectID6C = 0;
		m_bfmeGoalPosition60 = machine->m_goalPosition;
	}
	return ret;
}

void AIBackAwayAndCowerState::onExit( StateExitType status )
{
	if (m_backAwayMachine)
	{
		::delete m_backAwayMachine;
		m_backAwayMachine = NULL;
	}
}

StateReturnType AIBackAwayAndCowerState::update()
{
	if (m_backAwayMachine == NULL)
		return STATE_FAILURE;
	if (m_backAwayMachine->getCurrentStateID() == EXIT_MACHINE_WITH_SUCCESS)
		return STATE_SUCCESS;
	return m_backAwayMachine->updateStateMachine();
}

StateReturnType AIMoveToPositionAndDieState::onEnter()
{
	setAdjustsDestinationFalse60();
	getMachine()->lock("AIMoveToPositionAndDieState::onEnter");
	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	m_appendGoalPosition = true; // We may be moving off the map.
	return AIInternalMoveToState::onEnter();
}

StateReturnType GiantBirdDieState::onEnter()
{
	TheGameLogic->destroyObject(getMachineOwner());
	return STATE_SUCCESS;
}
