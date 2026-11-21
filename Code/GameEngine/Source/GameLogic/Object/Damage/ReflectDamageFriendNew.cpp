// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ReflectDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250D8A, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4BABB4. Class identity is the
// "ReflectDamage" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

#include "../../../../Include/GameLogic/Module/ReflectDamage.h"

// ?friend_newModuleInstance@ReflectDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReflectDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ReflectDamage(thing, moduleData));
}
