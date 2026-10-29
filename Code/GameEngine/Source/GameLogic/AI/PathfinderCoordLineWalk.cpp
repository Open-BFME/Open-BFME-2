// cl: /DNDEBUG /MD
// ?iterateCellsAlongLine@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002ED15AInfo@@@Z @0x002F0CF6 63B Coord3D overload converts both points via WorldToCell 0x002E7875 then walks via 0x002EF116.
// Evidence: callees rowed WorldToCell PathfindShimWorldToCell.cpp and iterate PathfinderCellLineWalks.cpp; caller 0x002F1BC6 in 51B unclaimed.
typedef int Int;
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Rva002ED15AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
	// 0x002ED0CC builds a 0x5C-byte query here (writes up to [ebx+0x58], ret 0xc).
	Rva002ED15AInfo *init(void *a, void *b, void *c);
	char storage[0x5B];
};

class Object;
class Pathfinder;

struct Rva002ECE6AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
	// 0x002ECD63 builds a 0x60-byte query here (writes up to [ebx+0x5D], ret 0x1c).
	Rva002ECE6AInfo(Pathfinder *pathfinder, const Object *obj, Int surfaces, Bool a, Bool b, Bool c, Bool d);
	char storage[0x60];
};

struct Rva002ED01EInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
	// 0x002E931F builds a 0x58-byte query here (writes up to [ebx+0x54], ret 0xc).
	Rva002ED01EInfo *init(void *a, void *b, void *c);
	char storage[0x57];
};

struct Rva002F1BD5Info
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

class PathfindCell;
struct Rva002F18D4Info
{
public:
	int cellCallback(void *previousCell, void *currentCell, int cellX, int cellY);
	int cellCallback(PathfindCell*,PathfindCell*,int,int);
	Object *m_obj; // +0x00
	Object *m_other; // +0x04
	PathfindCell *m_cell; // +0x08
	int m_skip; // +0x0C
	bool m_hitLayer; // +0x10
	char m_pad11[0x3];
	int m_layerCount; // +0x14
	int m_runLength; // +0x18
};

struct Coord3D;
struct Rva002F4D8BInfo
{
public:
	int cellCallback(void *previousCell, void *currentCell, int cellX, int cellY);
	int cellCallback(PathfindCell *,PathfindCell *,int,int);
	Pathfinder *pathfinder; // +0x00
	Object *object; // +0x04
	void *word08; // +0x08
	Coord3D position; // +0x0C
	int word18; // +0x18
	Bool flag1C; // +0x1C
	Bool flag1D; // +0x1D
	Bool flag1E; // +0x1E
	Bool flag1F; // +0x1F
	Bool flag20; // +0x20
	char m_pad21[0x3];
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
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
	// Line-query wrappers at 0x002F1AF4/32/66/A2: build the callback query via
	// the pinned init above, walk it, bool-convert the hit. Names from the
	// WorldBuilder debug build's asserts (pathfinder.cpp 3706/3713/3720/3727,
	// the same order as these addresses); each calls the same walk overload
	// and pops the same argument bytes as its WB twin.
	Int IsLinePassable(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c, Int a20, Int a24);
	Bool IsLineBlocked(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18);
	Int IsLinePassableForOptimize(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c);
	Bool IsHordeMeleeLinePassable(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18);
private:
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ED15AInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ECE6AInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002ED01EInfo *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F1BD5Info *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F18D4Info *callbackInfo);
	Int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
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

// 0x002F9578 63B: the same Coord3D overload over the cell walk 0x002F6C22,
// called by Pathfinder::CanApproachToTarget (0x002FA2DC) with its functor.
Int Pathfinder::iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, start), Rva002E7875WorldToCell(&tmpDest, true, destination), layer, callbackInfo);
}

// 0x002F1AF4 62B: 8-arg wrapper, helper1 0x002ECD63 with trailing imm 0, !logic.
Int Pathfinder::IsLinePassable(void *pathObject, void *acceptableSurfaces, PathfindLayerEnum lineLayer, const Coord3D *startWorld, const Coord3D *endWorld, void *a1c, Int a20, Int a24)
{
	return !iterateCellsAlongLine(startWorld, endWorld, lineLayer, &Rva002ECE6AInfo(this, (const Object *)pathObject, (Int)acceptableSurfaces, *(Bool *)&a1c, *(Bool *)&a20, *(Bool *)&a24, false));
}

// 0x002F1B32 52B: 5-arg wrapper, helper1 0x002E931F, !!logic.
Bool Pathfinder::IsLineBlocked(void *pathObject, void *acceptableSurfaces, PathfindLayerEnum lineLayer, const Coord3D *startWorld, const Coord3D *endWorld)
{
	Rva002ED01EInfo info;
	return iterateCellsAlongLine(startWorld, endWorld, lineLayer, info.init(this, pathObject, acceptableSurfaces)) != 0;
}

// 0x002F1B66 60B: 6-arg wrapper, helper1 0x002ECD63 with imms 0,1,1, !logic.
Int Pathfinder::IsLinePassableForOptimize(void *pathObject, void *acceptableSurfaces, PathfindLayerEnum lineLayer, const Coord3D *startWorld, const Coord3D *endWorld, void *a1c)
{
	return !iterateCellsAlongLine(startWorld, endWorld, lineLayer, &Rva002ECE6AInfo(this, (const Object *)pathObject, (Int)acceptableSurfaces, *(Bool *)&a1c, false, true, true));
}

// 0x002F1BA2 51B: 5-arg wrapper, helper1 0x002ED0CC, !logic.
Bool Pathfinder::IsHordeMeleeLinePassable(void *pathObject, void *acceptableSurfaces, PathfindLayerEnum lineLayer, const Coord3D *startWorld, const Coord3D *endWorld)
{
	Rva002ED15AInfo info;
	return !iterateCellsAlongLine(startWorld, endWorld, lineLayer, info.init(this, pathObject, acceptableSurfaces));
}
