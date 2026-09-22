// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LaserUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D522, 56 bytes. Dedicated TU: retail news 0x54 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x362EEE. Class identity is the
// "LaserUpdate" literal ModuleFactory registers alongside this stub and the
// LaserUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LaserUpdate
{
public:
	LaserUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x54];
};

// ?friend_newModuleInstance@LaserUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LaserUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LaserUpdate(thing, moduleData));
}
