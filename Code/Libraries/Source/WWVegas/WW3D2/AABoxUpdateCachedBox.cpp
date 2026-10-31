// cl: /arch:SSE2 /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?update_cached_box@AABoxRenderObjClass@@MAEXXZ @ 0x001757A0 (112B).
// Dedicated TU: boxrobj.cpp cannot take another row (bulk import left defs
// without rows or markers). Same headers and /arch:SSE2 as the OBBox twin.
// Verbatim BFME1 body.
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
// Reuse the verified particle translation/vector consumer views.
#include "../../../../../reference/shims/bfme_part_emt_inline/vector3.h"
#include "../../../../../reference/shims/bfme_part_emt_inline/matrix3d.h"
#include "rendobj.h"
#include "boxrobj.h"

// matrix3d.h's Matrix3D::Get_Translation() under a unit-local name: called as the
// Matrix3D member, this unit emitted an external copy that differs from the kept
// retail one. Body unchanged (Matrix3D::Get_Translation view, 96f26b7c4d pattern).
class AABoxTranslationView : public Matrix3D
{
public:
	WWINLINE Vector3 Get_Translation(void) const { return Vector3(Row[0][3],Row[1][3],Row[2][3]); }
};

// ?update_cached_box@AABoxRenderObjClass@@MAEXXZ
inline void AABoxRenderObjClass::update_cached_box(void)
{
	CachedBox.Center = ((const AABoxTranslationView &)Transform).Get_Translation() + ObjSpaceCenter;
	CachedBox.Extent = ObjSpaceExtent;
}

namespace BfmeAABoxUpdateCachedBoxAnchor
{
class Access : public AABoxRenderObjClass
{
public:
	static void _bfmeAABoxUpdateCachedBoxInlineAnchor(void *storage);
};
}

// This virtual method is a header inline in copier units. This anchor retains
// its matched row body here, but the anchor itself is not retail code.
#pragma inline_depth(0)
// ?_bfmeAABoxUpdateCachedBoxInlineAnchor@Access@BfmeAABoxUpdateCachedBoxAnchor@@SAXPAX@Z absent-from-retail
void BfmeAABoxUpdateCachedBoxAnchor::Access::_bfmeAABoxUpdateCachedBoxInlineAnchor(void *storage)
{
	((BfmeAABoxUpdateCachedBoxAnchor::Access *)storage)->AABoxRenderObjClass::update_cached_box();
}
#pragma inline_depth()
