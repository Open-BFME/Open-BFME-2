// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CashHackSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025191F, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C2626. Class identity is the
// "CashHackSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CashHackSpecialPower
{
public:
	CashHackSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@CashHackSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CashHackSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CashHackSpecialPower(thing, moduleData));
}
