// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ED01EInfo@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ED01EInfo@@@Z @0x002F0CB7 63B Coord3D overload converts both points via WorldToCell 0x002E7875 then walks via 0x002EF016.
// Evidence: callees rowed WorldToCell PathfindShimWorldToCell.cpp and iterate PathfinderCellLineWalks.cpp; caller 0x002F1B56 in 52B unclaimed.
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

struct Rva002ED01EInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo);
private:
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo);
};

// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ED01EInfo@@@Z present-unmatched
Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo)
{
	ICoord2D destinationCell;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&destinationCell, true, destination);
	Rva002E7875WorldToCell(&startCell, true, start);
	return iterateCellsAlongLine(&startCell, &destinationCell, layer, callbackInfo);
}
