#pragma once
// The existing Coord3D::length69B retail provider (RVA3571) is inline in
// the original MathCoord3D header. W3DView::scrollBy needs the compiler's
// knowledge that it leaves the displacement untouched, even when /O1 keeps
// the call out of line. Source semantics: BFME1 coord3d.cpp plus WB MathCoord3D.
// This exact definition emits the same69B body and _sqrt relocation as the
// existing provider; the float temporary fixes target's SSE rounding before
// promoting its sum to the double CRT sqrt argument. No layout changes.
#include "Coord3D.h"
#include <math.h>
inline float Coord3D::length() const
{
    float squares = x * x + y * y + z * z;
    return (float)sqrt((double)squares);
}
