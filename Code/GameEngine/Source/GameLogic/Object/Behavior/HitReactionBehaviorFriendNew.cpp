// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HitReactionBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AE12, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x459228. Class identity is the
// "HitReactionBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HitReactionBehavior
{
public:
	HitReactionBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@HitReactionBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HitReactionBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HitReactionBehavior(thing, moduleData));
}
