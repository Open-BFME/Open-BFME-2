// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GiantBirdSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B599, 56 bytes. Dedicated TU: retail news 0x68 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x461E58. Class identity is the
// "GiantBirdSlowDeathBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GiantBirdSlowDeathBehavior
{
public:
	GiantBirdSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x68];
};

// ?friend_newModuleInstance@GiantBirdSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiantBirdSlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GiantBirdSlowDeathBehavior(thing, moduleData));
}
