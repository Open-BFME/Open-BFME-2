// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BuildingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AB77, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x456217. Class identity is the
// "BuildingBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BuildingBehavior
{
public:
	BuildingBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@BuildingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BuildingBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BuildingBehavior(thing, moduleData));
}
