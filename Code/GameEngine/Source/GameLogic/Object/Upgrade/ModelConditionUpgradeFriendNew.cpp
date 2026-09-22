// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ModelConditionUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025050E, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B64E5. Class identity is the
// "ModelConditionUpgrade" literal ModuleFactory registers alongside this stub and the
// ModelConditionUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ModelConditionUpgrade
{
public:
	ModelConditionUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@ModelConditionUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ModelConditionUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ModelConditionUpgrade(thing, moduleData));
}
