// cl: /DNDEBUG /MD
//
// ?rva00263298@AIUpdateInterface@@QAEXXZ, retail 0x00263298, 27 bytes.
// AIUpdateInterface notifier: machine at +0x30, state ptr at +0x50 with id
// at +4, gate on +0x54 == -1, then rowed AIStateMachine::setTemporaryState(id, -2).
// Evidence: neighbours rva0026320D/rva002632B3 share +0x30 machine and
// +0x50 state layout; caller 0x004DCECE.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

void AIUpdateInterface::rva00263298()
{
    AIStateMachine *machine = m_stateMachine;
    State *state = machine->m_temporaryState;
    if (!state)
        return;
    if (machine->m_temporaryStateFramEnd != -1)
        return;
    machine->setTemporaryState(state->m_id, -2);
}
