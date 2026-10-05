// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WeaponBonusUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002501E2, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the rowed (Thing*,ModuleData*) ctor at 0x4B5633. Class identity is the
// "WeaponBonusUpgrade" literal ModuleFactory registers alongside this stub
// (twice: 0x0025A839 and 0x0025A8A9, both with data factory 0x00254DB3).
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WeaponBonusUpgrade
{
public:
	WeaponBonusUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@WeaponBonusUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *WeaponBonusUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WeaponBonusUpgrade(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitWeaponBonusUpgradeFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitWeaponBonusUpgradeFriendNew(Thing *thing, const ModuleData *moduleData)
{
	WeaponBonusUpgrade::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
