// cl: /Ireference/shims/bfmerendobj /G7 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// WWMath triangle helpers, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/tri.cpp). The unused find_dominant_plane_fast
// path and the #if 0 alternatives inside Contains_Point are omitted; the retained
// source is reused from Open-BFME-1; ledger rows record BFME2 byte verification.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "tri.h"
#include "vector2.h"

// The normal projection uses the IEEE sign-bit operation in WWMath::Fabs.
// Keep this file's inlined calculation local; the shared out-of-line Fabs
// provider has a different compiler frame setting.
static inline float normal_component_magnitude(float value)
{
    union { float value; unsigned int bits; } magnitude;
    magnitude.value = value;
    magnitude.bits &= 0x7fffffffU;
    return magnitude.value;
}


static inline void find_dominant_plane(const TriClass & tri, int * axis1,int * axis2,int * axis3)
{
	/*
	** Find the largest component of the normal
	*/
	int ni = 0;
	float x = normal_component_magnitude(tri.N->X);
	float y = normal_component_magnitude(tri.N->Y);
	float z = normal_component_magnitude(tri.N->Z);
	float val = x;

	if (y > val) {
		ni = 1;
		val = y;
	}

	if (z > val) {
		ni = 2;
	}

	/*
	** return the indices of the two axes perpendicular
	*/
	switch (ni)
	{
	case 0:
		// Dominant is the X axis
		*axis1 = 1;
		*axis2 = 2;
		*axis3 = 0;
		break;
	case 1:
		// Dominant is the Y axis
		*axis1 = 0;
		*axis2 = 2;
		*axis3 = 1;
		break;
	case 2:
		// Dominant is the Z axis
		*axis1 = 0;
		*axis2 = 1;
		*axis3 = 2;
		break;
	}
}


void TriClass::Find_Dominant_Plane(int * axis1,int * axis2) const
{
	/*
	** Find the largest component of the normal
	*/
	int ni = 0;
	float x = normal_component_magnitude(N->X);
	float y = normal_component_magnitude(N->Y);
	float z = normal_component_magnitude(N->Z);
	float val = x;

	if (y > val) {
		ni = 1;
		val = y;
	}

	if (z > val) {
		ni = 2;
	}

	/*
	** return the indices of the two axes perpendicular
	*/
	switch (ni)
	{
	case 0:
		// Dominant is the X axis
		*axis1 = 1;
		*axis2 = 2;
		break;
	case 1:
		// Dominant is the Y axis
		*axis1 = 0;
		*axis2 = 2;
		break;
	case 2:
		// Dominant is the Z axis
		*axis1 = 0;
		*axis2 = 1;
		break;
	}
}


bool TriClass::Contains_Point(const Vector3 & ipoint) const
{
	int vi;
	int axis1 = 0;
	int axis2 = 0;
	int axis3 = 0;

	find_dominant_plane(*this,&axis1,&axis2,&axis3);

	bool side[3];

	/*
	** Compute the 2D cross product of edge0 with a vector to the point
	*/
	Vector2 edge;
	Vector2 dp;

	for (vi=0; vi<3; vi++) {

		int va=vi;
		int vb=(vi+1)%3;

		edge.Set((*V[vb])[axis1] - (*V[va])[axis1] , (*V[vb])[axis2] - (*V[va])[axis2]);
		dp.Set(ipoint[axis1] - (*V[va])[axis1] , ipoint[axis2] - (*V[va])[axis2]);
		float cross = edge.X * dp.Y - edge.Y * dp.X;
		side[vi] = (cross >= 0.0f);
	}

	bool my_intersect = ((side[0] == side[1]) && (side[1] == side[2]));
	return my_intersect;
}
