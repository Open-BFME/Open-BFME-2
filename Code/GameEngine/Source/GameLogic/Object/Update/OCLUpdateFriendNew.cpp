// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "TeleportToCasterSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed OCLUpdate.
//
// ?friend_newModuleInstance@TeleportToCasterSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x00253057, 59 bytes. Dedicated TU: the rowed ctor TU
// OCLUpdateCtor.cpp proves the class news 0x88 (opaque 0x88-byte base, no
// trailing members, factory stub order). TU-local 0x88-byte class plus the
// declared-only ctor (rowed at 0x4CD3A4) reproduces the factory stub; operator
// new and __EH_prolog resolve via their rows. Recipe:
// DozerAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TeleportToCasterSpecialPower
{
public:
	TeleportToCasterSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@TeleportToCasterSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TeleportToCasterSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TeleportToCasterSpecialPower(thing, moduleData));
}
