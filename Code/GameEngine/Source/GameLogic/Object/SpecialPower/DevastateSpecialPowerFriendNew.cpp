// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DevastateSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025261B, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C81E3. Class identity is the
// "DevastateSpecialPower" literal ModuleFactory registers alongside this stub and the
// DevastateSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DevastateSpecialPower
{
public:
	DevastateSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@DevastateSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DevastateSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DevastateSpecialPower(thing, moduleData));
}
