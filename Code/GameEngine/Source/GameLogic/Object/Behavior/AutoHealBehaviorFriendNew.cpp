// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AutoHealBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024A8DC, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x452592. Class identity is the
// "AutoHealBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AutoHealBehavior
{
public:
	AutoHealBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@AutoHealBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoHealBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AutoHealBehavior(thing, moduleData));
}
