// cl: /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// Open-BFME: vector<GeometryShape> copy constructor, retail 0x000FDE60.
//
// GeometryInfo's exact copy constructor calls this body through ILT
// 0x00027570 for its +0x2C member.  The element layout and memberwise copy are
// independently exact in GeometryShapeCopyConstructor.cpp: seven dwords,
// StringBase<char> at +0x1C, and the enabled byte at +0x20.
// The explicit instantiation also emits the canonical get_allocator,
// allocator-proxy, and vector-base dependencies at 0x000FCB00, 0x000FCCD0,
// and 0x000FD230.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;

	// Making the aggregate copy explicit preserves retail's inlined
	// source-plus-0x18 cursor while retaining ordinary memberwise semantics.
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
	~GeometryShape();
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

template class _STL::vector<GeometryShape>;

// erase (retail 0x002B0CB0) and its __copy_ptrs forwarder (0x002B0B71) are
// not GeometryShape's: retail erase destroys the vacated tail element through
// 0x002AF1EC (vector<AsciiString> at +0x14, buffer at +8, AsciiString at +0)
// and the __copy loop (0x002AF6C5) assigns through 0x002AF505, where
// GeometryShape's own dtor is the 0x00255D17 tail jump (GeometryInfo's
// shape-vector dtor 0x00050A79 reaches it per 0x24 element) and its assign
// is 0x00063627.  Opaque view of that other 0x24-byte record.
struct Rva002AF6C5Element
{
	~Rva002AF6C5Element();
	Rva002AF6C5Element &operator=(const Rva002AF6C5Element &other);

	unsigned char m_pad[0x24];
};

template Rva002AF6C5Element *_STL::vector<Rva002AF6C5Element>::erase(Rva002AF6C5Element *);
