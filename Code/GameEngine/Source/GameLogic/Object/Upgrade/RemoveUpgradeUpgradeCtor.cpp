// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// ??0RemoveUpgradeUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B7FA4, 49 bytes.
// RemoveUpgradeUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x18 secondary slots. The rowed name getter at 0x4B7F3D and ModuleData pair
// (proc 0x4B7F82 plus ctor 0x4B7FF1 plus factory 0x25082A) prove the class;
// the rowed instance factory 0x2507F2 is the sole raw caller. Row supersedes
// the ctor pin.

#include "RemoveUpgradeUpgradeView.h"

// The four vptr stores are the compiler's own (DIR32-masked in
// comparison); the body is empty.

// ??0RemoveUpgradeUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B7FA4
RemoveUpgradeUpgrade::RemoveUpgradeUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}
