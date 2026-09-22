// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LargeGroupAudioUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F327, 59 bytes. Dedicated TU: retail news 0x94 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4AB811. Class identity is the
// "LargeGroupAudioUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LargeGroupAudioUpdate
{
public:
	LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x94];
};

// ?friend_newModuleInstance@LargeGroupAudioUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LargeGroupAudioUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LargeGroupAudioUpdate(thing, moduleData));
}
