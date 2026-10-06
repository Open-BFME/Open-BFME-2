// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??4GeometryShape@@QAEAAU0@ABU0@@Z retail 0x00063627 75 bytes.
// GeometryShape value assignment: seven scalar words then the AsciiString
// name at +0x1C through the folded assign pin at 0x000366F0 plus the two
// tail bytes at +0x20/+0x21. The +0x2C shapes vector of GeometryInfo calls
// this operator through the 0x24-stride copy loop and from set at 0x6BFF50
// and the shape scan at 0x6BD9C0. Layout matches the rowed shape vector
// base imul 0x24 and the matched copy ctor twin at 0x63BE4.

#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_offset;
	AsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_byte21;

	GeometryShape &operator=(const GeometryShape &other);
};

inline GeometryShape &GeometryShape::operator=(const GeometryShape &other)
{
	m_type = other.m_type;
	m_height = other.m_height;
	m_majorRadius = other.m_majorRadius;
	m_minorRadius = other.m_minorRadius;
	m_offset = other.m_offset;
	m_name = other.m_name;
	m_enabled = other.m_enabled;
	m_byte21 = other.m_byte21;
	return *this;
}

// This operator is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeGeometryShapeAssignInlineAnchor@@YAXXZ absent-from-retail
void _bfmeGeometryShapeAssignInlineAnchor()
{
    GeometryShape *destination = 0;
    const GeometryShape *source = 0;
    *destination = *source;
}
#pragma inline_depth()
