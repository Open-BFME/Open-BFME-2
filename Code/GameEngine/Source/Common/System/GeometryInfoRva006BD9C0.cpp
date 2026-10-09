// cl: /DNDEBUG /MD /EHsc /Ox /Ob2 /G6
//
// GeometryInfo::rva006BD9C0, retail 0x006BD9C0, 560 bytes. Banked partial
// (score 0.95: tail fst/fstp and store order) closed by tools/permute.py:
// /Ox instead of /O2, statement and operand order only; the body is the banked one.
// stlport
// GeometryInfo multi-shape bounding shape: single shape copied out whole via the
// rowed GeometryShape assign at 0x00063627, then 2D bounds over enabled BOX shapes
// with tiny-shape (<1.0f) filtering, bailing to the cylinder answer (boundingCircle
// at +0x10 plus rowed getMaxHeightAbovePosition at 0x006BD7C0) on any non-BOX type.
// Evidence: shapes vector at +0x2C/+0x30, +0x10 boundingCircle, callers at
// 0x002EE870 0x00422406 0x0073AE39 0x0073D10D passing a local GeometryShape temp,
// BFME1 donor GeometryInfoRva0087E190 (0x0087E190) same owner and shape.

#include <vector>

typedef bool Bool;
typedef float Real;

extern float g_Va00BBAEAC;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct GeometryShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	char m_name[0x04];
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape &operator=(const GeometryShape &other);
};

// STLport 4.5.3's unchanged inline accessors, scoped to this native consumer.
// Keep the target's stride-36 reads without competing out-of-line copies.
namespace _STL {
template<> __declspec(dllimport) __forceinline
vector<GeometryShape, allocator<GeometryShape> >::size_type
vector<GeometryShape, allocator<GeometryShape> >::size() const
{ return size_type(this->_M_finish - this->_M_start); }
template<> __declspec(dllimport) __forceinline
vector<GeometryShape, allocator<GeometryShape> >::const_reference
vector<GeometryShape, allocator<GeometryShape> >::operator[](size_type n) const
{ return *(begin() + n); }
}

template <class T>
static inline const T &bfmeMin(const T &a, const T &b)
{
	return (a < b) ? a : b;
}

template <class T>
static inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	void rva006BD9C0(GeometryShape &out) const;

private:
	void *m_vtbl;
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	Real m_boundingCircleRadius;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
};

void GeometryInfo::rva006BD9C0(GeometryShape &out) const
{
	if (m_shapes.size() == 1)
		out = m_shapes[0];

	Region2D bounds;
	bounds.lo.x = bounds.lo.y = bounds.hi.x = bounds.hi.y = 0.0f;
	Real maxZ = 0.0f;
	unsigned int numShapes = m_shapes.size();

	for (std::vector<GeometryShape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		if (!it->m_enabled)
			continue;
		if (1 != numShapes)
		{
			if (!(it->m_majorRadius >= 1.0f))
			{
				if (!(it->m_minorRadius >= 1.0f))
				{
					if (!(it->m_height >= 1.0f))
						continue;
				}
			}
		}
		if (it->m_type != GEOMETRY_BOX)
			goto cylinder;

		bounds.lo.x = bfmeMin(bounds.lo.x, it->m_offset.x - it->m_majorRadius);
		bounds.lo.y = bfmeMin(bounds.lo.y, it->m_offset.y - it->m_minorRadius);
		bounds.hi.x = bfmeMax(bounds.hi.x, it->m_majorRadius + it->m_offset.x);
		bounds.hi.y = bfmeMax(bounds.hi.y, it->m_offset.y + it->m_minorRadius);
		maxZ = bfmeMax(maxZ, it->m_height);
	}

	Real major = (bounds.hi.x - bounds.lo.x) * 0.5f;
	out.m_type = GEOMETRY_BOX;
	out.m_majorRadius = major;
	out.m_offset.z = 0.0f;
	Real minor = (bounds.hi.y - bounds.lo.y) * 0.5f;
	out.m_minorRadius = minor;
	out.m_offset.x = major + bounds.lo.x;
	out.m_offset.y = minor + bounds.lo.y;
	return;

cylinder:
	out.m_type = GEOMETRY_CYLINDER;
	out.m_majorRadius = m_boundingCircleRadius;
	out.m_minorRadius = m_boundingCircleRadius;
	out.m_height = getMaxHeightAbovePosition();
	Coord3D zero;
	zero.x = 0.0f;
	zero.z = 0.0f;
	zero.y = 0.0f;
	out.m_offset = zero;
}
