// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GettingBuiltBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024A99D, 56 bytes. Dedicated TU: retail news 0x44 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4542FA. Class identity is the
// "GettingBuiltBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GettingBuiltBehavior
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x44];
};

// ?friend_newModuleInstance@GettingBuiltBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GettingBuiltBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GettingBuiltBehavior(thing, moduleData));
}
