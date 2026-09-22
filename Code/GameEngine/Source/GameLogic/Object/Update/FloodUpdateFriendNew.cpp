// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FloodUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D142, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48E09F. Class identity is the
// "FloodUpdate" literal ModuleFactory registers alongside this stub and the
// FloodUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FloodUpdate
{
public:
	FloodUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@FloodUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FloodUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FloodUpdate(thing, moduleData));
}
