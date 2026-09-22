// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RadarUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E9A1, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A0C72. Class identity is the
// "RadarUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RadarUpdate
{
public:
	RadarUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@RadarUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RadarUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RadarUpdate(thing, moduleData));
}
