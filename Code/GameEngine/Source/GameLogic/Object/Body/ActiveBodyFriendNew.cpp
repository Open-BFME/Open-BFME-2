// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ActiveBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002513AD, 59 bytes. Dedicated TU: retail news 0x100 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4BF6A1. Class identity is the
// "ActiveBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../Include/GameLogic/Module/ActiveBody.h"

// ?friend_newModuleInstance@ActiveBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ActiveBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ActiveBody(thing, moduleData));
}
