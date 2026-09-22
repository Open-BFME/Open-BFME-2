// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BuildableHeroListUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025087E, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B8332. Class identity is the
// "BuildableHeroListUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BuildableHeroListUpgrade
{
public:
	BuildableHeroListUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@BuildableHeroListUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BuildableHeroListUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BuildableHeroListUpgrade(thing, moduleData));
}
