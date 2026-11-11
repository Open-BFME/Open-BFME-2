#include "../../../../Include/GameLogic/Module/RespawnBodyModuleData.h"
#include "../../../../Include/GameLogic/Module/ActiveBodyModuleData.h"


// cl: /O1 /DNDEBUG /MD
//
// Five single-field ModuleData::buildFieldParse procs (11 bytes each):
// ?buildFieldParse@BeaconClientUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C9663 (field RadarPulseFrequency), plus PilotFindVehicle (announcement),
// DynamicGeometryInfo (FX), BattlePlan (SoundUpgrade) and RepairDock (ModelCondition)
// sibs, plus LifetimeUpdate (table (unsigned int)&g_00C1B0F0, factory 0x24E3A3 pushes its VA).
// Each registers exactly one FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Provenance: the ZH
// MAKE_STANDARD_MODULE_DATA_MACRO_ABC macro passes clsmd::buildFieldParse to
// INI::initFromINIMultiProc, and each landed friend_newModuleData factory in
// this directory pushes its class proc immediate (no pin needed there, none
// needed here: the FieldParse address is a pushed absolute). Recipe: the
// factory TUs (*FriendNew.cpp) name the owning class per stub.

class MultiIniFieldParse;

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../../Include/Common/INI/FieldParse.h"
extern const FieldParse AssistedTargetingUpdateModuleDataFieldParse[5];

#include "../../../../Include/Common/INI/INI.h"

#include "../../../../Include/Common/Rva003B1017.h"

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);
void parseFloodMember(INI *ini, void *instance, void *store, const void *userData);
void iniParseFXListVec(INI *ini, void *instance, void *store, const void *userData);

// Retail FieldParse tables of four procs below; tokens, callbacks and offsets
// are read from the retail tables. The global names are descriptive; their
// original spellings are unknown.

// Retail VA 0x00C4DE90: 4 fields and the zero sentinel.
extern const FieldParse BfmePickupStuffUpdateFields[] = {
	{ "SkirmishAIOnly", &INI::parseBool, 0, 0x8 },
	{ "ScanRange", &INI::parseReal, 0, 0xC },
	{ "StuffToPickUp", &iniParseObjectFilter, 0, 0x10 },
	{ "ScanIntervalSeconds", &INI::parseReal, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C564D4: 2 fields and the zero sentinel.
extern const FieldParse BfmeAIGateUpdateFields[] = {
	{ "TriggerWidthX", &INI::parseReal, 0, 0x8 },
	{ "TriggerWidthY", &INI::parseReal, 0, 0xC },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C4DC48: 12 fields and the zero sentinel (retail spells
// ParentEnemyDiedtEvaEvent).
extern const FieldParse BfmeAttachUpdateFields[] = {
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x8 },
	{ "ScanRange", &INI::parseReal, 0, 0x1C },
	{ "ParentStatus", &Rva003B1017::parseFromINI, 0, 0xC },
	{ "AlwaysTeleport", &INI::parseBool, 0, 0x20 },
	{ "AnchorToTopOfGeometry", &INI::parseBool, 0, 0x21 },
	{ "ParentOwnerAttachmentEvaEvent", &Rva001DEE74Parse, 0, 0x24 },
	{ "ParentAllyAttachmentEvaEvent", &Rva001DEE74Parse, 0, 0x28 },
	{ "ParentEnemyAttachmentEvaEvent", &Rva001DEE74Parse, 0, 0x2C },
	{ "AttachFX", &INI::parseFXList, 0, 0x30 },
	{ "ParentOwnerDiedEvaEvent", &Rva001DEE74Parse, 0, 0x34 },
	{ "ParentAllyDiedEvaEvent", &Rva001DEE74Parse, 0, 0x38 },
	{ "ParentEnemyDiedtEvaEvent", &Rva001DEE74Parse, 0, 0x3C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C4C9A8: 3 fields and the zero sentinel.
extern const FieldParse BfmeFloodUpdateFields[] = {
	{ "FloodMember", &parseFloodMember, 0, 0x0 },
	{ "AngleOfFlow", &INI::parseAngleReal, 0, 0xC },
	{ "DirectionIsRelative", &INI::parseBool, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C50BA8: 5 fields and the zero sentinel.
extern const FieldParse BfmeOCLUpdateFields[] = {
	{ "OCL", &INI::parseObjectCreationList, 0, 0x8 },
	{ "MinDelay", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "MaxDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "CreateAtEdge", &INI::parseBool, 0, 0x18 },
	{ "Amount", &INI::parseInt, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C59238: 3 fields and the zero sentinel.
extern const FieldParse BfmeSpawnUnitBehaviorFields[] = {
	{ "UnitName", &INI::parseAsciiString, 0, 0x8 },
	{ "UnitCommand", &INI::parseAsciiString, 0, 0xC },
	{ "SpawnOnce", &INI::parseBool, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C5EA10: 3 fields and the zero sentinel.
extern const FieldParse BfmeCritterEmitterUpdateFields[] = {
	{ "FX", &iniParseFXListVec, 0, 0x8 },
	{ "ReloadTime", &INI::parseDurationUnsignedInt, 0, 0x20 },
	{ "SpawnObject", &INI::Rva004C8F94_ParseSpawnObject, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C1B1F8: 6 fields and the zero sentinel (retail spells
// Sweepfrequency).
extern const FieldParse BfmeStrafeAreaUpdateFields[] = {
	{ "WeaponName", &INI::parseAsciiString, 0, 0x8 },
	{ "StrafeAreaRadius", &INI::parseReal, 0, 0xC },
	{ "Sweepfrequency", &INI::parseReal, 0, 0x10 },
	{ "SweepAmplitude", &INI::parseReal, 0, 0x14 },
	{ "Slope", &INI::parseReal, 0, 0x18 },
	{ "InitialSweepPhase", &INI::parseReal, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C5ED98: 1 field and the zero sentinel.
extern const FieldParse BfmeRadarMarkerClientUpdateFields[] = {
	{ "MarkerType", &INI::parseAsciiString, 0, 0x8 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C4C000: 4 fields and the zero sentinel. Name agreed blind
// (reverse/name_agreed.csv nl-d64c0c845213).
extern const FieldParse FireSpreadUpdateModuleDataFieldParse[] = {
	{ "OCLEmbers", &INI::parseObjectCreationList, 0, 0x8 },
	{ "MinSpreadDelay", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "MaxSpreadDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "SpreadTryRange", &INI::parseReal, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

// The FieldParse tables of the procs below, read from retail: every token, parser,
// userData and offset is retail's. They were 1-byte zero placeholders, so in a
// linked game each module's INI block met an empty table. The parsers are the
// matched rows at retail's pointers; class statics and odd signatures are named
// by their decorated names.
void Rva002C8C06Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva003393DFParse(INI *ini, void *instance, void *store, const void *userData);
void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);
void Rva0048BCBBParse(INI *ini, void *instance, void *store, const void *userData);
void Rva0048D65FParse(INI *ini, void *instance, void *store, const void *userData);
void Rva000B9468Parse(INI *ini, void *instance, void *store, const void *userData);
void parseBannerCarrierMorphCondition(INI *ini, void *instance, void *store, const void *userData);
void parseBannerCarrierExpLevelDraw(INI *ini, void *instance, void *store, const void *userData);
void Rva0049DE6DParse(INI *ini, void *instance, void *store, const void *userData);
void Rva00438176Parse(INI *ini, void *instance, void *store, const void *userData);
void parseAngleFX(INI *ini, void *instance, void *store, const void *userData);
void Rva00339D74ParseCurve(INI *ini, void *instance, void *store, const void *userData);
void Rva004AEB84Parse(INI *ini, void *instance, void *store, const void *userData);
void parseSpecialPowerAIType(INI *ini, void *instance, void *store, const void *userData);
void Rva004BFD83Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva004CB047Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva004CC371Parse(INI *ini, void *instance, void *store, const void *userData);
void parseGeometryRotationAnchorOffset(INI *ini, void *instance, void *store, const void *userData);
extern "C" {
void __identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva003A47F3Parse@@YAXPAVINI@@PAVRva003A47F3Owner@@@Z")();
void __identifier("?IniParseEmotionType@EmotionNuggetTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFX@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseOCL@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseWeapon@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?rva0045E8A9@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseDeathFlags@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva0049B8A0@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseRadiusDecalTemplate@RadiusDecalTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?iniParseEatObjectEntry@AutoPickUpUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0049FDF9Parse@@YAXPAVINI@@PAVProductionUpdateModuleData@@@Z")();
void __identifier("?parseFromINI@Rva0049DD83@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
void __identifier("?rva004A646B@StructureToppleUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseAudioKeyTokens@Rva003D4920@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?IniParseAddEmotion@EmotionTrackerUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseSoundUpgrade@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGeometryType@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGeometryMajorRadius@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGeometryMinorRadius@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGeometryHeight@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGeometryIsSmall@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z")();
}

struct LookupListRec { const char *name; int value; };
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[];
// EvacuateDamage.cpp, the proc's approved unit, defines its table with that unit's names.
extern const FieldParse g_00C59DD0[];

// StealthUpdate's stealth level names (StealthForbiddenConditions), this unit's copy (a static in every unit that defines it) at retail
// .data 0x00DC03DC: 13 names and a null.
static const char *TheStealthLevelNames[] =
{
	"ATTACKING",
	"MOVING",
	"USING_ABILITY",
	"FIRING_PRIMARY",
	"FIRING_SECONDARY",
	"FIRING_TERTIARY",
	"FIRING_QUATERNARY",
	"FIRING_QUINARY",
	"MOUNTED",
	"AWAY_FROM_TREES",
	"HORDEBRAIN_NOT_STEALTHED",
	"PRIMARY_FORMATION",
	"TAKING_DAMAGE",
	0
};

// BFME 2's death type names (LifetimeUpdate's DeathType), this unit's copy (a static in every unit that defines it) at retail
// .data 0x00DC09C0: 24 names and a null.
static const char *TheDeathNames[] =
{
	"NORMAL",
	"NONE",
	"CRUSHED",
	"BURNED",
	"EXPLODED",
	"POISONED",
	"TOPPLED",
	"FLOODED",
	"SUICIDED",
	"LASERED",
	"DETONATED",
	"SPLATTED",
	"POISONED_BETA",
	"EXTRA_2",
	"EXTRA_3",
	"EXTRA_4",
	"EXTRA_5",
	"EXTRA_6",
	"EXTRA_7",
	"EXTRA_8",
	"KNOCKBACK",
	"SUPERNATURAL",
	"FADED",
	"SLAUGHTERED",
	0
};

// BFME 2's damage type names (FlammableUpdate's DamageType), this unit's copy (a static in every unit that defines it) at retail
// .data 0x00DCA800: 27 names and a null.
static const char *TheDamageNames[] =
{
	"FORCE",
	"CRUSH",
	"SLASH",
	"PIERCE",
	"SIEGE",
	"STRUCTURAL",
	"FLAME",
	"HEALING",
	"UNRESISTABLE",
	"WATER",
	"PENALTY",
	"FALLING",
	"TOPPLING",
	"REFLECTED",
	"PASSENGER",
	"MAGIC",
	"CHOP",
	"HERO",
	"SPECIALIST",
	"URUK",
	"HERO_RANGED",
	"FLY_INTO",
	"UNDEFINED",
	"LOGICAL_FIRE",
	"CAVALRY",
	"CAVALRY_RANGED",
	"POISON",
	0
};

// Retail VA 0x00BF1158: 99 fields and the zero sentinel.
extern const FieldParse g_00BF1158[] = {
	{ "DamageFXTypes", &INI::parseDamageTypeFlags, 0, 0x8 },
	{ "DamageOCLTypes", &INI::parseDamageTypeFlags, 0, 0x48C },
	{ "DamageParticleTypes", &INI::parseDamageTypeFlags, 0, 0x910 },
	{ "PristineFXList1", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
	{ "PristineFXList2", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x30 },
	{ "PristineFXList3", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x54 },
	{ "PristineFXList4", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x78 },
	{ "PristineFXList5", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x9C },
	{ "PristineFXList6", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC0 },
	{ "PristineFXList7", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xE4 },
	{ "PristineFXList8", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x108 },
	{ "DamagedFXList1", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x12C },
	{ "DamagedFXList2", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x150 },
	{ "DamagedFXList3", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x174 },
	{ "DamagedFXList4", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x198 },
	{ "DamagedFXList5", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1BC },
	{ "DamagedFXList6", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1E0 },
	{ "DamagedFXList7", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x204 },
	{ "DamagedFXList8", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x228 },
	{ "ReallyDamagedFXList1", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x24C },
	{ "ReallyDamagedFXList2", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x270 },
	{ "ReallyDamagedFXList3", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x294 },
	{ "ReallyDamagedFXList4", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2B8 },
	{ "ReallyDamagedFXList5", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2DC },
	{ "ReallyDamagedFXList6", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x300 },
	{ "ReallyDamagedFXList7", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x324 },
	{ "ReallyDamagedFXList8", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x348 },
	{ "RubbleFXList1", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x36C },
	{ "RubbleFXList2", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x390 },
	{ "RubbleFXList3", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3B4 },
	{ "RubbleFXList4", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3D8 },
	{ "RubbleFXList5", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3FC },
	{ "RubbleFXList6", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x420 },
	{ "RubbleFXList7", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x444 },
	{ "RubbleFXList8", (INIFieldParseProc)&__identifier("?parseFXList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x468 },
	{ "PristineOCL1", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x490 },
	{ "PristineOCL2", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4B4 },
	{ "PristineOCL3", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4D8 },
	{ "PristineOCL4", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4FC },
	{ "PristineOCL5", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x520 },
	{ "PristineOCL6", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x544 },
	{ "PristineOCL7", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x568 },
	{ "PristineOCL8", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x58C },
	{ "DamagedOCL1", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5B0 },
	{ "DamagedOCL2", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5D4 },
	{ "DamagedOCL3", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5F8 },
	{ "DamagedOCL4", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x61C },
	{ "DamagedOCL5", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x640 },
	{ "DamagedOCL6", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x664 },
	{ "DamagedOCL7", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x688 },
	{ "DamagedOCL8", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6AC },
	{ "ReallyDamagedOCL1", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6D0 },
	{ "ReallyDamagedOCL2", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6F4 },
	{ "ReallyDamagedOCL3", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x718 },
	{ "ReallyDamagedOCL4", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x73C },
	{ "ReallyDamagedOCL5", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x760 },
	{ "ReallyDamagedOCL6", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x784 },
	{ "ReallyDamagedOCL7", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7A8 },
	{ "ReallyDamagedOCL8", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7CC },
	{ "RubbleOCL1", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7F0 },
	{ "RubbleOCL2", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x814 },
	{ "RubbleOCL3", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x838 },
	{ "RubbleOCL4", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x85C },
	{ "RubbleOCL5", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x880 },
	{ "RubbleOCL6", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8A4 },
	{ "RubbleOCL7", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8C8 },
	{ "RubbleOCL8", (INIFieldParseProc)&__identifier("?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8EC },
	{ "PristineParticleSystem1", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x914 },
	{ "PristineParticleSystem2", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x938 },
	{ "PristineParticleSystem3", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x95C },
	{ "PristineParticleSystem4", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x980 },
	{ "PristineParticleSystem5", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x9A4 },
	{ "PristineParticleSystem6", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x9C8 },
	{ "PristineParticleSystem7", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x9EC },
	{ "PristineParticleSystem8", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA10 },
	{ "DamagedParticleSystem1", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA34 },
	{ "DamagedParticleSystem2", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA58 },
	{ "DamagedParticleSystem3", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA7C },
	{ "DamagedParticleSystem4", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xAA0 },
	{ "DamagedParticleSystem5", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xAC4 },
	{ "DamagedParticleSystem6", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xAE8 },
	{ "DamagedParticleSystem7", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB0C },
	{ "DamagedParticleSystem8", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB30 },
	{ "ReallyDamagedParticleSystem1", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB54 },
	{ "ReallyDamagedParticleSystem2", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB78 },
	{ "ReallyDamagedParticleSystem3", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB9C },
	{ "ReallyDamagedParticleSystem4", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xBC0 },
	{ "ReallyDamagedParticleSystem5", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xBE4 },
	{ "ReallyDamagedParticleSystem6", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC08 },
	{ "ReallyDamagedParticleSystem7", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC2C },
	{ "ReallyDamagedParticleSystem8", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC50 },
	{ "RubbleParticleSystem1", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC74 },
	{ "RubbleParticleSystem2", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC98 },
	{ "RubbleParticleSystem3", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xCBC },
	{ "RubbleParticleSystem4", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xCE0 },
	{ "RubbleParticleSystem5", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD04 },
	{ "RubbleParticleSystem6", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD28 },
	{ "RubbleParticleSystem7", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD4C },
	{ "RubbleParticleSystem8", (INIFieldParseProc)&__identifier("?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD70 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF17BC: 2 fields and the zero sentinel.
extern const FieldParse g_00BF17BC[] = {
	{ "MinLifetime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "MaxLifetime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF1B88: 3 fields and the zero sentinel.
extern const FieldParse g_00BF1B88[] = {
	{ "SpecialEnemyFilter", &iniParseObjectFilter, 0, 0x8 },
	{ "ScanRange", &INI::parseReal, 0, 0xC },
	{ "ScanInterval", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF1CC8: 8 fields and the zero sentinel.
extern const FieldParse g_00BF1CC8[] = {
	{ "DepositTiming", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "Upgrade", &INI::parseUpgradeTemplate, 0, 0x14 },
	{ "DepositAmount", &INI::parseInt, 0, 0xC },
	{ "InitialCaptureBonus", &INI::parseInt, 0, 0x10 },
	{ "UpgradeBonusPercent", &INI::parsePercentToReal, 0, 0x18 },
	{ "UpgradeMustBePresent", &iniParseObjectFilter, 0, 0x1C },
	{ "GiveNoXP", &INI::parseBool, 0, 0x20 },
	{ "OnlyWhenGarrisoned", &INI::parseBool, 0, 0x21 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF1EF8: 1 fields and the zero sentinel.
extern const FieldParse g_00BF1EF8[] = {
	{ "RadarExtendTime", &INI::parseDurationReal, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF2110: 26 fields and the zero sentinel.
extern const FieldParse g_00BF2110[] = {
	{ "LeashRange", &INI::parseInt, 0, 0x8 },
	{ "GuardMaxRange", &INI::parseInt, 0, 0xC },
	{ "GuardWanderRange", &INI::parseInt, 0, 0x10 },
	{ "AttackRange", &INI::parseInt, 0, 0x14 },
	{ "AttackWanderRange", &INI::parseInt, 0, 0x18 },
	{ "ScoutRange", &INI::parseInt, 0, 0x1C },
	{ "ScoutWanderRange", &INI::parseInt, 0, 0x20 },
	{ "RepairRange", &INI::parseInt, 0, 0x28 },
	{ "RepairMinAltitude", &INI::parseReal, 0, 0x2C },
	{ "RepairMaxAltitude", &INI::parseReal, 0, 0x30 },
	{ "DistToTargetToGrantRangeBonus", &INI::parseInt, 0, 0x24 },
	{ "RepairRatePerSecond", &INI::parseReal, 0, 0x34 },
	{ "RepairWhenBelowHealth%", &INI::parseInt, 0, 0x38 },
	{ "RepairMinReadyTime", &INI::parseDurationUnsignedInt, 0, 0x3C },
	{ "RepairMaxReadyTime", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "RepairMinWeldTime", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ "RepairMaxWeldTime", &INI::parseDurationUnsignedInt, 0, 0x48 },
	{ "RepairWeldingSys", &INI::parseAsciiString, 0, 0x4C },
	{ "RepairWeldingFXBone", &INI::parseAsciiString, 0, 0x50 },
	{ "StayOnSameLayerAsMaster", &INI::parseBool, 0, 0x54 },
	{ "UseSlaverAsControlForEvaObjectSightedEvents", &INI::parseBool, 0, 0x6D },
	{ "DieOnMastersDeath", &INI::parseBool, 0, 0x55 },
	{ "GuardPositionOffset", &INI::parseCoord3D, 0, 0x58 },
	{ "FadeOutRange", &INI::parseInt, 0, 0x64 },
	{ "FadeTime", &INI::parseDurationUnsignedInt, 0, 0x68 },
	{ "MarkUnselectable", &INI::parseBool, 0, 0x6C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF22D4: 1 fields and the zero sentinel.
extern const FieldParse g_00BF22D4[] = {
	{ "SpawnPointBoneName", &INI::parseAsciiString, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF2318: 2 fields and the zero sentinel.
extern const FieldParse g_00BF2318[] = {
	{ "AttachToTargetBone", &INI::parseAsciiString, 0, 0x8 },
	{ "ParachuteName", &INI::parseAsciiString, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BF2398: 2 fields and the zero sentinel.
extern const FieldParse g_00BF2398[] = {
	{ "UnitCreatePoint", &INI::parseCoord3D, 0, 0x8 },
	{ "NaturalRallyPoint", &INI::parseCoord3D, 0, 0x14 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C17208: 5 fields and the zero sentinel.
extern const FieldParse g_00C17208[] = {
	{ "MuzzleParticleSystem", &INI::parseAsciiString, 0, 0x8 },
	{ "TargetParticleSystem", &INI::parseAsciiString, 0, 0x14 },
	{ "ParentFireBoneName", &INI::parseAsciiString, 0, 0xC },
	{ "ParentFireBoneOnTurret", &INI::parseBool, 0, 0x10 },
	{ "LaserLifetime", &INI::parseReal, 0, 0x18 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C18210: 36 fields and the zero sentinel.
extern const FieldParse g_00C18210[] = {
	{ "StealthDelay", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "MoveThresholdSpeed", &INI::parseVelocityReal, 0, 0x20 },
	{ "StealthForbiddenConditions", &INI::parseBitString32, TheStealthLevelNames, 0xC },
	{ "RemoveTerrainRestrictionOnUpgrade", &INI::parseAsciiStringVector, 0, 0x74 },
	{ "HintDetectableConditions", &Rva003B1017::parseFromINI, 0, 0x10 },
	{ "FriendlyOpacityMin", &INI::parsePercentToReal, 0, 0x24 },
	{ "FriendlyOpacityMax", &INI::parsePercentToReal, 0, 0x28 },
	{ "PulseFrequency", &INI::parseDurationUnsignedInt, 0, 0x2C },
	{ "DisguisesAsTeam", &INI::parseBool, 0, 0x30 },
	{ "RevealDistanceFromTarget", &INI::parseReal, 0, 0x34 },
	{ "OrderIdleEnemiesToAttackMeUponReveal", &INI::parseBool, 0, 0x38 },
	{ "DisguiseFX", &INI::parseFXList, 0, 0x40 },
	{ "DisguiseRevealFX", &INI::parseFXList, 0, 0x3C },
	{ "DisguiseTransitionTime", &INI::parseDurationUnsignedInt, 0, 0x58 },
	{ "DisguiseRevealTransitionTime", &INI::parseDurationUnsignedInt, 0, 0x5C },
	{ "StartsActive", &INI::parseBool, 0, 0x54 },
	{ "InnateStealth", &INI::parseBool, 0, 0x55 },
	{ "DetectedByFriendliesOnly", &INI::parseBool, 0, 0x56 },
	{ "DetectedByAnyoneRange", &INI::parseReal, 0, 0x60 },
	{ "BecomeStealthedFX", &INI::parseFXList, 0, 0x44 },
	{ "ExitStealthFX", &INI::parseFXList, 0, 0x48 },
	{ "RevealWeaponSets", &Rva002C8C06Parse, 0, 0x64 },
	{ "VoiceMoveToStealthyArea", &Rva003393DFParse, 0, 0x80 },
	{ "VoiceEnterStateMoveToStealthyArea", &Rva003393DFParse, 0, 0x88 },
	{ "OneRingDelayOn", &INI::parseDurationUnsignedInt, 0, 0x90 },
	{ "OneRingDelayOff", &INI::parseDurationUnsignedInt, 0, 0x94 },
	{ "RingAnimTimeOn", &INI::parseDurationUnsignedInt, 0, 0x98 },
	{ "RingAnimTimeOff", &INI::parseDurationUnsignedInt, 0, 0x9C },
	{ "RingDelayAfterRemoving", &INI::parseDurationUnsignedInt, 0, 0xA0 },
	{ "BecomeStealthedOneRingFX", &INI::parseFXList, 0, 0x4C },
	{ "ExitStealthOneRingFX", &INI::parseFXList, 0, 0x50 },
	{ "EvaEventDetectedEnemy", &Rva001DEE74Parse, 0, 0xA4 },
	{ "EvaEventDetectedAlly", &Rva001DEE74Parse, 0, 0xA8 },
	{ "EvaEventDetectedOwner", &Rva001DEE74Parse, 0, 0xAC },
	{ "RequiredUpgradeNames", &INI::parseAsciiStringVector, 0, 0xB0 },
	{ "ForbiddenUpgradeNames", &INI::parseAsciiStringVector, 0, 0xBC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C1B00C: 1 fields and the zero sentinel.
extern const FieldParse g_00C1B00C[] = {
	{ "SpawnerTrigger", (INIFieldParseProc)&__identifier("?Rva003A47F3Parse@@YAXPAVINI@@PAVRva003A47F3Owner@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C1B0F0: 5 fields and the zero sentinel.
extern const FieldParse g_00C1B0F0[] = {
	{ "MinLifetime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "MaxLifetime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "WaitForWakeUp", &INI::parseBool, 0, 0x10 },
	{ "ScoreKill", &INI::parseBool, 0, 0x11 },
	{ "DeathType", &INI::parseIndexList, TheDeathNames, 0x14 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C3F120: 3 fields and the zero sentinel.
extern const FieldParse g_00C3F120[] = {
	{ "SacrificeFilter", &iniParseObjectFilter, 0, 0x8 },
	{ "ExperienceModifier", &INI::parseReal, 0, 0xC },
	{ "InitiateVoice", &Rva003393DFParse, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C413E4: 1 fields and the zero sentinel.
extern const FieldParse g_00C413E4[] = {
	{ "DUMMY", &INI::parseInt, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C41690: 11 fields and the zero sentinel.
extern const FieldParse g_00C41690[] = {
	{ "SpecialAbility", &INI::parseAsciiString, 0, 0x18 },
	{ "MaxScanRange", &INI::parseReal, 0, 0x8 },
	{ "MinScanRange", &INI::parseReal, 0, 0xC },
	{ "WorkingRadius", &INI::parseReal, 0, 0x10 },
	{ "StartsActive", &INI::parseBool, 0, 0x5C },
	{ "BaseMaxRangeFromStartPos", &INI::parseBool, 0, 0x5D },
	{ "AdjustAttackMeleePosition", &INI::parseBool, 0, 0x5E },
	{ "Query", &INI::Rva0045A22E_ParseQuery, 0, 0x2C },
	{ "AllowSelf", &INI::parseBool, 0, 0x5F },
	{ "IdleTimeSeconds", &INI::parseReal, 0, 0x14 },
	{ "ForbiddenStatus", &Rva003B1017::parseFromINI, 0, 0x1C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C41B58: 38 fields and the zero sentinel.
extern const FieldParse g_00C41B58[] = {
	{ "TumbleRandomly", &INI::parseBool, 0, 0x48 },
	{ "DetonateCallsKill", &INI::parseBool, 0, 0x4A },
	{ "OrientToFlightPath", &INI::parseBool, 0, 0x49 },
	{ "FirstHeight", &INI::parseReal, 0, 0x8 },
	{ "SecondHeight", &INI::parseReal, 0, 0xC },
	{ "FirstPercentIndent", &INI::parsePercentToReal, 0, 0x10 },
	{ "SecondPercentIndent", &INI::parsePercentToReal, 0, 0x14 },
	{ "CrushStyle", &INI::parseBool, 0, 0x18 },
	{ "DieOnImpact", &INI::parseBool, 0, 0x19 },
	{ "FinalStuckTime", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "PreLandingStateTime", &INI::parseDurationUnsignedInt, 0, 0x3C },
	{ "BounceCount", &INI::parseInt, 0, 0x1C },
	{ "BounceDistance", &INI::parseReal, 0, 0x20 },
	{ "BounceFirstHeight", &INI::parseReal, 0, 0x24 },
	{ "BounceSecondHeight", &INI::parseReal, 0, 0x28 },
	{ "BounceFirstPercentIndent", &INI::parsePercentToReal, 0, 0x2C },
	{ "BounceSecondPercentIndent", &INI::parsePercentToReal, 0, 0x30 },
	{ "GarrisonHitKillRequiredKindOf", &Rva002567EAParse, 0, 0x50 },
	{ "GarrisonHitKillForbiddenKindOf", &Rva002567EAParse, 0, 0x6C },
	{ "GarrisonHitKillCount", &INI::parseUnsignedInt, 0, 0x4C },
	{ "GarrisonHitKillFX", &INI::parseFXList, 0, 0x88 },
	{ "GroundHitFX", &INI::parseFXList, 0, 0x9C },
	{ "GroundBounceFX", &INI::parseFXList, 0, 0xA0 },
	{ "GroundHitWeapon", &INI::parseWeaponTemplate, 0, 0xA4 },
	{ "GroundBounceWeapon", &INI::parseWeaponTemplate, 0, 0xA8 },
	{ "FlightPathAdjustDistPerSecond", &INI::parseVelocityReal, 0, 0x8C },
	{ "IgnoreTerrainHeight", &INI::parseBool, 0, 0x90 },
	{ "FirstPercentHeight", &INI::parsePercentToReal, 0, 0x94 },
	{ "SecondPercentHeight", &INI::parsePercentToReal, 0, 0x98 },
	{ "CurveFlattenMinDist", &INI::parseReal, 0, 0x34 },
	{ "PreLandingEmotion", (INIFieldParseProc)&__identifier("?IniParseEmotionType@EmotionNuggetTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xAC },
	{ "PreLandingEmotionRadius", &INI::parseReal, 0, 0xB0 },
	{ "PreLandingEmotionAffectsAllies", &INI::parseBool, 0, 0xB4 },
	{ "InvisibleFrames", &INI::parseUnsignedInt, 0, 0x40 },
	{ "FadeInTime", &INI::parseUnsignedInt, 0, 0x44 },
	{ "PostLandingStateTime", &INI::parseDurationUnsignedInt, 0, 0xB8 },
	{ "PostLandingEmotion", (INIFieldParseProc)&__identifier("?IniParseEmotionType@EmotionNuggetTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xBC },
	{ "PostLandingEmotionRadius", &INI::parseReal, 0, 0xC0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C42290: 20 fields and the zero sentinel.
extern const FieldParse g_00C42290[] = {
	{ "SinkRate", &INI::parseVelocityReal, 0, 0x38 },
	{ "ProbabilityModifier", &INI::parseInt, 0, 0x3C },
	{ "ModifierBonusPerOverkillPercent", &INI::parsePercentToReal, 0, 0x40 },
	{ "SinkDelay", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ "SinkDelayVariance", &INI::parseDurationUnsignedInt, 0, 0x48 },
	{ "DestructionDelay", &INI::parseDurationUnsignedInt, 0, 0x4C },
	{ "DestructionDelayVariance", &INI::parseDurationUnsignedInt, 0, 0x50 },
	{ "DecayBeginTime", &INI::parseDurationUnsignedInt, 0, 0x54 },
	{ "FX", (INIFieldParseProc)&__identifier("?parseFX@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "OCL", (INIFieldParseProc)&__identifier("?parseOCL@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "Weapon", (INIFieldParseProc)&__identifier("?parseWeapon@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "Sound", (INIFieldParseProc)&__identifier("?rva0045E8A9@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "FlingForce", &INI::parseReal, 0, 0x118 },
	{ "FlingForceVariance", &INI::parseReal, 0, 0x11C },
	{ "FlingPitch", &INI::parseAngleReal, 0, 0x120 },
	{ "FlingPitchVariance", &INI::parseAngleReal, 0, 0x124 },
	{ "DeathFlags", (INIFieldParseProc)&__identifier("?parseDeathFlags@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "ShadowWhenDead", &INI::parseBool, 0, 0x18D },
	{ "FadeDelay", &INI::parseDurationUnsignedInt, 0, 0x188 },
	{ "FadeTime", &INI::parseDurationUnsignedInt, 0, 0x184 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C424B0: 1 fields and the zero sentinel.
extern const FieldParse g_00C424B0[] = {
	{ "StanceTemplate", (INIFieldParseProc)&__identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C494F0: 8 fields and the zero sentinel.
extern const FieldParse g_00C494F0[] = {
	{ "Radius", &INI::parseReal, 0, 0x8 },
	{ "MaxIncome", &INI::parseInt, 0, 0xC },
	{ "IncomeInterval", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "HighPriority", &INI::parseBool, 0, 0x14 },
	{ "Visible", &INI::parseBool, 0, 0x15 },
	{ "Upgrade", &INI::parseUpgradeTemplate, 0, 0x1C },
	{ "UpgradeBonusPercent", &INI::parsePercentToReal, 0, 0x20 },
	{ "UpgradeMustBePresent", &iniParseObjectFilter, 0, 0x18 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C49918: 2 fields and the zero sentinel.
extern const FieldParse g_00C49918[] = {
	{ "PoisonDamageInterval", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "PoisonDuration", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C49A10: 3 fields and the zero sentinel.
extern const FieldParse g_00C49A10[] = {
	{ "WorkerObjectName", &INI::parseAsciiString, 0, 0x10 },
	{ "WorkerRespawnDelay", &INI::parseDurationReal, 0, 0x8 },
	{ "HoleHealthRegen%PerSecond", &INI::parsePercentToReal, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C49B40: 3 fields and the zero sentinel.
extern const FieldParse g_00C49B40[] = {
	{ "SelfHealSupression", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "SelfHealDelay", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "SelfHealAmount", &INI::parseReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4A388: 10 fields and the zero sentinel.
extern const FieldParse g_00C4A388[] = {
	{ "EffectRadius", &INI::parseReal, 0, 0x8 },
	{ "PingDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "HealPercentPerSecond", &INI::parsePercentToReal, 0, 0xC },
	{ "ModifierName", &INI::parseAsciiStringVectorAppend, 0, 0x14 },
	{ "AllowFilter", &iniParseObjectFilter, 0, 0x20 },
	{ "UpgradeRequired", &INI::parseAsciiString, 0, 0x24 },
	{ "NonStackable", &INI::parseBool, 0, 0x28 },
	{ "AntiCategories", (INIFieldParseProc)&__identifier("?parseFromINI@Rva0049B8A0@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
	{ "AntiFX", &INI::parseFXList, 0, 0x30 },
	{ "HealFX", &INI::parseFXList, 0, 0x34 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4BE20: 8 fields and the zero sentinel.
extern const FieldParse g_00C4BE20[] = {
	{ "ChangeInterval", &INI::parseDurationUnsignedInt, 0, 0x1C },
	{ "GrowInterval", &INI::parseDurationUnsignedInt, 0, 0x20 },
	{ "ShrinkDelay", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "ShrinkTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "GrowDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "GrowTime", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "FinalVision", &INI::parseReal, 0, 0x18 },
	{ "GridDecalTemplate", (INIFieldParseProc)&__identifier("?parseRadiusDecalTemplate@RadiusDecalTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x28 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4C210: 4 fields and the zero sentinel.
extern const FieldParse g_00C4C210[] = {
	{ "FireWeaponNugget", &Rva0048BCBBParse, 0, 0x0 },
	{ "HeroModeTrigger", &INI::parseBool, 0, 0xC },
	{ "ChargingModeTrigger", &INI::parseBool, 0, 0xD },
	{ "AliveOnly", &INI::parseBool, 0, 0xE },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4C600: 21 fields and the zero sentinel.
extern const FieldParse g_00C4C600[] = {
	{ "BurnedDelay", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "AflameDuration", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "AflameDamageDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "AflameDamageAmount", &INI::parseInt, 0, 0x14 },
	{ "BurningSoundName", &INI::parseAudioEventRTS, 0, 0x18 },
	{ "FlameDamageLimit", &INI::parseReal, 0, 0x1C },
	{ "FlameDamageExpiration", &INI::parseDurationUnsignedInt, 0, 0x20 },
	{ "FireFXList", &Rva0048D65FParse, 0, 0x0 },
	{ "SetBurnedStatus", &INI::parseBool, 0, 0x34 },
	{ "SwapModelWhenAflame", &INI::parseBool, 0, 0x35 },
	{ "SwapModelWhenQuenched", &INI::parseBool, 0, 0x36 },
	{ "SwapTextureWhenAflame", &INI::parseBool, 0, 0x37 },
	{ "SwapTextureWhenQuenhed", &INI::parseBool, 0, 0x38 },
	{ "BurnContained", &INI::parseBool, 0, 0x39 },
	{ "RunToWater", &INI::parseBool, 0, 0x3A },
	{ "RunToWaterDepth", &INI::parseReal, 0, 0x3C },
	{ "RunToWaterSearchRadius", &INI::parseReal, 0, 0x40 },
	{ "RunToWaterSearchIncrement", &INI::parseReal, 0, 0x44 },
	{ "PanicLocomotorWhileAflame", &INI::parseBool, 0, 0x48 },
	{ "CustomAnimAndDuration", &INI::iniParseAnimAndDuration, 0, 0x4C },
	{ "DamageType", &INI::parseIndexList, TheDamageNames, 0x24 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4C7A4: 1 fields and the zero sentinel.
extern const FieldParse g_00C4C7A4[] = {
	{ "Enabled", &INI::parseBool, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4CFC8: 6 fields and the zero sentinel.
extern const FieldParse g_00C4CFC8[] = {
	{ "TargetHeight", &INI::parseReal, 0, 0x8 },
	{ "TargetHeightIncludesStructures", &INI::parseBool, 0, 0xC },
	{ "OnlyWhenMovingDown", &INI::parseBool, 0, 0xD },
	{ "DestroyAttachedParticlesAtHeight", &INI::parseReal, 0, 0x10 },
	{ "SnapToGroundOnDeath", &INI::parseBool, 0, 0x14 },
	{ "InitialDelay", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4D1A8: 8 fields and the zero sentinel.
extern const FieldParse g_00C4D1A8[] = {
	{ "UpdateRate", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "HordeMemberFilter", &iniParseObjectFilter, 0, 0xC },
	{ "Count", &INI::parseInt, 0, 0x10 },
	{ "Radius", &INI::parseReal, 0, 0x14 },
	{ "RubOffRadius", &INI::parseReal, 0, 0x1C },
	{ "AlliesOnly", &INI::parseBool, 0, 0x18 },
	{ "FlagSubObjectNames", &INI::parseAsciiStringVector, 0, 0x20 },
	{ "AttributeModifier", &INI::parseAsciiString, 0, 0x2C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4DA00: 4 fields and the zero sentinel.
extern const FieldParse g_00C4DA00[] = {
	{ "ModelConditionFlags", &Rva000B9468Parse, 0, 0x8 },
	{ "ModelConditionCommandSet", &INI::parseAsciiString, 0, 0x54 },
	{ "WeaponSetFlags", &Rva002C8C06Parse, 0, 0x58 },
	{ "WeaponToggleCommandSet", &INI::parseAsciiString, 0, 0x68 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4EC68: 4 fields and the zero sentinel.
extern const FieldParse g_00C4EC68[] = {
	{ "ScanRate", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "ScanRange", &INI::parseReal, 0, 0xC },
	{ "NeverHeal", &INI::parseReal, 0, 0x10 },
	{ "AlwaysHeal", &INI::parseReal, 0, 0x14 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4EEC8: 10 fields and the zero sentinel.
extern const FieldParse g_00C4EEC8[] = {
	{ "DefaultProximityMode", &INI::parseBool, 0, 0x3C },
	{ "DetonationWeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x2C },
	{ "ProximityModeWeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x30 },
	{ "ManualModeWeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x28 },
	{ "TriggerDetonationRange", &INI::parseReal, 0, 0x34 },
	{ "IgnoreTargetTypes", &Rva002567EAParse, 0, 0xC },
	{ "ScanRate", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "AutoDetonationWithFriendsInvolved", &INI::parseBool, 0, 0x3D },
	{ "DetonationWeapon", &INI::parseWeaponTemplate, 0, 0x8 },
	{ "DetonateWhenKilled", &INI::parseBool, 0, 0x3E },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4F4B8: 8 fields and the zero sentinel.
extern const FieldParse g_00C4F4B8[] = {
	{ "ScanDelayTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "PickUpFilter", &iniParseObjectFilter, 0, 0xC },
	{ "ScanDistance", &INI::parseReal, 0, 0x10 },
	{ "EatObjectEntry", (INIFieldParseProc)&__identifier("?iniParseEatObjectEntry@AutoPickUpUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x14 },
	{ "AutoThrowObject", &INI::parseBool, 0, 0x20 },
	{ "RunFromButton", &INI::parseBool, 0, 0x21 },
	{ "RunFromButtonNumber", &INI::parseInt, 0, 0x24 },
	{ "CanScanWhileAttackingOrMoving", &INI::parseBool, 0, 0x28 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4F618: 5 fields and the zero sentinel.
extern const FieldParse g_00C4F618[] = {
	{ "ScanDelayTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "ScanDistance", &INI::parseReal, 0, 0xC },
	{ "BoredFilter", &iniParseObjectFilter, 0, 0x10 },
	{ "CanScanWhileAttackingOrMoving", &INI::parseBool, 0, 0x14 },
	{ "SpecialPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x18 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C4F9E8: 12 fields and the zero sentinel.
extern const FieldParse g_00C4F9E8[] = {
	{ "IdleSpawnRate", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "MeleeFreeUnitSpawnTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "DiedRespawnTime", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "MeleeFreeBannerReSpawnTime", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "MorphCondition", &parseBannerCarrierMorphCondition, 0, 0x18 },
	{ "ExpLevelDraw", &parseBannerCarrierExpLevelDraw, 0, 0x24 },
	{ "BannerMorphFX", &INI::parseFXList, 0, 0x30 },
	{ "UnitSpawnFX", &INI::parseFXList, 0, 0x34 },
	{ "ReplenishNearbyHorde", &INI::parseBool, 0, 0x38 },
	{ "ReplenishAllNearbyHordes", &INI::parseBool, 0, 0x39 },
	{ "ScanHordeDistance", &INI::parseReal, 0, 0x3C },
	{ "UpgradeRequired", &INI::parseAsciiString, 0, 0x40 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C503B0: 7 fields and the zero sentinel.
extern const FieldParse g_00C503B0[] = {
	{ "SpecialObjectName", &INI::parseAsciiString, 0, 0x8 },
	{ "RingTimeBeforeSpawning", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "TimeSpentRoamingAround", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "TimeRingPowerSuppressed", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "StartingDistanceFromMe", &INI::parseReal, 0, 0x18 },
	{ "TimeFrozenFromPenalty", &INI::parseDurationUnsignedInt, 0, 0x1C },
	{ "DiscoveredSound", &INI::parseAudioEventRTS, 0, 0x20 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C517F0: 17 fields and the zero sentinel.
extern const FieldParse g_00C517F0[] = {
	{ "MaxQueueEntries", &INI::parseUnsignedInt, 0, 0x28 },
	{ "NumDoorAnimations", &INI::parseInt, 0, 0x8 },
	{ "DoorOpeningTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "DoorWaitOpenTime", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "DoorCloseTime", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "ConstructionCompleteDuration", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "QuantityModifier", (INIFieldParseProc)&__identifier("?Rva0049FDF9Parse@@YAXPAVINI@@PAVProductionUpdateModuleData@@@Z"), 0, 0x1C },
	{ "ProductionModifier", &Rva0049DE6DParse, 0, 0x0 },
	{ "DisabledTypesToProcess", (INIFieldParseProc)&__identifier("?parseFromINI@Rva0049DD83@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
	{ "GiveNoXP", &INI::parseBool, 0, 0x30 },
	{ "UnitInvulnerableTime", &INI::parseDurationUnsignedInt, 0, 0x34 },
	{ "SpecialPrepModelconditionTime", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "VeteranUnitsFromVeteranFactory", &INI::parseBool, 0, 0x40 },
	{ "SetBonusModelConditionOnSpeedBonus", &INI::parseBool, 0, 0x41 },
	{ "BonusForType", &INI::parseAsciiString, 0, 0x44 },
	{ "SpeedBonusAudioLoop", &INI::parseAudioEventRTS, 0, 0x48 },
	{ "SecondaryQueue", &INI::parseBool, 0, 0x4C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C51964: 1 fields and the zero sentinel.
extern const FieldParse g_00C51964[] = {
	{ "DamageToFramesRatio", &INI::parseReal, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C52188: 16 fields and the zero sentinel.
extern const FieldParse g_00C52188[] = {
	{ "DetectionRate", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "DetectionRange", &INI::parseReal, 0, 0xC },
	{ "InitiallyDisabled", &INI::parseBool, 0, 0x10 },
	{ "PingSound", &INI::parseAudioEventRTS, 0, 0x14 },
	{ "LoudPingSound", &INI::parseAudioEventRTS, 0, 0x18 },
	{ "IRBeaconParticleSysName", &INI::parseParticleSystemTemplate, 0, 0x1C },
	{ "IRParticleSysName", &INI::parseParticleSystemTemplate, 0, 0x20 },
	{ "IRBrightParticleSysName", &INI::parseParticleSystemTemplate, 0, 0x24 },
	{ "IRGridParticleSysName", &INI::parseParticleSystemTemplate, 0, 0x28 },
	{ "IRParticleSysBone", &INI::parseAsciiString, 0, 0x2C },
	{ "ExtraRequiredKindOf", &Rva002567EAParse, 0, 0x30 },
	{ "ExtraForbiddenKindOf", &Rva002567EAParse, 0, 0x4C },
	{ "CanDetectWhileGarrisoned", &INI::parseBool, 0, 0x68 },
	{ "CanDetectWhileContained", &INI::parseBool, 0, 0x69 },
	{ "CancelOneRingEffect", &INI::parseBool, 0, 0x6A },
	{ "RequiredUpgrade", &INI::parseAsciiString, 0, 0x6C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C52468: 10 fields and the zero sentinel.
extern const FieldParse g_00C52468[] = {
	{ "InvisibilityNugget", &Rva00438176Parse, 0, 0x8 },
	{ "UpdatePeriod", &INI::parseDurationUnsignedInt, 0, 0xC0 },
	{ "RequiredUpgrades", (INIFieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0xC4 },
	{ "ForbiddenUpgrades", (INIFieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x144 },
	{ "Broadcast", &INI::parseBool, 0, 0x1C4 },
	{ "BroadcastObjectFilter", &iniParseObjectFilter, 0, 0x1C8 },
	{ "BroadcastRange", &INI::parseReal, 0, 0x1CC },
	{ "StartsActive", &INI::parseBool, 0, 0x1D0 },
	{ "UnitSpecificSoundNameToUseAsVoiceMoveToStealthyArea", &INI::parseAsciiString, 0, 0x1D4 },
	{ "UnitSpecificSoundNameToUseAsVoiceEnterStateMoveToStealthyArea", &INI::parseAsciiString, 0, 0x1D8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C52BD8: 17 fields and the zero sentinel.
extern const FieldParse g_00C52BD8[] = {
	{ "MinToppleDelay", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "MaxToppleDelay", &INI::parseDurationUnsignedInt, 0, 0x3C },
	{ "MinToppleBurstDelay", &INI::parseDurationUnsignedInt, 0, 0x68 },
	{ "MaxToppleBurstDelay", &INI::parseDurationUnsignedInt, 0, 0x6C },
	{ "ToppleAccelerationFactor", &INI::parseReal, 0, 0x48 },
	{ "StructuralIntegrity", &INI::parseReal, 0, 0x40 },
	{ "StructuralDecay", &INI::parseReal, 0, 0x44 },
	{ "DamageFXTypes", &INI::parseDamageTypeFlags, 0, 0x4C },
	{ "TopplingFX", &INI::parseFXList, 0, 0x58 },
	{ "ToppleDelayFX", &INI::parseFXList, 0, 0x54 },
	{ "ToppleStartFX", &INI::parseFXList, 0, 0x50 },
	{ "ToppleDoneFX", &INI::parseFXList, 0, 0x5C },
	{ "CrushingFX", &INI::parseFXList, 0, 0x60 },
	{ "CrushingWeaponName", &INI::parseAsciiString, 0, 0x64 },
	{ "ForceToppleAngle", &INI::parseReal, 0, 0xB8 },
	{ "OCL", (INIFieldParseProc)&__identifier("?rva004A646B@StructureToppleUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "AngleFX", &parseAngleFX, 0, 0x0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C53980: 12 fields and the zero sentinel.
extern const FieldParse g_00C53980[] = {
	{ "ToppleFX", &INI::parseFXList, 0, 0x8 },
	{ "BounceFX", &INI::parseFXList, 0, 0xC },
	{ "StumpName", &INI::parseAsciiString, 0, 0x10 },
	{ "KillWhenStartToppling", &INI::parseBool, 0, 0x25 },
	{ "KillWhenFinishedToppling", &INI::parseBool, 0, 0x24 },
	{ "KillStumpWhenToppled", &INI::parseBool, 0, 0x26 },
	{ "ToppleLeftOrRightOnly", &INI::parseBool, 0, 0x27 },
	{ "ReorientToppledRubble", &INI::parseBool, 0, 0x28 },
	{ "InitialVelocityPercent", &INI::parsePercentToReal, 0, 0x14 },
	{ "InitialAccelPercent", &INI::parsePercentToReal, 0, 0x18 },
	{ "BounceVelocityPercent", &INI::parsePercentToReal, 0, 0x1C },
	{ "MinimumToppleSpeed", &INI::parsePositiveNonZeroReal, 0, 0x20 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C54868: 4 fields and the zero sentinel.
extern const FieldParse g_00C54868[] = {
	{ "TimeBetweenUpdatesMin", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "TimeBetweenUpdatesVariation", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "UnitWeight", &INI::parseUnsignedShort, 0, 0x1C },
	{ "Key", (INIFieldParseProc)&__identifier("?parseAudioKeyTokens@Rva003D4920@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C54B00: 9 fields and the zero sentinel.
extern const FieldParse g_00C54B00[] = {
	{ "StartRainTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "DarknessFadeTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "RainEmitterHeight", &INI::parsePositiveNonZeroReal, 0, 0x10 },
	{ "DarknessLevel", &INI::parsePositiveNonZeroReal, 0, 0x14 },
	{ "JitterRadius", &INI::parseReal, 0, 0x18 },
	{ "DPSMin", &INI::parsePositiveNonZeroReal, 0, 0x1C },
	{ "DPSMax", &INI::parsePositiveNonZeroReal, 0, 0x20 },
	{ "DPSRampupTime", &INI::parseDurationReal, 0, 0x24 },
	{ "RainOffset", &INI::parseCoord2D, 0, 0x28 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C54D28: 2 fields and the zero sentinel.
extern const FieldParse g_00C54D28[] = {
	{ "StartTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "DestructionTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C54DD8: 5 fields and the zero sentinel.
extern const FieldParse g_00C54DD8[] = {
	{ "Texture", &INI::parseAsciiString, 0, 0x8 },
	{ "Radius", &Rva00339D74ParseCurve, 0, 0x10 },
	{ "Color", &INI::parseColorInt, 0, 0xC },
	{ "Opacity", &Rva00339D74ParseCurve, 0, 0x3C },
	{ "Angle", &Rva00339D74ParseCurve, 0, 0x68 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C55638: 5 fields and the zero sentinel.
extern const FieldParse g_00C55638[] = {
	{ "RiderSubObjects", &INI::parseAsciiStringVector, 0, 0x14 },
	{ "RiderlessWeaponSlot", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x20 },
	{ "RiderlessHordeFlees", &INI::parseBool, 0, 0x24 },
	{ "DeathEntry", &Rva004AEB84Parse, 0, 0x8 },
	{ "RemoveRiderlessFromHorde", &INI::parseBool, 0, 0x25 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C56858: 12 fields and the zero sentinel.
extern const FieldParse g_00C56858[] = {
	{ "TauntAndPointDistance", &INI::parseReal, 0, 0x8 },
	{ "TauntAndPointUpdateDelay", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "TauntAndPointExcluded", &iniParseObjectFilter, 0, 0x10 },
	{ "AfraidOf", &iniParseObjectFilter, 0, 0x14 },
	{ "AlwaysAfraidOf", &iniParseObjectFilter, 0, 0x18 },
	{ "PointAt", &iniParseObjectFilter, 0, 0x1C },
	{ "HeroScanDistance", &INI::parseReal, 0, 0x20 },
	{ "FearScanDistance", &INI::parseReal, 0, 0x24 },
	{ "QuarrelProbability", &INI::parsePercentToReal, 0, 0x28 },
	{ "IgnoreVeterancy", &INI::parseBool, 0, 0x2C },
	{ "ImmuneToFearLevel", &INI::parseInt, 0, 0x30 },
	{ "AddEmotion", (INIFieldParseProc)&__identifier("?IniParseAddEmotion@EmotionTrackerUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C56A98: 10 fields and the zero sentinel.
extern const FieldParse g_00C56A98[] = {
	{ "ScanDelayTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "EnragedTime", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "TimeUntilCanRageAgain", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "ScanDistance", &INI::parseReal, 0, 0x14 },
	{ "HatedObjectFilter", &iniParseObjectFilter, 0, 0x1C },
	{ "FriendlyDeadFilter", &iniParseObjectFilter, 0, 0x18 },
	{ "EnragedTransitionTime", &INI::parseDurationUnsignedInt, 0, 0x20 },
	{ "EnragedTransitionFX", &INI::parseFXList, 0, 0x24 },
	{ "EnragedOnBuffFX", &INI::parseFXList, 0, 0x28 },
	{ "EnragedOffBuffFX", &INI::parseFXList, 0, 0x2C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C56ED8: 6 fields and the zero sentinel.
extern const FieldParse g_00C56ED8[] = {
	{ "CommandButtonName", &INI::parseAsciiString, 0, 0x8 },
	{ "SpecialPowerAIType", &parseSpecialPowerAIType, 0, 0xC },
	{ "SpecialPowerRadius", &INI::parseReal, 0, 0x10 },
	{ "SpecialPowerRange", &INI::parseReal, 0, 0x14 },
	{ "RandomizeTargetLocation", &INI::parseBool, 0, 0x18 },
	{ "SpellMakesAStructure", &INI::parseBool, 0, 0x19 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C59338: 1 fields and the zero sentinel.
extern const FieldParse g_00C59338[] = {
	{ "SlotToLock", &INI::parseLookupList, TheWeaponSlotTypeNamesLookupList, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C595B4: 2 fields and the zero sentinel.
extern const FieldParse g_00C595B4[] = {
	{ "LevelToGrant", &INI::parseInt, 0, 0x8 },
	{ "MPOnly", &INI::parseBool, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C59728: 3 fields and the zero sentinel.
extern const FieldParse g_00C59728[] = {
	{ "Radius", &INI::parseReal, 0, 0x8 },
	{ "Upgrade", (INIFieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0xC },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x8C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C59C70: 3 fields and the zero sentinel.
extern const FieldParse g_00C59C70[] = {
	{ "DamageTypesToReflect", &INI::parseDamageTypeFlags, 0, 0x8 },
	{ "ReflectDamagePercentage", &INI::parsePercentToReal, 0, 0xC },
	{ "MinimumDamageToReflect", &INI::parseReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5A190: 4 fields and the zero sentinel.
extern const FieldParse g_00C5A190[] = {
	{ "CollideWeapon", &INI::parseWeaponTemplate, 0, 0x8 },
	{ "FireOnce", &INI::parseBool, 0, 0x2C },
	{ "RequiredStatus", &Rva003B1017::parseFromINI, 0, 0xC },
	{ "ForbiddenStatus", &Rva003B1017::parseFromINI, 0, 0x1C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5AB48: 1 fields and the zero sentinel.
extern const FieldParse g_00C5AB48[] = {
	{ "DeleteObjectFilter", &iniParseObjectFilter, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5B228: 21 fields and the zero sentinel.
extern const FieldParse g_00C5B228[] = {
	{ "MaxHealth", &INI::parseReal, 0, 0x8 },
	{ "MaxHealthDamaged", &INI::parseReal, 0, 0x10 },
	{ "MaxHealthReallyDamaged", &INI::parseReal, 0, 0x14 },
	{ "InitialHealth", &INI::parseReal, 0, 0xC },
	{ "RecoveryTime", &INI::parseDurationUnsignedInt, 0, 0x24 },
	{ "DodgePercent", &INI::parsePercentToReal, 0, 0x18 },
	{ "EnteringDamagedTransitionTime", &INI::parseDurationUnsignedInt, 0, 0x1C },
	{ "EnteringReallyDamagedTransitionTime", &INI::parseDurationUnsignedInt, 0, 0x20 },
	{ "GrabObject", &INI::parseAsciiString, 0, 0x2C },
	{ "GrabFX", &INI::parseFXList, 0, 0x38 },
	{ "GrabDamage", &INI::parseReal, 0, 0x3C },
	{ "GrabOffset", &INI::parseCoord2D, 0, 0x40 },
	{ "UseDefaultDamageSettings", &INI::parseBool, 0, 0x28 },
	{ "DamageCreationList", &Rva004BFD83Parse, 0, 0x0 },
	{ "HealingBuffFx", &INI::parseFXList, 0, 0x48 },
	{ "DamagedAttributeModifier", &INI::parseAsciiString, 0, 0x30 },
	{ "ReallyDamagedAttributeModifier", &INI::parseAsciiString, 0, 0x34 },
	{ "CheerRadius", &INI::parseReal, 0, 0x4C },
	{ "RemoveUpgradesOnDeath", &INI::parseBool, 0, 0x50 },
	{ "BurningDeathBehavior", &INI::parseBool, 0, 0x51 },
	{ "BurningDeathFX", &INI::parseFXList, 0, 0x54 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5EB94: 2 fields and the zero sentinel.
extern const FieldParse g_00C5EB94[] = {
	{ "RadarPulseFrequency", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "RadarPulseDuration", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5ECB8: 8 fields and the zero sentinel.
extern const FieldParse g_00C5ECB8[] = {
	{ "AnnouncementEventEnemy", &Rva001DEE74Parse, 0, 0x8 },
	{ "AnnouncementEventAlly", &Rva001DEE74Parse, 0, 0xC },
	{ "AnnouncementEventOwner", &Rva001DEE74Parse, 0, 0x10 },
	{ "DelayBeforeAnnouncementMS", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "OnlyIfVisible", &INI::parseBool, 0, 0x18 },
	{ "CountAsFirstSightedAnnoucement", &INI::parseBool, 0, 0x19 },
	{ "UseObjectsPosition", &INI::parseBool, 0, 0x1A },
	{ "CreateFakeRadarEvent", &INI::parseBool, 0, 0x1B },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5F150: 1 fields and the zero sentinel.
extern const FieldParse g_00C5F150[] = {
	{ "SoundState", &Rva004CB047Parse, 0, 0x0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5F2DC: 1 fields and the zero sentinel.
extern const FieldParse g_00C5F2DC[] = {
	{ "SoundUpgrade", (INIFieldParseProc)&__identifier("?parseSoundUpgrade@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5F574: 1 fields and the zero sentinel.
extern const FieldParse g_00C5F574[] = {
	{ "ModelCondition", &Rva004CC371Parse, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5F5E4: 1 fields and the zero sentinel.
extern const FieldParse g_00C5F5E4[] = {
	{ "DefectDuration", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C42D08: 7 fields and the zero sentinel.
extern const FieldParse g_00C42D08[] = {
	{ "FXHitGround", &INI::parseFXList, 0, 0x190 },
	{ "OCLHitGround", &INI::parseObjectCreationList, 0, 0x194 },
	{ "DelayFromGroundToFinalDeath", &INI::parseDurationReal, 0, 0x198 },
	{ "CrashAvoidKindOfs", &Rva002567EAParse, 0, 0x19C },
	{ "CrashAvoidRadius", &INI::parseReal, 0, 0x1B8 },
	{ "CrashAvoidStrength", &INI::parseReal, 0, 0x1BC },
	{ "NeedToMaintainFlailingHeight", &INI::parseBool, 0, 0x1C0 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C49CB0: 11 fields and the zero sentinel.
extern const FieldParse g_00C49CB0[] = {
	{ "ClearanceGeometry", (INIFieldParseProc)&__identifier("?parseGeometryType@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "ClearanceGeometryMajorRadius", (INIFieldParseProc)&__identifier("?parseGeometryMajorRadius@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "ClearanceGeometryMinorRadius", (INIFieldParseProc)&__identifier("?parseGeometryMinorRadius@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "ClearanceGeometryRotationAnchorOffset", &parseGeometryRotationAnchorOffset, 0, 0x190 },
	{ "ClearanceGeometryHeight", (INIFieldParseProc)&__identifier("?parseGeometryHeight@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "ClearanceGeometryIsSmall", (INIFieldParseProc)&__identifier("?parseGeometryIsSmall@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "ClearanceGeometryOffset", &INI::parseCoord3D, 0, 0x1EC },
	{ "ClearanceMaxHeight", &INI::dup_002F02F, 0, 0x1F8 },
	{ "ClearanceMaxHeightFraction", &INI::dup_002F02F, 0, 0x1FC },
	{ "ClearanceMinHeight", &INI::dup_002F082, 0, 0x200 },
	{ "ClearanceMinHeightFraction", &INI::dup_002F02F, 0, 0x204 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5B8BC: 2 fields and the zero sentinel.
extern const FieldParse g_00C5B8BC[] = {
	{ "PermanentlyKilledByFilter", &iniParseObjectFilter, 0, 0x64 },
	{ "CanRespawn", &INI::parseBool, 0, 0x68 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00BEFCD4: 1 fields and the zero sentinel.
extern const FieldParse g_00BEFCD4[] = {
	{ "Symbiote", &INI::parseAsciiString, 0, 0x64 },
	{ 0, 0, 0, 0 }
};
extern const int g_emptyFieldParseTable[4];


int Rva004CE52EGet(void);

#define FIELD_PROC(cls, addr, field) \
class cls \
{ \
public: \
	static void buildFieldParse(MultiIniFieldParse &parse); \
}; \
\
void cls::buildFieldParse(MultiIniFieldParse &parse) \
{ \
	parse.add(reinterpret_cast<const FieldParse *>(addr), 0); \
}

#define FIELD_PROC_INLINE(cls, addr, field) \
class cls \
{ \
public: \
	static void buildFieldParse(MultiIniFieldParse &parse); \
}; \
\
inline void cls::buildFieldParse(MultiIniFieldParse &parse) \
{ \
	parse.add(reinterpret_cast<const FieldParse *>(addr), 0); \
}

#define FIELD_PROC_WITH_DIE_BASE(cls, addr) \
class cls \
{ \
public: \
	static void buildFieldParse(MultiIniFieldParse &parse); \
}; \
\
void cls::buildFieldParse(MultiIniFieldParse &parse) \
{ \
	parse.add(reinterpret_cast<const FieldParse *>(addr), 0); \
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8); \
}

FIELD_PROC(BeaconClientUpdateModuleData, (unsigned int)&g_00C5EB94, RadarPulseFrequency)
FIELD_PROC(EvaAnnounceClientCreateModuleData, (unsigned int)&g_00C5ECB8, AnnouncementEventEnemy)
FIELD_PROC(CritterEmitterUpdateModuleData, BfmeCritterEmitterUpdateFields, FX)
FIELD_PROC(UpgradeSoundSelectorClientBehaviorModuleData, (unsigned int)&g_00C5F2DC, SoundUpgrade)
FIELD_PROC(ModelConditionAudioLoopClientBehaviorModuleData, (unsigned int)&g_00C5F574, ModelCondition)
FIELD_PROC_INLINE(LifetimeUpdateModuleData, (unsigned int)&g_00C1B0F0, LifetimeUpdateTable)
FIELD_PROC(SpawnedModelConditionCreateModuleData, (unsigned int)&g_00C1B00C, SpawnerTrigger)
FIELD_PROC(FlammableUpdateModuleData, (unsigned int)&g_00C4C600, SalvageCrateTable)
FIELD_PROC(DetachableRiderUpdateModuleData, (unsigned int)&g_00C55638, PropagandaTowerTable)
FIELD_PROC(CivilianSpawnCollideModuleData, (unsigned int)&g_00C5AB48, SteeringTable)
FIELD_PROC(OCLUpdateModuleData, BfmeOCLUpdateFields, OCLTable)
FIELD_PROC(AutoPickUpUpdateModuleData, (unsigned int)&g_00C4F4B8, EatObjectTable)
FIELD_PROC(ProductionUpdateModuleData, (unsigned int)&g_00C517F0, DoorTable)
FIELD_PROC(ProneUpdateModuleData, (unsigned int)&g_00C51964, ProneTable)
FIELD_PROC_INLINE(BoneFXUpdateModuleData, (unsigned int)&g_00BF1158, BoneFXTable)
FIELD_PROC_INLINE(DeletionUpdateModuleData, (unsigned int)&g_00BF17BC, DeletionTable)
FIELD_PROC_INLINE(RadarUpdateModuleData, (unsigned int)&g_00BF1EF8, RadarTable)
FIELD_PROC_INLINE(DefaultProductionExitUpdateModuleData, (unsigned int)&g_00BF2398, DefaultExitTable)
FIELD_PROC(StealthUpdateModuleData, (unsigned int)&g_00C18210, StealthTable)
FIELD_PROC(DemoTrapUpdateModuleData, (unsigned int)&g_00C4EEC8, DetonationTable)
FIELD_PROC(ToppleUpdateModuleData, (unsigned int)&g_00C53980, ToppleTable)
// These retail bodies also append the shared DieMuxData table via
// Rva004CE52EGet at extraOffset 8; both functions end after that second add.
FIELD_PROC_WITH_DIE_BASE(StructureToppleUpdateModuleData, (unsigned int)&g_00C52BD8)
FIELD_PROC_INLINE(SpawnPointProductionExitUpdateModuleData, (unsigned int)&g_00BF22D4, SpawnPointBoneTable)
FIELD_PROC_INLINE(HijackerUpdateModuleData, (unsigned int)&g_00BF2318, HijackerTable)
FIELD_PROC_INLINE(SlavedUpdateModuleData, (unsigned int)&g_00BF2110, SlavedTable)
FIELD_PROC(BoredUpdateModuleData, (unsigned int)&g_00C4F618, BoredFilterTable)
FIELD_PROC(ModelConditionSoundSelectorClientBehaviorModuleData, (unsigned int)&g_00C5F150, SoundStateTable)
FIELD_PROC(BannerCarrierUpdateModuleData, (unsigned int)&g_00C4F9E8, HordeTable)
void ActiveBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5B228), 0);
}
FIELD_PROC(ReflectDamageModuleData, (unsigned int)&g_00C59C70, ReflectDamageTable)
FIELD_PROC(AISpecialPowerUpdateModuleData, (unsigned int)&g_00C56ED8, SpecialPowerAITable)
FIELD_PROC(EntEnragedUpdateModuleData, (unsigned int)&g_00C56A98, EnragedTable)
FIELD_PROC(EvacuateDamageModuleData, (unsigned int)&g_00C59DD0, PanicTable)
FIELD_PROC(RadarMarkerClientUpdateModuleData, BfmeRadarMarkerClientUpdateFields, MarkerType)
FIELD_PROC(LockWeaponCreateModuleData, (unsigned int)&g_00C59338, SlotToLock)
FIELD_PROC(StancesBehaviorModuleData, (unsigned int)&g_00C424B0, StanceTemplate)
FIELD_PROC(DestroyEnvironmentUpdateModuleData, (unsigned int)&g_00C54D28, StartTime)
FIELD_PROC(ExperienceLevelCreateModuleData, (unsigned int)&g_00C595B4, LevelToGrant)
FIELD_PROC(InheritUpgradeCreateModuleData, (unsigned int)&g_00C59728, Radius)
FIELD_PROC(AIGateUpdateModuleData, BfmeAIGateUpdateFields, TriggerWidthX)
FIELD_PROC(RainOfFireUpdateModuleData, (unsigned int)&g_00C54B00, StartRainTime)
FIELD_PROC(SpecialEnemySenseUpdateModuleData, (unsigned int)&g_00BF1B88, SpecialEnemyFilter)
FIELD_PROC(OneRingPenaltyUpdateModuleData, (unsigned int)&g_00C503B0, RingTable)
FIELD_PROC(SiegeDockingBehaviorModuleData, (unsigned int)&g_00C413E4, DUMMY)
FIELD_PROC_INLINE(AutoDepositUpdateModuleData, (unsigned int)&g_00BF1CC8, DepositTable)
FIELD_PROC(SpawnUnitBehaviorModuleData, BfmeSpawnUnitBehaviorFields, SpawnUnitTable)
FIELD_PROC(EmotionTrackerUpdateModuleData, (unsigned int)&g_00C56858, TauntAndPointDistance)
FIELD_PROC(PartTheHeavensUpdateModuleData, (unsigned int)&g_00C54DD8, Texture)
FIELD_PROC(InvisibilityUpdateModuleData, (unsigned int)&g_00C52468, InvisibilityNugget)
FIELD_PROC(TemporarilyDefectUpdateModuleData, (unsigned int)&g_00C5F5E4, DefectDurationTable)
FIELD_PROC(PoisonedBehaviorModuleData, (unsigned int)&g_00C49918, PoisonTable)
FIELD_PROC(SupplyWarehouseCripplingBehaviorModuleData, (unsigned int)&g_00C49B40, SelfHealTable)
FIELD_PROC(FireSpreadUpdateModuleData, FireSpreadUpdateModuleDataFieldParse, FireSpreadTable)
FIELD_PROC_WITH_DIE_BASE(SlowDeathBehaviorModuleData, (unsigned int)&g_00C42290)
FIELD_PROC(TerrainResourceBehaviorModuleData, (unsigned int)&g_00C494F0, IncomeTable)
FIELD_PROC(MonitorConditionUpdateModuleData, (unsigned int)&g_00C4DA00, ModelConditionTable)
FIELD_PROC(AttachUpdateModuleData, BfmeAttachUpdateFields, AttachTable)
FIELD_PROC(PickupStuffUpdateModuleData, BfmePickupStuffUpdateFields, PickupStuffTable)
FIELD_PROC(HeightDieUpdateModuleData, (unsigned int)&g_00C4CFC8, HeightTable)
FIELD_PROC(FloatUpdateModuleData, (unsigned int)&g_00C4C7A4, EnabledTable)
FIELD_PROC(AutoAbilityBehaviorModuleData, (unsigned int)&g_00C41690, ScanTable)
FIELD_PROC(AutoFindHealingUpdateModuleData, (unsigned int)&g_00C4EC68, HealScanTable)
FIELD_PROC(FloodUpdateModuleData, BfmeFloodUpdateFields, FloodTable)
FIELD_PROC(StrafeAreaUpdateModuleData, BfmeStrafeAreaUpdateFields, StrafeTable)
FIELD_PROC(LaserUpdateModuleData, (unsigned int)&g_00C17208, LaserTable)
FIELD_PROC(PassiveAreaEffectBehaviorModuleData, (unsigned int)&g_00C4A388, PassiveAreaEffectTable)
FIELD_PROC(DynamicShroudClearingRangeUpdateModuleData, (unsigned int)&g_00C4BE20, DynamicShroudTable)
FIELD_PROC(BloodthirstyUpdateModuleData, (unsigned int)&g_00C3F120, BloodthirstyTable)
FIELD_PROC(FireWeaponUpdateModuleData, (unsigned int)&g_00C4C210, Rva0048C0B4Table)
FIELD_PROC(BezierProjectileBehaviorModuleData, (unsigned int)&g_00C41B58, Rva0045B5E3Table)

// Chained proc: ?buildFieldParse@GiantBirdSlowDeathBehaviorModuleData@@,
// retail 0x00461E3D, 27 bytes. Calls the rowed SlowDeath base proc above,
// then registers the GiantBird table (unsigned int)&g_00C42D08 (FXHitGround,
// OCLHitGround, DelayFromGroundToFinalDeath, CrashAvoidKindOfs). The base
// call resolves to the rowed SlowDeath proc in this same TU; factory
// 0x24B5D1 pushes this proc VA.
class GiantBirdSlowDeathBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GiantBirdSlowDeathBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SlowDeathBehaviorModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C42D08), 0);
}

// Chained proc: ?buildFieldParse@ClearanceTestingSlowDeathBehaviorModuleData@@,
// retail 0x00483C1A, 27 bytes. Calls the rowed SlowDeath base proc above,
// then registers the Clearance table (unsigned int)&g_00C49CB0 (ClearanceGeometry at +0x190
// plus ClearanceGeometryOffset at +0x1EC plus ClearanceMaxHeight at +0x1F8).
// The base call resolves to the rowed SlowDeath proc in this same TU; factory
// 0x24C545 pushes this proc VA; the rowed ClearanceTestingSlowDeathBehavior
// pool key at 0x483CF4 names the class.
class ClearanceTestingSlowDeathBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void ClearanceTestingSlowDeathBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SlowDeathBehaviorModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C49CB0), 0);
}
FIELD_PROC(RebuildHoleBehaviorModuleData, (unsigned int)&g_00C49A10, WorkerTable)
FIELD_PROC(LargeGroupBonusUpdateModuleData, (unsigned int)&g_00C4D1A8, HordeBonusTable)
FIELD_PROC(LargeGroupAudioUpdateModuleData, (unsigned int)&g_00C54868, GroupAudioTable)
FIELD_PROC(FireWeaponCollideModuleData, (unsigned int)&g_00C5A190, CollideWeaponTable)
FIELD_PROC(StealthDetectorUpdateModuleData, (unsigned int)&g_00C52188, DetectionTable)

// Chained proc: ?buildFieldParse@RespawnBodyModuleData@@,
// retail 0x004C12D0, 27 bytes. Calls the ActiveBodyModuleData base proc
// above (0x4BFDF6, in this same TU -- the base call target, not the
// SupplyTruckAIUpdateModuleData proc a stale comment here once named), then
// registers the Respawn table (unsigned int)&g_00C5B8BC (PermanentlyKilledByFilter at +0x64
// plus CanRespawn at +0x68). Factory 0x251596 pushes this proc VA; the pool
// key at 0x4C1455 names the class; two further chained procs (0x4C15A2 plus
// 0x4C184F) call this one as their base. Identity: ModuleFactory registers
// ctor 0x4C14DF and this proc under "RespawnBody"; formerly misnamed
// RespawnUpdateModuleData.


void RespawnBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	ActiveBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5B8BC), 0);
}

// Chained proc: ?buildFieldParse@StructureBodyModuleData@@,
// retail 0x002514AF, 27 bytes. Calls the ActiveBodyModuleData base proc
// above (0x4BFDF6, in this same TU), then registers the Structure table
// 0x00C6BB18. Factory pushes this proc VA; ModuleFactory registers it
// under "StructureBody". Row supersedes the pin.
class StructureBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

inline void StructureBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	ActiveBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

// Chained proc: ?buildFieldParse@SymbioticStructuresBodyModuleData@@,
// retail 0x00251505, 27 bytes. Calls the ActiveBodyModuleData base proc
// above (0x4BFDF6, in this same TU), then registers the SymbioticStructures
// table (unsigned int)&g_00BEFCD4. Factory pushes this proc VA; ModuleFactory registers it
// under "SymbioticStructuresBody". Row supersedes the pin.
class SymbioticStructuresBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SymbioticStructuresBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	ActiveBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00BEFCD4), 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// These functions are header inlines; their ordinary owner definitions
// collided with select-any copies. The anchor keeps this unit's row copies;
// it is not retail code.
#pragma inline_depth(0)
// ?_bfmeModuleDataBuildFieldParseInlineAnchor@@YAXPAVMultiIniFieldParse@@@Z absent-from-retail
void _bfmeModuleDataBuildFieldParseInlineAnchor(MultiIniFieldParse *parse)
{
	AutoDepositUpdateModuleData::buildFieldParse(*parse);
	BoneFXUpdateModuleData::buildFieldParse(*parse);
	DefaultProductionExitUpdateModuleData::buildFieldParse(*parse);
	DeletionUpdateModuleData::buildFieldParse(*parse);
	HijackerUpdateModuleData::buildFieldParse(*parse);
	LifetimeUpdateModuleData::buildFieldParse(*parse);
	RadarUpdateModuleData::buildFieldParse(*parse);
	SlavedUpdateModuleData::buildFieldParse(*parse);
	SpawnPointProductionExitUpdateModuleData::buildFieldParse(*parse);
	StructureBodyModuleData::buildFieldParse(*parse);
}
#pragma inline_depth()
