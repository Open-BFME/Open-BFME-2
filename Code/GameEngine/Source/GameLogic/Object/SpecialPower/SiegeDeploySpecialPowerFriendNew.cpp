// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SiegeDeploySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025216B, 56 bytes. Dedicated TU: retail news 0x74 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C56BA. Class identity is the
// "SiegeDeploySpecialPower" literal ModuleFactory registers alongside this stub and the
// SiegeDeploySpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SiegeDeploySpecialPower
{
public:
	SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x74];
};

// ?friend_newModuleInstance@SiegeDeploySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDeploySpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SiegeDeploySpecialPower(thing, moduleData));
}
