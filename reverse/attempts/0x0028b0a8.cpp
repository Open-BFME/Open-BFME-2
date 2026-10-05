// ?isPosDifferent@@YA_NPBUCoord3D@@0@Z
// partial score=0.95 date=2026-10-05
// ?isPosDifferent@@YA_NPBUCoord3D@@0@Z
// partial score=0.95 date=2026-09-28
// ?isPosDifferent@@YA_NPBUCoord3D@@0@Z
// partial score=0.95 date=2026-09-28
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// ?isPosDifferent@@YA_NPBUCoord3D@@0@Z @0x0028B0A8 (113B) and
// ?isAngleDifferent@@YA_NMM@Z @0x0028B119 (40B): free helpers from ZH/BFME1
// Object.cpp verbatim (isPosDifferent/isAngleDifferent) with THRESH 0.01f.
// fabs resolves via the rowed msvcr71 import thunk at 0x00629210. Callers
// include 0x00292DD2 0x00292DE7.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

extern "C" double __cdecl fabs(double value);

extern float g_Va00BCF628; // 0.01 at 0xBCF628, shared tolerance

// ?isPosDifferent@@YA_NPBUCoord3D@@0@Z present-unmatched
bool isPosDifferent(const Coord3D *a, const Coord3D *b)
{
	if (fabs(a->x - b->x) > g_Va00BCF628)
		return true;

	if (fabs(a->y - b->y) > g_Va00BCF628)
		return true;

	if (fabs(a->z - b->z) > g_Va00BCF628)
		return true;

	return false;
}

// ?isAngleDifferent@@YA_NMM@Z present-unmatched
bool isAngleDifferent(Real a, Real b)
{
	if (fabs(a - b) > g_Va00BCF628)
		return true;

	return false;
}
