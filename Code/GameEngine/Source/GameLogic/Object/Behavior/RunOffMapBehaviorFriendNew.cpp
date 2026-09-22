// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RunOffMapBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B6B1, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x46217B. Class identity is the
// "RunOffMapBehavior" literal ModuleFactory registers alongside this stub and the
// RunOffMapBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RunOffMapBehavior
{
public:
	RunOffMapBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@RunOffMapBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RunOffMapBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RunOffMapBehavior(thing, moduleData));
}
