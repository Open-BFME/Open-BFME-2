// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ScavengerSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251D94, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C4353. Class identity is the
// "ScavengerSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ScavengerSpecialPower
{
public:
	ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@ScavengerSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ScavengerSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ScavengerSpecialPower(thing, moduleData));
}
