// cl: /DNDEBUG /MD /EHsc
// Pathfinder::SetDebugPathPosition (WorldBuilder name, pathfinder.cpp lines 5116..5120: copy the position into +0x4C).
// was ?rva002E74B5@Rva002E74B5@@QAEXPBUCoord3D@@@Z @0x002E74B5 17B
// Evidence: unlocks 0x00363930; copies 12B to +0x4C; caller passes Coord3D floats.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/GameLogic/AIPathfind.h"

void Pathfinder::SetDebugPathPosition(const Coord3D *pos)
{
	m_field4C = *pos;
}
