// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "ActivateModuleSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed DozerAIUpdate.
//
// ?friend_newModuleInstance@ActivateModuleSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x00253204, 59 bytes. Dedicated TU: the ZH ActivateModuleSpecialPower header sizes
// the class at 0x31C but retail news 0x88 (proven by the rowed ctor TU
// DozerAIUpdateCtor.cpp: opaque 0x88-byte base, no trailing members, factory
// stub order). TU-local 0x88-byte class plus the declared-only ctor (rowed at
// 0x4CDD02) reproduces the factory stub; operator new and __EH_prolog resolve
// via their rows. Pattern: MAKE_STANDARD_MODULE_MACRO newInstance spelling.

class Thing;
class ModuleData;
class Module;

class ActivateModuleSpecialPower
{
public:
	ActivateModuleSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@ActivateModuleSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ActivateModuleSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ActivateModuleSpecialPower(thing, moduleData));
}
