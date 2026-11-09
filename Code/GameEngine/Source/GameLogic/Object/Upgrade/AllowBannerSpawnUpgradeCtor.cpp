// cl: /DNDEBUG /MD
//
// ??0AllowBannerSpawnUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B8587, 49 bytes.
// AllowBannerSpawnUpgrade behavior ctor over the canonical UpgradeModule base
// (0x460AEC, thing plus data); the compiler stores the class's four tables over
// its declaration in AllowBannerSpawnUpgrade.h (0x00C59030 at +0, UpgradeModule's
// 0x00C57328 at +0x0C, 0x00C58FE8 at +0x10 and UpgradeModule's 0x00C58790 at
// +0x18). The rowed name getter at 0x4B8520 proves the class; the rowed instance
// factory 0x2508B6 is the sole raw caller.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class Thing;
class ModuleData;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/AllowBannerSpawnUpgrade.h"

// ??0AllowBannerSpawnUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B8587
AllowBannerSpawnUpgrade::AllowBannerSpawnUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}

// ?xfer@AllowBannerSpawnUpgrade@@MAEXPAVXfer@@@Z: slot 3 of 0x00C59030 is 0x004B8710, version 1 then
// UpgradeModule's xfer; retail folds the body with ArmorUpgrade::xfer
// (ArmorUpgradeXfer.cpp).
void AllowBannerSpawnUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpgradeModule::xfer(xfer);
}

// Primary slot 1, retail 0x00497805 (`jmp 0x0058B03E`): the UpgradeModule base call that
// every module-family override without work of its own shares (ICF).
void AllowBannerSpawnUpgrade::loadPostProcess()
{
	UpgradeModule::loadPostProcess();
}
