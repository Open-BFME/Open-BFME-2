// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SplitHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002526A7, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C8574. Class identity is the
// "SplitHordeSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SplitHordeSpecialPower
{
public:
	SplitHordeSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@SplitHordeSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SplitHordeSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SplitHordeSpecialPower(thing, moduleData));
}
