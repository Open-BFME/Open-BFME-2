// cl: /O1 /G7 /DNDEBUG /MD
// ?rva002EED41@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002E93A7Info@@@Z @0x002EED41 63B
// World-to-cell line-walk wrapper: converts two world positions via rowed
// 0x002E7875 WorldToCell then calls rowed 0x002EB6B4 iterateCellsAlongLine.
// Evidence: two calls to 0x002E7875 with center=1 then call to 0x002EB6B4;
// ecx preserved as Pathfinder this; ret 0x10 = 4 stack args; caller 0x002EF67E.
typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Rva002E93A7Info;

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class Pathfinder
{
public:
	int rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld, PathfindLayerEnum layer, Rva002E93A7Info *info);
private:
	int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002E93A7Info *callbackInfo);
};

int Pathfinder::rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld, PathfindLayerEnum layer, Rva002E93A7Info *info)
{
	ICoord2D endCell;
	ICoord2D startCell;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&startCell, true, startWorld), Rva002E7875WorldToCell(&endCell, true, endWorld), layer, info);
}
