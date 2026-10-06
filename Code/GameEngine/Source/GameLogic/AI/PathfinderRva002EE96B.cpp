// cl: /DNDEBUG /MD /EHsc
// ?rva002EE96B@Pathfinder@@QAEHPAUCoord3D@@PBU2@@Z 0x002EE96B 53B Pathfinder helper calling rva002EB675 then copying back x y on success. Evidence: rowed rva002EB675 0x002EB675 plus SSE movss copy callers 0x00261A47 0x002CBA3A unblocks 0x002619C1 0x002CB9BD.
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
	LAYER_INVALID = 0,
	LAYER_ONE = 1
};
class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};
struct Rva002E7ED6Info
{
	Real m_x;
	Real m_y;
	Real m_z;
	Int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY);
};
class Pathfinder
{
public:
	int rva002EE96B(Coord3D *a, const Coord3D *b);
	int rva002EB675(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, Rva002E7ED6Info *info);
};
int Pathfinder::rva002EE96B(Coord3D *a, const Coord3D *b)
{
	Rva002E7ED6Info info;
	int ret = rva002EB675(a, b, LAYER_ONE, &info);
	if (ret != 0)
	{
		a->x = info.m_x;
		a->y = info.m_y;
	}
	return ret;
}
