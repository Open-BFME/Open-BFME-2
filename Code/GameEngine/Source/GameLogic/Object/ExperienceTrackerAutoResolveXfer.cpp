// cl: /DNDEBUG /MD
//
// ?xfer@ExperienceTrackerAutoResolve@@MAEXPAVXfer@@@Z, retail 0x005DB074, 27 bytes.
// Slot 3 of the vftable 0x00C766A4 whose slot-2 name getter returns
// "ExperienceTrackerAutoResolve" (slot 0 the rowed ??_GRva005DB100). Version1
// then the base ExperienceTracker::xfer (pinned at 0x0039AFC8, slot 3 of the
// abstract base vftable 0x00C1AD20). No members of its own.

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

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

#include "../../../Include/GameLogic/ExperienceTracker.h"

class ExperienceTrackerAutoResolve : public ExperienceTracker
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@ExperienceTrackerAutoResolve@@MAEXPAVXfer@@@Z @0x005DB074
void ExperienceTrackerAutoResolve::xfer(Xfer *xfer)
{
	xfer->Version1();
	ExperienceTracker::xfer(xfer);
}
