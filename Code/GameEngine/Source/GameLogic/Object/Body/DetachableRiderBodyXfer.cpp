// cl: /DNDEBUG /MD
//
// ?xfer@DetachableRiderBody@@MAEXPAVXfer@@@Z, retail 0x004C1D0B, 62 bytes.
// Slot 3 of the vftable 0x00C5C0B8 whose slot-2 name getter returns
// "DetachableRiderBody" (the rowed dtor 0x004C1BAB installs it).
// Version(1,2), the rowed ActiveBody::xfer 0x004BF1E8, then from version 2
// the upgrade mux on the +0x100 subobject (rowed upgradeMuxXfer 0x004CE397).

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

#include "../../../../Include/GameLogic/Module/ActiveBody.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class DetachableRiderBody : public ActiveBody, public UpgradeMux
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@DetachableRiderBody@@MAEXPAVXfer@@@Z @0x004C1D0B
void DetachableRiderBody::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;

	ActiveBody::xfer(xfer);

	if (version.m_minimum >= 2)
		UpgradeMux::upgradeMuxXfer(xfer);
}
