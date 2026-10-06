// cl: /DNDEBUG /MD /EHs-c-
// ?rva002636F6@Object@@QBEMPBUCoord3D@@PBX0@Z
//
// retail 0x002636F6 (109 bytes). Two-radius twin of the rowed 0x002C97E8.
// Planar shrunken-distance-squared with two radii:
//   sqr(max(0, sqrt(dx*dx+dy*dy) - this->m_majorRadius - otherRadius))
// where otherRadius is the +0xB8 float of the middle object.
//
// Recovered from the banked attempt reverse/attempts/0x002636f6.cpp (verdict
// 2026-09-29, partial score=1.0): byte-exact, 41 instructions, no structural
// difference, and unlanded only because the commit gate refused it. The gate
// was objecting to the marker's trailing comma -- '// ?<mangled>,' is the
// ledger row's own shape, copied with its separator, and
// find_declared_unmatched reads everything after '// ?' as the symbol name. The
// banked file carried that comma on the marker immediately above the
// definition while two clean copies sat above it, so the parser took the last
// one. Same one-character cause as 0x000E5F60, landed just before this.
//
// Evidence: same x87+qword+sqrt-import shape as ObjectRva002C97E8.cpp;
// this+0xB8 and arg2+0xB8 both fsubbed; ret 0xC with
// (Coord3D*, void*, Coord3D*); middle typed void to avoid inventing its class;
// callers 0x002C9863/0x002CB2EA/0x002CB4D1.
#include <math.h>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	float rva002636F6(const Coord3D *a, const void *other, const Coord3D *b) const;
	float rva00263763(const void *other) const;

private:
	char m_pad00[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0xB8 - 0x38 - 12];
	float m_majorRadius; // +0xB8
};

// retail 0x00263763 (21B). Object wrapper forwarding to rowed 0x002636F6
// with this+0x38 and other+0x38 as Coord3D args. Evidence: callee rowed
// in this TU; callers at 0x002C9B22 and 0x002CB3EA among 32.
float Object::rva00263763(const void *other) const
{
	return rva002636F6(&m_position, other, (const Coord3D *)((const char *)other + 0x38));
}

float Object::rva002636F6(const Coord3D *a, const void *other, const Coord3D *b) const
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float rad = m_majorRadius;
	float rad2 = *(float const *)((char const *)other + 0xB8);
	double dist = sqrt((double)(dx * dx + dy * dy));
	float d = (float)dist - rad - rad2;
	float result;
	if (d < 0.0f)
		result = 0.0f;
	else
		result = d * d;
	return result;
}
