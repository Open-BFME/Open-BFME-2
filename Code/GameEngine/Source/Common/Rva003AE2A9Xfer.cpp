// cl: /MD
// ?xfer@Rva003AE2A9@@MAEXPAVXfer@@@Z @0x0056454F 79B.
// Slot 3 (offset 0xC) of vtable 0x0081CAA4, the class of the rowed copy
// ctor ??0Rva003AE2A9@@QAE@ABV0@@Z: its xfer. Version(1,2) local via Xfer
// slot 0x28 (==(Version&)), subobject tail at this+0x10 through the rowed
// 0x00564522, bool at +0xC via slot 0x90 (==(bool&)), and the
// version-minimum-gated bool at +0x20 via slot 0x90. Caller at 0x003ACB6A.
// Xfer declaration copied verbatim from PoisonedBehaviorXfer.cpp (its
// reversed ==-overload layout is what puts Version at 0x28 and bool at
// 0x90); Xfer::Version 2-byte idiom from StancesBehaviorXfer.cpp.

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

#include "../../Include/Common/XferVersion.h"

class Rva00564522
{
public:
	void xfer(Xfer *xfer);
};

class Rva003AE2A9
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad4[8];
	bool m_boolC;
	char m_padD[0x13];
	bool m_bool20;
};

void Rva003AE2A9::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	((Rva00564522 *)((char *)this + 0x10))->xfer(xfer);
	*xfer == m_boolC;
	if (version.m_minimum >= 2)
		*xfer == m_bool20;
}
