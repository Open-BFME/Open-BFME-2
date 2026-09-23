// cl: /O1 /DNDEBUG /MD
//
// Chained ModuleData::buildFieldParse procs: each calls its base-class
// buildFieldParse, then registers its own FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Bodies:
// ?buildFieldParse@Rva0044EB54@@SAXAAVMultiIniFieldParse@@@Z, retail
// 0x0044ED95, 11 bytes (field SpecialPowerTemplate; base shared by the
// SpecialAbility family below; attached to the already-pinned Rva0044EB54
// entity, no new class invented);
// ?buildFieldParse@DockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x005896C1, 11 bytes (field NumberApproachPositions; adjacent to
// the ledger-named DockUpdateModuleData ctor pin at 0x5896B0);
// ?buildFieldParse@TeleportToCasterSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CD389, 27 bytes (field Radius);
// ?buildFieldParse@StoreObjectsSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CD918, 27 bytes (field Radius);
// ?buildFieldParse@CurseSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CCD64, 27 bytes (field TriggerFX);
// ?buildFieldParse@SupplyWarehouseDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004A7D3A, 27 bytes (field StartingBoxes; follows a jump-table
// pad, address-taken by its factory at 0x24F02F).
// ?buildFieldParse@DelayedDeathBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C159E, 27 bytes (chained on the pinned RespawnUpdate base proc
// at 0x4C12D0, then table 0x00C5BAE8 holding DelayedDeathTime at +0x6C plus
// ImmortalUntilDeathTime at +0x70 plus InvulnerableFX at +0x74 plus
// DoHealthCheck at +0x78 plus DelayedDeathPrerequisiteUpgrade at +0x7C,
// matching the ctor stores; factory at 0x251622 pushes this proc).
// ?buildFieldParse@DominateEnemySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CC96D, 27 bytes (chained on the rowed Rva0044EB54 base proc at
// 0x44ED95, then table 0x00C5F638 holding DominateRadius at +0xC8 plus
// TriggerFX at +0xCC plus DominatedFX at +0xD0 plus PermanentlyConvert at
// +0xD4 plus AttributeModifierAffects at +0xD8, matching the ctor stores;
// factory at 0x252EE5 pushes this proc; pool key at 0x4CC9DF names the class).
// ?buildFieldParse@GiveUpgradeUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0049C391, 27 bytes (chained on the rowed Rva0044EB54 base proc at
// 0x44ED95, then table 0x00C511A0 holding GiveUpgradeEffect at +0xD4 plus
// SpawnOutFX at +0xD8 plus FadeOutSpeed at +0xDC plus DeliverUpgrade at +0xE0;
// factory at 0x24E800 pushes this proc; pool key at 0x49C471 names the class).
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

class TeleportToCasterSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class StoreObjectsSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CurseSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SupplyWarehouseDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RespawnBodyModuleData
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

// ?buildFieldParse@Rva0044EB54@@SAXAAVMultiIniFieldParse@@@Z
void Rva0044EB54::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C3F7F8), 0);
}

void DockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C702CC), 0);
}

void TeleportToCasterSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FAE0), 0);
}

void StoreObjectsSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FB9C), 0);
}

void CurseSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
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
	RespawnBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5BAE8), 0);
}

void FreeLifeBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnBodyModuleData::buildFieldParse(parse);
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

class KeepObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@KeepObjectDieModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00253B95 (34 bytes): double-add on the rowed Die getter 0x4CE52E
// with extraOffset 8 then the KeepObjectDie table at 0x00BF0994
// (CollapsingTime at +0x38 plus StayOnRadar at +0x3C matching the ctor
// stores 0x19/0 at 0x253B78). The owning ModuleData factory at 0x00253BB7
// pushes this proc VA (unique image-wide) and the ModuleFactory registrar
// at 0x00258D9B maps the KeepObjectDie INI name to that factory.
void KeepObjectDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0994), 0);
}

class RefundDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@RefundDieModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0025391E (34 bytes): double-add on the rowed Die getter 0x4CE52E
// with extraOffset 8 then the RefundDie table at 0x00BF0700
// (UpgradeRequired at +0x38 plus RefundPercent at +0x3C plus
// BuildingRequired at +0x40 matching the ctor stores and member). The owning
// ModuleData factory at 0x00253940 pushes this proc VA (unique image-wide)
// and the ModuleFactory registrar maps the RefundDie INI name to that
// factory.
void RefundDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0700), 0);
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

int Rva0033A495Get(void);

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RandomSoundSelectorClientBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F318), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva0033A495Get()), 8);
}

class GiveUpgradeUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GiveUpgradeUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C511A0), 0);
}

class OpenContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CreateObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CreateObjectDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4A928), 0);
}

class CaveContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CaveContainModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024B77C (27 bytes): base-table call above plus the CaveContain
// table at 0x00BEEAC8 (CaveIndex at +0x98). The field matches BFME1's
// CaveContainModuleData table verbatim at the identical offset (vote 1/1).
// The owning factory at 0x00257714 pushes this proc's VA (unique
// image-wide); the CaveContain pool key plus name getter are rowed in their
// own file-unit. The TimeForFullHeal factory shares the class ctor (fold);
// that name stays unclaimed.
void CaveContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEEAC8), 0);
}

// ?buildFieldParse@OpenContainModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0046523D (34 bytes): table-first double-add registering the
// Contain table at 0x00C438B0 (ContainMax at +0x70 plus EnterSound at +0x38
// plus ExitSound at +0x3C plus DamagePercentToUnits at +0x6C plus
// PassengerFilter at +0x40 plus ManualPickUpFilter at +0x44 plus
// PassengersTestCollisionHeight at +0x68 plus PassengersInTurret at +0x85)
// then the Die getter 0x4CE52E with extraOffset 8 (RubbleRise table-first
// precedent). All eight fields match BFME1's OpenContainModuleData table at
// diverged offsets (votes 10/9); this proc is the base of the
// GarrisonContain pinned chain plus the CaveContain and TimeForFullHeal
// chains. Row supersedes the base pin.
void OpenContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C438B0), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
}

// ?buildFieldParse@GarrisonContainModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00254F75 (27 bytes): base-table call above plus the Garrison
// table at 0x00BF3360 (five of five BFME1 GarrisonContain fields in order).
// The owning factory at 0x00254F90 pushes this proc's VA (unique
// image-wide). Row supersedes the chained pin; HordeGarrison chains above.
void GarrisonContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF3360), 0);
}

// ?buildFieldParse@WeaponSetUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004B56F6 (34 bytes): double-add on the rowed ModuleData getter
// table 0x4CE29D with extraOffset 8 then own table 0x00C58020 holding
// WeaponCondition at +0x118 (ReplaceSelf/Unpause precedent). Identity:
// ModuleFactory registers factory 0x00250252 -- which calls ctor 0x4B57AA
// (already rowed WeaponSetUpgradeModuleData) and pushes this proc's VA --
// under "WeaponSetUpgrade"; formerly misnamed HealContainModuleData on the
// theory that the WeaponSetUpgrade pool key ending at this address was
// packing coincidence. HealContain is a real, separate module (data factory
// 0x24B80D, ctor 0x466D37).
class WeaponSetUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void WeaponSetUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58020), 0);
}

// ?buildFieldParse@RemoveUpgradeUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004B7F82 (34 bytes): double-add on the rowed ModuleData getter
// table 0x4CE29D with extraOffset 8 then own table 0x00C58EA0 holding
// UpgradeToRemove at +0x118 plus UpgradeGroupsToRemove at +0x124 plus
// SuppressEvaEventForRemoval at +0x130 plus RemoveFromAllPlayerObjects at
// +0x131 (ReplaceSelf/Unpause precedent). The rowed factory at 0x0025082A
// calls the pinned ctor at 0x4B7FF1 and pushes this proc's VA (unique
// image-wide); pool key at 0x4B7F67 names the class. Row supersedes the pin.
class RemoveUpgradeUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RemoveUpgradeUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C58EA0), 0);
}

class ReplaceObjectUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ReplaceObjectUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024FC94 (27 bytes): chained on the rowed Rva0044EB54 base proc
// at 0x44ED95, then table 0x00BEF960 holding ReplaceObject at +0x18 plus
// ReplaceRadius at +0x1C plus ReplaceFX at +0x20 plus Scatter at +0x24.
// The rowed factory at 0x0024FCEA calls the rowed ctor at 0x4B2AC4 and
// pushes this proc's VA (unique image-wide); the pool key at 0x4B2A29 names
// the class. Row supersedes the pin.
void ReplaceObjectUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEF960), 0);
}

class MonsterDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@MonsterDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004A137F (27 bytes): chained on the rowed DockUpdate base proc at
// 0x5896C1, then table 0x00C51CE4 holding DockableObjectFilter at +0x10 plus
// DockedAnimationTime at +0x14. The rowed factory at 0x0024EB2C pushes this
// proc's VA (unique image-wide); the MonsterDockUpdate pool key plus Update
// ctor plus dtor sit in the cluster at 0x4A139A right where this proc ends.
// Row supersedes the pin.
void MonsterDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C51CE4), 0);
}

class FireWeaponWhenDeadBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FireWeaponWhenDeadBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x002537A6 (54 bytes): triple-add with own table 0x00BF0508 holding
// StartsActive plus ActiveDuringConstruction plus DelayTime plus DeathWeapon
// plus WeaponOffset then the rowed getter 0x4CE29D with extraOffset 8 then
// the rowed getter 0x4CE52E with extraOffset 0x12C. The rowed factory at
// 0x002537DC pushes this proc VA and calls the pinned ctor at 0x253737;
// ModuleFactory registers the FireWeaponWhenDeadBehavior literal with that
// factory and the proc ends where the factory begins. Row supersedes pin.
void FireWeaponWhenDeadBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0508), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 0x12C);
}

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FireWeaponWhenDamagedBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x002536E1 (34 bytes): table-first double-add with own table
// 0x00BF0400 holding StartsActive at +0x118 plus ReactionWeaponPristine at
// +0x124 plus ReactionWeaponDamaged at +0x128 plus
// ReactionWeaponReallyDamaged at +0x12C plus ReactionWeaponRubble at +0x130
// plus ContinuousWeaponPristine at +0x134 plus ContinuousWeaponDamaged at
// +0x138 plus ContinuousWeaponReallyDamaged at +0x13C plus
// ContinuousWeaponRubble at +0x140 plus DamageTypes at +0x11C plus
// DamageAmount at +0x120 then the rowed getter 0x4CE29D with extraOffset 8
// (RubbleRise table-first precedent). The free factory at 0x00253703 pushes
// this proc VA (unique image-wide) and calls ctor 0x253682; field_names
// votes ReactionWeaponPristine to FireWeaponWhenDamagedBehaviorModuleData;
// behavior pool key at 0x4827AA names the family. Row supersedes pin when
// the factory lands.
void FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0400), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}
