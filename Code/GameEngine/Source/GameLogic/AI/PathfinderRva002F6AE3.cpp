// cl: /O1 /G7 /DNDEBUG /MD
//
// ?rva002F6AE3@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002F3F7DInfo@@@Z @0x002F6AE3 63B.
// Pathfinder helper converting two Coord3D to cells via rowed Rva002E7875WorldToCell
// at 0x002E7875 then running the private rowed iterateCellsAlongLine for
// Rva002F3F7DInfo at 0x002F4391. Evidence: callees rowed WorldToCell
// PathfindShimWorldToCell.cpp twice plus rowed walk PathfinderCellLineWalks.cpp;
// caller 0x002F714B in 91B unclaimed; sits between 0x002F69E3 and 0x002F6B22 gap.

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

struct Rva002F3F7DInfo
{
	char m_pad[4];
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	int rva002F6AE3(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F3F7DInfo *info);
private:
	int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002F3F7DInfo *callbackInfo);
};

int Pathfinder::rva002F6AE3(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F3F7DInfo *info)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, startPos), Rva002E7875WorldToCell(&tmpDest, true, destPos), layer, info);
}
