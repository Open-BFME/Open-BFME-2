// cl: /DNDEBUG /MD
// ?IsGroundLineOnly@Pathfinder@@QAE_NPBUCoord3D@@0@Z @0x002ED219 29B Pathfinder wrapper: calls rowed rva002EADE1 with layer 1 and temp info then returns not. Evidence: rowed callee 0x002EADE1, callers 0x0027D276 0x00364551 0x004B0FEB, neighbours share flags.
typedef int Int;
typedef float Real;
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
struct Rva002E7ED6Info
{
	int m_00;
};
class Pathfinder
{
public:
	bool IsGroundLineOnly(const Coord3D *a, const Coord3D *b);
	int rva002EADE1(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, Rva002E7ED6Info *info);
};
bool Pathfinder::IsGroundLineOnly(const Coord3D *a, const Coord3D *b)
{
	Rva002E7ED6Info info;
	return !rva002EADE1(a, b, LAYER_ONE, &info);
}
