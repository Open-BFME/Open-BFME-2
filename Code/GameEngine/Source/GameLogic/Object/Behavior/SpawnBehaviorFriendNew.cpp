// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpawnBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B405, 56 bytes. Dedicated TU: retail news 0x64 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45F581. Class identity is the
// "SpawnBehavior" literal ModuleFactory registers alongside this stub and the
// SpawnBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpawnBehavior
{
public:
	SpawnBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x64];
};

// ?friend_newModuleInstance@SpawnBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpawnBehavior(thing, moduleData));
}
