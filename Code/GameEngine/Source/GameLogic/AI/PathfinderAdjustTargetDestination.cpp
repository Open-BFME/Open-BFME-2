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

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

class Rva002EBC34
{
public:
	ICoord2D *rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3);
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
	char prefix[0x9b8]; // +0x00
	int m_flag9B8; // +0x9B8
	char m_pad9BC[0x804];
	unsigned int limitMs; // +0x11C0
	char m_pad11C4[0x24];
	int cellsPerFrame; // +0x11E8
	char m_pad11EC[0xC];
	int m_maxCellsAdjustTargetDestination; // +0x11F8
	char m_pad11FC[0x20];
	unsigned callbackLimit; // +0x121C
};
extern class GlobalData *TheWritableGlobalData;

class Pathfinder
{
public:
	Bool AdjustTargetDestination(Object *obj, Int a, Int b, Int c, const Coord3D *dest);
	Bool rva002F379E(ICoord2D *cell, Int range, void *info);	// row 0x002F379E spelling
};

Bool Pathfinder::AdjustTargetDestination(Object *obj, Int a, Int b, Int c, const Coord3D *dest)
{
	ICoord2D cell;
	((Rva002EBC34 *)this)->rva002EBC34(&cell, obj, dest);
	if (cell.x < 0)
		return false;
	Rva002ED7B6 info;
	return rva002F379E(&cell, TheWritableGlobalData->m_maxCellsAdjustTargetDestination,
		info.rva002ED7B6((Int)this, obj, a, b, c, (Int)dest));
}
