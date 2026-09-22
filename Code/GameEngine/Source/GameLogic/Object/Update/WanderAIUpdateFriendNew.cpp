// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WanderAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F20D, 59 bytes. Dedicated TU: retail news 0x3E4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A931F. Class identity is the
// "WanderAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WanderAIUpdate
{
public:
	WanderAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3E4];
};

// ?friend_newModuleInstance@WanderAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WanderAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WanderAIUpdate(thing, moduleData));
}
