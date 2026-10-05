// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ECE6AInfo@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ECE6AInfo@@@Z @0x002F0C78 63B Coord3D overload converts both points via WorldToCell 0x002E7875 then walks via 0x002EEF16.
// Evidence: callees rowed WorldToCell PathfindShimWorldToCell.cpp and iterate PathfinderCellLineWalks.cpp; callers 0x002F1B23 and 0x002F1B93 in unclaimed users.
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Rva002ECE6AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo);
private:
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo);
};

// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ECE6AInfo@@@Z present-unmatched
Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo)
{
	ICoord2D destinationCell;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&destinationCell, true, destination);
	Rva002E7875WorldToCell(&startCell, true, start);
	return iterateCellsAlongLine(&startCell, &destinationCell, layer, callbackInfo);
}
