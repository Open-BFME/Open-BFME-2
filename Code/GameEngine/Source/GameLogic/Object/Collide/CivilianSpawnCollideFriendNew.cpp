// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CivilianSpawnCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002512EC, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8) and
// runs the rowed behavior ctor (0x004BD694, CollideModule base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe: SquishCollideFriendNew.cpp.
// Class identity is the CivilianSpawn retail cluster (behavior ctor rowed at
// 0x004BD694 as the sole callee here).
class Thing;
class ModuleData;
class Module;

class CivilianSpawnCollide
{
public:
	CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@CivilianSpawnCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CivilianSpawnCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CivilianSpawnCollide(thing, moduleData));
}
