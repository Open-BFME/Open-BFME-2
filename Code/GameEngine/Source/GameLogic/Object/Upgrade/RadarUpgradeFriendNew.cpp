// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RadarUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250006, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B478E. Class identity is the
// "RadarUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RadarUpgrade
{
public:
	RadarUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@RadarUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RadarUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RadarUpgrade(thing, moduleData));
}
