// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponModeSpecialPowerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DCE9, 56 bytes. Dedicated TU: retail news 0x3C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x494B38. Class identity is the
// "WeaponModeSpecialPowerUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WeaponModeSpecialPowerUpdate
{
public:
	WeaponModeSpecialPowerUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3C];
};

// ?friend_newModuleInstance@WeaponModeSpecialPowerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponModeSpecialPowerUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponModeSpecialPowerUpdate(thing, moduleData));
}
