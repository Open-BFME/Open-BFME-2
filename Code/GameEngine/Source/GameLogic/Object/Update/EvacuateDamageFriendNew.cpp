// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@EvacuateDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "EvacuateDamage"
// (addModule pairs the name with it). news 0x18 and runs the declared-only
// module ctor, pinned at 0x004BAE1D.

class Thing;
class ModuleData;
class Module;

class EvacuateDamage
{
public:
	EvacuateDamage(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@EvacuateDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EvacuateDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EvacuateDamage(thing, moduleData));
}
