// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?updateViewImpassableAreas@BaseHeightMapRenderObjClass@@QAEXH...@Z, retail
// 0x0006DBB2..0x0006DC8E (220 bytes, RET 0x14). Zero Hour's
// BaseHeightMapRenderObjClass::updateViewImpassableAreas (BaseHeightMap.cpp):
// grow the vector<bool> cliff-visibility table at +0x37EC to xExtent*yExtent,
// widen a non-partial request to the whole map, take the tangent of the
// current impassable slope (+0x379C, degrees) once and refill the requested
// cells through the rowed evaluateAsVisibleCliff (0x0006737E).

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <math.h>
// always.h defines array placement-new itself.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
// bfme link decl-only end

typedef int Int;
typedef float Real;
typedef bool Bool;

namespace _STL
{
template<> vector<bool, allocator<bool> >::reference vector<bool, allocator<bool> >::operator[](size_t n);
}

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The cliff-visibility vector<bool> at +0x37EC.
static __forceinline _STL::vector<bool> &visibleCliffBits(BaseHeightMapRenderObjClass *self)
{
	return self->unknown37EC;
}

void BaseHeightMapRenderObjClass::updateViewImpassableAreas(Bool partial, Int minX, Int maxX, Int minY, Int maxY)
{
	Int xSize = m_map->getXExtent();
	Int ySize = m_map->getYExtent();
	if (visibleCliffBits(this).size() != xSize * ySize) {
		visibleCliffBits(this).resize(xSize * ySize);
	}

	if (!partial) {
		minX = 0;
		minY = 0;
		maxX = xSize;
		maxY = ySize;
	}

	// save calculating the tangent over and over again.
	Real tanImpassableRad = tan(m_curImpassableSlope * 0.017453292f);
	for (Int j = minY; j < maxY; ++j) {
		for (Int i = minX; i < maxX; ++i) {
			visibleCliffBits(this)[i + j * xSize] = evaluateAsVisibleCliff(i, j, tanImpassableRad);
		}
	}
}
