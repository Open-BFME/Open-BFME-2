// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E525, 59 bytes. Dedicated TU: retail news 0x3E8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x49A7F3. Class identity is the
// "HordeAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../Include/GameLogic/Module/HordeAIUpdate.h"

// ?friend_newModuleInstance@HordeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeAIUpdate(thing, moduleData));
}
