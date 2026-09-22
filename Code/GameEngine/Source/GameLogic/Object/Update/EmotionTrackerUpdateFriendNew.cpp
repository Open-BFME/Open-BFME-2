// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@EmotionTrackerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FAB5, 59 bytes. Dedicated TU: retail news 0xC8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4B21B9. Class identity is the
// "EmotionTrackerUpdate" literal ModuleFactory registers alongside this stub and the
// EmotionTrackerUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class EmotionTrackerUpdate
{
public:
	EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xC8];
};

// ?friend_newModuleInstance@EmotionTrackerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EmotionTrackerUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EmotionTrackerUpdate(thing, moduleData));
}
