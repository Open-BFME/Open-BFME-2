// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PhysicsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "PhysicsBehavior"
// (addModule pairs the name with it). news 0x68 and runs the declared-only
// module ctor, pinned at 0x003907A6.

#include "../../../../Include/GameLogic/Module/PhysicsBehavior.h"

// ?friend_newModuleInstance@PhysicsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PhysicsBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PhysicsBehavior(thing, moduleData));
}
