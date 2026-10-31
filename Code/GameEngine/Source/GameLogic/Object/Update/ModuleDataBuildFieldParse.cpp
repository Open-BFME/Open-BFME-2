char g_00BF1158;
char g_00BF17BC;
char g_00BF1B88;
char g_00BF1CC8;
char g_00BF1EF8;
char g_00BF2110;
char g_00BF22D4;
char g_00BF2318;
char g_00BF2398;
char g_00C17208;
char g_00C18210;
char g_00C1B00C;
char g_00C1B0F0;
char g_00C3F120;
char g_00C413E4;
char g_00C41690;
char g_00C41B58;
char g_00C42290;
char g_00C424B0;
char g_00C494F0;
char g_00C49918;
char g_00C49A10;
char g_00C49B40;
char g_00C4A388;
char g_00C4AFE8;
char g_00C4BE20;
char g_00C4C210;
char g_00C4C600;
char g_00C4C7A4;
char g_00C4CFC8;
char g_00C4D1A8;
char g_00C4DA00;
char g_00C4EC68;
char g_00C4EEC8;
char g_00C4F4B8;
char g_00C4F618;
char g_00C4F9E8;
char g_00C503B0;
char g_00C517F0;
char g_00C51964;
char g_00C52188;
char g_00C52468;
char g_00C52BD8;
char g_00C53980;
char g_00C54868;
char g_00C54B00;
char g_00C54D28;
char g_00C54DD8;
char g_00C55638;
char g_00C56858;
char g_00C56A98;
char g_00C56ED8;
char g_00C59338;
char g_00C595B4;
char g_00C59728;
char g_00C59C70;
char g_00C59DD0;
char g_00C5A190;
char g_00C5AB48;
char g_00C5B228;
char g_00C5EB94;
char g_00C5ECB8;
char g_00C5F150;
char g_00C5F2DC;
char g_00C5F574;
char g_00C5F5E4;

char g_00C42D08;
char g_00C49CB0;
char g_00C5B8BC;
char g_00BEFCD4;

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
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C8F94_ParseSpawnObject(INI *ini, void *instance, void *store, const void *userData);
};

class Rva003B1017
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

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
extern const int g_emptyFieldParseTable[4];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

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
FIELD_PROC(ActiveBodyModuleData, (unsigned int)&g_00C5B228, SupplyTruckTable)
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
FIELD_PROC(AssistedTargetingUpdateModuleData, (unsigned int)&g_00C4AFE8, AssistedTargetingTable)
FIELD_PROC(SpawnUnitBehaviorModuleData, BfmeSpawnUnitBehaviorFields, SpawnUnitTable)
FIELD_PROC(EmotionTrackerUpdateModuleData, (unsigned int)&g_00C56858, TauntAndPointDistance)
FIELD_PROC(PartTheHeavensUpdateModuleData, (unsigned int)&g_00C54DD8, Texture)
FIELD_PROC(InvisibilityUpdateModuleData, (unsigned int)&g_00C52468, InvisibilityNugget)
FIELD_PROC(TemporarilyDefectUpdateModuleData, (unsigned int)&g_00C5F5E4, DefectDurationTable)
FIELD_PROC(PoisonedBehaviorModuleData, (unsigned int)&g_00C49918, PoisonTable)
FIELD_PROC(SupplyWarehouseCripplingBehaviorModuleData, (unsigned int)&g_00C49B40, SelfHealTable)
FIELD_PROC(FireSpreadUpdateModuleData, 0x00C4C000, FireSpreadTable)
FIELD_PROC_WITH_DIE_BASE(SlowDeathBehaviorModuleData, (unsigned int)&g_00C42290)
FIELD_PROC(TerrainResourceBehaviorModuleData, (unsigned int)&g_00C494F0, IncomeTable)
FIELD_PROC(MonitorConditionUpdateModuleData, (unsigned int)&g_00C4DA00, ModelConditionTable)
FIELD_PROC(AttachUpdateModuleData, BfmeAttachUpdateFields, AttachTable)
FIELD_PROC(PickupStuffUpdateModuleData, BfmePickupStuffUpdateFields, PickupStuffTable)
FIELD_PROC(HeightDieUpdateModuleData, (unsigned int)&g_00C4CFC8, HeightTable)
FIELD_PROC(FloatUpdateModuleData, (unsigned int)&g_00C4C7A4, EnabledTable)
FIELD_PROC(AutoAbilityBehaviorModuleData, (unsigned int)&g_00C41690, ScanTable)
class AimWeaponBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};
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
class RespawnBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

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
