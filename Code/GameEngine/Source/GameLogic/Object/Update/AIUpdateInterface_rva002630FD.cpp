// cl: /DNDEBUG /MD
//
// ?rva002630FD@AIUpdateInterface@@MAEXH@Z, retail 0x002630FD, 54 bytes.
// Vtable slot 84 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// if state machine at +0x30 current id is 0x2D skip else clear via slot 0x14
// store int at +0x48 then setState 0x2D via slot 0x20. No direct callees.





#include "../../../../Include/GameLogic/AIStateMachineClass.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva002630FD(int val)
{
	if (m_stateMachine->getCurrentStateID() == 0x2D)
		return;
	m_stateMachine->clear();
	m_lastCommandSource = static_cast<CommandSourceType>(val);
	m_stateMachine->setState(0x2D);
}
