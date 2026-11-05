// cl: /DNDEBUG /MD
//
// ?rva002632B3@AIUpdateInterface@@QBEHXZ, retail 0x002632B3, 20 bytes.
// Leaf int beside AIUpdateInterface tail: machine at +0x30 null-safe
// then non-zero dword at machine+0x50 means 1 else 0. Caller at 0x45AA48.
// No direct callees.

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

int AIUpdateInterface::rva002632B3() const
{
    AIStateMachine *machine = m_stateMachine;
    if (machine && machine->m_temporaryState)
        return 1;
    return 0;
}
