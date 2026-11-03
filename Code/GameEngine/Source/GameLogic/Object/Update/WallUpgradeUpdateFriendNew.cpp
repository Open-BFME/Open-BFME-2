// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WallUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F2EF, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4AB317. Class identity is the
// "WallUpgradeUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../Include/GameLogic/Module/WallUpgradeUpdate.h"

// ?friend_newModuleInstance@WallUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WallUpgradeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WallUpgradeUpdate(thing, moduleData));
}
