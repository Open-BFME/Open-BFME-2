// cl: /DNDEBUG /MD
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
#include "../../../Include/Common/StateMachine.h"
// The canonical header places the state-machine notification at slot 153.
#include "../../../Include/GameLogic/Module/AIUpdate.h"
class Object
{
public:
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};
enum
{
	MACHINE_DONE_STATE_ID = 999998,
	INVALID_STATE_ID = 999999
};
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual StateReturnType resetToDefaultState();
	virtual StateReturnType setState(unsigned int newStateID);
	Object *getOwner() const { return m_owner; }
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->m_id : INVALID_STATE_ID; }
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
};
class AIStateMachine : public StateMachine
{
public:
	virtual StateReturnType resetToDefaultState();
	virtual StateReturnType setState(unsigned int newStateID);
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

	AIUpdateInterface *ai = Object::getAI(getOwner());
	if (ai)
		ai->vslot153();

	return tmp;
}
StateReturnType AIStateMachine::setState(unsigned int newStateID)
{
	if (m_temporaryState)
	{
		if (m_54 == -1)
			return STATE_CONTINUE;
		rva0035033F();
	}
	StateID oldID = getCurrentStateID();
	StateReturnType tmp = StateMachine::setState(newStateID);

	AIUpdateInterface *ai = Object::getAI(getOwner());
	if (ai && oldID != newStateID)
		ai->vslot153();

	return tmp;
}
