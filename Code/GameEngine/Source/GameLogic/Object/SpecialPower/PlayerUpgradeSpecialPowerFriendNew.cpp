// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PlayerUpgradeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252503, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C7C03. Class identity is the
// "PlayerUpgradeSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PlayerUpgradeSpecialPower
{
public:
	PlayerUpgradeSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@PlayerUpgradeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PlayerUpgradeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PlayerUpgradeSpecialPower(thing, moduleData));
}
