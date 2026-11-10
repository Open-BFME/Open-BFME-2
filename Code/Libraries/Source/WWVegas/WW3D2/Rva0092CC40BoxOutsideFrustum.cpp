// cl: /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep /arch:SSE /G7
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/Rva0092CC40BoxOutsideFrustum.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.

// Retail 0x0092CC40 (180 bytes): a frustum-versus-AABox rejection test built
// from the WWMath plane pieces.  For each of the six frustum planes it takes
// the box corner farthest against the plane normal (get_far_extent, then
// Vector3::Subtract from the centre in place -- the aliasing out-pointer is
// what keeps x and y on the stack) and reports the box outside as soon as
// that corner is on the plane's positive side.  Nothing calls it directly
// and no table points at it; the name is the address's.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "colmath.h"
// The out-of-line Overlap_Test(PlaneClass, Vector3) this unit emits must be
// retail's size-optimized body (row 0x0007B638), so its header is read under /Os.
#pragma optimize("s", on)
#include "colmathplane.h"
#pragma optimize("", on)
#include "colmathinlines.h"
#include "frustum.h"
#include "aabox.h"

bool Rva0092CC40BoxOutsideFrustum(const FrustumClass & frustum,const AABoxClass & box)
{
	for (int i = 0; i < 6; i++) {
		Vector3 negfarpt;
		get_far_extent(frustum.Planes[i].N,box.Extent,&negfarpt);
		Vector3::Subtract(box.Center,negfarpt,&negfarpt);
		if (CollisionMath::Overlap_Test(frustum.Planes[i],negfarpt) == CollisionMath::POS) {
			return true;
		}
	}
	return false;
}
