// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MoneyCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251183, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8) and
// runs the rowed behavior ctor (0x004BC93F, CrateCollide base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the MoneyCrate retail
// cluster (pool key rowed at 0x004BC988, behavior ctor rowed at 0x004BC93F
// as the sole callee here).
class Thing;
class ModuleData;
class Module;

class MoneyCrateCollide
{
public:
	MoneyCrateCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@MoneyCrateCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MoneyCrateCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MoneyCrateCollide(thing, moduleData));
}
