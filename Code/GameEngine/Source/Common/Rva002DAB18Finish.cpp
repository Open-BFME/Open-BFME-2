// ??0TerrainVisual@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /Ireference/shims/moduledata
//
// ??0TerrainVisual@@QAE@XZ @0x002DAB18 (70B):
// Multiple-inheritance ctor: primary base Snapshot at +0 installs vtable
// 0x00BBB554 in line, secondary base SubsystemInterface at +4 is constructed
// by the pinned base ctor 0x001B4E63 (twin ??0SubsystemInterface@@QAE@XZ),
// then the derived vtables 0x00C03910 at +0 and 0x00C039A0 at +4 and the
// +0x10 member. Caller 0x00091A83.
// Finishing levers vs the banked attempt: the +4 subobject is a real secondary
// base (its ctor is the pinned 0x001B4E63), so the compiler emits the derived
// vptr stores itself; Snapshot's base cleanup arms the EH prologue, which
// puts the ecx restore right after the base call; and the +0x10 member is a
// struct with an inline zeroing ctor so its store is ordered after the vptr
// stores instead of being hoisted above them.
#include "../../Include/GameClient/TerrainVisualClass.h"
TerrainVisual::TerrainVisual()
{
}

// ??1TerrainVisual@@UAE@XZ, retail 0x002DAB6C, 79 bytes.
// Dual-vptr dtor: derived vtables 0x00C03910 at +0 and 0x00C039A0 at +4,
// AsciiString member at +0x10 via shared header (releaseBuffer rowed),
// secondary base via GameEngineDeletingBase dtor, primary Snapshot inline
// vptr restore to its native base table. Evidence: gap packet, callers, prev/next flags.
TerrainVisual::~TerrainVisual()
{
}

class UnicodeString;
class PooledString;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
#include "../../Include/Common/BfmeXfer.h"

// TerrainVisual's own virtuals that its table 0x00C03910 (and the subobject
// table 0x00C039A0) holds: each body is one retail shares with other classes'
// slots (ICF), so each row is an alias of that shared body.
// Primary slot 1 and secondary slots 1/10: the empty body 0x000B3FD0.
void TerrainVisual::loadPostProcess()
{
}

void TerrainVisual::init()
{
}

void TerrainVisual::update()
{
}

// Secondary slot 9 (0x0004F82B): this is the +4 subobject, so the +0x10 name
// is at +0xC; the clear is the rowed releaseBuffer tail call.
void TerrainVisual::reset()
{
	m_filenameString.clear();
}

// Primary slot 3 (0x00306A9B): Version1-only transfer.
void TerrainVisual::xfer(Xfer *xfer)
{
	xfer->Version1();
}

// Primary slot 8 (0x0041BA5C): no terrain to intersect.
bool TerrainVisual::intersectTerrain(Coord3D *, Coord3D *, Coord3D *)
{
	return false;
}
