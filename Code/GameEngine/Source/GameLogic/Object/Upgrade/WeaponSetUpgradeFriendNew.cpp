// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponSetUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025021A, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5718. Class identity is the
// "WeaponSetUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WeaponSetUpgrade
{
public:
	WeaponSetUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@WeaponSetUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WeaponSetUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponSetUpgrade(thing, moduleData));
}
