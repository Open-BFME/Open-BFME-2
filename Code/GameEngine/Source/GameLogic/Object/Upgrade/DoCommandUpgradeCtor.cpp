// cl: /DNDEBUG /MD
//
// ??0DoCommandUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B4C2E, 49 bytes.
// DoCommandUpgrade behavior ctor over the canonical UpgradeModule base
// (0x460AEC, thing plus data); the compiler stores the class's four tables
// over its declaration in DoCommandUpgrade.h (0x00C57B58 at +0,
// UpgradeModule's 0x00C57328 at +0x0C, 0x00C57B10 at +0x10 and UpgradeModule's
// 0x00C58790 at +0x18). The rowed name getter at 0x4B4BC7 and ModuleData pair
// (proc 0x4B4C0C plus factory 0x2557B5) prove the class; the rowed instance
// factory 0x2500AE is the sole raw caller.

class Thing;
class ModuleData;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/DoCommandUpgrade.h"

// ??0DoCommandUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B4C2E
DoCommandUpgrade::DoCommandUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}
