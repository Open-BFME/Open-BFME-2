// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StealthUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EC25, 59 bytes. Dedicated TU: retail news 0x14C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x374B02. Class identity is the
// "StealthUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../Include/GameLogic/Module/StealthUpdate.h"

// ?friend_newModuleInstance@StealthUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StealthUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StealthUpdate(thing, moduleData));
}
