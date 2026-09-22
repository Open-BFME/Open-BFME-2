// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DominateEnemySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252EAA, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4CC988. Class identity is the
// "DominateEnemySpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DominateEnemySpecialPower
{
public:
	DominateEnemySpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@DominateEnemySpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DominateEnemySpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DominateEnemySpecialPower(thing, moduleData));
}
