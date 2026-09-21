// cl: /O1 /DNDEBUG /MD
//
// Chained ModuleData::buildFieldParse procs: each calls its base-class
// buildFieldParse, then registers its own FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Bodies:
// ?buildFieldParse@Rva0044EB54@@SAXAAVMultiIniFieldParse@@@Z, retail
// 0x0044ED95, 11 bytes (field SpecialPowerTemplate; base shared by the
// SpecialAbility family below; attached to the already-pinned Rva0044EB54
// entity, no new class invented);
// ?buildFieldParse@DockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x005896C1, 11 bytes (field NumberApproachPositions; adjacent to
// the ledger-named DockUpdateModuleData ctor pin at 0x5896B0);
// ?buildFieldParse@SpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CD389, 27 bytes (field Radius);
// ?buildFieldParse@SupplyCenterProductionExitUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CD918, 27 bytes (field Radius);
// ?buildFieldParse@SpyVisionUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CCD64, 27 bytes (field TriggerFX);
// ?buildFieldParse@SupplyWarehouseDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A7D3A, 27 bytes (field StartingBoxes; follows a jump-table
// pad, address-taken by its factory at 0x24F02F).
// ?buildFieldParse@DelayedDeathBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C159E, 27 bytes (chained on the pinned RespawnUpdate base proc
// at 0x4C12D0, then table 0x00C5BAE8 holding DelayedDeathTime at +0x6C plus
// ImmortalUntilDeathTime at +0x70 plus InvulnerableFX at +0x74 plus
// DoHealthCheck at +0x78 plus DelayedDeathPrerequisiteUpgrade at +0x7C,
// matching the ctor stores; factory at 0x251622 pushes this proc).
// ?buildFieldParse@DominateEnemySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CC96D, 27 bytes (chained on the rowed Rva0044EB54 base proc at
// 0x44ED95, then table 0x00C5F638 holding DominateRadius at +0xC8 plus
// TriggerFX at +0xCC plus DominatedFX at +0xD0 plus PermanentlyConvert at
// +0xD4 plus AttributeModifierAffects at +0xD8, matching the ctor stores;
// factory at 0x252EE5 pushes this proc; pool key at 0x4CC9DF names the class).
// Provenance: the ZH MAKE_STANDARD_MODULE_DATA_MACRO_ABC macro passes
// clsmd::buildFieldParse to INI::initFromINIMultiProc, and each landed
// friend_newModuleData factory pushes its class proc immediate.

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class Rva0044EB54
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SupplyCenterProductionExitUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SpyVisionUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SupplyWarehouseDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RespawnUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DelayedDeathBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class FreeLifeBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void Rva0044EB54::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C3F7F8), 0);
}

void DockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C702CC), 0);
}

void SpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FAE0), 0);
}

void SupplyCenterProductionExitUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FB9C), 0);
}

void SpyVisionUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F810), 0);
}

void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5370C), 0);
}

void DelayedDeathBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5BAE8), 0);
}

void FreeLifeBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5BD38), 0);
}

class GloriousChargeUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GloriousChargeUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C550C8), 0);
}

class GiveOrRestoreUpgradeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GiveOrRestoreUpgradeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F8C0), 0);
}

int Rva004CE29DGet(void);

class ReplaceSelfUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ReplaceSelfUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58A88), 0);
}

class UnpauseSpecialPowerUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void UnpauseSpecialPowerUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C57EF0), 0);
}

class AttributeModifierAuraUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void AttributeModifierAuraUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x28);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C50DC8), 0);
}

class LevelGrantSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void LevelGrantSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C8D0), 0);
}

class LevelUpUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void LevelUpUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C574AC), 0);
}

class MaxHealthUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void MaxHealthUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C585DC), 0);
}

class TooltipUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void TooltipUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58C38), 0);
}

class ExperienceScalarUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ExperienceScalarUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58524), 0);
}

int Rva004CE52EGet(void);

class UpgradeDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void UpgradeDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0958), 0);
}

class CrushDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CrushDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0868), 0);
}

class SpecialPowerCompletionDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SpecialPowerCompletionDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0928), 0);
}

class RebuildHoleExposeDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RebuildHoleExposeDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4AE00), 0);
}

class DamageFilteredCreateObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void DamageFilteredCreateObjectDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4ABE0), 0);
}

class SupplyCenterDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SupplyCenterDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C51A80), 0);
}

class CommandPointsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CommandPointsUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C590E8), 0);
}

class BaseUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void BaseUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C57208), 0);
}

class AudioLoopUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class GarrisonContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HordeGarrisonContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void AudioLoopUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x14);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 0x124);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58D98), 0);
}

void HordeGarrisonContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	GarrisonContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C46388), 0);
}

class Rva0048C0B4Base
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class OilSpillUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void OilSpillUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0048C0B4Base::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4C2A8), 0);
}

class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void WeaponFireSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEF0A8), 0);
}

class ReplenishUnitsBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ReplenishUnitsBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4A150), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}

class DominateEnemySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void DominateEnemySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F638), 0);
}

class RousingSpeechUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RousingSpeechUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C54F28), 0);
}

class GeometryUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GeometryUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58918), 0);
}

class RadiateFearUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RadiateFearUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x20);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C510B8), 0);
}

class ModelConditionUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ModelConditionUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58730), 0);
}

class Rva0045B5E3Base
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class MissileUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void MissileUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0045B5E3Base::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C53470), 0);
}

class SpawnBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SpawnBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x5C);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 0x2C);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0200), 0);
}

class RubbleRiseUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RubbleRiseUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C52960), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
}

class SubObjectsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SubObjectsUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C57D38), 0);
}
