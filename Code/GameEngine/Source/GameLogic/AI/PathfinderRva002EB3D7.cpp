// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EB3D7 @0x002EB3D7 63B. Pathfinder helper
// converting two Coord3D to cells (rowed WorldToCell twice, shared stack
// args) then the pinned rowed line-walk 0x002E8448. Mirrors rowed 0x002EB675
// with rowed iterateCellsAlongLine. Identity unproven.
typedef int Int;
typedef float Real;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};
struct Rva002E7B29Info
{
	int m_00;
};
#include "../../../Include/GameLogic/AIPathfind.h"
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
// ?rva002EB3D7@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002E7B29Info@@@Z @0x002EB3D7 63B.
int Pathfinder::rva002EB3D7(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, Rva002E7B29Info *info)
{
	ICoord2D tmp1;
	ICoord2D tmp2;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmp2, true, a), Rva002E7875WorldToCell(&tmp1, true, b), layer, info);
}
