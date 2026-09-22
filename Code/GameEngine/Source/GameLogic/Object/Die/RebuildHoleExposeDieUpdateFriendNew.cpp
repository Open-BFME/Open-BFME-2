// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this module as "RebuildHoleExposeDie" (addModule pairs
// the name with its factories); formerly misnamed RebuildHoleExposeDieUpdate.
//
// ?friend_newModuleInstance@RebuildHoleExposeDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// retail 0x0024CAE0, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the rowed behavior ctor (0x486768, pinned Die base plus vtable
// 0xC4AE54 plus secondaries) with the Thing plus ModuleData args. Operator
// new and __EH_prolog resolve via their rows. Recipe:
// OathbreakersFadeAwayBehaviorFriendNew.cpp. Class identity is the
// RebuildHole retail cluster (ModuleData proc plus ctor plus factory plus
// pool key all rowed, behavior ctor rowed in the companion TU, this
// factory sole-calls it right before the rowed ModuleData factory).

class Thing;
class ModuleData;
class Module;

class RebuildHoleExposeDie
{
public:
	RebuildHoleExposeDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@RebuildHoleExposeDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RebuildHoleExposeDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RebuildHoleExposeDie(thing, moduleData));
}
