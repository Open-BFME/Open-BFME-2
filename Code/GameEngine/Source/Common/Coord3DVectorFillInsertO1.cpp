// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// stlport
//
// Size-optimised (/O1) instantiation of vector<Coord3D>::_M_fill_insert.
//
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "prerts.h"
#include "coord.h"
#include "bezier_segment.h"
#include "bez_fwd_iterator.h"
#include "d3dx8math.h"

// Retail's uninitialized-copy target at 0x000766F5 is rowed as the 12-byte
// BfmeE12 specialization, although this vector body uses Coord3D (three Real
// values, also three floats). Forward only this copy through the rowed type.
struct BfmeE12
{
	float x, y, z;
};

namespace _STL
{
	inline Coord3D *__uninitialized_copy(Coord3D *first, Coord3D *last,
		Coord3D *result, const __false_type &tag)
	{
		return reinterpret_cast<Coord3D *>(__uninitialized_copy<const BfmeE12 *, BfmeE12 *>(
			reinterpret_cast<const BfmeE12 *>(first),
			reinterpret_cast<const BfmeE12 *>(last),
			reinterpret_cast<BfmeE12 *>(result), tag));
	}
}

extern void (_STL::vector<Coord3D>::*const g_bfmeCoord3DFillInsertAnchor)(Coord3D *, unsigned int, const Coord3D &);
void (_STL::vector<Coord3D>::*const g_bfmeCoord3DFillInsertAnchor)(Coord3D *, unsigned int, const Coord3D &) = &_STL::vector<Coord3D>::_M_fill_insert;
