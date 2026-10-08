// cl: /Ireference/shims/bfme2_vector3 /Ireference/shims/bfmerendobj /arch:SSE /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// WWMath collision-vs-plane tests, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/colmathplane.cpp). WWASSERT compiles out in
// the retail (non-DEBUG_CRASHING) build, matching what BFME shipped.
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
#include "vector3.h" // existing BFME2 constructor view must win
#define COLMATHPLANE_H // use the source-local inline expressions below
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "colmath.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"

// BFME1@34f59164f6 supplies the plane-overlap expressions below.
// Keep the already-inlined math local: only the existing native providers
// own out-of-line get_far_extent (0x0007B5C8) and Plane/Point (0x0007B638).
// ?bfmeNegateInline absent-from-retail
static __forceinline Vector3 bfmeNegateInline(const Vector3 & value)
{
    Vector3 result;
    result.Set(-value.X,-value.Y,-value.Z);
    return result;
}

// ?bfmeNativeFarExtentInline absent-from-retail
static __forceinline void bfmeNativeFarExtentInline(const Vector3 & normal,const Vector3 & extent,Vector3 * posfarpt)
{
	if (WWMath::Fast_Is_Float_Positive(normal.X)) {
		posfarpt->X = extent.X;
	} else {
		posfarpt->X = -extent.X;
	}

	if (WWMath::Fast_Is_Float_Positive(normal.Y)) {
		posfarpt->Y = extent.Y;
	} else {
		posfarpt->Y = -extent.Y;
	}

	if (WWMath::Fast_Is_Float_Positive(normal.Z)) {
		posfarpt->Z = extent.Z;
	} else {
		posfarpt->Z = -extent.Z;
	}
}
// ?bfmeNativePlanePointInline absent-from-retail
static __forceinline CollisionMath::OverlapType
bfmeNativePlanePointInline(const PlaneClass & plane,const Vector3 & point,const float & epsilon)
{
	float delta = Vector3::Dot_Product(point,plane.N) - plane.D;
	if (delta > epsilon) {
		return CollisionMath::POS;
	}
	if (delta < -epsilon) {
		return CollisionMath::NEG;
	}
	return CollisionMath::ON;
}


CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const Vector3 & point)
{
	float delta = point[plane.Normal] - plane.Dist;
	if (delta > COINCIDENCE_EPSILON) {
		return POS;
	}
	if (delta < -COINCIDENCE_EPSILON) {
		return NEG;
	}
	return ON;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const LineSegClass & line)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P0());
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P1());
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const TriClass & tri)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[0]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[1]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[2]);
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const SphereClass & sphere)
{
	float delta = sphere.Center[plane.Normal] - plane.Dist;
	if (delta > sphere.Radius) {
		return POS;
	}
	if (delta < sphere.Radius) {
		return NEG;
	}
	return BOTH;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const AABoxClass & box)
{
	float delta;
	int mask = 0;

	// check the 'min' side of the box
	delta = (box.Center[plane.Normal] - box.Extent[plane.Normal]) - plane.Dist;
	if (delta > WWMATH_EPSILON) {
		mask |= POS;
	} else if (delta < -WWMATH_EPSILON) {
		mask |= NEG;
	} else {
		mask |= ON;
	}

	// check the 'max' side of the box
	delta = (box.Center[plane.Normal] + box.Extent[plane.Normal]) - plane.Dist;
	if (delta > WWMATH_EPSILON) {
		mask |= POS;
	} else if (delta < -WWMATH_EPSILON) {
		mask |= NEG;
	} else {
		mask |= ON;
	}

	return eval_overlap_mask(mask);
}


CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & /*plane*/,const OBBoxClass & /*box*/)
{
// TODO
	WWASSERT(0);
	return POS;
}


// Plane functions.  Where is operand B with respect to the plane

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const LineSegClass & line)
{
	int mask = 0;
	mask |= bfmeNativePlanePointInline(plane,line.Get_P0(),COINCIDENCE_EPSILON);
	mask |= bfmeNativePlanePointInline(plane,line.Get_P1(),COINCIDENCE_EPSILON);
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const TriClass & tri)
{
	int mask = 0;
	mask |= bfmeNativePlanePointInline(plane,*tri.V[0],COINCIDENCE_EPSILON);
	mask |= bfmeNativePlanePointInline(plane,*tri.V[1],COINCIDENCE_EPSILON);
	mask |= bfmeNativePlanePointInline(plane,*tri.V[2],COINCIDENCE_EPSILON);
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const SphereClass & sphere)
{
	float dist = Vector3::Dot_Product(sphere.Center,plane.N) - plane.D;
	if (dist > sphere.Radius) {
		return POS;
	}
	if (dist < -sphere.Radius) {
		return NEG;
	}
	return BOTH;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const OBBoxClass & box)
{
	// rotate the plane normal into box coordinates
	Vector3 local_normal;
	Vector3 posfarpt;
	Vector3 negfarpt;
	Matrix3::Transpose_Rotate_Vector(box.Basis,plane.N,&local_normal);

	bfmeNativeFarExtentInline(local_normal,box.Extent,&posfarpt);

	// transform the two extreme box coordinates into world space
	Matrix3::Rotate_Vector(box.Basis,posfarpt,&posfarpt);
	negfarpt = bfmeNegateInline(posfarpt);
	posfarpt += box.Center;
	negfarpt += box.Center;

	// overlap test
	if (bfmeNativePlanePointInline(plane,negfarpt,COINCIDENCE_EPSILON) == POS) {
		return POS;
	}
	if (bfmeNativePlanePointInline(plane,posfarpt,COINCIDENCE_EPSILON) == NEG) {
		return NEG;
	}
	return BOTH;
}
