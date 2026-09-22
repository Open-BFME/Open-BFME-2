// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TaintSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251EAC, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C4896. Class identity is the
// "TaintSpecialPower" literal ModuleFactory registers alongside this stub and the
// TaintSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TaintSpecialPower
{
public:
	TaintSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@TaintSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TaintSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TaintSpecialPower(thing, moduleData));
}
