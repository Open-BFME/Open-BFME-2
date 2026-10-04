// cl: /O1 /DNDEBUG /MD
//
// isAttack overrides of the attack states (State vtable slot 8, after
// onEnter/onExit/update at 4-6 and isIdle at 7):
//  - AIAttackAreaState::isAttack, retail 0x003422EF (29 bytes): slot 8 of
//    vtable 0x00C11900 (name getter AIAttackAreaState). Zero Hour's
//    header-inline body, kept out of line by retail: the attack sub-machine's isInAttackState (a machine without a
//    current state counts as attacking), FALSE without a sub-machine.
//    m_attackMachine +0x20.
//  - AIAttackState::isAttack, retail 0x0034141F (29 bytes): slot 8 of
//    vtable 0x00C13B78 (name getter AIAttackState). Zero Hour returns TRUE;
//    BFME 2 asks its attack machine (+0x24) the same way.
//  - AIGuardState::isAttack, retail 0x00341D81 (26 bytes): slot 8 of vtable
//    0x00C11740 (name getter AIGuardState). Zero Hour asks the guard
//    sub-machine (+0x20) and returns FALSE without one; BFME 2 returns TRUE.
// Ported from Zero Hour's GameEngine/Include/GameLogic/AIStateMachine.h,
// GameLogic/AI/AIStates.cpp and
// Common/StateMachine.h (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference); StateMachine's current state is
// at +0x04.
typedef bool Bool;
#define TRUE true
#define FALSE false
class State;
class StateMachine
{
public:
	inline Bool isInAttackState() const;
private:
	unsigned char m_pad00[0x04];
	State *m_currentState; // +0x04
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void onEnter();
	virtual void onExit();
	virtual void update();
	virtual Bool isIdle() const;
	virtual Bool isAttack() const;
};
// ?StateMachine::isInAttackState absent-from-retail
inline Bool StateMachine::isInAttackState() const
{
	return m_currentState ? m_currentState->isAttack() : true; // stateless things are considered 'idle'
}
class AIAttackAreaState : public State
{
public:
	virtual Bool isAttack() const;
private:
	unsigned char m_pad04[0x20 - 0x04];
	StateMachine *m_attackMachine; // +0x20
};
class AIGuardState : public State
{
public:
	virtual Bool isAttack() const;
private:
	unsigned char m_pad04[0x20 - 0x04];
	StateMachine *m_guardMachine; // +0x20
};
class AIAttackState : public State
{
public:
	virtual Bool isAttack() const;
private:
	unsigned char m_pad04[0x24 - 0x04];
	StateMachine *m_attackMachine; // +0x24
};

Bool AIAttackAreaState::isAttack() const
{
	return m_attackMachine ? m_attackMachine->isInAttackState() : FALSE;
}

Bool AIAttackState::isAttack() const
{
	return m_attackMachine ? m_attackMachine->isInAttackState() : FALSE;
}

//----------------------------------------------------------------------------------------------------------
Bool AIGuardState::isAttack() const
{
	if( m_guardMachine )
	{
		return m_guardMachine->isInAttackState();
	}
	return TRUE;
}
