// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpecialDisguiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F99D, 59 bytes. Dedicated TU: retail news 0x94 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4B0292. Class identity is the
// "SpecialDisguiseUpdate" literal ModuleFactory registers alongside this stub and the
// SpecialDisguiseUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpecialDisguiseUpdate
{
public:
	SpecialDisguiseUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x94];
};

// ?friend_newModuleInstance@SpecialDisguiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialDisguiseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpecialDisguiseUpdate(thing, moduleData));
}
