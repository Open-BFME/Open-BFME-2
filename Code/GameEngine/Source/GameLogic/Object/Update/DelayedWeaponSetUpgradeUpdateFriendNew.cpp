// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DelayedWeaponSetUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CCBC, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4882E4. Class identity is the
// "DelayedWeaponSetUpgradeUpdate" literal ModuleFactory registers alongside this stub and the
// DelayedWeaponSetUpgradeUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DelayedWeaponSetUpgradeUpdate
{
public:
	DelayedWeaponSetUpgradeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@DelayedWeaponSetUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedWeaponSetUpgradeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DelayedWeaponSetUpgradeUpdate(thing, moduleData));
}
