// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /O1 /G7 /arch:SSE
// AIAttackState::~AIAttackState, retail 0x0034B178 (113 bytes, EH; the opaque
// pin ??1Rva0034B178 stays). Destructor-only view of the class
// Rva0034B0DDFinish.cpp builds (State base with its dtor out of line at
// 0x0049B47C, NotifyWeaponFiredInterface at +0x20, attack machine at +0x24,
// locked weapon name at +0x3C). ZH AIAttackState::~AIAttackState halts and
// deleteInstance()s the attack machine; retail reloads the pointer after the
// halt() call (vslot 15) and calls the machine's slot 0 with flag 0, handing
// its return to operator delete, so slot 0 is modelled as destroy(flag).
#include "ascii_string.h"

#include <new>

#include "../../../Include/Common/StateMachineClass.h"
class AttackExitConditionsInterface;
class Team;
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/GameLogic/AIAttackState.h"

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
// Slot 0 of the machine, called directly: the scalar deleting destructor with flag 0.
class StateMachineDeleteSlot
{
public:
	virtual void *destroy(int flag);
};

__declspec(noinline) inline AIAttackState::~AIAttackState()
{
	if (m_attackMachine)
	{
		m_attackMachine->halt();
		operator delete(m_attackMachine ? ((StateMachineDeleteSlot *)m_attackMachine)->destroy(0) : 0);
		m_attackMachine = 0;
	}
}

// ?bfmeAnchorAIAttackStateDtor absent-from-retail
void bfmeAnchorAIAttackStateDtor(AIAttackState *aIAttackState)
{
	aIAttackState->AIAttackState::~AIAttackState();
}
