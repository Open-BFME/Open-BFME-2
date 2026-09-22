// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@UpgradeSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00254BF7, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x252CB5. Class identity is the
// "UpgradeSoundSelectorClientBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class UpgradeSoundSelectorClientBehavior
{
public:
	UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@UpgradeSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UpgradeSoundSelectorClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UpgradeSoundSelectorClientBehavior(thing, moduleData));
}
