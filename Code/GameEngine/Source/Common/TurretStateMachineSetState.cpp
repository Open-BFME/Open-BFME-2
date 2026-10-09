// cl: /MD
// ?setState@TurretStateMachine@@QAE?AW4StateReturnType@@H@Z, retail 0x004D8578, 62 bytes.
// Virtual slot 8 (offset 0x20) of vtable 0x008609C8 (VA 0x00C609C8), class
// TurretStateMachine (slot 2 returns "TurretStateMachine" at 0x00860A08).
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// TurretStateMachine::setState verbatim plus BFME2 layout deltas: current-state
// pointer at +0x04 (StateMachine base), StateID at State+0x04, TurretAI owner at
// +0x3C, friend_notifyStateMachineChanged inlined as m_sleepUntil (+0x34) =
// TheGameLogic->getFrame ([0x00DFE78C]+0x40). Single callee setState 0x004D7ACD
// already rowed in StateMachineGoal.cpp.

extern class GameLogic *TheGameLogic;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

typedef int StateID;

enum { INVALID_STATE_ID = 999999 };

struct TurretState
{
	char m_pad00[4];
	StateID m_id;
};

struct GameLogicFrame
{
	char m_pad00[0x40];
	unsigned int m_frame;
	unsigned int getFrame() const { return m_frame; }
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

class TurretAI
{
public:
	void friend_notifyStateMachineChanged() { m_sleepUntil = TheGameLogic->getFrame(); }
	char m_pad00[0x34];
	unsigned int m_sleepUntil;
};

class StateMachine
{
public:
	StateReturnType setState(StateID newStateID);
	StateReturnType resetToDefaultState();
	void clear();
	// The machine's vptr (only the derived turret machine's own slots are
	// declared below; the base's are not modelled here).
	virtual ~StateMachine();
	TurretState *m_currentState;
	char m_pad08[0x3C - 0x08];
};

class TurretStateMachine : public StateMachine
{
public:
	virtual StateReturnType setState(StateID newStateID);	// slot 8
	virtual StateReturnType resetToDefaultState();		// slot 6
	virtual void clear();					// slot 5
	TurretAI *m_turretAI;
};

StateReturnType TurretStateMachine::setState(StateID newStateID)
{
	TurretState *current = m_currentState;
	StateID oldID = current ? current->m_id : INVALID_STATE_ID;
	StateReturnType tmp = StateMachine::setState(newStateID);
	TurretAI *turret = m_turretAI;
	if (turret && oldID != newStateID)
		turret->friend_notifyStateMachineChanged();
	return tmp;
}

// ?resetToDefaultState@TurretStateMachine@@QAE?AW4StateReturnType@@XZ @0x004D855B 29B
// Retail vtable slot 6 (offset 0x18) of vtable 0x008609C8, class TurretStateMachine.
// BFME1 donor TurretAI.cpp resetToDefaultState verbatim plus BFME2 deltas (owner at
// +0x3C, notify inlined as m_sleepUntil (+0x34) = frame). Single callee reset 0x004D7A75.
StateReturnType TurretStateMachine::resetToDefaultState()
{
	StateReturnType tmp = StateMachine::resetToDefaultState();
	TurretAI *turret = m_turretAI;
	if (turret)
		turret->friend_notifyStateMachineChanged();
	return tmp;
}

// ?clear@TurretStateMachine@@UAEXXZ @0x004D853F 28B
// Retail vtable slot 5 (offset 0x14) of vtable 0x008609C8, class TurretStateMachine.
// BFME1 donor TurretAI.cpp clear verbatim plus BFME2 deltas (owner +0x3C, notify).
// Single callee clear 0x004D72C5 rowed in StateMachineGoal.cpp.
void TurretStateMachine::clear()
{
	StateMachine::clear();
	TurretAI *turret = m_turretAI;
	if (turret)
		turret->friend_notifyStateMachineChanged();
}
