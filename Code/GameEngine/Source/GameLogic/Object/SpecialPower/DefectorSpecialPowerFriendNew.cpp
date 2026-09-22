// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DefectorSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002519AB, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C298B. Class identity is the
// "DefectorSpecialPower" literal ModuleFactory registers alongside this stub and the
// DefectorSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DefectorSpecialPower
{
public:
	DefectorSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@DefectorSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DefectorSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DefectorSpecialPower(thing, moduleData));
}
