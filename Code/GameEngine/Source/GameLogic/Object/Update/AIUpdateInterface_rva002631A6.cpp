// cl: /DNDEBUG /MD
//
// ?rva002631A6@AIUpdateInterface@@MAEXMH@Z, retail 0x002631A6, 103 bytes.
// Vtable slot 87 of DeployStyle Siege Transport Wander HordeWorker AIUpdates:
// if m_object+0x04+0x53C float >= global 0x00BC6254 return else build
// Coord3D from float arg then clear via slot 0x14 then StateMachine
// setGoalPosition with FLT_MAX 0x00BBB8E0 then store int at +0x48
// then setState 0x48 via slot 0x20. Callees rowed 0x004D745C.


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"
#include "../object.h"
#include "../../../../Include/Common/ThingTemplate.h"




#define Gbl00BC6254 360.0f
#define Gbl00BBB8E0 3.4028235e+38f


void AIUpdateInterface::rva002631A6(float f, int b)
{
	if (m_object->m_template->m_firingArc >= Gbl00BC6254)
		return;
	Coord3D pos;
	pos.x = f;
	pos.y = f;
	pos.z = f;
	m_stateMachine->clear();
	m_stateMachine->setGoalPosition(&pos, Gbl00BBB8E0);
	m_lastCommandSource = static_cast<CommandSourceType>(b);
	m_stateMachine->setState(0x48);
}
