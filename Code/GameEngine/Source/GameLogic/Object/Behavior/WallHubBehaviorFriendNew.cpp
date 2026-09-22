// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WallHubBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024A914, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x452E27. Class identity is the
// "WallHubBehavior" literal ModuleFactory registers alongside this stub and the
// WallHubBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WallHubBehavior
{
public:
	WallHubBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@WallHubBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WallHubBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WallHubBehavior(thing, moduleData));
}
