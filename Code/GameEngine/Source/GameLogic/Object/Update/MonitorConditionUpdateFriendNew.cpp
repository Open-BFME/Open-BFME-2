// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MonitorConditionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D811, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x491633. Class identity is the
// "MonitorConditionUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

#include "../../../../Include/Common/MonitorConditionUpdate.h"

// ?friend_newModuleInstance@MonitorConditionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MonitorConditionUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MonitorConditionUpdate(thing, moduleData));
}
