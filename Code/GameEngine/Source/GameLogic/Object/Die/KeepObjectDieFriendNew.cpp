// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@KeepObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CBD9, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x486D73. Class identity is the
// "KeepObjectDie" literal ModuleFactory registers alongside this stub and the
// KeepObjectDieModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class KeepObjectDie
{
public:
	KeepObjectDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@KeepObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *KeepObjectDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new KeepObjectDie(thing, moduleData));
}
