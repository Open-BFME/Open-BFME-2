// cl: /MD
//
// ?xfer@RebuildHoleExposeDie@@MAEXPAVXfer@@@Z retail 0x004866F3 44 bytes.
// Virtual slot 3 of RebuildHoleExposeDie (DieModule family) doing Version
// 1 1 via Xfer slot 0x28 then rowed base Rva004CE56D xfer. Evidence is
// vslot 3 plus ZH BFME1 donor version-first plus rowed base 0x004CE56D.

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004CE56D
{
public:
	virtual void b0();
	virtual void b1();
	virtual void b2();
	void xfer(Xfer *xfer);
};

// The TU's RebuildHoleExposeDie derives from DieModule; the rowed base xfer
// is reached through Rva004CE56D at the same this.
class RebuildHoleExposeDie
{
protected:
	virtual void xfer(Xfer *xfer);
};

void RebuildHoleExposeDie::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	((Rva004CE56D *)this)->xfer(xfer);
}
