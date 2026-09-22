// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "EvacuateGarrisonSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SupplyCenterDockUpdate.
//
// ?friend_newModuleInstance@EvacuateGarrisonSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x00253175, 59 bytes. Dedicated TU: the ZH header sizes the class at
// 0x84 but retail news 0x88 (proven by the rowed ctor TU
// SupplyCenterDockUpdateCtor.cpp: opaque 0x88-byte base, factory stub order).
// TU-local 0x88-byte class plus the declared-only ctor (rowed at 0x4CDBFC)
// reproduces the factory stub; operator new and __EH_prolog resolve via their
// rows. Recipe: DozerAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class EvacuateGarrisonSpecialPower
{
public:
	EvacuateGarrisonSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@EvacuateGarrisonSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EvacuateGarrisonSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EvacuateGarrisonSpecialPower(thing, moduleData));
}
