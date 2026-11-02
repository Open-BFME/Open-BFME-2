// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?SetLastNodePortal@Path@@QAEXH@Z @0x00363B24 (17B).
// Leaf Path tail waypoint setter via tail +0x8 and waypoint +0x20.
// Evidence: Path layout from PathCtor 0x00363DC8 and PathRva00363DF9
// (tail +8 waypoint +20); callers need tail waypoint set; /O1 int-only.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../Include/GameLogic/PathfindPath.h"

void Path::SetLastNodePortal(int id)
{
	PathNode *tail = m_pathTail;
	if (tail == 0) {
		return;
	}
	tail->m_portalID = id;
}
