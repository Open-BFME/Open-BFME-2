// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireWeaponCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250FAE, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the rowed behavior ctor (0x004BB79A, CollideModule base plus
// weapon allocation) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the FireWeapon retail
// cluster (pool key rowed at 0x004BB755, behavior ctor rowed at 0x004BB79A
// as the sole callee here).
class Thing;
class ModuleData;
class Module;

class FireWeaponCollide
{
public:
	FireWeaponCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@FireWeaponCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireWeaponCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireWeaponCollide(thing, moduleData));
}
