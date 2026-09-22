// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CloudBreakSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251E20, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C44D8. Class identity is the
// "CloudBreakSpecialPower" literal ModuleFactory registers alongside this stub and the
// CloudBreakSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CloudBreakSpecialPower
{
public:
	CloudBreakSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@CloudBreakSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CloudBreakSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CloudBreakSpecialPower(thing, moduleData));
}
