// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeWorkerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E560, 59 bytes. Dedicated TU: retail news 0x3F8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x49AD15. Class identity is the
// "HordeWorkerAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeWorkerAIUpdate
{
public:
	HordeWorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3F8];
};

// ?friend_newModuleInstance@HordeWorkerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeWorkerAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeWorkerAIUpdate(thing, moduleData));
}
