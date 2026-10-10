// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
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
#include <vector>

typedef int Int;
typedef float Real;
typedef bool Bool;

namespace _STL
{
template<> vector<bool, allocator<bool> >::reference vector<bool, allocator<bool> >::operator[](size_t n);
}

class BaseHeightMapExtent
{
public:
	char m_pad00[8];
	Int m_xExtent;
	Int m_yExtent;
};

class BaseHeightMapRenderObjClass
{
public:
	void updateViewImpassableAreas(Bool partial, Int minX, Int maxX, Int minY, Int maxY);
	Bool evaluateAsVisibleCliff(Int xIndex, Int yIndex, Real valuesGreaterThanRad);

private:
	char m_pad00[0x379C];
	Real m_curImpassableSlope;			// +0x379C
	char m_pad37A0[0x37C0 - 0x37A0];
	BaseHeightMapExtent *m_map;			// +0x37C0
	char m_pad37C4[0x37EC - 0x37C4];
	_STL::vector<bool> m_showAsVisibleCliff;	// +0x37EC
};

void BaseHeightMapRenderObjClass::updateViewImpassableAreas(Bool partial, Int minX, Int maxX, Int minY, Int maxY)
{
	Int xSize = m_map->m_xExtent;
	Int ySize = m_map->m_yExtent;
	if (m_showAsVisibleCliff.size() != xSize * ySize) {
		m_showAsVisibleCliff.resize(xSize * ySize);
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
			m_showAsVisibleCliff[i + j * xSize] = evaluateAsVisibleCliff(i, j, tanImpassableRad);
		}
	}
}
