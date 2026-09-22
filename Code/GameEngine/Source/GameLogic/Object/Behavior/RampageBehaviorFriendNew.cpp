// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RampageBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AD00, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x458B60. Class identity is the
// "RampageBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RampageBehavior
{
public:
	RampageBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@RampageBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RampageBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RampageBehavior(thing, moduleData));
}
