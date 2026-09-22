// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GiveOrRestoreUpgradeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252FC8, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4CD0DC. Class identity is the
// "GiveOrRestoreUpgradeSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GiveOrRestoreUpgradeSpecialPower
{
public:
	GiveOrRestoreUpgradeSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@GiveOrRestoreUpgradeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiveOrRestoreUpgradeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GiveOrRestoreUpgradeSpecialPower(thing, moduleData));
}
