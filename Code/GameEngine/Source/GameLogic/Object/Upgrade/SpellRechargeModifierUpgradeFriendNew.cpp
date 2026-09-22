// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpellRechargeModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025036A, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5D7D. Class identity is the
// "SpellRechargeModifierUpgrade" literal ModuleFactory registers alongside this stub and the
// SpellRechargeModifierUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpellRechargeModifierUpgrade
{
public:
	SpellRechargeModifierUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@SpellRechargeModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpellRechargeModifierUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpellRechargeModifierUpgrade(thing, moduleData));
}
