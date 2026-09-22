// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@InvisibilitySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251893, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C23A4. Class identity is the
// "InvisibilitySpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class InvisibilitySpecialPower
{
public:
	InvisibilitySpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@InvisibilitySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *InvisibilitySpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new InvisibilitySpecialPower(thing, moduleData));
}
