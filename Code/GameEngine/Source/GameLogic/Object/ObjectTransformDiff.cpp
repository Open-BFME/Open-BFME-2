// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Object.cpp's transform-change thresholds (Zero Hour Object.cpp, donor
// source; retail keeps them out of line):
//   ?isPosDifferent@@YA_NPBUCoord3D@@0@Z  0x0028B0A8 (113B)
//   ?isAngleDifferent@@YA_NMM@Z           0x0028B119 (40B)
// Target evidence: Object::reactToTransformChange (WorldBuilder lead
// 0x00292D49) calls 0x0028B0A8 with (oldPos, &m_position at Object+0x38) and
// 0x0028B119 with (oldAngle, Object+0x44) exactly where the donor calls
// isPosDifferent(oldPos, getPosition()) / isAngleDifferent(oldAngle,
// getOrientation()), then ORs the results. Each compares fabs (the CRT
// import _fabs, called: /O1 has no /Oi) of the difference against the one
// float constant 0.01f, axis by axis, returning true on the first excess;
// math.h's float fabs overload keeps the compare in float, so the
// threshold loads as a dword.
typedef float Real;
typedef bool Bool;

#include <math.h>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

Bool isPosDifferent(const Coord3D *a, const Coord3D *b)
{
	const Real THRESH = 0.01f;

	if (fabs(a->x - b->x) > THRESH)
		return true;

	if (fabs(a->y - b->y) > THRESH)
		return true;

	if (fabs(a->z - b->z) > THRESH)
		return true;

	return false;
}

Bool isAngleDifferent(Real a, Real b)
{
	const Real THRESH = 0.01f;

	if (fabs(a - b) > THRESH)
		return true;

	return false;
}
