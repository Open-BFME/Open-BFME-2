// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SiegeDeployHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002521F4, 56 bytes. Dedicated TU: retail news 0x4C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C6386. Class identity is the
// "SiegeDeployHordeSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SiegeDeployHordeSpecialPower
{
public:
	SiegeDeployHordeSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4C];
};

// ?friend_newModuleInstance@SiegeDeployHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDeployHordeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SiegeDeployHordeSpecialPower(thing, moduleData));
}
