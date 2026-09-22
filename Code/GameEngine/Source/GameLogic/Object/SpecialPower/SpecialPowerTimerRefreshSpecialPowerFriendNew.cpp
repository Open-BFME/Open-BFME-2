// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpecialPowerTimerRefreshSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00254B1E, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x251BDE. Class identity is the
// "SpecialPowerTimerRefreshSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpecialPowerTimerRefreshSpecialPower
{
public:
	SpecialPowerTimerRefreshSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@SpecialPowerTimerRefreshSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialPowerTimerRefreshSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpecialPowerTimerRefreshSpecialPower(thing, moduleData));
}
