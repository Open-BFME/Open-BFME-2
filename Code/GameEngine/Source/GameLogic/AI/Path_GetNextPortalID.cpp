// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Unlock Path waypoint scan via head +0x4 and selected node +0x10 with
// optimized links +0x8 and waypoint guard +0x20. Evidence: Path layout
// matches PathCtor 0x00363DC8 and PathRva00363DF9 (head +4 sel +10
// nextOpt +8 waypoint +20); 0x7fffffff sentinel; neighbours use /O1.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class PathNode
{
public:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	int m_layer;
	bool m_canOptimize;
	int m_waypointID;
};

#include "../../../Include/GameLogic/PathfindPath.h"

int Path::GetNextPortalID()
{
	const int max = 0x7fffffff;
	PathNode *node;
	if (m_path == 0)
		return max;
	node = field_10;
	if (node == 0)
		return max;
	while (node != 0 && node->m_waypointID == max)
		node = node->m_nextOptimized;
	return node != 0 ? node->m_waypointID : max;
}
