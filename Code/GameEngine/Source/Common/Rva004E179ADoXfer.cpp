// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?DoXfer@Rva004E179A@@UAEXAAVXfer@@@Z retail 0x004E1398 83B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61B78 (class of unrowed dtor ??1 at 0x004E179A
// tearing down AsciiStrings at +0x0C then +0x08 then +0x04 before restoring
// Snapshot base 0x00BBB554). Snapshot order is dtor plus LoadPostProcess plus
// GetSnapshotName plus DoXfer per LivingWorldRegionConnectionDtor; slot 1 is
// the shared empty ret at 0x000B3FD0 and slot 2 is the rowed string getter at
// 0x004E1794 returning SpawnBuilding. Body is Version 1 1 via Xfer slot 0x28
// then AsciiString at +0x04 via Xfer slot 0x6C then AsciiString at +0x08 via
// Xfer slot 0x6C then AsciiString at +0x0C via Xfer slot 0x6C then bool at
// +0x10 via Xfer slot 0x90. Xfer declaration mirrors GpuDrawModuleInfoDoXfer
// for retail vtable 0x00BBB910. Layout is three AsciiStrings at +4/+8/+0x0C
// plus bool at +0x10.

#include "Rva004E179A.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
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
class Snapshot;

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

void Rva004E179A::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_member08;
	xfer == m_member0C;
	xfer == m_bool10;
}
