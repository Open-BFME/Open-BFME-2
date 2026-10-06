// cl: /DNDEBUG /MD
// ?rva001E3647Pos@Pathfinder@@QAEPAXHPBUCoord3D@@@Z @0x001E3647 50B: Pathfinder pos-to-cell via bounded WorldToCell 0x002E7964 then getCell 0x002E6D62.
// Evidence: calls pin-only 0x002E7964 plus rowed getCell 0x002E6D62 plus 30 callers including 0x001E4469 plus LINK 15 files 1664B plus prev 0x001E3624 next 0x001E3679.
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

class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};

class Rva002E7964
{
public:
	void rva002E7964(ICoord2D *out, unsigned char center, const Coord3D *pos);
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int cellX, int cellY);
	void *rva001E3647Pos(int layer, const Coord3D *pos);
};

void *Pathfinder::rva001E3647Pos(int layer, const Coord3D *pos)
{
	ICoord2D tmp;
	((Rva002E7964 *)this)->rva002E7964(&tmp, 1, pos);
	void *cell = 0;
	if (tmp.x >= 0)
		cell = getCell((PathfindLayerEnum)layer, tmp.x, tmp.y);
	return cell;
}
