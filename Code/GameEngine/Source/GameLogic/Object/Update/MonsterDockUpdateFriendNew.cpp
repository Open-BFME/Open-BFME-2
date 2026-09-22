// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MonsterDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EAF1, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A139A. Class identity is the
// "MonsterDockUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class MonsterDockUpdate
{
public:
	MonsterDockUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@MonsterDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MonsterDockUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MonsterDockUpdate(thing, moduleData));
}
