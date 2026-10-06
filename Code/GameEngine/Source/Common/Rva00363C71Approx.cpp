// cl: /DNDEBUG /MD /Oi-
#include <math.h>
//
// ?Rva00363C71Approx@@YANPBUCoord3D@@0@Z
// RVA 0x00363C71 size 130. Fast 2D hypotenuse approximation max+K*min over
// fabs components with K at 0x007BB8D4; fabs stays a call via /Oi- (pin
// _fabs at 0x00629210). Evidence: callers at 0x00363D3C/52 pass two point
// pointers and accumulate the double result; sibling PathDistance proves the
// Coord3D arg shape and push-ecx double-temp idiom; no EH frame.
// The 0.25 factor is the pooled float literal (the banked attempt read it
// through a float global), and /arch:SSE enables the P6 fcomi compare
// (fxch/fcomip/fstp/jbe) retail uses instead of fcomp/fnstsw.

struct Coord3D
{
	float x;
	float y;
	float z;
};


double __cdecl Rva00363C71Approx(const Coord3D *a, const Coord3D *b)
{
	if (fabs(a->x - b->x) > fabs(a->y - b->y))
		return fabs(a->x - b->x) + fabs(a->y - b->y) * 0.25f;
	return fabs(a->y - b->y) + fabs(a->x - b->x) * 0.25f;
}
