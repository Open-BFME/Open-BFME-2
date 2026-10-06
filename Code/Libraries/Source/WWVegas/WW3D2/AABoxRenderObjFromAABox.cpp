// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ??0AABoxRenderObjClass@@QAE@ABVAABoxClass@@@Z @ 0x00175CD0 (262B).
// Dedicated TU: boxrobj.cpp cannot take another row. BFME1 twin is 147B via
// set_aabox_ctor_position helper; BFME2 retail (262B) inlines Set_Position +
// update, so both are defined in-TU (proven OBBox/AABox-def pattern).
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

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"
#include "boxrobj.h"

// ?Set_Position@AABoxRenderObjClass@@UAEXABVVector3@@@Z is rowed in boxrobj.cpp
// (0x00175780) and ?update_cached_box@AABoxRenderObjClass@@MAEXXZ in
// AABoxUpdateCachedBox.cpp (0x001757A0), but this TU's ctor row inlines their
// bodies, so they stay defined here as inline (select-any) copies instead of
// strong duplicates; the owners get LINK-OWNER items at the next census.
inline void AABoxRenderObjClass::Set_Position(const Vector3 & v)
{
	RenderObjClass::Set_Position(v);
	update_cached_box();
}

inline void AABoxRenderObjClass::update_cached_box(void)
{
	CachedBox.Center = Transform.Get_Translation() + ObjSpaceCenter;
	CachedBox.Extent = ObjSpaceExtent;
}

// ??0AABoxRenderObjClass@@QAE@ABVAABoxClass@@@Z
AABoxRenderObjClass::AABoxRenderObjClass(const AABoxClass & box)
{
	ObjSpaceCenter.Set(0, 0, 0);
	ObjSpaceExtent.Set(box.Extent);
	Set_Position(box.Center);
	update_cached_box();
}
