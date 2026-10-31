// cl: /MD
// ?xfer@Rva00485BB8@@QAEXPAVXfer@@@Z, retail 0x00485BB8 28B: Version1 via rowed 0x000053EE then uint at +0x00 via Xfer slot 0x78.
// Evidence: called with this+0x14 from 0x00485BD4 (version-gated) plus second caller 0x004B4B97; callee rowed 0x000053EE;
// class unproven so honest Rva name.
class AsciiString;
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

class Rva00485BB8
{
public:
	void xfer(Xfer *xfer);
	unsigned int m_00; // +0x00
};

void Rva00485BB8::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_00;
}
