// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireWeaponWhenDeadBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C333, 59 bytes. Dedicated TU: retail news 0xAC (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x482D80. Class identity is the
// "FireWeaponWhenDeadBehavior" literal ModuleFactory registers alongside this stub and the
// FireWeaponWhenDeadBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FireWeaponWhenDeadBehavior
{
public:
	FireWeaponWhenDeadBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xAC];
};

// ?friend_newModuleInstance@FireWeaponWhenDeadBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireWeaponWhenDeadBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireWeaponWhenDeadBehavior(thing, moduleData));
}
