// cl: /DNDEBUG /MD
//
// ?rva002632C7@AIUpdateInterface@@QBEHXZ, retail 0x002632C7, 26 bytes.
// Leaf int beside AIUpdateInterface tail: machine at +0x30 null-safe
// then field50 non-zero and field54 == -1 means 1 else 0 shares
// zero getter at 0x002632DE. Callers at 295F69 337193 352C56 4C05EB.
// No direct callees.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

int AIUpdateInterface::rva002632C7() const
{
    AIStateMachine *machine = m_stateMachine;
    if (machine && machine->m_temporaryState && machine->m_temporaryStateFramEnd == -1)
        return 1;
    return 0;
}
