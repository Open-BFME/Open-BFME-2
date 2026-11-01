// cl: /DNDEBUG /MD
//
// ?xfer@HorseHordeContain@@MAEXPAVXfer@@@Z, retail 0x004766C8, 27 bytes.
// Slot 3 of the vftable 0x00C45C38 whose slot-2 name getter returns
// "HorseHordeContain" (the rowed dtor 0x00476653 installs it). Version1 then
// the pinned HordeContain::xfer 0x00474EA8. No members of its own.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

class HordeContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
};

class HorseHordeContain : public HordeContain
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@HorseHordeContain@@MAEXPAVXfer@@@Z @0x004766C8
void HorseHordeContain::xfer(Xfer *xfer)
{
	xfer->Version1();
	HordeContain::xfer(xfer);
}
