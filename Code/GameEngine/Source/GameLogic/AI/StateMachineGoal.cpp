// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
//
// ?internalSetGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z,
// retail 0x004D73C4, 32 bytes, plus
// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z,
// retail 0x004D7435, 39 bytes, plus
// ?setGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z,
// retail 0x004D745C, 26 bytes, plus
// ?setGoalPosition@TurretStateMachine@@QAEXPBUCoord3D@@@Z,
// retail 0x00262224, 22 bytes, plus
// ?halt@StateMachine@@QAEXXZ,
// retail 0x004D73A4, 9 bytes, plus
// ?internalGetState@StateMachine@@QAEPAUState@@H@Z,
// retail 0x004D764C, 31 bytes, plus
// ?internalSetState@StateMachine@@QAE?AW4StateReturnType@@H@Z,
// retail 0x004D766B, 135 bytes, plus
// ?initDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ,
// retail 0x004D770F, 23 bytes. Dedicated TU for the StateMachine goal
// file-unit: the lock-gated setter, the storing worker, the object setter,
// the TurretAI wrapper that supplies the default range, the halt, the
// state-map lookup, the transition worker that exits the old state,
// enters the new one, and handles sleep versus transition returns,
// and the default-state initializer guarded by the inited flag.
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/
// StateMachine.cpp, StateMachine::setGoalPosition plus
// internalSetGoalPosition plus setGoalObject plus halt plus
// internalGetState plus internalSetState): the lock flag gates the setter, the worker copies the
// position when non-null, and the object setter records the id plus
// forwards the object's position. BFME2 deltas:
// the worker takes a second float argument kept in the new member at +0x30
// (callers pass FLT_MAX for the unlimited default, the object setter
// forwards the stored value), the lock lives at +0x38, the id/position
// reads are direct (m_id at +0x74, m_position at +0x38) instead of virtual,
// and the lookup returns null on a miss instead of recovering.

#include <cfloat>
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int StateID;

enum { MACHINE_DONE_STATE_ID = 999998, INVALID_STATE_ID = 999999 };

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL,
	EXIT_RESET
};

#define IS_STATE_SLEEP(ret) ((Int)(ret) > 0)
#define GET_STATE_SLEEP_FRAMES(ret) ((UnsignedInt)(ret))
#define STATE_SLEEP(numFrames) ((StateReturnType)(numFrames))

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	Int m_id; // +0x74
};

struct State
{
	// Retail reaches onEnter through vtable slot 4 and onExit through
	// slot 5; the lower slots belong to the Snapshot and MemoryPoolObject
	// bases plus the State virtuals this TU never calls.
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	StateReturnType friend_checkForTransitions(StateReturnType status);
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
	UnsignedInt getFrame() { return m_frame; }
};

static GameLogic *TheGameLogic;

class StateMachine
{
public:
	unsigned char m_pad00[0x04];
	void *m_currentState; // +0x04
	_STL::map<StateID, State *> m_stateMap; // +0x08
	unsigned char m_pad14[0x18 - 0x14];
	UnsignedInt m_sleepTill; // +0x18
	StateID m_defaultStateID; // +0x1C
	Int m_goalObjectID; // +0x20
	Coord3D m_goalPosition; // +0x24
	float m_goalRange; // +0x30, BFME2-new range carried with the goal
	unsigned char m_pad34[0x38 - 0x34];
	bool m_locked; // +0x38
	bool m_defaultStateInited; // +0x39

	void setGoalPosition(const Coord3D *pos, float goalRange);
	void internalSetGoalPosition(const Coord3D *pos, float goalRange);
	void setGoalObject(Object *obj);
	void halt();
	State *internalGetState(StateID id);
	StateReturnType internalSetState(StateID newStateID);
	StateReturnType initDefaultState();
};

class TurretStateMachine : public StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);
};

// ?internalSetGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z
void StateMachine::internalSetGoalPosition(const Coord3D *pos, float goalRange)
{
	if (pos) {
		m_goalPosition = *pos;
		// Don't clear the goal object, or everything breaks.  Like construction of buildings.
	}
	m_goalRange = goalRange;
}

// ?setGoalPosition@StateMachine@@QAEXPBVCoord3D@@M@Z
void StateMachine::setGoalPosition(const Coord3D *pos, float goalRange)
{
	if (m_locked)
		return;
	internalSetGoalPosition(pos, goalRange);
}

// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z
void StateMachine::setGoalObject(Object *obj)
{
	if (obj) {
		m_goalObjectID = obj->m_id;
		internalSetGoalPosition(&obj->m_position, m_goalRange);
	}
	else {
		m_goalObjectID = 0;
	}
}

// ?setGoalPosition@TurretStateMachine@@QAEXPBUCoord3D@@@Z
void TurretStateMachine::setGoalPosition(const Coord3D *pos)
{
	StateMachine::setGoalPosition(pos, FLT_MAX);
}

// ?halt@StateMachine@@QAEXXZ
void StateMachine::halt()
{
	m_locked = true;
	m_currentState = 0; // don't exit current state, just clear it.
}

// ?internalGetState@StateMachine@@QAEPAUState@@H@Z
State *StateMachine::internalGetState(StateID id)
{
	// locate the actual state associated with the given ID
	_STL::map<StateID, State *>::iterator i = m_stateMap.find(id);
	if (i == m_stateMap.end())
		return 0;
	return (*i).second;
}

// ?internalSetState@StateMachine@@QAE?AW4StateReturnType@@H@Z
StateReturnType StateMachine::internalSetState(StateID newStateID)
{
	State *newState = NULL;

	// anytime the state changes, stop sleeping
	m_sleepTill = 0;

	// if we're not setting the "done" state ID we will continue with the actual transition
	if (newStateID != MACHINE_DONE_STATE_ID)
	{
		// if incoming state is invalid, go to the machine's default state
		if (newStateID == INVALID_STATE_ID)
		{
			newStateID = m_defaultStateID;
			if (newStateID == INVALID_STATE_ID)
			{
				return STATE_FAILURE;
			}
		}

		// extract the state associated with the given ID
		newState = internalGetState(newStateID);
	}

	// invoke the old state's onExit()
	if (m_currentState)
		((State *)m_currentState)->onExit(EXIT_NORMAL);

	// set the new state
	m_currentState = newState;

	// invoke the new state's onEnter()
	if (m_currentState)
	{
		// onEnter() could conceivably change m_currentState, so save it for a moment...
		State *stateBeforeEnter = (State *)m_currentState;

		StateReturnType status = ((State *)m_currentState)->onEnter();

		// it is possible that the state's onEnter() method may cause the state to be destroyed
		if (m_currentState == NULL)
		{
			return STATE_FAILURE;
		}

		// if the state changed, we must ignore any sleep result and pretend we got STATE_CONTINUE,
		// so that the new state will be called immediately.
		if (stateBeforeEnter != m_currentState)
		{
			status = STATE_CONTINUE;
		}

		if (IS_STATE_SLEEP(status))
		{
			// hey, we're sleepy!
			UnsignedInt now = TheGameLogic->getFrame();
			m_sleepTill = now + GET_STATE_SLEEP_FRAMES(status);
			return ((State *)m_currentState)->friend_checkForSleepTransitions(STATE_SLEEP(m_sleepTill - now));
		}
		else
		{
			// check for state transitions, possibly exiting this machine
			return ((State *)m_currentState)->friend_checkForTransitions(status);
		}
	}
	else
	{
		return STATE_CONTINUE;
	}
}

// ?initDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ
StateReturnType StateMachine::initDefaultState()
{
	if (m_defaultStateInited)
	{
		return STATE_FAILURE;
	}

	m_defaultStateInited = true;
	return internalSetState(m_defaultStateID);
}
