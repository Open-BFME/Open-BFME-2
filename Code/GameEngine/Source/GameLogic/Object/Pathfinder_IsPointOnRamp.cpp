// cl: /DNDEBUG /MD /EHsc
// ?IsPointOnRamp@Pathfinder@@QAE_NPBUCoord3D@@@Z @0x002E757D 38B
// Evidence: chain from Bridge::isPointOnBridge 0x0027EEAD; walks Bridge list head +0x5C next +0x04; callers 0x002803A3 0x002EF6C5.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/GameLogic/BridgeClass.h"

#include "../../../Include/GameLogic/AIPathfind.h"

bool Pathfinder::IsPointOnRamp(const Coord3D *p)
{
	for (Bridge *bridge = m_field5C; bridge; bridge = bridge->getNext()) {
		if (bridge->isPointOnBridge(p))
			return true;
	}
	return false;
}
