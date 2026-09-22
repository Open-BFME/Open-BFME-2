// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SubObjectsUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002500E6, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B4D63. Class identity is the
// "SubObjectsUpgrade" literal ModuleFactory registers alongside this stub and the
// SubObjectsUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SubObjectsUpgrade
{
public:
	SubObjectsUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@SubObjectsUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SubObjectsUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SubObjectsUpgrade(thing, moduleData));
}
