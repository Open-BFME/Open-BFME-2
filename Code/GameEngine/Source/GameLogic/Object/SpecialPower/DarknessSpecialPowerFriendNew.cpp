// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DarknessSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251FC4, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C4DB9. Class identity is the
// "DarknessSpecialPower" literal ModuleFactory registers alongside this stub and the
// DarknessSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DarknessSpecialPower
{
public:
	DarknessSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@DarknessSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DarknessSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DarknessSpecialPower(thing, moduleData));
}
