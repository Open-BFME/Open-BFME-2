// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AnimalAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BE95, 59 bytes. Dedicated TU: retail news 0x3FC (push-imm32)
// and runs the pinned behavior ctor (0x0047ECA8, six-vtable installs over the
// Transport-family base with double-store at +0x3E4 plus zeros plus floats)
// with the Thing plus ModuleData args. Operator new and __EH_prolog resolve
// via their rows. The TU-local class keeps only size (0x3FC). Recipe:
// AssaultTransportAIUpdateFriendNew.cpp. Class identity is the AnimalAIUpdate
// retail cluster (pool key 0x47EC1A rowed plus ModuleData triple rowed at
// 0x24BE7A/0x24BE43/0x24BED0); the ctor has a single raw caller (this factory).

class Thing;
class ModuleData;
class Module;

class AnimalAIUpdate
{
public:
	AnimalAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3FC];
};

// ?friend_newModuleInstance@AnimalAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnimalAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AnimalAIUpdate(thing, moduleData));
}
