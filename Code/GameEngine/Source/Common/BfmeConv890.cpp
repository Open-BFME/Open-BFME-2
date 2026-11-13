// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
#include "../../Include/GameLogic/AIAttackState.h"
#include "../../Include/Common/StateMachineClass.h"

void AIAttackState::bfmeGoFAC(void *goal)
{
    m_machine->setGoalObject((const Object *)goal);
    if (m_attackMachine)
        m_attackMachine->setGoalObject((const Object *)goal);
}
