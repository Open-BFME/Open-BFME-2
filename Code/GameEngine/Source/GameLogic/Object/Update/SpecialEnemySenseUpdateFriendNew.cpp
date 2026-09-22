// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpecialEnemySenseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E47D, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x499FA9. Class identity is the
// "SpecialEnemySenseUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpecialEnemySenseUpdate
{
public:
	SpecialEnemySenseUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@SpecialEnemySenseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialEnemySenseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpecialEnemySenseUpdate(thing, moduleData));
}
