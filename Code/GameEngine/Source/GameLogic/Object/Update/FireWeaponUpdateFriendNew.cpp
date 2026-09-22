// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireWeaponUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CF1E, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48C0C5. Class identity is the
// "FireWeaponUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FireWeaponUpdate
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@FireWeaponUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireWeaponUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireWeaponUpdate(thing, moduleData));
}
