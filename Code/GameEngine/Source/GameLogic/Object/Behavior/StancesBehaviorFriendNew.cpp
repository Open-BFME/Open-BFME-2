// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StancesBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B37C, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45EF80. Class identity is the
// "StancesBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StancesBehavior
{
public:
	StancesBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@StancesBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StancesBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StancesBehavior(thing, moduleData));
}
