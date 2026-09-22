// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireWeaponWhenDamagedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C2F5, 56 bytes. Dedicated TU: retail news 0x4C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x482803. Class identity is the
// "FireWeaponWhenDamagedBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FireWeaponWhenDamagedBehavior
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4C];
};

// ?friend_newModuleInstance@FireWeaponWhenDamagedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireWeaponWhenDamagedBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireWeaponWhenDamagedBehavior(thing, moduleData));
}
