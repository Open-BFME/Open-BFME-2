// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DefaultProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CC84, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x487FC7. Class identity is the
// "DefaultProductionExitUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DefaultProductionExitUpdate
{
public:
	DefaultProductionExitUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@DefaultProductionExitUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DefaultProductionExitUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DefaultProductionExitUpdate(thing, moduleData));
}
