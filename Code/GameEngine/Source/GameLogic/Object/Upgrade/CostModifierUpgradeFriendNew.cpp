// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CostModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002502DE, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5A06. Class identity is the
// "CostModifierUpgrade" literal ModuleFactory registers alongside this stub and the
// CostModifierUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CostModifierUpgrade
{
public:
	CostModifierUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@CostModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CostModifierUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CostModifierUpgrade(thing, moduleData));
}
