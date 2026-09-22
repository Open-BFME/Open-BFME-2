// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ElvenWoodSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251C7C, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C38D5. Class identity is the
// "ElvenWoodSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ElvenWoodSpecialPower
{
public:
	ElvenWoodSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@ElvenWoodSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ElvenWoodSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ElvenWoodSpecialPower(thing, moduleData));
}
