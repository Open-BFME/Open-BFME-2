// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpawnPointProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ECEC, 59 bytes. Dedicated TU: retail news 0xF4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A3C1B. Class identity is the
// "SpawnPointProductionExitUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpawnPointProductionExitUpdate
{
public:
	SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xF4];
};

// ?friend_newModuleInstance@SpawnPointProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnPointProductionExitUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpawnPointProductionExitUpdate(thing, moduleData));
}
