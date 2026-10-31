
char g_00C5BAE8;
char g_00C5BD38;
char g_00C585DC;

// cl: /O1 /DNDEBUG /MD
//
// Chained ModuleData::buildFieldParse procs: each calls its base-class
// buildFieldParse, then registers its own FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Bodies:
// ?buildFieldParse@SpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z, retail
// 0x0044ED95, 11 bytes (field SpecialPowerTemplate; base shared by the
// SpecialAbility family below; attached to the already-pinned SpecialAbilityUpdateModuleData
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
// at 0x4C12D0, then table (unsigned int)&g_00C5BAE8 holding DelayedDeathTime at +0x6C plus
// ImmortalUntilDeathTime at +0x70 plus InvulnerableFX at +0x74 plus
// DoHealthCheck at +0x78 plus DelayedDeathPrerequisiteUpgrade at +0x7C,
// matching the ctor stores; factory at 0x251622 pushes this proc).
// ?buildFieldParse@DominateEnemySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CC96D, 27 bytes (chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00C5F638 holding DominateRadius at +0xC8 plus
// TriggerFX at +0xCC plus DominatedFX at +0xD0 plus PermanentlyConvert at
// +0xD4 plus AttributeModifierAffects at +0xD8, matching the ctor stores;
// factory at 0x252EE5 pushes this proc; pool key at 0x4CC9DF names the class).
// ?buildFieldParse@GiveUpgradeUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0049C391, 27 bytes (chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00C511A0 holding GiveUpgradeEffect at +0xD4 plus
// SpawnOutFX at +0xD8 plus FadeOutSpeed at +0xDC plus DeliverUpgrade at +0xE0;
// factory at 0x24E800 pushes this proc; pool key at 0x49C471 names the class).
// Provenance: the ZH MAKE_STANDARD_MODULE_DATA_MACRO_ABC macro passes
// clsmd::buildFieldParse to INI::initFromINIMultiProc, and each landed
// friend_newModuleData factory pushes its class proc immediate.

class MultiIniFieldParse;

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseAudioEventRTS(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseFXList(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
	static void parsePercentToReal(INI *, void *, void *, const void *);
	static void parseDurationUnsignedInt(INI *, void *, void *, const void *);
	static void parseWeaponTemplate(INI *, void *, void *, const void *);
	static void parseCoord3D(INI *, void *, void *, const void *);
	static void parseAsciiStringVectorAppend(INI *, void *, void *, const void *);
	static void parseSpecialPowerTemplate(INI *, void *, void *, const void *);
	static void parseDamageTypeFlags(INI *, void *, void *, const void *);
	static void parseUnsignedInt(INI *, void *, void *, const void *);
	static void parseObjectCreationList(INI *, void *, void *, const void *);
	static void parseAsciiStringVector(INI *, void *, void *, const void *);
	static void Rva004B2B64_ParseReplaceObject(INI *, void *, void *, const void *);
	static void iniParseAnim(INI *, void *, void *, const void *);
	static void parseDurationReal(INI *, void *, void *, const void *);
	static void parseUpgradeTemplate(INI *, void *, void *, const void *);
	static void iniParseAnimAndDuration(INI *, void *, void *, const void *);
	static void dup_002F02F(INI *, void *, void *, const void *);
	static void parseBitString32(INI *, void *, void *, const void *);
	static void parseIndexList(INI *, void *, void *, const void *);
	static void parseParticleSystemTemplate(INI *, void *, void *, const void *);
	static void parseScience(INI *, void *, void *, const void *);
};

class Rva003B1017
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

class Rva004B65E4
{
public:
	static void rva004B65E4(INI *, void *, void *, const void *);
};

void Rva000B9468Parse(INI *, void *, void *, const void *);
void Rva002567EAParse(INI *, void *, void *, const void *);
void Rva002C8C06Parse(INI *, void *, void *, const void *);
void Rva00464081ParseMask(INI *, void *, void *, const void *);
void Rva00464574Parse(INI *, void *, void *, const void *);
void iniParseObjectFilter(INI *, void *, void *, const void *);
void rva004649A1(INI *, void *, void *, const void *);
void rva004B5293(INI *, void *, void *, const void *);

class Rva0049B8A0
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

// Retail VA 0x00DC8F08: ordered names consumed by the table parsers below.
// Complete null-terminated array; global spelling is descriptive.
extern const char *const BfmeSpecialAbilityConditionNames[] = {
	"MOUNTED",
	"WEAPON_TOGGLE",
	"MOVING",
	0
};

// Retail VA 0x00DCB75C: ordered names consumed by the table parsers below.
// Complete null-terminated array; global spelling is descriptive.
extern const char *const BfmeAuraConditionNames[] = {
	"MOUNTED",
	"TAINT",
	"ELVEN_WOOD",
	0
};

// Retail VA 0x00DCA3F0: ordered names consumed by the table parsers below.
// Complete null-terminated array; global spelling is descriptive.
extern const char *const BfmeDamageTriggerNames[] = {
	"NORMAL",
	"BECOME_UNDEAD",
	0
};

void Rva0049B51EParse(INI *, void *, void *, const void *);

// Retail VA 0x00C550C8 is the GloriousChargeUpdateModuleData FieldParse
// table: .rdata holds BonusRadius/parseReal at +0xC8, SpeechDuration and
// UpdateInterval/parseDurationUnsignedInt at +0xCC/+0xD0, then a zero
// sentinel. The matched buildFieldParse caller supplies the independent class
// identity and the relocation pins this named definition to the table address.
extern const FieldParse g_00C550C8GloriousChargeFieldParse[] = {
	{ "BonusRadius", &INI::parseReal, 0, 0xC8 },
	{ "SpeechDuration", &INI::parseDurationUnsignedInt, 0, 0xCC },
	{ "UpdateInterval", &INI::parseDurationUnsignedInt, 0, 0xD0 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C5FB9C is the StoreObjectsSpecialPowerModuleData FieldParse
// table: .rdata holds Radius/parseReal at +0xC8, followed by a zero sentinel.
// The matched buildFieldParse caller supplies the independent class identity.
extern const FieldParse g_00C5FB9CStoreObjectsFieldParse[] = {
	{ "Radius", &INI::parseReal, 0, 0xC8 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BF0508 is the FireWeaponWhenDeadBehaviorModuleData
// FieldParse table: StartsActive/ActiveDuringConstruction use parseBool,
// DelayTime uses parseDurationUnsignedInt, DeathWeapon uses
// parseWeaponTemplate, and WeaponOffset uses parseCoord3D at the retail
// offsets. The matched buildFieldParse row supplies the class identity.
extern const FieldParse g_00BF0508FireWeaponWhenDeadBehaviorFieldParse[] = {
	{ "StartsActive", &INI::parseBool, 0, 0x118 },
	{ "ActiveDuringConstruction", &INI::parseBool, 0, 0x119 },
	{ "DelayTime", &INI::parseDurationUnsignedInt, 0, 0x11C },
	{ "DeathWeapon", &INI::parseWeaponTemplate, 0, 0x15C },
	{ "WeaponOffset", &INI::parseCoord3D, 0, 0x120 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C58C38 is the TooltipUpgradeModuleData FieldParse table:
// DisplayName and Description use parseAsciiString at +0x118/+0x11C, then
// the table's zero sentinel. The matched buildFieldParse caller supports the
// class identity.
extern const FieldParse g_00C58C38TooltipUpgradeFieldParse[] = {
	{ "DisplayName", &INI::parseAsciiString, 0, 0x118 },
	{ "Description", &INI::parseAsciiString, 0, 0x11C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BEF0A8 is the WeaponFireSpecialAbilityUpdateModuleData
// FieldParse table: SpecialWeapon/parseAsciiString at +0xC8,
// WhichSpecialWeapon/parseInt at +0xCC, SkipContinue/parseBool at +0xD0,
// BusyForDuration/parseDurationUnsignedInt at +0xD4, NeedLivingTargets and
// PlayWeaponPreFireFX/parseBool at +0xD8/+0xD9, then a zero sentinel. The
// matched caller is corroborated by target pool key 0x00492685 and factory
// 0x0024DB56.
extern const FieldParse g_00BEF0A8WeaponFireSpecialAbilityFieldParse[] = {
	{ "SpecialWeapon", &INI::parseAsciiString, 0, 0xC8 },
	{ "WhichSpecialWeapon", &INI::parseInt, 0, 0xCC },
	{ "SkipContinue", &INI::parseBool, 0, 0xD0 },
	{ "BusyForDuration", &INI::parseDurationUnsignedInt, 0, 0xD4 },
	{ "NeedLivingTargets", &INI::parseBool, 0, 0xD8 },
	{ "PlayWeaponPreFireFX", &INI::parseBool, 0, 0xD9 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BEF150 is the TeleportSpecialAbilityUpdateModuleData
// FieldParse table: BusyForDuration/parseDurationUnsignedInt at +0xC8,
// DestinationWeaponName and SourceWeaponName/parseAsciiString at +0xCC/+0xD0,
// MaxDistance/parseReal at +0xD4, then a zero sentinel. The matched caller
// is independently tied to the TeleportSpecialAbilityUpdate factory.
extern const FieldParse g_00BEF150TeleportSpecialAbilityFieldParse[] = {
	{ "BusyForDuration", &INI::parseDurationUnsignedInt, 0, 0xC8 },
	{ "DestinationWeaponName", &INI::parseAsciiString, 0, 0xCC },
	{ "SourceWeaponName", &INI::parseAsciiString, 0, 0xD0 },
	{ "MaxDistance", &INI::parseReal, 0, 0xD4 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class SpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C3F7F8: 58 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeSpecialAbilityUpdateFields[] = {
	{ "SpecialPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x38 },
	{ "StartAbilityRange", &INI::parseReal, 0, 0x4C },
	{ "AbilityAbortRange", &INI::parseReal, 0, 0x50 },
	{ "PreparationTime", &INI::parseDurationUnsignedInt, 0, 0x74 },
	{ "PersistentPrepTime", &INI::parseDurationUnsignedInt, 0, 0x78 },
	{ "PersistentCount", &INI::parseInt, 0, 0x70 },
	{ "PackTime", &INI::parseDurationUnsignedInt, 0, 0x84 },
	{ "UnpackTime", &INI::parseDurationUnsignedInt, 0, 0x88 },
	{ "PreTriggerUnstealthTime", &INI::parseDurationUnsignedInt, 0, 0x8C },
	{ "SkipPackingWithNoTarget", &INI::parseBool, 0, 0xA8 },
	{ "PackUnpackVariationFactor", &INI::parseReal, 0, 0x54 },
	{ "ParalyzeDurationWhenCompleted", &INI::parseDurationUnsignedInt, 0, 0x90 },
	{ "ParalyzeDurationWhenAborted", &INI::parseDurationUnsignedInt, 0, 0x94 },
	{ "SpecialObject", &INI::parseAsciiString, 0, 0x40 },
	{ "SpecialObjectAttachToBone", &INI::parseAsciiString, 0, 0x44 },
	{ "MaxSpecialObjects", &INI::parseUnsignedInt, 0, 0x80 },
	{ "SpecialObjectsPersistent", &INI::parseBool, 0, 0xA9 },
	{ "EffectDuration", &INI::parseDurationUnsignedInt, 0, 0x7C },
	{ "EffectValue", &INI::parseInt, 0, 0x5C },
	{ "EffectRange", &INI::parseReal, 0, 0x60 },
	{ "UniqueSpecialObjectTargets", &INI::parseBool, 0, 0xAA },
	{ "SpecialObjectsPersistWhenOwnerDies", &INI::parseBool, 0, 0xAB },
	{ "AlwaysValidateSpecialObjects", &INI::parseBool, 0, 0xAE },
	{ "FlipOwnerAfterPacking", &INI::parseBool, 0, 0xAC },
	{ "FlipOwnerAfterUnpacking", &INI::parseBool, 0, 0xAD },
	{ "FleeRangeAfterCompletion", &INI::parseReal, 0, 0x58 },
	{ "DisableFXParticleSystem", &INI::parseParticleSystemTemplate, 0, 0x3C },
	{ "DoCaptureFX", &INI::parseBool, 0, 0xAF },
	{ "PackSound", &INI::parseAudioEventRTS, 0, 0x8 },
	{ "UnpackSound", &INI::parseAudioEventRTS, 0, 0xC },
	{ "PrepSoundLoop", &INI::parseAudioEventRTS, 0, 0x10 },
	{ "TriggerSound", &INI::parseAudioEventRTS, 0, 0x14 },
	{ "ActiveLoopSound", &INI::parseAudioEventRTS, 0, 0x34 },
	{ "LoseStealthOnTrigger", &INI::parseBool, 0, 0xB0 },
	{ "AwardXPForTriggering", &INI::parseInt, 0, 0x64 },
	{ "SkillPointsForTriggering", &INI::parseInt, 0, 0x68 },
	{ "ApproachRequiresLOS", &INI::parseBool, 0, 0xB1 },
	{ "ChargeAttackSpeedBoost", &INI::parseBool, 0, 0xB2 },
	{ "CustomAnimAndDuration", &INI::iniParseAnimAndDuration, 0, 0x18 },
	{ "GrabPassengerAnimAndDuration", &INI::iniParseAnimAndDuration, 0, 0x24 },
	{ "GrabPassengerHealGainPercent", &INI::dup_002F02F, 0, 0x30 },
	{ "UnpackingVariation", &INI::parseInt, 0, 0x6C },
	{ "MustFinishAbility", &INI::parseBool, 0, 0xB5 },
	{ "FreezeAfterTriggerDuration", &INI::parseDurationUnsignedInt, 0, 0x9C },
	{ "DisableWhenWearingTheRing", &INI::parseBool, 0, 0xB6 },
	{ "RequiredConditions", &INI::parseBitString32, BfmeSpecialAbilityConditionNames, 0xA0 },
	{ "RejectedConditions", &INI::parseBitString32, BfmeSpecialAbilityConditionNames, 0xA4 },
	{ "ContactPointOverride", &INI::parseAsciiString, 0, 0xBC },
	{ "TriggerAttributeModifier", &INI::parseAsciiString, 0, 0x48 },
	{ "AttributeModifierDuration", &INI::parseDurationUnsignedInt, 0, 0x98 },
	{ "KillAttributeModifierOnExit", &INI::parseBool, 0, 0xB3 },
	{ "KillAttributeModifierOnRejected", &INI::parseBool, 0, 0xB4 },
	{ "Instant", &INI::parseBool, 0, 0xB7 },
	{ "NeedCollisionBeforeTrigger", &INI::parseBool, 0, 0xB8 },
	{ "ChainedButton", &INI::parseAsciiString, 0, 0xC0 },
	{ "SuppressForHordes", &INI::parseBool, 0, 0xC4 },
	{ "ApproachUntilMembersInRange", &INI::parseBool, 0, 0xC5 },
	{ "IgnoreFacingCheck", &INI::parseBool, 0, 0xC6 },
	{ 0, 0, 0, 0 }
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C5FAE0: 5 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeTeleportToCasterSpecialPowerFields[] = {
	{ "Radius", &INI::parseReal, 0, 0xC8 },
	{ "MinDestinationRadius", &INI::parseReal, 0, 0xCC },
	{ "MaxDestinationRadius", &INI::parseReal, 0, 0xD0 },
	{ "TriggerFX", &INI::parseFXList, 0, 0xD4 },
	{ "TargetFX", &INI::parseFXList, 0, 0xD8 },
	{ 0, 0, 0, 0 }
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

// Retail VA 0x00C5370C: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeSupplyWarehouseDockUpdateFields[] = {
	{ "StartingBoxes", &INI::parseInt, 0, 0x10 },
	{ "DeleteWhenEmpty", &INI::parseBool, 0, 0x14 },
	{ 0, 0, 0, 0 }
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

// ?buildFieldParse@SpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void SpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeSpecialAbilityUpdateFields, 0);
}

// ?bfmeAnchorSpecialAbilityUpdateModuleDatabuildFieldParse absent-from-retail
void bfmeAnchorSpecialAbilityUpdateModuleDatabuildFieldParse(SpecialAbilityUpdateModuleData *specialAbilityUpdateModuleData, MultiIniFieldParse &parse)
{
	specialAbilityUpdateModuleData->buildFieldParse(parse);
}

void TeleportToCasterSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeTeleportToCasterSpecialPowerFields, 0);
}

void StoreObjectsSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C5FB9CStoreObjectsFieldParse, 0);
}

void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeSupplyWarehouseDockUpdateFields, 0);
}

void DelayedDeathBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5BAE8), 0);
}

void FreeLifeBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5BD38), 0);
}

class GloriousChargeUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GloriousChargeUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C550C8GloriousChargeFieldParse, 0);
}

class GiveOrRestoreUpgradeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C5F8C0: 3 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeGiveOrRestoreUpgradeSpecialPowerFields[] = {
	{ "CommandButton", &INI::parseAsciiString, 0, 0xC8 },
	{ "UpgradeToGive", &INI::parseAsciiString, 0, 0xCC },
	{ "FlagsUsedForToggle", &Rva002C8C06Parse, 0, 0xD0 },
	{ 0, 0, 0, 0 }
};

void GiveOrRestoreUpgradeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeGiveOrRestoreUpgradeSpecialPowerFields, 0);
}

int Rva004CE29DGet(void);

// Retail VA 0x00C58A88: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeReplaceSelfUpgradeFields[] = {
	{ "ReplaceWith", &INI::parseAsciiStringVectorAppend, 0, 0x118 },
	{ "AndThenAddA", &INI::parseAsciiStringVectorAppend, 0, 0x118 },
	{ 0, 0, 0, 0 }
};

class ReplaceSelfUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ReplaceSelfUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeReplaceSelfUpgradeFields, 0);
}

// Retail VA 0x00C57EF0: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeUnpauseSpecialPowerUpgradeFields[] = {
	{ "SpecialPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x118 },
	{ "ObeyRechageOnTrigger", &INI::parseBool, 0, 0x11C },
	{ 0, 0, 0, 0 }
};

class UnpauseSpecialPowerUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void UnpauseSpecialPowerUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeUnpauseSpecialPowerUpgradeFields, 0);
}

class AutoHealBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00BF3CE0: 18 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeAutoHealBehaviorFields[] = {
	{ "StartsActive", &INI::parseBool, 0, 0x118 },
	{ "ButtonTriggered", &INI::parseBool, 0, 0x119 },
	{ "SingleBurst", &INI::parseBool, 0, 0x11A },
	{ "HealingAmount", &INI::parseInt, 0, 0x11C },
	{ "HealingDelay", &INI::parseDurationUnsignedInt, 0, 0x120 },
	{ "Radius", &INI::parseInt, 0, 0x128 },
	{ "KindOf", &Rva002567EAParse, 0, 0x130 },
	{ "UnitHealPulseFX", &INI::parseFXList, 0, 0x150 },
	{ "StartHealingDelay", &INI::parseDurationUnsignedInt, 0, 0x124 },
	{ "AffectsWholePlayer", &INI::parseBool, 0, 0x12C },
	{ "AffectsContained", &INI::parseBool, 0, 0x12D },
	{ "HealOnlyIfNotUnderAttack", &INI::parseBool, 0, 0x12E },
	{ "HealOnlyIfNotInCombat", &INI::parseBool, 0, 0x12F },
	{ "HealOnlyOthers", &INI::parseBool, 0, 0x14C },
	{ "NonStackable", &INI::parseBool, 0, 0x154 },
	{ "RespawnNearbyHordeMembers", &INI::parseBool, 0, 0x155 },
	{ "RespawnFXList", &INI::parseFXList, 0, 0x158 },
	{ "RespawnMinimumDelay", &INI::parseUnsignedInt, 0, 0x15C },
	{ 0, 0, 0, 0 }
};

inline void AutoHealBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeAutoHealBehaviorFields, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}

class AttributeModifierAuraUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C50DC8: 17 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeAttributeModifierAuraUpdateFields[] = {
	{ "BonusName", &INI::parseAsciiString, 0, 0x8 },
	{ "RefreshDelay", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "Range", &INI::parseReal, 0, 0x1C },
	{ "TargetEnemy", &INI::parseBool, 0, 0x21 },
	{ "AllowPowerWhenAttacking", &INI::parseBool, 0, 0x20 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x24 },
	{ "AffectsKindOf", &Rva0049B51EParse, 0, 0x0 },
	{ "StartsActive", &INI::parseBool, 0, 0x138 },
	{ "RequiredConditions", &INI::parseBitString32, BfmeAuraConditionNames, 0x13C },
	{ "AntiCategory", &Rva0049B8A0::parseFromINI, 0, 0x140 },
	{ "AntiFX", &INI::parseFXList, 0, 0x144 },
	{ "AffectGood", &INI::parseBool, 0, 0x148 },
	{ "AffectEvil", &INI::parseBool, 0, 0x149 },
	{ "RunWhileDead", &INI::parseBool, 0, 0x14A },
	{ "AllowSelf", &INI::parseBool, 0, 0x14B },
	{ "AffectContainedOnly", &INI::parseBool, 0, 0x14C },
	{ "MaxActiveRank", &INI::parseInt, 0, 0x150 },
	{ 0, 0, 0, 0 }
};

void AttributeModifierAuraUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x28);
	parse.add(BfmeAttributeModifierAuraUpdateFields, 0);
}

class LevelGrantSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C5C8D0: 4 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeLevelGrantSpecialPowerFields[] = {
	{ "Experience", &INI::parseInt, 0, 0xC8 },
	{ "RadiusEffect", &INI::parseReal, 0, 0xCC },
	{ "LevelFX", &INI::parseFXList, 0, 0xD4 },
	{ "AcceptanceFilter", &iniParseObjectFilter, 0, 0xD0 },
	{ 0, 0, 0, 0 }
};

void LevelGrantSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeLevelGrantSpecialPowerFields, 0);
}

// Retail VA 0x00C574AC: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeLevelUpUpgradeFields[] = {
	{ "LevelsToGain", &INI::parseInt, 0, 0x118 },
	{ "LevelCap", &INI::parseInt, 0, 0x11C },
	{ 0, 0, 0, 0 }
};

class LevelUpUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void LevelUpUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeLevelUpUpgradeFields, 0);
}

class MaxHealthUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void MaxHealthUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C585DC), 0);
}

class TooltipUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void TooltipUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(g_00C58C38TooltipUpgradeFieldParse, 0);
}

// Retail VA 0x00C58524: 1 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeExperienceScalarUpgradeFields[] = {
	{ "AddXPScalar", &INI::parseReal, 0, 0x118 },
	{ 0, 0, 0, 0 }
};

class ExperienceScalarUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ExperienceScalarUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeExperienceScalarUpgradeFields, 0);
}

int Rva004CE52EGet(void);

// Retail VA 0x00BF0958: 1 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeUpgradeDieFields[] = {
	{ "UpgradeToRemove", &INI::parseAsciiString, 0, 0x38 },
	{ 0, 0, 0, 0 }
};

class UpgradeDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

inline void UpgradeDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(BfmeUpgradeDieFields, 0);
}

class CrushDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00BF0868: 6 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeCrushDieFields[] = {
	{ "TotalCrushSound", &INI::parseAudioEventRTS, 0, 0x38 },
	{ "BackEndCrushSound", &INI::parseAudioEventRTS, 0, 0x3C },
	{ "FrontEndCrushSound", &INI::parseAudioEventRTS, 0, 0x40 },
	{ "TotalCrushSoundPercent", &INI::parseInt, 0, 0x48 },
	{ "BackEndCrushSoundPercent", &INI::parseInt, 0, 0x4C },
	{ "FrontEndCrushSoundPercent", &INI::parseInt, 0, 0x50 },
	{ 0, 0, 0, 0 }
};

inline void CrushDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(BfmeCrushDieFields, 0);
}

// Retail VA 0x00BF0994: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeKeepObjectDieFields[] = {
	{ "CollapsingTime", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "StayOnRadar", &INI::parseBool, 0, 0x3C },
	{ 0, 0, 0, 0 }
};

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
	parse.add(BfmeKeepObjectDieFields, 0);
}

class RefundDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00BF0700: 3 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeRefundDieFields[] = {
	{ "UpgradeRequired", &INI::parseUpgradeTemplate, 0, 0x38 },
	{ "BuildingRequired", &iniParseObjectFilter, 0, 0x40 },
	{ "RefundPercent", &INI::parsePercentToReal, 0, 0x3C },
	{ 0, 0, 0, 0 }
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
	parse.add(BfmeRefundDieFields, 0);
}

// Retail VA 0x00BF0928: 1 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeSpecialPowerCompletionDieFields[] = {
	{ "SpecialPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x38 },
	{ 0, 0, 0, 0 }
};

class SpecialPowerCompletionDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

inline void SpecialPowerCompletionDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(BfmeSpecialPowerCompletionDieFields, 0);
}

class RebuildHoleExposeDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DamageFilteredCreateObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C4ABE0: 4 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeDamageFilteredCreateObjectDieFields[] = {
	{ "CreationList", &INI::parseObjectCreationList, 0, 0x38 },
	{ "DamageTypeTriggersInstantly", &INI::parseIndexList, BfmeDamageTriggerNames, 0x3C },
	{ "DamageTypeTriggersForDuration", &INI::parseIndexList, BfmeDamageTriggerNames, 0x40 },
	{ "PostFilterTriggeredDuration", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ 0, 0, 0, 0 }
};

void DamageFilteredCreateObjectDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(BfmeDamageFilteredCreateObjectDieFields, 0);
}

class SupplyCenterDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C51A80: 3 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeSupplyCenterDockUpdateFields[] = {
	{ "ValueMultiplier", &INI::parseReal, 0, 0x10 },
	{ "BonusScience", &INI::parseScience, 0, 0x14 },
	{ "BonusScienceMultiplier", &INI::parsePercentToReal, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

void SupplyCenterDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeSupplyCenterDockUpdateFields, 0);
}

class CommandPointsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C57208: 3 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeBaseUpgradeFields[] = {
	{ "BuildingTemplateName", &INI::parseAsciiString, 0, 0x118 },
	{ "PlacementPrefix", &INI::parseAsciiString, 0, 0x11C },
	{ "PlacementIndex", &INI::parseInt, 0, 0x120 },
	{ 0, 0, 0, 0 }
};

class BaseUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void BaseUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeBaseUpgradeFields, 0);
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
	static void parseInitialRoster(INI *, void *, void *, const void *);
};

// Retail VA 0x00BF3360: 5 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeGarrisonContainFields[] = {
	{ "MobileGarrison", &INI::parseBool, 0, 0xA0 },
	{ "HealObjects", &INI::parseBool, 0, 0x98 },
	{ "TimeForFullHeal", &INI::parseDurationReal, 0, 0x9C },
	{ "InitialRoster", &GarrisonContainModuleData::parseInitialRoster, 0, 0x0 },
	{ "ImmuneToClearBuildingAttacks", &INI::parseBool, 0, 0xA1 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C46388: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeHordeGarrisonContainFields[] = {
	{ "ExitDelay", &INI::parseDurationUnsignedInt, 0, 0xAC },
	{ "EntryOffset", &INI::parseCoord3D, 0, 0xB0 },
	{ "EntryPosition", &INI::parseCoord3D, 0, 0xBC },
	{ "ExitOffset", &INI::parseCoord3D, 0, 0xC8 },
	{ 0, 0, 0, 0 }
};

class HordeGarrisonContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void HordeGarrisonContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	GarrisonContainModuleData::buildFieldParse(parse);
	parse.add(BfmeHordeGarrisonContainFields, 0);
}

class FireWeaponUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C4C2A8: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeOilSpillUpdateFields[] = {
	{ "BreadcrumbName", &INI::parseAsciiString, 0, 0x10 },
	{ "IgnitionWeaponName", &INI::parseAsciiString, 0, 0x14 },
	{ "IgnitionWeaponSpacing", &INI::parseReal, 0, 0x18 },
	{ "OilSpillFX", &INI::parseFXList, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

class OilSpillUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void OilSpillUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	FireWeaponUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeOilSpillUpdateFields, 0);
}

class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void WeaponFireSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00BEF0A8WeaponFireSpecialAbilityFieldParse, 0);
}

class ReplenishUnitsBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C4A150: 7 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeReplenishUnitsBehaviorFields[] = {
	{ "StartsActive", &INI::parseBool, 0, 0x138 },
	{ "ReplenishDelay", &INI::parseDurationUnsignedInt, 0, 0x134 },
	{ "ReplenishRadius", &INI::parseReal, 0, 0x118 },
	{ "NoReplenishIfEnemyWithinRadius", &INI::parseReal, 0, 0x11C },
	{ "ReplenishFXList", &INI::parseFXList, 0, 0x120 },
	{ "ReplenishStatii", &Rva003B1017::parseFromINI, 0, 0x124 },
	{ "ReplenishHordeMembersOnly", &INI::parseBool, 0, 0x139 },
	{ 0, 0, 0, 0 }
};

void ReplenishUnitsBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeReplenishUnitsBehaviorFields, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}

class DominateEnemySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C5F638: 5 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeDominateEnemySpecialPowerFields[] = {
	{ "DominateRadius", &INI::parseReal, 0, 0xC8 },
	{ "TriggerFX", &INI::parseFXList, 0, 0xCC },
	{ "DominatedFX", &INI::parseFXList, 0, 0xD0 },
	{ "PermanentlyConvert", &INI::parseBool, 0, 0xD4 },
	{ "AttributeModifierAffects", &iniParseObjectFilter, 0, 0xD8 },
	{ 0, 0, 0, 0 }
};

void DominateEnemySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeDominateEnemySpecialPowerFields, 0);
}

class RousingSpeechUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C54F28: 10 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeRousingSpeechUpdateFields[] = {
	{ "BonusRadius", &INI::parseReal, 0, 0xC8 },
	{ "SpeechDuration", &INI::parseDurationUnsignedInt, 0, 0xCC },
	{ "UpdateInterval", &INI::parseDurationUnsignedInt, 0, 0xD0 },
	{ "LeaderFX", &INI::parseFXList, 0, 0xD4 },
	{ "FollowerFX", &INI::parseFXList, 0, 0xD8 },
	{ "CreateWave", &INI::parseBool, 0, 0xDC },
	{ "WaveWidth", &INI::parseReal, 0, 0xE0 },
	{ "ModifierName", &INI::parseAsciiStringVectorAppend, 0, 0xE4 },
	{ "LevelUp", &INI::parseBool, 0, 0xF0 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0xF4 },
	{ 0, 0, 0, 0 }
};

void RousingSpeechUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeRousingSpeechUpdateFields, 0);
}

// Retail VA 0x00C58918: 5 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeGeometryUpgradeFields[] = {
	{ "ShowGeometry", &INI::parseAsciiStringVectorAppend, 0, 0x118 },
	{ "HideGeometry", &INI::parseAsciiStringVectorAppend, 0, 0x124 },
	{ "WallBoundsMesh", &INI::parseAsciiString, 0, 0x130 },
	{ "RampMesh1", &INI::parseAsciiString, 0, 0x134 },
	{ "RampMesh2", &INI::parseAsciiString, 0, 0x138 },
	{ 0, 0, 0, 0 }
};

class GeometryUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GeometryUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeGeometryUpgradeFields, 0);
}

class RadiateFearUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class ModelConditionUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C58730: 5 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeModelConditionUpgradeFields[] = {
	{ "AddConditionFlags", &Rva000B9468Parse, 0, 0x118 },
	{ "RemoveConditionFlags", &Rva000B9468Parse, 0, 0x164 },
	{ "RemoveConditionFlagsInRange", &Rva004B65E4::rva004B65E4, 0, 0x164 },
	{ "AddTempConditionFlag", &INI::iniParseAnim, 0, 0x1B0 },
	{ "TempConditionTime", &INI::parseReal, 0, 0x1B4 },
	{ 0, 0, 0, 0 }
};

void ModelConditionUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeModelConditionUpgradeFields, 0);
}

class BezierProjectileBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class MissileUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00BF0200: 15 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeSpawnBehaviorFields[] = {
	{ "SpawnNumber", &INI::parseInt, 0, 0x8 },
	{ "SpawnReplaceDelay", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "OneShot", &INI::parseBool, 0, 0x14 },
	{ "CanReclaimOrphans", &INI::parseBool, 0, 0x15 },
	{ "AggregateHealth", &INI::parseBool, 0, 0x16 },
	{ "ExitByBudding", &INI::parseBool, 0, 0x17 },
	{ "SpawnTemplateName", &INI::parseAsciiStringVectorAppend, 0, 0x20 },
	{ "SpawnedRequireSpawner", &INI::parseBool, 0, 0x18 },
	{ "PropagateDamageTypesToSlavesWhenExisting", &INI::parseDamageTypeFlags, 0, 0x1C },
	{ "InitialBurst", &INI::parseInt, 0, 0x10 },
	{ "RespectCommandLimit", &INI::parseBool, 0, 0x19 },
	{ "FadeInTime", &INI::parseUnsignedInt, 0, 0x16C },
	{ "KillSpawnsBasedOnModelConditionState", &INI::parseBool, 0, 0x170 },
	{ "ShareUpgrades", &INI::parseBool, 0, 0x171 },
	{ "SpawnInsideBuilding", &INI::parseBool, 0, 0x172 },
	{ 0, 0, 0, 0 }
};

class SpawnBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

inline void SpawnBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x5C);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 0x2C);
	parse.add(BfmeSpawnBehaviorFields, 0);
}

class RubbleRiseUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static void parseFXList(INI *, void *, void *, const void *);
	static void parseOCL(INI *, void *, void *, const void *);
};

// Retail VA 0x00C52960: 10 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeRubbleRiseUpdateFields[] = {
	{ "MinRubbleRiseDelay", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "MaxRubbleRiseDelay", &INI::parseDurationUnsignedInt, 0, 0x3C },
	{ "MinBurstDelay", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "MaxBurstDelay", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ "RubbleRiseDamping", &INI::parseReal, 0, 0x4C },
	{ "RubbleHeight", &INI::parseReal, 0, 0x50 },
	{ "MaxShudder", &INI::parseReal, 0, 0x54 },
	{ "BigBurstFrequency", &INI::parseInt, 0, 0x48 },
	{ "OCL", &RubbleRiseUpdateModuleData::parseOCL, 0, 0x0 },
	{ "FXList", &RubbleRiseUpdateModuleData::parseFXList, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

void RubbleRiseUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeRubbleRiseUpdateFields, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
}

class SubObjectsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C57D38: 10 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeSubObjectsUpgradeFields[] = {
	{ "ShowSubObjects", &INI::parseAsciiStringVectorAppend, 0, 0x118 },
	{ "HideSubObjects", &INI::parseAsciiStringVectorAppend, 0, 0x124 },
	{ "UpgradeTexture", &rva004B5293, 0, 0x13C },
	{ "FadeTimeInSeconds", &INI::parseReal, 0, 0x148 },
	{ "WaitBeforeFadeInSeconds", &INI::parseReal, 0, 0x14C },
	{ "RecolorHouse", &INI::parseBool, 0, 0x150 },
	{ "ExcludeSubobjects", &INI::parseAsciiStringVectorAppend, 0, 0x130 },
	{ "SkipFadeOnCreate", &INI::parseBool, 0, 0x151 },
	{ "HideSubObjectsOnRemove", &INI::parseBool, 0, 0x152 },
	{ "UnHideSubObjectsOnRemove", &INI::parseBool, 0, 0x153 },
	{ 0, 0, 0, 0 }
};

void SubObjectsUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeSubObjectsUpgradeFields, 0);
}

int Rva0033A495Get(void);
void Rva0033DC9CParse(INI *, void *, void *, const void *);

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static void parseVoicePriority(INI *, void *, void *, const void *);
};

// Retail VA 0x00C511A0: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeGiveUpgradeUpdateFields[] = {
	{ "GiveUpgradeEffect", &INI::parseFXList, 0, 0xD4 },
	{ "SpawnOutFX", &INI::parseFXList, 0, 0xD8 },
	{ "FadeOutSpeed", &INI::parseReal, 0, 0xDC },
	{ "DeliverUpgrade", &INI::parseBool, 0, 0xE0 },
	{ 0, 0, 0, 0 }
};

class GiveUpgradeUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GiveUpgradeUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeGiveUpgradeUpdateFields, 0);
}

class OpenContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C438B0: 24 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeOpenContainFields[] = {
	{ "ContainMax", &INI::parseInt, 0, 0x70 },
	{ "EnterSound", &INI::parseAudioEventRTS, 0, 0x38 },
	{ "ExitSound", &INI::parseAudioEventRTS, 0, 0x3C },
	{ "DamagePercentToUnits", &INI::parsePercentToReal, 0, 0x6C },
	{ "PassengerFilter", &iniParseObjectFilter, 0, 0x40 },
	{ "ManualPickUpFilter", &iniParseObjectFilter, 0, 0x44 },
	{ "PassengersTestCollisionHeight", &INI::parseReal, 0, 0x68 },
	{ "PassengersInTurret", &INI::parseBool, 0, 0x85 },
	{ "NumberOfExitPaths", &INI::parseInt, 0, 0x74 },
	{ "DoorOpenTime", &INI::parseDurationUnsignedInt, 0, 0x78 },
	{ "AllowOwnPlayerInsideOverride", &INI::parseBool, 0, 0x7C },
	{ "AllowAlliesInside", &INI::parseBool, 0, 0x7D },
	{ "AllowEnemiesInside", &INI::parseBool, 0, 0x7E },
	{ "AllowNeutralInside", &INI::parseBool, 0, 0x7F },
	{ "ShowPips", &INI::parseBool, 0, 0x80 },
	{ "CollidePickup", &INI::parseBool, 0, 0x81 },
	{ "PassengerBonePrefix", &Rva00464574Parse, 0, 0x0 },
	{ "BoneSpecificConditionState", &rva004649A1, 0, 0x0 },
	{ "EjectPassengersOnDeath", &INI::parseBool, 0, 0x82 },
	{ "KillPassengersOnDeath", &INI::parseBool, 0, 0x83 },
	{ "Enabled", &INI::parseBool, 0, 0x84 },
	{ "ObjectStatusOfContained", &Rva00464081ParseMask, 0, 0x58 },
	{ "ModifierToGiveOnExit", &INI::parseAsciiStringVectorAppend, 0, 0x88 },
	{ "ModifierRequiredTime", &INI::parseDurationUnsignedInt, 0, 0x94 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C4A928: 3 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeCreateObjectDieFields[] = {
	{ "CreationList", &INI::parseObjectCreationList, 0, 0x38 },
	{ "DebrisPortionOfSelf", &INI::parseAsciiString, 0, 0x3C },
	{ "UpgradeRequired", &INI::parseAsciiStringVector, 0, 0x40 },
	{ 0, 0, 0, 0 }
};

class CreateObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CreateObjectDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(BfmeCreateObjectDieFields, 0);
}

// Retail VA 0x00BEEAC8: 1 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeCaveContainFields[] = {
	{ "CaveIndex", &INI::parseInt, 0, 0x98 },
	{ 0, 0, 0, 0 }
};

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
inline void CaveContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(BfmeCaveContainFields, 0);
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
	parse.add(BfmeOpenContainFields, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
}

// ?buildFieldParse@GarrisonContainModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00254F75 (27 bytes): base-table call above plus the Garrison
// table at 0x00BF3360 (five of five BFME1 GarrisonContain fields in order).
// The owning factory at 0x00254F90 pushes this proc's VA (unique
// image-wide). Row supersedes the chained pin; HordeGarrison chains above.
inline void GarrisonContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(BfmeGarrisonContainFields, 0);
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

// ?buildFieldParse@RemoveUpgradeUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004B7F82 (34 bytes): double-add on the rowed ModuleData getter
// table 0x4CE29D with extraOffset 8 then own table 0x00C58EA0 holding
// UpgradeToRemove at +0x118 plus UpgradeGroupsToRemove at +0x124 plus
// SuppressEvaEventForRemoval at +0x130 plus RemoveFromAllPlayerObjects at
// +0x131 (ReplaceSelf/Unpause precedent). The rowed factory at 0x0025082A
// calls the pinned ctor at 0x4B7FF1 and pushes this proc's VA (unique
// image-wide); pool key at 0x4B7F67 names the class. Row supersedes the pin.
// Retail VA 0x00C58EA0: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeRemoveUpgradeUpgradeFields[] = {
	{ "UpgradeToRemove", &INI::parseAsciiStringVectorAppend, 0, 0x118 },
	{ "UpgradeGroupsToRemove", &INI::parseAsciiStringVectorAppend, 0, 0x124 },
	{ "SuppressEvaEventForRemoval", &INI::parseBool, 0, 0x130 },
	{ "RemoveFromAllPlayerObjects", &INI::parseBool, 0, 0x131 },
	{ 0, 0, 0, 0 }
};

class RemoveUpgradeUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RemoveUpgradeUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(BfmeRemoveUpgradeUpgradeFields, 0);
}

// Retail VA 0x00BEF960: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeReplaceObjectUpdateFields[] = {
	{ "ReplaceObject", &INI::Rva004B2B64_ParseReplaceObject, 0, 0x0 },
	{ "ReplaceRadius", &INI::parseReal, 0, 0xD4 },
	{ "ReplaceFX", &INI::parseFXList, 0, 0xD8 },
	{ "Scatter", &INI::parseBool, 0, 0xDC },
	{ 0, 0, 0, 0 }
};

class ReplaceObjectUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ReplaceObjectUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024FC94 (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc
// at 0x44ED95, then table 0x00BEF960 holding ReplaceObject at +0x18 plus
// ReplaceRadius at +0x1C plus ReplaceFX at +0x20 plus Scatter at +0x24.
// The rowed factory at 0x0024FCEA calls the rowed ctor at 0x4B2AC4 and
// pushes this proc's VA (unique image-wide); the pool key at 0x4B2A29 names
// the class. Row supersedes the pin.
void ReplaceObjectUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeReplaceObjectUpdateFields, 0);
}

class MonsterDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00C51CE4: 2 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeMonsterDockUpdateFields[] = {
	{ "DockableObjectFilter", &iniParseObjectFilter, 0, 0x10 },
	{ "DockedAnimationTime", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ 0, 0, 0, 0 }
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
	parse.add(BfmeMonsterDockUpdateFields, 0);
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
inline void FireWeaponWhenDeadBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BF0508FireWeaponWhenDeadBehaviorFieldParse, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 0x12C);
}

// Retail VA 0x00BF0400: 11 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeFireWeaponWhenDamagedBehaviorFields[] = {
	{ "StartsActive", &INI::parseBool, 0, 0x118 },
	{ "ReactionWeaponPristine", &INI::parseWeaponTemplate, 0, 0x124 },
	{ "ReactionWeaponDamaged", &INI::parseWeaponTemplate, 0, 0x128 },
	{ "ReactionWeaponReallyDamaged", &INI::parseWeaponTemplate, 0, 0x12C },
	{ "ReactionWeaponRubble", &INI::parseWeaponTemplate, 0, 0x130 },
	{ "ContinuousWeaponPristine", &INI::parseWeaponTemplate, 0, 0x134 },
	{ "ContinuousWeaponDamaged", &INI::parseWeaponTemplate, 0, 0x138 },
	{ "ContinuousWeaponReallyDamaged", &INI::parseWeaponTemplate, 0, 0x13C },
	{ "ContinuousWeaponRubble", &INI::parseWeaponTemplate, 0, 0x140 },
	{ "DamageTypes", &INI::parseDamageTypeFlags, 0, 0x11C },
	{ "DamageAmount", &INI::parseReal, 0, 0x120 },
	{ 0, 0, 0, 0 }
};

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
inline void FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeFireWeaponWhenDamagedBehaviorFields, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}

// Retail VA 0x00BEEE08: 6 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeArrowStormUpdateFields[] = {
	{ "WeaponTemplate", &INI::parseAsciiString, 0, 0xC8 },
	{ "TargetRadius", &INI::parseReal, 0, 0xCC },
	{ "ShotsPerTarget", &INI::parseInt, 0, 0xD0 },
	{ "ShotsPerBurst", &INI::parseInt, 0, 0xD4 },
	{ "MaxShots", &INI::parseInt, 0, 0xD8 },
	{ "CanShootEmptyGround", &INI::parseBool, 0, 0xDC },
	{ 0, 0, 0, 0 }
};

class ArrowStormUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ArrowStormUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024D5AB (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEEE08. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under "ArrowStormUpdate".
void ArrowStormUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeArrowStormUpdateFields, 0);
}

class ModelConditionSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// Retail VA 0x00BEEED0: 5 fields and the zero sentinel.
// The matched registration proves the class relationship; retail supplies
// every token, offset and callback. Global spelling is descriptive.
extern const FieldParse BfmeModelConditionSpecialAbilityUpdateFields[] = {
	{ "WhichSpecialPower", &INI::parseInt, 0, 0xC8 },
	{ "GenerateTerror", &INI::parseBool, 0, 0xCC },
	{ "GenerateUncontrollableFear", &INI::parseBool, 0, 0xCD },
	{ "EmotionPulseRadius", &INI::parseReal, 0, 0xD0 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0xD4 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@ModelConditionSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024D655 (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEEED0. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under
// "ModelConditionSpecialAbilityUpdate".
void ModelConditionSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeModelConditionSpecialAbilityUpdateFields, 0);
}

// Retail VA 0x00BEEF90: 4 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeHeroModeSpecialAbilityUpdateFields[] = {
	{ "HeroAttributeModifier", &INI::parseAsciiString, 0, 0xC8 },
	{ "HeroEffectDuration", &INI::parseDurationUnsignedInt, 0, 0xCC },
	{ "UseUSERModelcondition", &INI::parseBool, 0, 0xD0 },
	{ "StopUnitBeforeActivating", &INI::parseBool, 0, 0xD1 },
	{ 0, 0, 0, 0 }
};

class HeroModeSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HeroModeSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024D9AC (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEEF90. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under
// "HeroModeSpecialAbilityUpdate".
void HeroModeSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeHeroModeSpecialAbilityUpdateFields, 0);
}

// Retail VA 0x00BEF008: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeWeaponSetSpecialAbilityUpdateFields[] = {
	{ "WeaponsetEffectDuration", &INI::parseDurationUnsignedInt, 0, 0xC8 },
	{ "WhichWeaponSet", &INI::parseInt, 0, 0xCC },
	{ 0, 0, 0, 0 }
};

class WeaponSetSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WeaponSetSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024DA56 (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEF008. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under
// "WeaponSetSpecialAbilityUpdate".
void WeaponSetSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeWeaponSetSpecialAbilityUpdateFields, 0);
}

class TeleportSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TeleportSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024DBAA (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEF150. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under
// "TeleportSpecialAbilityUpdate".
void TeleportSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00BEF150TeleportSpecialAbilityFieldParse, 0);
}

// Retail VA 0x00BEF770: 5 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeToggleMountedSpecialAbilityUpdateFields[] = {
	{ "OpacityTarget", &INI::parseReal, 0, 0xC8 },
	{ "TriggerInstantlyOnCreate", &INI::parseBool, 0, 0xCC },
	{ "CancelDisguiseWhenDismounting", &INI::parseBool, 0, 0xCD },
	{ "MountedTemplate", &INI::parseAsciiString, 0, 0xD0 },
	{ "SynchronizeTimerOnSpecialPower", &INI::parseAsciiStringVector, 0, 0xD4 },
	{ 0, 0, 0, 0 }
};

class ToggleMountedSpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ToggleMountedSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024F66F (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEF770. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under
// "ToggleMountedSpecialAbilityUpdate".
void ToggleMountedSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeToggleMountedSpecialAbilityUpdateFields, 0);
}

// Retail VA 0x00BEF8B8: 6 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeSpecialDisguiseUpdateFields[] = {
	{ "OpacityTarget", &INI::parseReal, 0, 0xCC },
	{ "TriggerInstantlyOnCreate", &INI::parseBool, 0, 0xC8 },
	{ "DisguiseAsTemplate", &INI::parseAsciiString, 0, 0xD0 },
	{ "DisguisedAsTemplate_EnemyPerspective", &INI::parseAsciiString, 0, 0xD4 },
	{ "DisguiseFX", &INI::parseFXList, 0, 0xD8 },
	{ "ForceMountedWhenDisguising", &INI::parseBool, 0, 0xDC },
	{ 0, 0, 0, 0 }
};

class SpecialDisguiseUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SpecialDisguiseUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x0024F982 (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEF8B8. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under "SpecialDisguiseUpdate".
void SpecialDisguiseUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeSpecialDisguiseUpdateFields, 0);
}

// Retail VA 0x00BEFE14: 2 fields and the zero sentinel.
// Class identity comes from this unit's matched registration function;
// tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeFellBeastSwoopPowerFields[] = {
	{ "SpecialWeapon", &INI::parseWeaponTemplate, 0, 0xC8 },
	{ "WhichSpecialWeapon", &INI::parseInt, 0, 0xCC },
	{ 0, 0, 0, 0 }
};

class FellBeastSwoopPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FellBeastSwoopPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00252398 (27 bytes): chained on the rowed SpecialAbilityUpdateModuleData base proc at
// 0x44ED95, then table 0x00BEFE14. The owning factory pushes this proc VA
// (unique image-wide); ModuleFactory registers it under "FellBeastSwoopPower".
void FellBeastSwoopPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(BfmeFellBeastSwoopPowerFields, 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// These functions are header inlines; their ordinary owner definitions
// collided with select-any copies. The anchor keeps this unit's row copies;
// it is not retail code.
#pragma inline_depth(0)
// ?_bfmeModuleDataBuildFieldParseChainedInlineAnchor@@YAXPAVMultiIniFieldParse@@@Z absent-from-retail
void _bfmeModuleDataBuildFieldParseChainedInlineAnchor(MultiIniFieldParse *parse)
{
	AutoHealBehaviorModuleData::buildFieldParse(*parse);
	CaveContainModuleData::buildFieldParse(*parse);
	CrushDieModuleData::buildFieldParse(*parse);
	FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse(*parse);
	FireWeaponWhenDeadBehaviorModuleData::buildFieldParse(*parse);
	GarrisonContainModuleData::buildFieldParse(*parse);
	SpawnBehaviorModuleData::buildFieldParse(*parse);
	SpecialPowerCompletionDieModuleData::buildFieldParse(*parse);
	UpgradeDieModuleData::buildFieldParse(*parse);
}
#pragma inline_depth()
