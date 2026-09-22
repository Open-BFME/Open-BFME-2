// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyCenterProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EE3F, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A65AE. Class identity is the
// "SupplyCenterProductionExitUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyCenterProductionExitUpdate
{
public:
	SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@SupplyCenterProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyCenterProductionExitUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyCenterProductionExitUpdate(thing, moduleData));
}
