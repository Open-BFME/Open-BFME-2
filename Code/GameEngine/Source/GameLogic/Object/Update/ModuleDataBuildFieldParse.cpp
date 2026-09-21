// cl: /O1 /DNDEBUG /MD
//
// Five single-field ModuleData::buildFieldParse procs (11 bytes each):
// ?buildFieldParse@CleanupHazardUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C9663 (field RadarPulseFrequency), plus PilotFindVehicle (announcement),
// DynamicGeometryInfo (FX), BattlePlan (SoundUpgrade) and RepairDock (ModelCondition)
// sibs, plus LifetimeUpdate (table 0x00C1B0F0, factory 0x24E3A3 pushes its VA).
// Each registers exactly one FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Provenance: the ZH
// MAKE_STANDARD_MODULE_DATA_MACRO_ABC macro passes clsmd::buildFieldParse to
// INI::initFromINIMultiProc, and each landed friend_newModuleData factory in
// this directory pushes its class proc immediate (no pin needed there, none
// needed here: the FieldParse address is a pushed absolute). Recipe: the
// factory TUs (*FriendNew.cpp) name the owning class per stub.

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

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

FIELD_PROC(CleanupHazardUpdateModuleData, 0x00C5EB94, RadarPulseFrequency)
FIELD_PROC(PilotFindVehicleUpdateModuleData, 0x00C5ECB8, AnnouncementEventEnemy)
FIELD_PROC(DynamicGeometryInfoUpdateModuleData, 0x00C5EA10, FX)
FIELD_PROC(BattlePlanUpdateModuleData, 0x00C5F2DC, SoundUpgrade)
FIELD_PROC(RepairDockUpdateModuleData, 0x00C5F574, ModelCondition)
FIELD_PROC(LifetimeUpdateModuleData, 0x00C1B0F0, LifetimeUpdateTable)
FIELD_PROC(SalvageCrateCollideModuleData, 0x00C4C600, SalvageCrateTable)
FIELD_PROC(PropagandaTowerBehaviorModuleData, 0x00C55638, PropagandaTowerTable)
FIELD_PROC(AnimationSteeringUpdateModuleData, 0x00C5AB48, SteeringTable)
FIELD_PROC(OCLUpdateModuleData, 0x00C50BA8, OCLTable)
FIELD_PROC(AutoPickUpUpdateModuleData, 0x00C4F4B8, EatObjectTable)
FIELD_PROC(ProductionUpdateModuleData, 0x00C517F0, DoorTable)
FIELD_PROC(ProneUpdateModuleData, 0x00C51964, ProneTable)
FIELD_PROC(BoneFXUpdateModuleData, 0x00BF1158, BoneFXTable)
FIELD_PROC(DeletionUpdateModuleData, 0x00BF17BC, DeletionTable)
FIELD_PROC(RadarUpdateModuleData, 0x00BF1EF8, RadarTable)
FIELD_PROC(DefaultProductionExitUpdateModuleData, 0x00BF2398, DefaultExitTable)
FIELD_PROC(StealthUpdateModuleData, 0x00C18210, StealthTable)
FIELD_PROC(DemoTrapUpdateModuleData, 0x00C4EEC8, DetonationTable)
FIELD_PROC(ToppleUpdateModuleData, 0x00C53980, ToppleTable)
FIELD_PROC(StructureCollapseUpdateModuleData, 0x00C52BD8, CollapseTable)
FIELD_PROC(SpawnPointProductionExitUpdateModuleData, 0x00BF22D4, SpawnPointBoneTable)
FIELD_PROC(HijackerUpdateModuleData, 0x00BF2318, HijackerTable)
FIELD_PROC(SlavedUpdateModuleData, 0x00BF2110, SlavedTable)
FIELD_PROC(BoredUpdateModuleData, 0x00C4F618, BoredFilterTable)
FIELD_PROC(BaikonurLaunchPowerModuleData, 0x00C5F150, SoundStateTable)
FIELD_PROC(HordeUpdateModuleData, 0x00C4F9E8, HordeTable)
FIELD_PROC(SupplyTruckAIUpdateModuleData, 0x00C5B228, SupplyTruckTable)
FIELD_PROC(ReflectDamageModuleData, 0x00C59C70, ReflectDamageTable)
FIELD_PROC(AISpecialPowerUpdateModuleData, 0x00C56ED8, SpecialPowerAITable)
FIELD_PROC(EnragedUpdateModuleData, 0x00C56A98, EnragedTable)
FIELD_PROC(PanicUpdateModuleData, 0x00C59DD0, PanicTable)
FIELD_PROC(MarkerTypeUpdateModuleData, 0x00C5ED98, MarkerType)
FIELD_PROC(SlotToLockUpdateModuleData, 0x00C59338, SlotToLock)
FIELD_PROC(StanceTemplateUpdateModuleData, 0x00C424B0, StanceTemplate)
FIELD_PROC(DestroyEnvironmentUpdateModuleData, 0x00C54D28, StartTime)
FIELD_PROC(ExperienceLevelCreateModuleData, 0x00C595B4, LevelToGrant)
FIELD_PROC(InheritUpgradeCreateModuleData, 0x00C59728, Radius)
FIELD_PROC(AIGateUpdateModuleData, 0x00C564D4, TriggerWidthX)
FIELD_PROC(RainOfFireUpdateModuleData, 0x00C54B00, StartRainTime)
FIELD_PROC(SpecialEnemySenseUpdateModuleData, 0x00BF1B88, SpecialEnemyFilter)
FIELD_PROC(OneRingPenaltyUpdateModuleData, 0x00C503B0, RingTable)
FIELD_PROC(AutoDepositUpdateModuleData, 0x00BF1CC8, DepositTable)
FIELD_PROC(AssistedTargetingUpdateModuleData, 0x00C4AFE8, AssistedTargetingTable)
FIELD_PROC(SpawnUnitBehaviorModuleData, 0x00C59238, SpawnUnitTable)
FIELD_PROC(EmotionTrackerUpdateModuleData, 0x00C56858, TauntAndPointDistance)
FIELD_PROC(PartTheHeavensUpdateModuleData, 0x00C54DD8, Texture)
FIELD_PROC(InvisibilityUpdateModuleData, 0x00C52468, InvisibilityNugget)
FIELD_PROC(TemporarilyDefectUpdateModuleData, 0x00C5F5E4, DefectDurationTable)
FIELD_PROC(PoisonedBehaviorModuleData, 0x00C49918, PoisonTable)
FIELD_PROC(SupplyWarehouseCripplingBehaviorModuleData, 0x00C49B40, SelfHealTable)
FIELD_PROC(FireSpreadUpdateModuleData, 0x00C4C000, FireSpreadTable)
FIELD_PROC(SlowDeathBehaviorModuleData, 0x00C42290, SinkTable)
FIELD_PROC(TerrainResourceBehaviorModuleData, 0x00C494F0, IncomeTable)
FIELD_PROC(ModelConditionSpecialAbilityUpdateModuleData, 0x00C4DA00, ModelConditionTable)
FIELD_PROC(AttachUpdateModuleData, 0x00C4DC48, AttachTable)
FIELD_PROC(PickupStuffUpdateModuleData, 0x00C4DE90, PickupStuffTable)
FIELD_PROC(HeightDieUpdateModuleData, 0x00C4CFC8, HeightTable)
FIELD_PROC(FloatUpdateModuleData, 0x00C4C7A4, EnabledTable)
FIELD_PROC(AutoAbilityBehaviorModuleData, 0x00C41690, ScanTable)
FIELD_PROC(AimWeaponBehaviorModuleData, 0x00C41948, AimTable)
FIELD_PROC(AutoFindHealingUpdateModuleData, 0x00C4EC68, HealScanTable)
FIELD_PROC(FloodUpdateModuleData, 0x00C4C9A8, FloodTable)
FIELD_PROC(StrafeAreaUpdateModuleData, 0x00C1B1F8, StrafeTable)
FIELD_PROC(LaserUpdateModuleData, 0x00C17208, LaserTable)
FIELD_PROC(PassiveAreaEffectBehaviorModuleData, 0x00C4A388, PassiveAreaEffectTable)
FIELD_PROC(DynamicShroudClearingRangeUpdateModuleData, 0x00C4BE20, DynamicShroudTable)
FIELD_PROC(BloodthirstyUpdateModuleData, 0x00C3F120, BloodthirstyTable)

// Chained proc: ?buildFieldParse@GiantBirdSlowDeathBehaviorModuleData@@,
// retail 0x00461E3D, 27 bytes. Calls the rowed SlowDeath base proc above,
// then registers the GiantBird table 0x00C42D08 (FXHitGround,
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
	parse.add(reinterpret_cast<const FieldParse *>(0x00C42D08), 0);
}

// Chained proc: ?buildFieldParse@ClearanceTestingSlowDeathBehaviorModuleData@@,
// retail 0x00483C1A, 27 bytes. Calls the rowed SlowDeath base proc above,
// then registers the Clearance table 0x00C49CB0 (ClearanceGeometry at +0x190
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
	parse.add(reinterpret_cast<const FieldParse *>(0x00C49CB0), 0);
}
