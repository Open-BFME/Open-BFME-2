// cl: /DNDEBUG /MD
//
// ?xfer@ProductionQueueHordeContain@@MAEXPAVXfer@@@Z, retail 0x0048127E, 54 bytes.
// Slot 3 of the ProductionQueueHordeContain vftable (slot 0 the rowed ??_G
// 0x00481397, slot 4 the rowed pool-name key 0x004812B9). Light-CRC
// early-out, Version(1,1) through Xfer slot 0x28, then the
// HordeGarrisonContain::xfer 0x00479D28. No members of its own.

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

class HordeGarrisonContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
};

class ProductionQueueHordeContain : public HordeGarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@ProductionQueueHordeContain@@MAEXPAVXfer@@@Z @0x0048127E
void ProductionQueueHordeContain::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	HordeGarrisonContain::xfer(xfer);
}
