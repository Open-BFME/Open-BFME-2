// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B264, 56 bytes. Dedicated TU: retail news 0x50 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45D4B4. Class identity is the
// "SlowDeathBehavior" literal ModuleFactory registers alongside this stub and the
// SlowDeathBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SlowDeathBehavior
{
public:
	SlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x50];
};

// ?friend_newModuleInstance@SlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SlowDeathBehavior(thing, moduleData));
}
