// cl: /DNDEBUG /MD
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
	// 0x002ED0CC builds a 0x5C-byte query here (writes up to [ebx+0x58], ret 0xc).
	Rva002ED15AInfo *init(void *a, void *b, void *c);
	char storage[0x5B];
};

struct Rva002ECE6AInfo
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
	// 0x002ECD63 builds a 0x60-byte query here (writes up to [ebx+0x5D], ret 0x1c).
	Rva002ECE6AInfo *init(void *a, void *b, void *c, void *d, Int e, Int f, Int g);
	char storage[0x5F];
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

struct Rva002F18D4Info
{
	Int cellCallback(void *previousCell, void *currentCell, Int cellX, Int cellY);
};

struct Rva002F4D8BInfo
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
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
	// Unproven-identity line-query wrappers at 0x002F1AF4/32/66/A2: build the
	// callback query via the pinned init above, walk it, bool-convert the hit.
	Int Rva002F1AF4(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c, Int a20, Int a24);
	Int Rva002F1B32(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18);
	Int Rva002F1B66(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c);
	Int Rva002F1BA2(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18);
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
Int Pathfinder::Rva002F1AF4(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c, Int a20, Int a24)
{
	Rva002ECE6AInfo info;
	return !iterateCellsAlongLine(a14, a18, a10, info.init(this, a8, ac, a1c, a20, a24, 0));
}

// 0x002F1B32 52B: 5-arg wrapper, helper1 0x002E931F, !!logic.
Int Pathfinder::Rva002F1B32(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18)
{
	Rva002ED01EInfo info;
	return iterateCellsAlongLine(a14, a18, a10, info.init(this, a8, ac)) != 0;
}

// 0x002F1B66 60B: 6-arg wrapper, helper1 0x002ECD63 with imms 0,1,1, !logic.
Int Pathfinder::Rva002F1B66(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18, void *a1c)
{
	Rva002ECE6AInfo info;
	return !iterateCellsAlongLine(a14, a18, a10, info.init(this, a8, ac, a1c, 0, 1, 1));
}

// 0x002F1BA2 51B: 5-arg wrapper, helper1 0x002ED0CC, !logic.
Int Pathfinder::Rva002F1BA2(void *a8, void *ac, PathfindLayerEnum a10, const Coord3D *a14, const Coord3D *a18)
{
	Rva002ED15AInfo info;
	return !iterateCellsAlongLine(a14, a18, a10, info.init(this, a8, ac));
}
