// cl: /MD
//
// ?xfer@ReplaceSelfUpgrade@@MAEXPAVXfer@@@Z, retail 0x004B6FF7, 44 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00858B10 (class of rowed ctor
// ??0ReplaceSelfUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z in
// ReplaceSelfUpgradeCtor.cpp): Version(1,1) via Xfer slot 0x28 then base
// UpgradeModule xfer via rowed 0x004CE3F9. Layout is the rowed ctor class
// (UpgradeModule base 0x1C plus pointer at +0x1C not xferred). Identity is
// slot 3 plus the UpgradeModule base call; donor is BFME1 StatusBitsUpgrade
// and ModelConditionUpgrade xfer shape (Version plus base) verbatim.

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

#include "../../../../Include/Common/XferVersion.h"

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

class ReplaceSelfUpgrade : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ReplaceSelfUpgrade::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpgradeModule::xfer(xfer);
}
