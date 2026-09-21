// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ShroudCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002511BB, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8) and
// runs the rowed behavior ctor (0x004BCADD, CrateCollide base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the ShroudCrate retail
// cluster (pool key rowed at 0x004BCBB2, behavior ctor rowed at 0x004BCADD
// as the sole callee here).
class Thing;
class ModuleData;
class Module;

class ShroudCrateCollide
{
public:
	ShroudCrateCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@ShroudCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ShroudCrateCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ShroudCrateCollide(thing, moduleData));
}
