// cl: /DNDEBUG /MD
//
// ?friend_setGoalObject@AIUpdateInterface@@QAEXPAVObject@@@Z, retail 0x00262B0F, 42 bytes.
// Retail42B262B0F..262B39 RET4: machine30, lock38, virtual goal setter
// slot14 (+38), restoring the prior lock. WB E46FC0 has the same
// sequence and "Friend_setGlobalObject re-locking" diagnostic. ZH
// AIUpdate.cpp friend_setGoalObject has this exact diagnostic and
// behavior; the spelling is donor-carried. Native callers34BB5B,
// 26D3FB and3497E6 pass their Object victim without integer conversion.

class Object;

#include "../../../../Include/Common/StateMachineClass.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

void AIUpdateInterface::friend_setGoalObject(Object *obj)
{
	bool wasLocked = m_stateMachine->m_locked;
	m_stateMachine->m_locked = false;
	m_stateMachine->setGoalObject(obj);
	if (wasLocked)
		m_stateMachine->m_locked = true;
}
