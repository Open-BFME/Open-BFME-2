// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StopSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025227D, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C676C. Class identity is the
// "StopSpecialPower" literal ModuleFactory registers alongside this stub and the
// StopSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StopSpecialPower
{
public:
	StopSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@StopSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StopSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StopSpecialPower(thing, moduleData));
}
