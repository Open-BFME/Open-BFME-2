// cl: /O1 /MD
// ?rva002E8BF8@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@PBUCoord3D@@@Z @0x002E8BF8 43B: world-pos to cell lookup via clamp wrapper then getCell; callees 0x002E7917 and 0x002E6D62 both rowed; callers 23 unclaimed wrappers
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
	PF_LAYER_0 = 0
};

class PathfindCell
{
public:
	char _00[4];
	void *m_04;
};

class Pathfinder
{
public:
	void Rva002E7917(ICoord2D *out, bool center, const Coord3D *pos);
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
};

PathfindCell *Pathfinder::rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos)
{
	ICoord2D cell;
	Rva002E7917(&cell, true, pos);
	return getCell(layer, cell.x, cell.y);
}
