// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector base for the 36-byte GeometryShape element.
// The count-taking _Vector_base (retail 0x0010E5A2, 60B) is emitted here as
// a side product of the explicit instantiation, mirroring the
// PrereqUnitRec allocate_copy TU that placed its own 60B _Vector_base.
// The allocator (0x5DFB2C, rowed) and the alloc proxy (0x14F3C4, pinned)
// callees are both settled; the 36-byte stride (imul 0x24) selects the
// GeometryShape element spelling. Layout copied verbatim from
// GeometryShapeVectorCopyConstructor.cpp (seven dwords, StringBase at
// +0x1C, enabled byte at +0x20) so the true UGeometryShape mangling and
// 36-byte size both hold.
#include <vector>

typedef bool Bool;

struct AsciiString
{
	void *m_data;
};

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_centerOffset;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape();
	GeometryShape(const GeometryShape &other)
		: m_type(other.m_type),
		  m_height(other.m_height),
		  m_majorRadius(other.m_majorRadius),
		  m_minorRadius(other.m_minorRadius),
		  m_centerOffset(other.m_centerOffset),
		  m_name(other.m_name),
		  m_enabled(other.m_enabled),
		  m_unmodelled21()
	{
	}
};

template class _STL::vector<GeometryShape, _STL::allocator<GeometryShape> >;

// Reference the count-taking _Vector_base so the object emits it: retail
// 0x0010E5A2 is the (count, allocator) base ctor, which nothing above calls.
void forceGeometryShapeVectorBase()
{
	_STL::vector<GeometryShape, _STL::allocator<GeometryShape> > counted(3);
}
