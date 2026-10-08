// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// HierarchicalPath::lookUpPositionOnPath, retail 0x0053446D (83B), from the
// WorldBuilder lead (pathfinder_hierarchicalpath.cpp): convert the position to
// a cell (0x0053442A) and look it up in the path's two-level cell index (map at
// +4 keyed by x, each value a map keyed by y); returns the stored path index
// or -1.
//
// The maps are spelled map<unsigned int, void *> so both finds name the rowed
// unsigned-key _M_find worker 0x00357180 (identical tree mechanics); the outer
// value is the inner map itself, at the node's value slot.

#include <map>

typedef int Int;

struct ICoord2D
{
	Int x, y;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

void rva0053442A(ICoord2D *out, const Coord3D *pos);

typedef _STL::map<unsigned int, void *> Rva0053446DMap;

class HierarchicalPath
{
public:
	Int lookUpPositionOnPath(const Coord3D *pos);

private:
	void *m_vtbl;
	Rva0053446DMap m_cells;
};

Int HierarchicalPath::lookUpPositionOnPath(const Coord3D *pos)
{
	ICoord2D cell;
	rva0053442A(&cell, pos);
	Rva0053446DMap::iterator it = m_cells.find(cell.x);
	if (it == m_cells.end())
		return -1;
	unsigned int y = cell.y;
	Rva0053446DMap &row = *(Rva0053446DMap *)&(*it).second;
	Rva0053446DMap::iterator it2 = row.find(y);
	if (it2 == row.end())
		return -1;
	return (Int)(*it2).second;
}
