// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TerrainResourceBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C26C, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48209B. Class identity is the
// "TerrainResourceBehavior" literal ModuleFactory registers alongside this stub and the
// TerrainResourceBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TerrainResourceBehavior
{
public:
	TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@TerrainResourceBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TerrainResourceBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TerrainResourceBehavior(thing, moduleData));
}
