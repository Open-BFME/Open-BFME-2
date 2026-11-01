// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?DoXfer@Rva004E1B00@@UAEXAAVXfer@@@Z retail 0x004E1302 58B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61DB4 (class of the native record dtor at 0x004E1B00
// tearing down AsciiStrings at +8 then +4 before restoring Snapshot base
// 0x00BBB554). Snapshot order is dtor plus LoadPostProcess plus
// GetSnapshotName plus DoXfer per LivingWorldRegionConnectionDtor; slot 1 is
// the shared empty ret at 0x000B3FD0 and slot 2 is the rowed string getter at
// 0x004E133C returning MoveArmy. Body is Version 1 1 via Xfer slot 0x28 then
// AsciiString at +0x04 via Xfer slot 0x6C then AsciiString at +0x08 via Xfer
// slot 0x6C. This record owns table C61DB4; the receiver Xfer has its own
// separate39-slot table BBB910 (Common/System/Xfer.cpp). The shared BfmeXfer
// declaration supplies its proven version and AsciiString transfer slots.

#include "ascii_string.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"


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

class Rva004E1B00 : public Snapshot
{
public:
 Rva004E1B00();
 virtual ~Rva004E1B00();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer &xfer);
private:
 AsciiString m_member04;
 AsciiString m_member08;
};


void Rva004E1B00::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_member08;
}
