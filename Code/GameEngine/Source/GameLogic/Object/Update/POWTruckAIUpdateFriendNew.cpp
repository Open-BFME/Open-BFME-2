// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "UnleashSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed POWTruckAIUpdate.
//
// ?friend_newModuleInstance@UnleashSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x0025323F, 59 bytes. Dedicated TU: the rowed ctor TU
// POWTruckAIUpdateCtor.cpp proves the class news 0x88 (opaque 0x88-byte base,
// distinct +0x20 dummy, factory stub order). TU-local 0x88-byte class plus the
// declared-only ctor (rowed at 0x4CE006) reproduces the factory stub; operator
// new and __EH_prolog resolve via their rows. Recipe:
// DozerAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class UnleashSpecialPower
{
public:
	UnleashSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@UnleashSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UnleashSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UnleashSpecialPower(thing, moduleData));
}
