// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// RenderObjClass::Intersect from BFME1 WW3D2 rendobj.cpp at donor revision
// 071013b3c6f1228dfda315732197bed0fd191209. Donor semantics: reject by the
// quick sphere test then cast the line segment and populate the intersection
// result. Target evidence: RenderObjClass vftable 0x00BD2F68 slot62 points to
// 0x0013C3B0; target code calls the quick-test slot +0x100 and Cast_Ray slot
// +0xF0 then stores the result through offsets 0x44..0x64. The code ends at
// RET 8 at 0x0013C5B6 before the next Ghidra boundary 0x0013C5C0. Target
// boundary and virtual-slot facts are separate from donor semantics.
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

#include "rendobj.h"
#include "colmath.h"
#include "coltest.h"
#include "inttest.h"
#include "intersec.h"

bool RenderObjClass::Intersect(IntersectionClass *Intersection, IntersectionResultClass *Final_Result)
{
	// do the quick sphere test just to make sure it is worth the more expensive intersection test
	if (Intersect_Sphere_Quick(Intersection, Final_Result)) {

		CastResultStruct castresult;
		LineSegClass lineseg;

		Vector3 end = *Intersection->RayLocation + *Intersection->RayDirection * Intersection->MaxDistance;
		lineseg.Set(*Intersection->RayLocation, end);

		RayCollisionTestClass ray(lineseg, &castresult);
		ray.CollisionType = COLL_TYPE_ALL;

		if (Cast_Ray(ray)) {
			lineseg.Compute_Point(ray.Result->Fraction, &(Final_Result->Intersection));
			Final_Result->Intersects = true;
			Final_Result->IntersectionType = IntersectionResultClass::GENERIC;
			if (Intersection->IntersectionNormal)
				*Intersection->IntersectionNormal = castresult.Normal;
			Final_Result->IntersectedRenderObject = this;
			Final_Result->ModelMatrix = Transform;
			return true;
		}
	}
	Final_Result->Intersects = false;
	return false;
}
