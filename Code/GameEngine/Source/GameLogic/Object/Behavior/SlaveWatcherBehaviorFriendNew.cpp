// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SlaveWatcherBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C625, 59 bytes. Dedicated TU: retail news 0xA4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4845CB. Class identity is the
// "SlaveWatcherBehavior" literal ModuleFactory registers alongside this stub and the
// SlaveWatcherBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SlaveWatcherBehavior
{
public:
	SlaveWatcherBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xA4];
};

// ?friend_newModuleInstance@SlaveWatcherBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlaveWatcherBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SlaveWatcherBehavior(thing, moduleData));
}
