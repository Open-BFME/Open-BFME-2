// cl: /O1 /DNDEBUG /MD
//
// AIStateMachine::resetToDefaultState, retail 0x00350392 (62 bytes): slot 6 of
// vtable 0x00C14CD0, whose slot-2 name getter 0x00351753 returns
// AIStateMachine; slots 5..7 follow the Zero Hour StateMachine order clear,
// resetToDefaultState, initDefaultState (slot 7 is the rowed
// StateMachine::initDefaultState 0x004D770F). The body is the ZH override:
// StateMachine::resetToDefaultState (rowed 0x004D7A75), then the owner's AI is
// notified (AIUpdateInterface vslot 153, +0x264). BFME2 adds a first step:
// when a temporary state is set (+0x50) it returns STATE_CONTINUE if +0x54 is
// -1 and otherwise exits it through 0x0035033F (pinned by address).
// AIStateMachine::setState, retail 0x003503D0 (93 bytes), slot 8: the same
// temporary-state step, then the ZH override (current state id, rowed
// StateMachine::setState 0x004D7ACD, AI notified when the id changed). The
// current state is at machine+0x04 and its id at state+0x04.
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
template <int N> class AIStateMachineAISlots : public AIStateMachineAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIStateMachineAISlots<0>
{
};
// AIUpdateInterface virtual slots 0..152 are placeholders; slot 153 (+0x264)
// is the state-machine-changed notification.
class AIUpdateInterface : public AIStateMachineAISlots<153>
{
public:
	virtual void friend_notifyStateMachineChanged() = 0;
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};
typedef int StateID;
enum
{
	MACHINE_DONE_STATE_ID = 999998,
	INVALID_STATE_ID = 999999
};
class State
{
public:
	StateID getID() const { return m_ID; }
private:
	void *m_vtbl;
	StateID m_ID; // +0x04
};
class StateMachine
{
public:
	virtual ~StateMachine();
	StateReturnType resetToDefaultState();
	StateReturnType setState(StateID newStateID);
	Object *getOwner() const { return m_owner; }
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
};
class AIStateMachine : public StateMachine
{
public:
	virtual StateReturnType resetToDefaultState();
	virtual StateReturnType setState(StateID newStateID);
	void rva0035033F();
private:
	unsigned char m_pad18[0x50 - 0x18];
	State *m_temporaryState; // +0x50
	int m_54; // +0x54
};
StateReturnType AIStateMachine::resetToDefaultState()
{
	if (m_temporaryState)
	{
		if (m_54 == -1)
			return STATE_CONTINUE;
		rva0035033F();
	}
	StateReturnType tmp = StateMachine::resetToDefaultState();

	AIUpdateInterface *ai = getOwner()->getAI();
	if (ai)
		ai->friend_notifyStateMachineChanged();

	return tmp;
}
StateReturnType AIStateMachine::setState(StateID newStateID)
{
	if (m_temporaryState)
	{
		if (m_54 == -1)
			return STATE_CONTINUE;
		rva0035033F();
	}
	StateID oldID = getCurrentStateID();
	StateReturnType tmp = StateMachine::setState(newStateID);

	AIUpdateInterface *ai = getOwner()->getAI();
	if (ai && oldID != newStateID)
		ai->friend_notifyStateMachineChanged();

	return tmp;
}
