// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00263778Distance@@YAMPBUCoord3D@@MM0MM@Z,
// retail 0x00263778 (106 bytes). Free function near Object planar worker.
// Computes sqrt(dx*dx+dy*dy+dz*dz)-c-f clamped at zero then squared.
// Evidence: caller 0x002637E2 passes (ptr float get() float ptr 0 0);
// Coord3D layout from Object_planarSubtractWorker.cpp; sqrt import 0x0062921C.
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

float Rva00263778Distance(Coord3D const *a, float b, float c, Coord3D const *d, float e, float f)
{
	float dx = a->x - d->x;
	float dy = a->y - d->y;
	float dz = b + a->z - d->z - e;
	float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
	float t = dist - c - f;
	if (t < 0.0f)
		t = 0.0f;
	else
		t = t * t;
	return t;
}
