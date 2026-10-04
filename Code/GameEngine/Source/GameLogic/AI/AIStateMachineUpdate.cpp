// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AIStateMachine temporary-state bodies, ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Vtable 0x00C14CD0 (slot-2 name
// getter returns AIStateMachine; slots 6 and 8 are the rowed
// resetToDefaultState and setState).
//  - updateStateMachine, retail 0x003502CA (117 bytes), slot 4: Zero Hour's
//    temporary-state step (state +0x50, end frame +0x54), where BFME 2 keeps
//    running while the state returns STATE_CONTINUE or a sleep (>= 0) or is
//    gone (returning the status without the base update), and
//    on leaving the temporary state restores the saved goal object (id
//    +0x58, through the rowed StateMachine::rva004D750F) and goal position
//    (+0x5C), then pokes the current state's vslot 7; the base
//    StateMachine::updateStateMachine (rowed 0x004D7321) follows.
//  - rva0035033F, retail 0x0035033F (83 bytes): the same exit with
//    EXIT_RESET, used by clear, resetToDefaultState and setState; it ends by
//    handing the owner's +0x24C object to 0x004B0E9C.
//  - clear, retail 0x00352B41 (92 bytes), slot 5: BFME 2 first leaves a
//    temporary state (none while its end frame is -1, as in setState), then
//    Zero Hour's StateMachine::clear (rowed 0x004D72C5), goal path clear (the
//    out-of-line 12-byte vector erase 0x002A133B), goal waypoint (+0x48) and
//    goal squad (+0x4C, deleted here with a global delete) cleared, and the
//    AI notified (AIUpdateInterface vslot 153).
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};
#define IS_STATE_CONTINUE_OR_SLEEP(r) ((r) >= STATE_CONTINUE)

struct Coord3D
{
	Real x, y, z;
};

template <int N> class AIStateMachineAISlots : public AIStateMachineAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIStateMachineAISlots<0>
{
};
class AIUpdateInterface : public AIStateMachineAISlots<153>
{
public:
	virtual void friend_notifyStateMachineChanged() = 0;
};

class Rva004B0E9C
{
public:
	void rva004B0E9C();
};

class Object
{
public:
	unsigned char m_pad000[0x24C];
	Rva004B0E9C *m_bfme24C; // +0x24C
	unsigned char m_pad250[0x258 - 0x250];
	AIUpdateInterface *m_ai; // +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

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
	virtual void slot07();
};

class Squad
{
public:
	virtual ~Squad();
};

class StateMachine
{
public:
	virtual ~StateMachine();
	StateReturnType updateStateMachine();
	void clear();
	void rva004D750F(Object *obj); // goal object setter
	void setGoalPosition(const Coord3D *pos);
	Object *getOwner() const { return m_owner; }
protected:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
};

class Waypoint;

// vector::clear spelled out: the census's other vector<Coord3D>::clear copy
// comes from a configuration that inlines erase, while retail calls the
// out-of-line erase here.
typedef _STL::vector<Coord3D> GoalPathVector;
static inline void clearGoalPath(GoalPathVector &path)
{
	path.erase(path.begin(), path.end());
}

class AIStateMachine : public StateMachine
{
public:
	virtual StateReturnType updateStateMachine();
	virtual void clear();
	void rva0035033F();
private:
	unsigned char m_pad18[0x3C - 0x18];
	GoalPathVector m_goalPath; // +0x3C
	const Waypoint *m_goalWaypoint; // +0x48
	Squad *m_goalSquad; // +0x4C
	State *m_temporaryState; // +0x50
	UnsignedInt m_temporaryStateFramEnd; // +0x54
	ObjectID m_savedGoalObjectID; // +0x58
	Coord3D m_savedGoalPosition; // +0x5C
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIStateMachine::updateStateMachine()
{
	if (m_temporaryState)
	{
		// execute this state
		StateReturnType status = m_temporaryState->update();
		if (m_temporaryStateFramEnd < TheGameLogic->getFrame()) {
			// ran out of time.
			if (status == STATE_CONTINUE) {
				status = STATE_SUCCESS;
			}
		}
		if (IS_STATE_CONTINUE_OR_SLEEP(status) || m_temporaryState == NULL)
		{
			return status;
		}
		m_temporaryState->onExit(EXIT_NORMAL);
		rva004D750F(TheGameLogic->findObjectByID(m_savedGoalObjectID));
		setGoalPosition(&m_savedGoalPosition);
		m_savedGoalObjectID = INVALID_ID;
		m_temporaryState = NULL;
		if (m_currentState)
			m_currentState->slot07();
	}
	return StateMachine::updateStateMachine();
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::rva0035033F()
{
	if (m_temporaryState)
	{
		m_temporaryState->onExit(EXIT_RESET);
		rva004D750F(TheGameLogic->findObjectByID(m_savedGoalObjectID));
		setGoalPosition(&m_savedGoalPosition);
		m_savedGoalObjectID = INVALID_ID;
		m_temporaryState = NULL;
		Object *owner = getOwner();
		if (owner && owner->m_bfme24C)
			owner->m_bfme24C->rva004B0E9C();
	}
}

//----------------------------------------------------------------------------------------------------------
void AIStateMachine::clear()
{
	if (m_temporaryState)
	{
		if (m_temporaryStateFramEnd == (UnsignedInt)-1)
			return;
		rva0035033F();
	}
	StateMachine::clear();
	clearGoalPath(m_goalPath);
	m_goalWaypoint = NULL;
	if (m_goalSquad)
		::delete m_goalSquad;
	m_goalSquad = NULL;

	AIUpdateInterface* ai = getOwner()->m_ai;
	if (ai)
		ai->friend_notifyStateMachineChanged();
}
