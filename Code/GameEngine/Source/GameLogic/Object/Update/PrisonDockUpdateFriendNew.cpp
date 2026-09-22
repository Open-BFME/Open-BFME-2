// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "TemporarilyDefectUpdate" (addModule pairs
// the name with its factories); formerly misnamed PrisonDockUpdate.
//
// ?friend_newModuleInstance@TemporarilyDefectUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x00252E72, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8; the
// rowed ctor TU PrisonDockUpdateCtor.cpp builds the UpdateModule-direct layout).
// TU-local 0x30-byte class plus the declared-only ctor (rowed at 0x4CC6AF)
// reproduces the factory stub; operator new and __EH_prolog resolve via their
// rows. Recipe: PointDefenseLaserUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TemporarilyDefectUpdate
{
public:
	TemporarilyDefectUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@TemporarilyDefectUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TemporarilyDefectUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TemporarilyDefectUpdate(thing, moduleData));
}
