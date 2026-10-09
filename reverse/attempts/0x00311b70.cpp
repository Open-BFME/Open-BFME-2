// 0x00311B70
// partial score=0.86 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// NEAR draft (~0.85-0.87, 610B vs 617B) for retail 0x00311B70 (617B). The banked
// body (reverse/attempts/0x00311b70.cpp) re-expressed over the canonical Coord3D
// (class_gate refuses the bank's private Coord3D) with member-wise set/sub/scale
// helpers; it reproduces the bank's output exactly under region flags.
// Walls: retail scales delta with three mulss [len] memory operands and sinks
// the scaled delta stores past the size() idiv where cl caches len in xmm0 and
// stores delta.z at once; retail loads the first record's x after the
// delta=point movsd (y/z before); block 2 keeps n*0xB8 in ecx not esi.
// WB twin 0x00EB38C0: p1=rec[1] p2=rec[2] delta=p1-p2 len; p0=rec[0];
// delta=p1-p0 normalize scale(len) p1-=delta rec[0]=p1; same for the tail with
// a fresh len (local_28). The free static helpers must become in-class inline
// members before this file could land (find_declared_unmatched).
#include "Coord3D.h"

typedef float Real;
typedef int Int;

static __forceinline void coordSet(Coord3D &c, const Coord3D *a) { c.x = a->x; c.y = a->y; c.z = a->z; }
static __forceinline void coordSub(Coord3D &c, const Coord3D *a) { c.x -= a->x; c.y -= a->y; c.z -= a->z; }
static __forceinline void coordScale(Coord3D &c, Real s) { c.x *= s; c.y *= s; c.z *= s; }

struct Rva00311B70Point
{
	char m_pad00[0xa4];
	Coord3D m_pos;		// +0xA4
	char m_padB0[0xb8 - 0xb0];
};

class Rva00311B70PointVector
{
public:
	Rva00311B70Point &operator[](Int i) { return _M_start[i]; }
	Int size() const { return _M_finish - _M_start; }
private:
	Rva00311B70Point *_M_start;
	Rva00311B70Point *_M_finish;
	Rva00311B70Point *_M_end_of_storage;
};

class Rva00311B70
{
public:
	void rva00311B70();
private:
	char m_pad00[0x2c];
	Rva00311B70PointVector m_points;	// +0x2C
};

void Rva00311B70::rva00311B70()
{
	Coord3D point, delta;
	coordSet(point, &m_points[1].m_pos);
	Coord3D second;
	coordSet(second, &m_points[2].m_pos);
	delta.x = point.x - second.x; delta.y = point.y - second.y; delta.z = point.z - second.z;
	Real length = delta.length();
	Coord3D first;
	coordSet(first, &m_points[0].m_pos);
	delta = point; coordSub(delta, &first); delta.normalize(); coordScale(delta, length);
	coordSub(point, &delta); m_points[0].m_pos = point;
	Int n = m_points.size();
	coordSet(point, &m_points[n - 2].m_pos); delta = point;
	Coord3D beforeLast; coordSet(beforeLast, &m_points[n - 3].m_pos); coordSub(delta, &beforeLast);
	length = delta.length(); delta = point;
	Coord3D last; coordSet(last, &m_points[n - 1].m_pos); coordSub(delta, &last); delta.normalize(); coordScale(delta, length);
	coordSub(point, &delta); m_points[n - 1].m_pos = point;
}
