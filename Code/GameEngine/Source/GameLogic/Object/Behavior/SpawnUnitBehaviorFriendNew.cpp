// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpawnUnitBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250926, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B87E3. Class identity is the
// "SpawnUnitBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpawnUnitBehavior
{
public:
	SpawnUnitBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@SpawnUnitBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnUnitBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpawnUnitBehavior(thing, moduleData));
}
