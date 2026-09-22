// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AutoAbilityBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AFAD, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45A78F. Class identity is the
// "AutoAbilityBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AutoAbilityBehavior
{
public:
	AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@AutoAbilityBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoAbilityBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AutoAbilityBehavior(thing, moduleData));
}
