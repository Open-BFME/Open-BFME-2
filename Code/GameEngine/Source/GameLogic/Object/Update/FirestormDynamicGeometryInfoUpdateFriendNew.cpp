// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "AnimatedParticleSysBoneClientUpdate" (addModule pairs
// the name with its factories); formerly misnamed FirestormDynamicGeometryInfoUpdate.
//
// ?friend_newModuleInstance@AnimatedParticleSysBoneClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x00252957, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8; the
// rowed ctor TU FirestormDynamicGeometryInfoUpdateCtor.cpp builds the
// opaque-base layout). TU-local 0x10-byte class plus the declared-only ctor
// (rowed at 0x4C8FE8) reproduces the factory stub; operator new and
// __EH_prolog resolve via their rows. Recipe:
// PointDefenseLaserUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AnimatedParticleSysBoneClientUpdate
{
public:
	AnimatedParticleSysBoneClientUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@AnimatedParticleSysBoneClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnimatedParticleSysBoneClientUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AnimatedParticleSysBoneClientUpdate(thing, moduleData));
}
