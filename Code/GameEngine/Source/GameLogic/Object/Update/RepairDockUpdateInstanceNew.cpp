// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RepairDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EA65, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A118B. Class identity is the
// "RepairDockUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RepairDockUpdate
{
public:
	RepairDockUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@RepairDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RepairDockUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RepairDockUpdate(thing, moduleData));
}
