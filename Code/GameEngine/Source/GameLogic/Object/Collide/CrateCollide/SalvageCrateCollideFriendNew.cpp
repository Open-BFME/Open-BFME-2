// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SalvageCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002512B4, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8) and
// runs the rowed behavior ctor (0x004BD1D7, CrateCollide base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// PlayerHealSpecialPowerFriendNew.cpp. Class identity is the SalvageCrate
// retail cluster (pool key rowed at 0x004BD220, name getter rowed at
// 0x004BD201, ctor-thunk rowed at 0x004BD207, behavior ctor rowed at
// 0x004BD1D7 as the sole callee here).
class Thing;
class ModuleData;
class Module;

class SalvageCrateCollide
{
public:
	SalvageCrateCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@SalvageCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SalvageCrateCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SalvageCrateCollide(thing, moduleData));
}
