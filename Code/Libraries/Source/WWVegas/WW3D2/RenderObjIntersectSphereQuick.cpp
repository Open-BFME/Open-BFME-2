// cl: /Ireference/shims/bfme2_vector3 /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// RenderObjClass::Intersect_Sphere_Quick, from the BFME1 WW3D2 rendobj.cpp
// at donor revision 071013b3c6f1228dfda315732197bed0fd191209. Donor semantics:
// obtain the object-space bounding sphere and run the inline quick ray/sphere
// test. Target evidence: RenderObjClass vftable 0x00BD2F68 slot 64 points to
// 0x0013BD70; its body reads the RenderObj bounding-sphere slot +0x104 and
// computes alpha/beta/intersects, ending in RET 8 at 0x0013BE1D before the
// independently named RenderObj destructor at 0x0013BE20. The body is a BFME2
// expansion of the donor's helper call; field semantics are donor facts, while
// the vtable slot, target offsets, and boundary are target evidence.
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

#include "vector3.h" // select the verified three-word constructor before donor math headers
#include "rendobj.h"
#include "intersec.h"

bool RenderObjClass::Intersect_Sphere_Quick(IntersectionClass *Intersection, IntersectionResultClass *Final_Result)
{
	SphereClass sphere = Get_Bounding_Sphere();
	// Expand the donor quick-sphere helper: the native 176-byte body
	// inlines this calculation, including floating-point field assignment.
	Vector3 sphere_vector;
	sphere_vector.Set(sphere.Center.X - Intersection->RayLocation->X, sphere.Center.Y - Intersection->RayLocation->Y, sphere.Center.Z - Intersection->RayLocation->Z);
	Final_Result->Alpha = Vector3::Dot_Product(sphere_vector, *Intersection->RayDirection);
	Final_Result->Beta = sphere.Radius * sphere.Radius - (Vector3::Dot_Product(sphere_vector, sphere_vector) - Final_Result->Alpha * Final_Result->Alpha);
	if (Final_Result->Beta < 0.0f) {
		return Final_Result->Intersects = false;
	}
	return Final_Result->Intersects = true;
}
