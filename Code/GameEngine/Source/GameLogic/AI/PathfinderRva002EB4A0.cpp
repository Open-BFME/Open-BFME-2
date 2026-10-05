// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ?rva002EB4A0 @0x002EB4A0 63B. Pathfinder helper
// converting two Coord3D to cells (rowed WorldToCell twice, shared stack
// args) then the pinned line-walker 0x002E8251. Mirrors rowed 0x002EB675
// with the positions swapped and a different walker. Identity unproven.
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
class Pathfinder
{
public:
	int rva002EB4A0(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, void *info);
private:
	int rva002E85AD(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, void *callbackInfo);
};
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
// ?rva002EB4A0@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAX@Z @0x002EB4A0 63B.
// Walker info type unproven, left as void*; pinned 0x002E85AD takes void*.
int Pathfinder::rva002EB4A0(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, void *info)
{
	ICoord2D tmp1;
	ICoord2D tmp2;
	return rva002E85AD(Rva002E7875WorldToCell(&tmp2, true, a), Rva002E7875WorldToCell(&tmp1, true, b), layer, info);
}
