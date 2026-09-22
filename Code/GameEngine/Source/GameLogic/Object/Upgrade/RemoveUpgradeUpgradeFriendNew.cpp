// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RemoveUpgradeUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002507F2, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B7FA4. Class identity is the
// "RemoveUpgradeUpgrade" literal ModuleFactory registers alongside this stub and the
// RemoveUpgradeUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RemoveUpgradeUpgrade
{
public:
	RemoveUpgradeUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@RemoveUpgradeUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RemoveUpgradeUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RemoveUpgradeUpgrade(thing, moduleData));
}
