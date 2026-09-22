// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WargBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B443, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x460804. Class identity is the
// "WargBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WargBehavior
{
public:
	WargBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@WargBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WargBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WargBehavior(thing, moduleData));
}
