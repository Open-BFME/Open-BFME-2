// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@UnitCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025120E, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8) and
// runs the rowed behavior ctor (0x004BCC13, CrateCollide base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the UnitCrate retail
// cluster (pool key rowed at 0x004BCC5C, behavior ctor rowed at 0x004BCC13
// as the sole callee here).
class Thing;
class ModuleData;
class Module;

class UnitCrateCollide
{
public:
	UnitCrateCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@UnitCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UnitCrateCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UnitCrateCollide(thing, moduleData));
}
