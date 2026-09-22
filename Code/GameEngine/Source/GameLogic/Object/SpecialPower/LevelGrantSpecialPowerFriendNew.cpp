// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LevelGrantSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251A37, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C2B0E. Class identity is the
// "LevelGrantSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LevelGrantSpecialPower
{
public:
	LevelGrantSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@LevelGrantSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LevelGrantSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LevelGrantSpecialPower(thing, moduleData));
}
