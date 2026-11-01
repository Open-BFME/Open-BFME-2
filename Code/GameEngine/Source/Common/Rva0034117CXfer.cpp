// cl: /MD
// ?xfer@Rva0034117C@@MAEXPAVXfer@@@Z @0x0034117C 65B: Rva0034117C xfer slot 3.
// Version(1 1) via Xfer slot 0x28 then base Rva0034103B xfer via rowed 0x0034103B then IsLightCRC early-out via slot 0x10 then Snapshot at +0x68 via slot 0x30.
// Precedent Rva0033F33D xfer (Version1 plus Snapshot via slot 0x30) plus Version(1 1) via slot 0x28 shape.
// Chain from 0x0034103B.
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
#include "../../Include/Common/XferVersion.h"
class Rva0034103B
{
public:
	virtual ~Rva0034103B();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad04[0x68 - 0x04];
};
class Rva0034117C : public Rva0034103B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Snapshot *m_68;
};
void Rva0034117C::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva0034103B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == *m_68;
}
