// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@UpgradeDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CBA1, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x486BBA. Class identity is the
// "UpgradeDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class UpgradeDie
{
public:
	UpgradeDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@UpgradeDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *UpgradeDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new UpgradeDie(thing, moduleData));
}
