// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CombineHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002527B9, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C87C4. Class identity is the
// "CombineHordeSpecialPower" literal ModuleFactory registers alongside this stub and the
// CombineHordeSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CombineHordeSpecialPower
{
public:
	CombineHordeSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@CombineHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CombineHordeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CombineHordeSpecialPower(thing, moduleData));
}
