// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MaxHealthUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250482, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B630A. Class identity is the
// "MaxHealthUpgrade" literal ModuleFactory registers alongside this stub and the
// MaxHealthUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class MaxHealthUpgrade
{
public:
	MaxHealthUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@MaxHealthUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MaxHealthUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MaxHealthUpgrade(thing, moduleData));
}
