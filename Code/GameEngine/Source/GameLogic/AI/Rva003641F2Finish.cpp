// cl: /GX /DNDEBUG /MD
//
// ?rva003641F2@Path@@QBE?AUCoord3D@@XZ @0x003641F2 (124B).
// Path last-valid-waypoint position, by-value Coord3D return (BFME1 donor
// PathGetLastValidWaypointPosition, 0x003FE330 in lotrbfme.exe).  The BFME2
// ABI is the hidden-return form: this+0x10 scan start, this+0x4 head, node
// +0x4 previous, +0xc position, +0x20 waypoint id, TerrainLogic slot +0x8c.
// Retail prologue is push ebp / mov ebp,esp / sub esp,0x10 / and [ebp-4],0:
// an RVO guard for the returned Coord3D, whose destructor is declared but not
// defined (BV11 /GX trial reproduces all 124 bytes exactly).  The zero
// fallback is the POD-shaped local so no trivial-local destructor call is
// emitted; the guard itself is the only zeroed 4-byte frame slot.

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_EXTERN_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "../../../Include/GameLogic/PathNode.h"

class Waypoint;

#include "../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/PathfindPath.h"

struct Coord3DPod { float x, y, z; };

Coord3D Path::rva003641F2(void) const
{
	PathNode *sel = field_10;
	Waypoint *waypoint = 0;
	while (sel != 0) {
		int wp = sel->m_portalID;
		if (wp == 0x7fffffff)
			break;
		waypoint = TheTerrainLogic->getWaypointByID(wp);
		if (waypoint != 0)
			break;
		sel = sel->m_prev;
	}
	const Coord3D *src;
	Coord3DPod zero;
	if (sel != 0)
		src = &sel->m_pos;
	else if (m_path != 0)
		src = &m_path->m_pos;
	else {
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		src = (const Coord3D *)&zero;
	}
	return *src;
}
