// cl: /O1 /DNDEBUG /MD
// ?rva002EB675@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002E7ED6Info@@@Z 0x002EB675 63B Pathfinder helper converting two Coord3D to cells then iterateCellsAlongLine 0x002E8A47. Evidence: rowed WorldToCell 0x002E7875 twice plus rowed walk 0x002E8A47 caller 0x002EE97F unlocks 0x002EE96B.
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
class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};
struct Rva002E7ED6Info
{
	Int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY);
};
class Pathfinder
{
public:
	int rva002EB675(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, Rva002E7ED6Info *info);
private:
	int iterateCellsAlongLine(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002E7ED6Info *callbackInfo);
};
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
int Pathfinder::rva002EB675(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, Rva002E7ED6Info *info)
{
	ICoord2D tmp1;
	ICoord2D tmp2;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmp2, true, a), Rva002E7875WorldToCell(&tmp1, true, b), layer, info);
}
