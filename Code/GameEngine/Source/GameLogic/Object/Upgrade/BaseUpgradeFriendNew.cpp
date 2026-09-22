// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BaseUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FDFF, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B371C. Class identity is the
// "BaseUpgrade" literal ModuleFactory registers alongside this stub and the
// BaseUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BaseUpgrade
{
public:
	BaseUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@BaseUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BaseUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BaseUpgrade(thing, moduleData));
}
