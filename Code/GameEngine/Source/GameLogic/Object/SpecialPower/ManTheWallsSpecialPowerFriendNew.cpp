// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ManTheWallsSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252442, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C6F47. Class identity is the
// "ManTheWallsSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ManTheWallsSpecialPower
{
public:
	ManTheWallsSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@ManTheWallsSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ManTheWallsSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ManTheWallsSpecialPower(thing, moduleData));
}
