// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GiveUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E7C5, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x49C3AC. Class identity is the
// "GiveUpgradeUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GiveUpgradeUpdate
{
public:
	GiveUpgradeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@GiveUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiveUpgradeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GiveUpgradeUpdate(thing, moduleData));
}
