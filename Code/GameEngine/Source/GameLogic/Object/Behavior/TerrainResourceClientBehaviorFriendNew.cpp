// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TerrainResourceClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00254C56, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x252DEB. Class identity is the
// "TerrainResourceClientBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TerrainResourceClientBehavior
{
public:
	TerrainResourceClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@TerrainResourceClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TerrainResourceClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TerrainResourceClientBehavior(thing, moduleData));
}
