// cl: /MD
// ?xfer@Rva004DF87C@@QAEXPAVXfer@@@Z, retail 0x004DF87C 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed Rva004DF81B xfer.
// Evidence: vslot 3 of 0x007FBD98 plus 0x007FBDF0 plus 0x007FBE48 plus 0x00861588
// plus rowed callees 0x000053EE and 0x004DF81B; class unproven so honest Rva name.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/Rva004DF81B.h"

class Rva004DF87C {
public:
	void xfer(Xfer *xfer);
};

void Rva004DF87C::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004DF81B *)this)->xfer(xfer);
}
