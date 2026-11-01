// cl: /MD
//
// ?rva001F37C4@Rva001F37C4@@QAEXPAVXfer@@@Z, retail 0x001F37C4, 100 bytes.
// Xfer-shaped body: IsLightCRC early-out via Xfer slot 0x10, Version1 via
// rowed 0x000053EE, then four Coord3DBase members at +0x04/+0x10/+0x1C/+0x28
// via Xfer slot 0x60, uint at +0x34 via Xfer slot 0x78, bool at +0x38 via
// Xfer slot 0x90. Called from the 0x001FAA8D xfer with the same this, which
// then xfers its own later members. Owner unknown so honest-address naming;
// Xfer declaration copied verbatim from PoisonedBehaviorXfer.cpp and the
// GiantBirdSlowDeathBehaviorXfer.cpp Coord3DBase layout (slot-3 recipe).

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
class Thing;
class ModuleData;
class Object;

#include "../../Include/Common/BfmeXfer.h"

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva001F37C4
{
public:
	void rva001F37C4(Xfer *xfer);
private:
	unsigned char m_pad00[4];
	Coord3DBase m_04;
	Coord3DBase m_10;
	Coord3DBase m_1C;
	Coord3DBase m_28;
	unsigned int m_34;
	bool m_38;
};

void Rva001F37C4::rva001F37C4(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_04;
	*xfer == m_10;
	*xfer == m_1C;
	*xfer == m_28;
	*xfer == m_34;
	*xfer == m_38;
}
