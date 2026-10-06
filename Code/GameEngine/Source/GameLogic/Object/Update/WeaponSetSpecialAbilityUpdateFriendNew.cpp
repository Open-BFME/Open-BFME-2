// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponSetSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DA71, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x492402. Class identity is the
// "WeaponSetSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

// The matched ctor at 0x492402 calls the SpecialAbilityUpdate base at 0x44EF5E;
// the adjacent pool-key body at 0x492459 independently names this module.
#pragma comment(linker, "/alternatename:??0WeaponSetSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva00492402@@QAE@PAVThing@@PBVModuleData@@@Z")

class Thing;
class ModuleData;
class Module;

class WeaponSetSpecialAbilityUpdate
{
public:
	WeaponSetSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@WeaponSetSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponSetSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponSetSpecialAbilityUpdate(thing, moduleData));
}
