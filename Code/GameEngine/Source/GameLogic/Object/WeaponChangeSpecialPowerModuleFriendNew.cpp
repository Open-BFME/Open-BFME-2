// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponChangeSpecialPowerModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251D08, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C3FF8. Class identity is the
// "WeaponChangeSpecialPowerModule" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WeaponChangeSpecialPowerModule
{
public:
	WeaponChangeSpecialPowerModule(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@WeaponChangeSpecialPowerModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponChangeSpecialPowerModule::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponChangeSpecialPowerModule(thing, moduleData));
}
