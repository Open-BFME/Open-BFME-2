// cl: /MD
// ?xfer@GameSpyStagingRoom@@UAEXPAVXfer@@@Z @0x004FDAC7 39B: slot 3 (offset 0x0C)
// of vtable 0x00819440; IsLightCRC guard via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then rowed SkirmishGameInfo::xfer 0x003FFA3C. Evidence: vslot,
// callers none, donor GameSpyStagingRoomCopy layout, PoisonedBehaviorXfer Xfer
// order recipe.
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
class DamageInfo;
#include "../../../Include/Common/BfmeXfer.h"
class SkirmishGameInfo
{
public:
	virtual void xfer(Xfer *xfer);
};
// Declaration-only transfer call view: the retail call at 004FDAE4 targets
// the existing SkirmishGameInfo::xfer row at 003FFA3C. This does not model
// GameSpyStagingRoom's inheritance; its shared header derives from GameInfo.
class GameSpyStagingRoom
{
public:
	virtual void xfer(Xfer *xfer);
};
void GameSpyStagingRoom::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	reinterpret_cast<SkirmishGameInfo *>(this)->SkirmishGameInfo::xfer(xfer);
}
