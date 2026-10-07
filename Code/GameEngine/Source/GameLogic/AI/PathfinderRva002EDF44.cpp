// cl: /O1 /G7 /DNDEBUG /MD
// Dump lane range 13: ?Rva002EDF44 @0x002EDF44 52B and ?Rva002EDF7C @0x002EDF7C
// 65B. Consecutive Pathfinder cell-resolution wrappers: resolve the object's
// +0x38 position to a cell via pinned 0x002EBC14, read the rowed Object flag
// getter 0x0028B511 as the layer, and answer the rowed Pathfinder::getCell
// 0x002E6D62 cell. EDF7C additionally copies the cell back to its out param.
// Identities unproven (address-derived names, minimal +0x38 view).
typedef int Int;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct ObjWithPos
{
	char m_pad[0x38];
	Coord3D pos;
};

class Object
{
public:
	Int rva0028B511() const;
};

class PathfindCell
{
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);
	PathfindCell *Rva002EDF44(ObjWithPos *obj);
	PathfindCell *Rva002EDF7C(ObjWithPos *obj, ICoord2D *out);
};

ICoord2D *__cdecl rva002EBC14(ICoord2D *out, void *obj, const Coord3D *pos);

PathfindCell *Pathfinder::Rva002EDF44(ObjWithPos *obj)
{
	ICoord2D tmp;
	rva002EBC14(&tmp, obj, &obj->pos);
	return getCell((PathfindLayerEnum)((Object *)obj)->rva0028B511(), tmp.x, tmp.y);
}

PathfindCell *Pathfinder::Rva002EDF7C(ObjWithPos *obj, ICoord2D *out)
{
	ICoord2D tmp;
	ICoord2D *cell = rva002EBC14(&tmp, obj, &obj->pos);
	out->x = cell->x;
	return getCell((PathfindLayerEnum)((Object *)obj)->rva0028B511(), out->x, out->y = cell->y);
}
