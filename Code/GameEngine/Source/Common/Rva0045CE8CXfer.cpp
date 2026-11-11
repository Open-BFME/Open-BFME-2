// cl: /MD
// ?xfer@Rva0045CE8C@@QAEXPAVXfer@@@Z, retail 0x0045CE8C 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed Rva004CE56D xfer.
// Evidence: vslot 3 of DieModuleDerived vtables (Rva0045CE6D plus 15 siblings incl Rva004851FE/Rva00485425/Rva0048593D)
// plus caller 0x00485BF5; callees rowed 0x000053EE and 0x004CE56D; class unproven so honest Rva name.
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

#include "../../Include/Common/Rva004CE56D.h"

class Rva0045CE8C {
public:
	void xfer(Xfer *xfer);
};

void Rva0045CE8C::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004CE56D *)this)->xfer(xfer);
}
