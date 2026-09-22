// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponFireSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DB1B, 59 bytes. Dedicated TU: retail news 0x8C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x492708. Class identity is the
// "WeaponFireSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WeaponFireSpecialAbilityUpdate
{
public:
	WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@WeaponFireSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponFireSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponFireSpecialAbilityUpdate(thing, moduleData));
}
