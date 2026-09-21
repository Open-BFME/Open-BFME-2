// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SquishCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250FE6, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8) and
// runs the rowed behavior ctor (0x004BB9CF, CollideModule base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the Squish retail
// cluster (behavior ctor rowed at 0x004BB9CF as the sole callee here).
class Thing;
class ModuleData;
class Module;

class SquishCollide
{
public:
	SquishCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@SquishCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SquishCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SquishCollide(thing, moduleData));
}
