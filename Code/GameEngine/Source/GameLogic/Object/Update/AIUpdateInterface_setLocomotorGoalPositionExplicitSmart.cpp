// cl: /O1 /DNDEBUG /MD
// ?setLocomotorGoalPositionExplicitSmart@AIUpdateInterface@@UAEXABUCoord3D@@@Z @0x00262C53 72B. Slot 133 of 8
// AIUpdate vtables: if (m_1FC != 4) delete Path at +0x140 via rowed
// ??1Path@@QAE@XZ plus rowed ??3@YAXPAX@Z and null it; set m_1FC=4; copy 12B
// Coord3D arg to +0x200 via 3x movsd. Prev setLocomotorGoalPositionExplicit.
// Identity: WorldBuilder's AIUpdate.cpp:4256-4258 defines
// AIUpdateInterface::setLocomotorGoalPositionExplicitSmart with exactly this
// body (m_locomotorGoalType +0x1FC != 4 -> delete the +0x140 Path; type 4;
// copy the position to +0x200).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Include/GameLogic/PathfindPath.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
void AIUpdateInterface::setLocomotorGoalPositionExplicitSmart(const Coord3D &newPos)
{
	if (m_field1FC != 4) {
		delete m_path;
		m_path = 0;
	}
	m_field1FC = 4;
	m_field200 = newPos;
}
