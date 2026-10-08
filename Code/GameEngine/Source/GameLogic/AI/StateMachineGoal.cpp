// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
//
// ?internalSetGoalPosition@StateMachine@@QAEXPBUCoord3D@@M@Z,
// retail 0x004D73C4, 32 bytes, plus
// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z,
// retail 0x004D7435, 39 bytes, plus
// ?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@M@Z,
// retail 0x004D745C, 26 bytes, plus
// ?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z,
// retail 0x00262224, 22 bytes, plus
// ?halt@StateMachine@@QAEXXZ,
// retail 0x004D73A4, 9 bytes, plus
// ?internalGetState@StateMachine@@QAEPAUState@@H@Z,
// retail 0x004D764C, 31 bytes, plus
// ?internalSetState@StateMachine@@QAE?AW4StateReturnType@@H@Z,
// retail 0x004D766B, 135 bytes, plus
// ?initDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ,
// retail 0x004D770F, 23 bytes, plus
// ?hasState@StateMachine@@QAE_NH@Z,
// retail 0x004D76F2, 29 bytes. Dedicated TU for the StateMachine goal
// file-unit: the lock-gated setter, the storing worker, the object setter,
// the one-argument overload that supplies the default range, the halt, the
// state-map lookup, the transition worker that exits the old state,
// enters the new one, and handles sleep versus transition returns,
// and the default-state initializer guarded by the inited flag,
// and the state-map contains check.
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

// The shared headers declare these members with the access/virtual spelling
// retail's vftables reference; the ledger row keeps the spelling this TU
// compiled to. Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:?initDefaultState@StateMachine@@UAE?AW4StateReturnType@@XZ=?initDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?halt@StateMachine@@UAEXXZ=?halt@StateMachine@@QAEXXZ")
#pragma comment(linker, "/alternatename:?updateStateMachine@StateMachine@@UAE?AW4StateReturnType@@XZ=?updateStateMachine@StateMachine@@QAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?resetToDefaultState@StateMachine@@UAE?AW4StateReturnType@@XZ=?resetToDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?clear@StateMachine@@UAEXXZ=?clear@StateMachine@@QAEXXZ")
#include <cfloat>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int StateID;
typedef bool Bool;

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
	// slot 5 and update through slot 6 and isBusy through slot 10; the lower
	// slots belong to the Snapshot and MemoryPoolObject bases plus the State
	// virtuals this TU never calls.
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual Bool isIdle() const;
	virtual Bool isAttack() const;
	virtual Bool isGuardIdle() const;
	virtual Bool isBusy() const;
	virtual Bool vslot2C() const;
	virtual Bool vslot30() const;
	virtual Bool vslot34() const;
	virtual Bool vslot38() const;
	virtual void vslot3C();
	virtual void vslot40();
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

extern GameLogic *TheGameLogic;

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
	Int m_unk34; // +0x34 retail resetToDefaultState zeroes alongside goal members (internalClear); identity unproven
	bool m_locked; // +0x38
	bool m_defaultStateInited; // +0x39

	void setGoalPosition(const Coord3D *pos, float goalRange);
	void setGoalPosition(const Coord3D *pos);
	void internalSetGoalPosition(const Coord3D *pos, float goalRange);
	void setGoalObject(Object *obj);
	void halt();
	State *internalGetState(StateID id);
	Bool hasState(StateID id);
 	StateReturnType internalSetState(StateID newStateID);
 	StateReturnType initDefaultState();
 	StateReturnType resetToDefaultState();
 	StateReturnType setState(StateID newStateID);
 	void rva004D7627(StateID id);
 	void clear();
	StateReturnType updateStateMachine();
	Bool isInBusyState() const;
	Bool isInAttackState() const;
	Bool isInGuardIdleState() const;
	Bool rva002621DA() const;
	Bool rva002621EB() const;
	Bool rva002621FC() const;
	Bool rva0026220D() const;
	void lock(const char *msg);
	void rva004D7395();
};

// ?internalSetGoalPosition@StateMachine@@QAEXPBUCoord3D@@M@Z
void StateMachine::internalSetGoalPosition(const Coord3D *pos, float goalRange)
{
	if (pos) {
		m_goalPosition = *pos;
		// Don't clear the goal object, or everything breaks.  Like construction of buildings.
	}
	m_goalRange = goalRange;
}

// ?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@M@Z
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

// ?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z (the unlimited-range
// overload; 10 matched callers pin this name)
void StateMachine::setGoalPosition(const Coord3D *pos)
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

// ?hasState@StateMachine@@QAE_NH@Z
Bool StateMachine::hasState(StateID id)
{
	return m_stateMap.find(id) != m_stateMap.end();
}

// ?rva004D7627@StateMachine@@QAEXH@Z @0x004D7627 37B
// Evidence: leaf with 1 unclaimed caller; layout from StateMachine (map at +0x08 via rowed _M_find 0x00357180, default at +0x1C); branchless neg/sbb/and sets default to id when found else 0.
void StateMachine::rva004D7627(StateID id)
{
	m_defaultStateID = (m_stateMap.find(id) != m_stateMap.end()) ? id : 0;
}

// ?setState@StateMachine@@QAE?AW4StateReturnType@@H@Z @0x004D7ACD 16B
// Retail lock-gated setter tail-jmps to internalSetState when unlocked.
// Donor BFME1 StateMachine.cpp setState verbatim minus debug.
// Vtable slot 8 of 19 Rva004D759C-derived classes; callers at 0x350403 and 0x4D8593.
StateReturnType StateMachine::setState(StateID newStateID)
{
	if (m_locked)
	{
		return STATE_CONTINUE;
	}

	return internalSetState(newStateID);
}

// ?resetToDefaultState@StateMachine@@QAE?AW4StateReturnType@@XZ @0x004D7A75 88B
// Retail vtable slot 6 (offset 0x18) of 19 Rva004D759C-derived vtables; donor BFME1
// StateMachine.cpp resetToDefaultState (locked check plus inited check plus onExit RESET
// plus internalClear plus internalSetState of default). BFME2 deltas: goalRange FLT_MAX
// plus unk34 zeroed with goal members; single callee internalSetState 0x004D766B rowed.
StateReturnType StateMachine::resetToDefaultState()
{
	if (m_locked)
	{
		return STATE_FAILURE;
	}

	if (!m_defaultStateInited)
	{
		return STATE_FAILURE;
	}

	if (m_currentState)
		((State *)m_currentState)->onExit(EXIT_RESET);

	m_goalPosition.x = 0.0f;
	m_goalPosition.y = 0.0f;
	m_goalPosition.z = 0.0f;
	m_currentState = NULL;
	m_goalObjectID = 0;
	m_unk34 = 0;
	m_goalRange = FLT_MAX;
	return internalSetState(m_defaultStateID);
}

// ?clear@StateMachine@@QAEXXZ @0x004D72C5 68B
// Retail vtable slot 5 (offset 0x14) of 19 Rva004D759C-derived vtables; donor BFME1
// StateMachine.cpp clear (locked gate plus onExit RESET plus internalClear inlined).
// BFME2 deltas same as reset: goalRange FLT_MAX plus unk34 zeroed; no callees.
void StateMachine::clear()
{
	if (m_locked)
	{
		return;
	}

	if (m_currentState)
		((State *)m_currentState)->onExit(EXIT_RESET);

	m_currentState = NULL;
	m_goalObjectID = 0;
	m_unk34 = 0;
	m_goalPosition.x = 0.0f;
	m_goalPosition.y = 0.0f;
	m_goalPosition.z = 0.0f;
	m_goalRange = FLT_MAX;
}

// ?updateStateMachine@StateMachine@@QAE?AW4StateReturnType@@XZ @0x004D7321 98B
// Retail vtable slot 4 (offset 0x10) of 19 Rva004D759C-derived vtables; donor BFME1
// StateMachine.cpp updateStateMachine verbatim minus debug (sleep gate plus update
// plus transition friends). BFME2 layout deltas: sleepTill +0x18 current +0x04.
// Callees update slot6 plus friend pins 0x004D722A 0x004D7148 already pinned.
StateReturnType StateMachine::updateStateMachine()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_sleepTill != 0 && now < m_sleepTill)
	{
		if (m_currentState == NULL)
		{
			return STATE_FAILURE;
		}
		return ((State *)m_currentState)->friend_checkForSleepTransitions(STATE_SLEEP(m_sleepTill - now));
	}

	m_sleepTill = 0;

	if (m_currentState)
	{
		State *stateBeforeUpdate = (State *)m_currentState;
		StateReturnType status = ((State *)m_currentState)->update();
		if (m_currentState == NULL)
		{
			return STATE_FAILURE;
		}
		if (stateBeforeUpdate != m_currentState)
		{
			status = STATE_CONTINUE;
		}
		if (IS_STATE_SLEEP(status))
		{
			m_sleepTill = now + GET_STATE_SLEEP_FRAMES(status);
			return ((State *)m_currentState)->friend_checkForSleepTransitions(STATE_SLEEP(m_sleepTill - now));
		}
		else
		{
			return ((State *)m_currentState)->friend_checkForTransitions(status);
		}
	}
	else
	{
		return STATE_FAILURE;
	}
}

// ?isInBusyState@StateMachine@@QBE_NXZ @0x004D7309 24B
// Retail gap between clear 0x004D72C5 and update 0x004D7321 in same TU; donor
// StateMachine.h isInBusyState verbatim (current null false else isBusy slot 0x28).
// No direct callees; indirect isBusy slot10.
inline Bool StateMachine::isInBusyState() const
{
	if (m_currentState != NULL)
	{
		if (((State *)m_currentState)->isBusy())
			return true;
	}
	return false;
}

// Out-of-line copies of the current-state queries, retail 0x002621B8..
// 0x0026221C (17, 17, 17, 17, 17 and 16 bytes) followed by lock (7 bytes,
// 0x0026221D). Each asks the current state's virtual at the given slot
// (isAttack 8, isGuardIdle 9, then slots 11-14) and answers true without a
// state, except the last, which answers false. isInAttackState sits in slot
// 11 of the StateMachine vtables (e.g. 0x00C11AEC); the others and lock have
// no reference, like the retail-kept copies of other header inlines.
inline Bool StateMachine::isInAttackState() const
{
	return m_currentState ? ((State *)m_currentState)->isAttack() : true;
}

inline Bool StateMachine::isInGuardIdleState() const
{
	return m_currentState ? ((State *)m_currentState)->isGuardIdle() : true;
}

inline Bool StateMachine::rva002621DA() const
{
	return m_currentState ? ((State *)m_currentState)->vslot2C() : true;
}

inline Bool StateMachine::rva002621EB() const
{
	return m_currentState ? ((State *)m_currentState)->vslot30() : true;
}

inline Bool StateMachine::rva002621FC() const
{
	return m_currentState ? ((State *)m_currentState)->vslot34() : true;
}

inline Bool StateMachine::rva0026220D() const
{
	return m_currentState ? ((State *)m_currentState)->vslot38() : false;
}

inline void StateMachine::lock(const char *msg)
{
	m_locked = true;
}

// ?rva004D7395@StateMachine@@QAEXXZ @0x004D7395 15B: slot 13 of the
// StateMachine vtables (e.g. 0x00C11AF4), between isInBusyState (slot 12)
// and setGoalObject; tail-calls the current state's slot 16 when there is one.
void StateMachine::rva004D7395()
{
	if (m_currentState != NULL)
		((State *)m_currentState)->vslot40();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStateMachineInlineAnchor@@YAXPAVStateMachine@@@Z absent-from-retail
void _bfmeStateMachineInlineAnchor(StateMachine *p)
{
    p->isInBusyState();
    p->isInAttackState();
    p->isInGuardIdleState();
    p->rva002621DA();
    p->rva002621EB();
    p->rva002621FC();
    p->rva0026220D();
    p->lock(0);
}
#pragma inline_depth()
