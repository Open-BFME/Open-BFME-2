// cl: /DNDEBUG /MD
//
// ?rva0026316B@AIUpdateInterface@@MAEXPAXH@Z, retail 0x0026316B, 59 bytes.
// Vtable slot 86 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// clear via slot 0x14 then slot 0x38 with obj then Turret setGoalPosition
// with obj+0x38 then store int at +0x48 then setState 0x46 via slot 0x20.
// Callees rowed: Turret setGoalPosition 0x00262224.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

struct MiniArg1
{
	char m_pad00[0x38];
	Coord3D m_pos;
};



void AIUpdateInterface::rva0026316B(void *a, int b)
{
	MiniArg1 *miniArg1 = (MiniArg1 *)a;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(static_cast<const Object *>(a));
	m_stateMachine->setGoalPosition(&miniArg1->m_pos);
	m_lastCommandSource = static_cast<CommandSourceType>(b);
	m_stateMachine->setState(0x46);
}
