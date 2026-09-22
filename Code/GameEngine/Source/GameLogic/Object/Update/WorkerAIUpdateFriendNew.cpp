// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WorkerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F2B4, 59 bytes. Dedicated TU: retail news 0x4D0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4AA3AB. Class identity is the
// "WorkerAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WorkerAIUpdate
{
public:
	WorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4D0];
};

// ?friend_newModuleInstance@WorkerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WorkerAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WorkerAIUpdate(thing, moduleData));
}
