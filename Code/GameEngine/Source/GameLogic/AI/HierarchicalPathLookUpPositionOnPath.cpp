// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// HierarchicalPath::lookUpPositionOnPath, retail 0x0053446D (83B), from the
// WorldBuilder lead (pathfinder_hierarchicalpath.cpp): convert the position to
// a cell and look it up in the path's two-level cell index (map at
// +4 keyed by x, each value a map keyed by y); returns the stored path index
// or -1.
//
// The maps are spelled map<unsigned int, void *> so both finds name the rowed
// unsigned-key _M_find worker 0x00357180 (identical tree mechanics); the outer
// value is the inner map itself, at the node's value slot.
//
// The cell comes back from the rowed helper 0x0053442A
// (PathfindZoneManagerXfer.cpp): it divides the two input dwords by 16 into
// an 8-byte record returned through a hidden pointer, here the cell slot at
// [ebp-8]. It is called by its ledger name, as
// Rva00534557.cpp does, with the position viewed as its two input dwords.

#include <map>

// map/set<unsigned> internals otherwise emit an unreferenced
// less<unsigned>::operator() COMDAT in a register shape retail's 0x00758C50
// does not have. Every compare here is inlined, so an inline-only
// specialization keeps them so and emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
}

typedef int Int;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/Rva00534557EmptyBase.h"

struct Rva00534557Record : Rva00534557EmptyBase
{
	int x;
	int y;
	Rva00534557Record() {}
};

Rva00534557Record rva0053442A(const int *source);

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
	Rva00534557Record cell = rva0053442A((const int *)pos);
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
