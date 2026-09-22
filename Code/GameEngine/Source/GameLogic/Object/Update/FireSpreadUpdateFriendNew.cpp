// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireSpreadUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CE95, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48B769. Class identity is the
// "FireSpreadUpdate" literal ModuleFactory registers alongside this stub and the
// FireSpreadUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FireSpreadUpdate
{
public:
	FireSpreadUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@FireSpreadUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FireSpreadUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireSpreadUpdate(thing, moduleData));
}
