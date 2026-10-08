// cl: /O1 /G7 /DNDEBUG /MD
//
// Pathfinder::AdjustTargetDestination, retail 0x002F3BB3 (86B), from the
// WorldBuilder lead (pathfinder.cpp): convert the goal to a cell (0x002EBC34),
// fail off the map, otherwise build the check-for-target context
// (WorldBuilder's Pathfinder_IsCheckForTarget constructor, the rowed
// 0x002ED7B6 initialiser returning this) and search outward from the cell
// (0x002F379E) up to TheGlobalData +0x11F8.
//
// Target facts: argument roles beyond the object and goal position, the
// context layout (0x20 bytes) and the search keep address-derived names.

typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x, y;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

class Rva002EBC34
{
public:
	ICoord2D *rva002EBC34(ICoord2D *out, void *obj, const Coord3D *pos);
};

class Rva002ED7B6
{
public:
	Rva002ED7B6 *rva002ED7B6(Int pathfinder, void *obj, Int a, Int b, Int c, Int d);

private:
	unsigned char m_data[0x20];
};

class GlobalData
{
public:
	unsigned char m_pad00[0x11F8];
	Int m_11f8;
};
extern class GlobalData *TheWritableGlobalData;

class Pathfinder
{
public:
	Bool AdjustTargetDestination(Object *obj, Int a, Int b, Int c, const Coord3D *dest);
	Bool rva002F379E(ICoord2D *cell, Int range, Rva002ED7B6 *info);
};

Bool Pathfinder::AdjustTargetDestination(Object *obj, Int a, Int b, Int c, const Coord3D *dest)
{
	ICoord2D cell;
	((Rva002EBC34 *)this)->rva002EBC34(&cell, obj, dest);
	if (cell.x < 0)
		return false;
	Rva002ED7B6 info;
	return rva002F379E(&cell, TheWritableGlobalData->m_11f8,
		info.rva002ED7B6((Int)this, obj, a, b, c, (Int)dest));
}
