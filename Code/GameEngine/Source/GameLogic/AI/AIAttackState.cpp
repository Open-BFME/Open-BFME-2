// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ??0AIAttackState@@QAE@PAVStateMachine@@_N11PAVAttackExitConditionsInterface@@@Z
// retail 0x0034B0DD, 115 bytes.
// Donor: reference/open-bfme-1 game/GameEngine/Source/GameLogic/AI/AIAttackStateCtorThunk.cpp
// (Open-BFME-1 revision, ZH AIStates.cpp). BFME2 deltas (target evidence):
// the State base takes the NameKeyType hash 0xE7D2F1FF instead of an AsciiString
// name, and BFME2's State is 0x20 bytes so the NotifyWeaponFiredInterface
// sub-vtable lands at +0x20 (the dead 0xc078dc store) and AIAttackState's
// members start at +0x24. Every field offset and initializer matches retail,
// including the Coord3D zero at +0x30..+0x38 and m_attackMachineType=3 at +0x4C.
#include "ascii_string.h"

class StateMachine;
class AttackExitConditionsInterface;
class Team;

#include "../../../Include/Common/StateMachine.h"

#include "../../../Include/GameLogic/AIAttackState.h"

// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"


AIAttackState::AIAttackState(StateMachine *machine, bool follow, bool attackingObject, bool forceAttacking,
	AttackExitConditionsInterface *attackParameters) :
	State(machine, 0xE7D2F1FFu),
	m_attackMachine(0),
	m_attackParameters(attackParameters),
	m_victimTeam(0),
	m_lockedWeaponOnEnter(),
	m_follow(follow),
	m_isAttackingObject(attackingObject),
	m_isForceAttacking(forceAttacking),
	m_bfmeAttackState48(0),
	m_bfmeAttackState4C(false),
	m_bfmeAttackState4D(false),
	m_attackMachineType(3)
{
	m_originalVictimPos.zero();
}
