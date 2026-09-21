// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OathbreakersFadeAwayBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025095E, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8) and
// runs the rowed behavior ctor (0x4B8A8A, UpdateModule base plus secondaries
// plus fading flag plus 1.0f fade timer) with the Thing plus ModuleData args.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// DestroyEnvironmentUpdateFriendNew.cpp. Class identity is the
// OathbreakersFadeAwayBehavior retail cluster (pool key rowed at 0x4B8A02,
// name getter at 0x4B8A22, ModuleData pair rowed at 0x4B8A79/0x254936).

class Thing;
class ModuleData;
class Module;

class OathbreakersFadeAwayBehavior
{
public:
	OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@OathbreakersFadeAwayBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OathbreakersFadeAwayBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OathbreakersFadeAwayBehavior(thing, moduleData));
}
