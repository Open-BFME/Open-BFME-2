// cl: /O1 /G7 /DNDEBUG /MD
// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ED15AInfo@@@Z @0x002F0CF6 63B Coord3D overload converts both points via WorldToCell 0x002E7875 then walks via 0x002EF116.
// Evidence: callees rowed WorldToCell PathfindShimWorldToCell.cpp and iterate PathfinderCellLineWalks.cpp; caller 0x002F1BC6 in 51B unclaimed.
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

struct Rva002ED15AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

struct Rva002ECE6AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

struct Rva002ED01EInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

struct Rva002F1BD5Info
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

struct Rva002F18D4Info
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED15AInfo *callbackInfo);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F1BD5Info *callbackInfo);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F18D4Info *callbackInfo);
private:
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ED15AInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F1BD5Info *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F18D4Info *callbackInfo);
};

Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED15AInfo *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}

Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}

Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}

Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F1BD5Info *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}

Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F18D4Info *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}
