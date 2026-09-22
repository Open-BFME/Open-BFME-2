// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GiantBirdAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D2EF, 59 bytes. Dedicated TU: retail news 0x57C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x36B717. Class identity is the
// "GiantBirdAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GiantBirdAIUpdate
{
public:
	GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x57C];
};

// ?friend_newModuleInstance@GiantBirdAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiantBirdAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GiantBirdAIUpdate(thing, moduleData));
}
