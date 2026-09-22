// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@UntamedAllegianceSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025247A, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C7B06. Class identity is the
// "UntamedAllegianceSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class UntamedAllegianceSpecialPower
{
public:
	UntamedAllegianceSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@UntamedAllegianceSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UntamedAllegianceSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UntamedAllegianceSpecialPower(thing, moduleData));
}
