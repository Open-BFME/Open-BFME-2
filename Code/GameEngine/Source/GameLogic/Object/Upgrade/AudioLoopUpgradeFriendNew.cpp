// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AudioLoopUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250760, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B7CBC. Class identity is the
// "AudioLoopUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AudioLoopUpgrade
{
public:
	AudioLoopUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@AudioLoopUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AudioLoopUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AudioLoopUpgrade(thing, moduleData));
}
