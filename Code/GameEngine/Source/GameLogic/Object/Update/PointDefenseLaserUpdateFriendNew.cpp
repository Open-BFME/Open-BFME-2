// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "BeaconClientUpdate" (addModule pairs
// the name with its factories); formerly misnamed PointDefenseLaserUpdate.
//
// ?friend_newModuleInstance@BeaconClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x002529C7, 56 bytes. Dedicated TU: the ZH header sizes the class at
// 0x2C but retail news 0x14 (push-imm8; the rowed ctor TU
// PointDefenseLaserUpdateCtor.cpp builds the opaque-base layout whose total
// the factory stub measures at 0x14). TU-local 0x14-byte class plus the
// declared-only ctor (rowed at 0x4C9598) reproduces the factory stub;
// operator new and __EH_prolog resolve via their rows.
// Recipe: DozerAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BeaconClientUpdate
{
public:
	BeaconClientUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@BeaconClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BeaconClientUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BeaconClientUpdate(thing, moduleData));
}
