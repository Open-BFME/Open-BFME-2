// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@UnpauseSpecialPowerUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250156, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B548C. Class identity is the
// "UnpauseSpecialPowerUpgrade" literal ModuleFactory registers alongside this stub and the
// UnpauseSpecialPowerUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class UnpauseSpecialPowerUpgrade
{
public:
	UnpauseSpecialPowerUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@UnpauseSpecialPowerUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UnpauseSpecialPowerUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UnpauseSpecialPowerUpgrade(thing, moduleData));
}
