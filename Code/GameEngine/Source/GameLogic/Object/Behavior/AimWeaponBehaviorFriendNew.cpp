// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AimWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B0BF, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45B226. Class identity is the
// "AimWeaponBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AimWeaponBehavior
{
public:
	AimWeaponBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@AimWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AimWeaponBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AimWeaponBehavior(thing, moduleData));
}
