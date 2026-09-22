// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PoisonedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C36E, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x482F7D. Class identity is the
// "PoisonedBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PoisonedBehavior
{
public:
	PoisonedBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@PoisonedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PoisonedBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PoisonedBehavior(thing, moduleData));
}
