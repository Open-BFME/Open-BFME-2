// cl: /DNDEBUG /MD
//
// ?getCurrentStateID@AIUpdateInterface@@QBEHXZ, retail 0x00262FC3, 40 bytes.
// AIUpdateInterface::getCurrentStateID inlined from AIStateMachine: machine at
// +0x30; primary State* at machine+0x50 else INVALID 999999 (0xF423F); if that
// id is INVALID fall back to State* at machine+0x04 else INVALID. State ID at
// +0x04. Donor BFME1 AIUpdateInterface_joinTeam.cpp getCurrentStateID plus
// WaypointGoalPathSize.cpp primary/fallback shape (BFME2 shifts +0x58/+0x1C to
// +0x50/+0x04); callers compare to AI_FOLLOW_PATH 6 and 0x43 then size a
// 12-byte vector. No direct callees.

struct AIState
{
	char m_pad00[4];
	int m_id;
};

#include "../../../../Include/GameLogic/AIStateMachineClass.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

int AIUpdateInterface::getCurrentStateID() const
{
	AIStateMachine *aIStateMachine = m_stateMachine;
	int id = aIStateMachine->m_temporaryState ? aIStateMachine->m_temporaryState->m_id : 0xF423F;
	if (id != 0xF423F)
		return id;
	return aIStateMachine->m_currentState ? aIStateMachine->m_currentState->m_id : 0xF423F;
}
