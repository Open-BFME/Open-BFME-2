// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RadarMarkerClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252AD9, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C9BCD. Class identity is the
// "RadarMarkerClientUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RadarMarkerClientUpdate
{
public:
	RadarMarkerClientUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@RadarMarkerClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RadarMarkerClientUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RadarMarkerClientUpdate(thing, moduleData));
}
