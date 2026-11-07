// cl: /DNDEBUG /MD /EHsc

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

// The class is DelayedUpgrade.h's, over the canonical UpgradeModule.h (retail's
// table facts are there).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/DelayedUpgrade.h"

DelayedUpgrade::DelayedUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// ?xfer@DelayedUpgrade@@MAEXPAVXfer@@@Z: slot 3 of 0x00C573E4 is 0x004B8710,
// version 1 then UpgradeModule's xfer; retail folds the body with
// ArmorUpgrade::xfer (ArmorUpgradeXfer.cpp).
void DelayedUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpgradeModule::xfer(xfer);
}
