// cl: /O1 /G7 /DNDEBUG /MD
//
// ?rva002F95B7@Pathfinder@@QAEH... retail 0x002F95B7 63B.
// Pathfinder helper that converts two world positions to cells via rowed
// Rva002E7875WorldToCell at 0x002E7875 then runs the private rowed
// iterateCellsAlongLine for Rva002F600CInfo at 0x002F6D22. Same this as the
// private walk (same Pathfinder), 4 stack args (ret 0x10), no EH. Caller
// 0x002FC95E. Flags copy PathfinderCellLineWalks neighbours (/O1 /G7).

struct ICoord2D
{
	int x;
	int y;
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

struct Rva002F600CInfo
{
	char m_pad[4];
};

struct Rva002E6F92Info
{
	char m_pad[4];
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	int rva002F95B7(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F600CInfo *info);
	int rva002EAE20(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002E6F92Info *info);
private:
	int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F600CInfo *callbackInfo);
	int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002E6F92Info *callbackInfo);
};

int Pathfinder::rva002F95B7(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F600CInfo *info)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, startPos), Rva002E7875WorldToCell(&tmpDest, true, destPos), layer, info);
}

// ?rva002EAE20@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002E6F92Info@@@Z retail 0x002EAE20 63B sibling of 0x002F95B7.
// Same WorldToCell then private iterate shape but for Rva002E6F92Info at
// 0x002E8348. Same flags and nested-return recipe.
int Pathfinder::rva002EAE20(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002E6F92Info *info)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, startPos), Rva002E7875WorldToCell(&tmpDest, true, destPos), layer, info);
}
