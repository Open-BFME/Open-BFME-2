// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@QueueProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E969, 56 bytes. Dedicated TU: retail news 0x44 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A010E. Class identity is the
// "QueueProductionExitUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class QueueProductionExitUpdate
{
public:
	QueueProductionExitUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x44];
};

// ?friend_newModuleInstance@QueueProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *QueueProductionExitUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new QueueProductionExitUpdate(thing, moduleData));
}
