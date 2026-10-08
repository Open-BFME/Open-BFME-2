// Ported from BFME1; retain only after independent BFME2 placement.
// BFME1 Geometry.cpp donors (byte-identical): calcDotProduct retail 0x6BD370,
// calcDistSquared retail 0x6BD650, calcPointToLineDistSquared retail 0x6BD680,
// GeometryInfo::isIntersectedByLineSegment retail 0x6BD780.
// The donor's prerts.h chain (Lib/Basetype.h) does not resolve in this tree,
// so TU-local views (GeometryInfoCalcPitches precedent). DEBUG_CRASH lines are
// retail-empty under /DNDEBUG and are omitted.
// All four bodies share this TU because the statics use a custom register
// convention and inline into each other; splitting changes codegen.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <typename NUM>
inline NUM sqr(NUM x)
{
	return x * x;
}

static Real calcDotProduct(const Coord3D &a, const Coord3D &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static Real calcDistSquared(const Coord3D &a, const Coord3D &b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

static Real calcPointToLineDistSquared(const Coord3D &pt, const Coord3D &lineStart, const Coord3D &lineEnd)
{
	Coord3D line, lineToPt, closest;

	line.x = lineEnd.x - lineStart.x;
	line.y = lineEnd.y - lineStart.y;
	line.z = lineEnd.z - lineStart.z;

	lineToPt.x = pt.x - lineStart.x;
	lineToPt.y = pt.y - lineStart.y;
	lineToPt.z = pt.z - lineStart.z;

	Real dot = calcDotProduct(lineToPt, line);
	if (dot <= 0.0f)
	{
		// angle is obtuse
		return calcDistSquared(pt, lineStart);
	}

	Real lineLenSqr = calcDistSquared(lineStart, lineEnd);
	if (lineLenSqr <= dot)
	{
		return calcDistSquared(pt, lineEnd);
	}

	Real tmp = dot / lineLenSqr;

	closest.x = lineStart.x + tmp * line.x;
	closest.y = lineStart.y + tmp * line.y;
	closest.z = lineStart.z + tmp * line.z;

	return calcDistSquared(pt, closest);
}

class GeometryInfo
{
public:
	Bool isIntersectedByLineSegment(const Coord3D &loc, const Coord3D &from, const Coord3D &to) const;
};

Bool GeometryInfo::isIntersectedByLineSegment(const Coord3D &loc, const Coord3D &from, const Coord3D &to) const
{
	// retail layout: m_boundingSphereRadius sits at this+0x14 (ahead of
	// m_boundingCircleRadius at this+0x18, verified via getBoundingCircleRadius).
	Real boundingSphereRadius = *(const Real *)((const char *)this + 0x14);
	Real distSquared = calcPointToLineDistSquared(loc, from, to);
	return distSquared <= sqr(boundingSphereRadius);
}

// BF1 9cbfb551fe GeometryInfoCalcBoundingStuff.cpp emits sqr<double> in the
// clean named Common O1/SSE/G7 sweep. This supplies the expression, not a
// target template identity. Retail 6BD4D0..6BD4D9 is independently INT3-bounded
// on both sides: load a stack double, multiply by itself, return in ST0.
// No calls/globals/literals; no direct CALL/JMP was found in all image sections.
// The original name/owner/template identity remain unknown, so this ordinary
// helper has a neutral address name in the existing geometry arithmetic home.
double Rva006BD4D0Square(double value)
{
    return value * value;
}
