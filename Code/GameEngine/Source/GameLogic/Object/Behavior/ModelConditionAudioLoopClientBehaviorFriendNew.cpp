// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ModelConditionAudioLoopClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252D62, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4CBECA. Class identity is the
// "ModelConditionAudioLoopClientBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ModelConditionAudioLoopClientBehavior
{
public:
	ModelConditionAudioLoopClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@ModelConditionAudioLoopClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ModelConditionAudioLoopClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ModelConditionAudioLoopClientBehavior(thing, moduleData));
}
