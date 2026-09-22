// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RepairSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252730, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C86B4. Class identity is the
// "RepairSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RepairSpecialPower
{
public:
	RepairSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@RepairSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RepairSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RepairSpecialPower(thing, moduleData));
}
