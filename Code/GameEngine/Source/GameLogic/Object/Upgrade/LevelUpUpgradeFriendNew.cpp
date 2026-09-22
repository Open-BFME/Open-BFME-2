// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LevelUpUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FEFB, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B3DC8. Class identity is the
// "LevelUpUpgrade" literal ModuleFactory registers alongside this stub and the
// LevelUpUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LevelUpUpgrade
{
public:
	LevelUpUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@LevelUpUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LevelUpUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LevelUpUpgrade(thing, moduleData));
}
