// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LockWeaponCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250996, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B8C0E. Class identity is the
// "LockWeaponCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LockWeaponCreate
{
public:
	LockWeaponCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@LockWeaponCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LockWeaponCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LockWeaponCreate(thing, moduleData));
}
