// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Destructor and scalar deleting destructor of an unidentified class with
// vtable 0x00C61DC4: one string member at +4, then an empty base whose vtable
// is 0x00BBB554. These bodies were first claimed as AttackNugget's, but the
// real AttackNugget (built by AttackNugget::parse) uses vtable 0x00BE0FF4 and
// a different member, so the class stays address-named until identified.
//
// ?DoXfer@Rva004E1B72@@UAEXAAVXfer@@@Z retail 0x004E1355 61B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61DC4 (class of rowed ??1Rva004E1B72@@UAE@XZ).
// Snapshot order is dtor plus LoadPostProcess plus GetSnapshotName plus DoXfer
// per LivingWorldRegionConnectionDtor; slot 1 is the shared empty ret at
// 0x000B3FD0 and slot 2 is the rowed string getter at 0x004E1392 returning
// SetPlayerControlOfArmy. Body is Version 1 1 via Xfer slot 0x28 then
// AsciiString at +0x04 via Xfer slot 0x6C then bool at +0x08 via Xfer slot
// 0x90. Xfer declaration mirrors GpuDrawModuleInfoDoXfer for retail vtable
// 0x00BBB910. Layout is AsciiString at +4 plus bool at +8.

// Fold-shared string member teardown (never defined; resolves through the
// symbols.csv pin at 0x00036410).
#include "Rva004E1B72.h"

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

Rva004E1B72::~Rva004E1B72()
{
}

void Rva004E1B72::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_bool08;
}

// C61DC4 slots 1 and 2 point to B3FD0 and 4E1392 respectively.
void Rva004E1B72::LoadPostProcess() {}
const char *Rva004E1B72::GetSnapshotName()
{
 return "SetPlayerControlOfArmy";
}
