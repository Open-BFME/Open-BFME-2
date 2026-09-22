// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpawnedModelConditionCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025496D, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x250A1F. Class identity is the
// "SpawnedModelConditionCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpawnedModelConditionCreate
{
public:
	SpawnedModelConditionCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@SpawnedModelConditionCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnedModelConditionCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpawnedModelConditionCreate(thing, moduleData));
}
