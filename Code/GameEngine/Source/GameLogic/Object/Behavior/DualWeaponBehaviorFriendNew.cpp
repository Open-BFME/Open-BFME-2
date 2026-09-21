// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DualWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B036, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8) and
// runs the rowed behavior ctor (0x45AE55, UpdateModule base plus re-stored
// +0x0C/+0x10 slots plus close-range flag plus switch timer) with the Thing
// plus ModuleData args. Operator new and __EH_prolog resolve via their rows.
// Recipe: OathbreakersFadeAwayBehaviorFriendNew.cpp. Class identity is the
// DualWeaponBehavior retail cluster (pool key rowed at 0x45ADE0, ModuleData
// triple rowed at 0x45AE25/0x45AE44/0x24B06E, behavior ctor rowed at 0x45AE55
// whose sole raw caller is this factory); completes the file-unit.

class Thing;
class ModuleData;
class Module;

class DualWeaponBehavior
{
public:
	DualWeaponBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@DualWeaponBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DualWeaponBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DualWeaponBehavior(thing, moduleData));
}
