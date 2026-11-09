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
class State;
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/Common/StateMachine.h"
// StateMachine::isInAttackState's body as these slots inline it; the virtual's row is elsewhere.
static __forceinline Bool machineInAttackState(const StateMachine *machine)
{
	return machine->m_currentState ? machine->m_currentState->isAttack() : true;
}
class AIAttackAreaState : public State
{
public:
	virtual Bool isAttack() const;
private:
	StateMachine *m_attackMachine; // +0x20
};
class AIGuardState : public State
{
public:
	virtual Bool isAttack() const;
private:
	StateMachine *m_guardMachine; // +0x20
};
class AIAttackState : public State
{
public:
	virtual Bool isAttack() const;
private:
	unsigned char m_pad20[0x24 - 0x20];
	StateMachine *m_attackMachine; // +0x24
};


Bool AIAttackAreaState::isAttack() const
{
	return m_attackMachine ? machineInAttackState(m_attackMachine) : false;
}

Bool AIAttackState::isAttack() const
{
	return m_attackMachine ? machineInAttackState(m_attackMachine) : false;
}

//----------------------------------------------------------------------------------------------------------
Bool AIGuardState::isAttack() const
{
	if( m_guardMachine )
	{
		return machineInAttackState(m_guardMachine);
	}
	return true;
}

// AIFollowPathAsTeamState (vtable 0x00C121E8, name slot 0x00340D6A) keeps a
// sub-machine at +0x5C. Retail 0x00340E39, 37 bytes, its slot 9: true only
// while that machine exists and is not in an attack state.
class AIFollowPathAsTeamState : public State
{
public:
	virtual Bool rva00340E39() const;
private:
	unsigned char m_pad20[0x5C - 0x20];
	StateMachine *m_subMachine; // +0x5C
};
Bool AIFollowPathAsTeamState::rva00340E39() const
{
	if (m_subMachine && !machineInAttackState(m_subMachine))
		return true;
	return false;
}
