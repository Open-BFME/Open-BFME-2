// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RandomSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252D2A, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4CBC2B. Class identity is the
// "RandomSoundSelectorClientBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RandomSoundSelectorClientBehavior
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@RandomSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RandomSoundSelectorClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RandomSoundSelectorClientBehavior(thing, moduleData));
}
