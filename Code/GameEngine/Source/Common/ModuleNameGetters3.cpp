// Module literal name getters (cold slice): six-byte const members with one
// shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated class-name string in
// .rdata. Contributor-local unit split from ModuleNameGetters2.cpp to keep
// concurrent landings conflict-free; the BFME_LITERAL_NAME_GETTER macro is
// verbatim, only the class names follow this tree's address-derived
// convention (identity unrecoverable from 6 bytes, string carried in source
// where verify_string_refs re-reads it).
// No // cl: line (defaults match the frameless 6-byte shape, same as the
// ModuleNameGetters.cpp precedent).

#define BFME_SNAPSHOT_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	protected: \
		virtual const char *GetSnapshotName() const; \
	}; \
	const char *NAME::GetSnapshotName() const \
	{ \
		return TEXT; \
	}

#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

BFME_LITERAL_NAME_GETTER(AttackContesterStateMachine, "AttackContesterStateMachine")
BFME_LITERAL_NAME_GETTER(GiantBirdGuardMachine, "GiantBirdGuardMachine")
BFME_LITERAL_NAME_GETTER(CastleBehavior, "CastleBehavior")
BFME_LITERAL_NAME_GETTER(Rva003A433BNamed, "FadeAndDieOrnamentUpdate")
BFME_LITERAL_NAME_GETTER(Rva003ABCEENamed, "DefaultModule<CAT_COLOR>")
BFME_LITERAL_NAME_GETTER(Rva00452D72Named, "WallHubBehavior")
BFME_LITERAL_NAME_GETTER(Rva004561BBNamed, "BuildingBehavior")
BFME_LITERAL_NAME_GETTER(RampageBehavior, "RampageBehavior")
BFME_LITERAL_NAME_GETTER(AimWeaponBehavior, "AimWeaponBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045CE86Named, "InstantDeathBehavior")
BFME_LITERAL_NAME_GETTER(ProductionQueueHordeContain, "ProductionQueueHordeContain")
BFME_LITERAL_NAME_GETTER(Rva00485217Named, "RefundDie")
BFME_LITERAL_NAME_GETTER(Rva0048543ENamed, "CreateCrateDie")
BFME_LITERAL_NAME_GETTER(DamageFilteredCreateObjectDie, "DamageFilteredCreateObjectDie")
BFME_LITERAL_NAME_GETTER(Rva0048614FNamed, "CrushDie")
BFME_LITERAL_NAME_GETTER(Rva004864C3Named, "DestroyDie")
BFME_LITERAL_NAME_GETTER(Rva00486592Named, "FXListDie")
BFME_LITERAL_NAME_GETTER(Rva00486A15Named, "SpecialPowerCompletionDie")
BFME_LITERAL_NAME_GETTER(Rva00486B6FNamed, "UpgradeDie")
BFME_LITERAL_NAME_GETTER(Rva00487F5ANamed, "DefaultProductionExitUpdate")
BFME_SNAPSHOT_NAME_GETTER(DeletionUpdate, "DeletionUpdate")
class DozerActionState
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *DozerActionState::GetSnapshotName() const
{
	return "DozerActionState";
}
BFME_SNAPSHOT_NAME_GETTER(DozerPrimaryStateMachine, "DozerPrimaryStateMachine")
BFME_SNAPSHOT_NAME_GETTER(FireSpreadUpdate, "FireSpreadUpdate")
BFME_SNAPSHOT_NAME_GETTER(FloatUpdate, "FloatUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048FBD3Named, "HeightDieUpdate")
BFME_LITERAL_NAME_GETTER(ArrowStormUpdate, "ArrowStormUpdate")
BFME_LITERAL_NAME_GETTER(Rva004918A6Named, "AttachUpdate")
BFME_LITERAL_NAME_GETTER(PickupStuffUpdate, "PickupStuffUpdate")
BFME_LITERAL_NAME_GETTER(Rva00495087Named, "AutoFindHealingUpdate")
BFME_LITERAL_NAME_GETTER(AutoPickUpUpdate, "AutoPickUpUpdate")
BFME_LITERAL_NAME_GETTER(BoredUpdate, "BoredUpdate")
BFME_LITERAL_NAME_GETTER(Rva00496A18Named, "BannerCarrierUpdate")
BFME_LITERAL_NAME_GETTER(Rva00499954Named, "OneRingPenaltyUpdate")
BFME_LITERAL_NAME_GETTER(Rva00499F5ENamed, "SpecialEnemySenseUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049A1C4Named, "AutoDepositUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049ACC5Named, "HordeWorkerAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049B2BBNamed, "OCLUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049BFD7Named, "RadiateFearUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049FE94Named, "ProneUpdate")
BFME_LITERAL_NAME_GETTER(QueueProductionExitUpdate, "QueueProductionExitUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A0C27Named, "RadarUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A3FA4Named, "HijackerUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A4234Named, "StructureCollapseUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A4C39Named, "RubbleRiseUpdate")
BFME_SNAPSHOT_NAME_GETTER(StructureToppleUpdate, "StructureToppleUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A655DNamed, "SupplyCenterProductionExitUpdate")
BFME_LITERAL_NAME_GETTER(SupplyTruckStateMachine, "SupplyTruckStateMachine")
BFME_LITERAL_NAME_GETTER(Rva004A7D75Named, "SupplyWarehouseDockUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A80B1Named, "ToppleUpdate")
BFME_SNAPSHOT_NAME_GETTER(WorkerStateMachine, "WorkerStateMachine")
BFME_LITERAL_NAME_GETTER(RousingSpeechUpdate, "RousingSpeechUpdate")
BFME_LITERAL_NAME_GETTER(GloriousChargeUpdate, "GloriousChargeUpdate")
BFME_LITERAL_NAME_GETTER(Rva004AD9DANamed, "ToggleMountedSpecialAbilityUpdate")
BFME_LITERAL_NAME_GETTER(Rva004AE7A7Named, "DetachableRiderUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B2394Named, "EntEnragedUpdate")
BFME_LITERAL_NAME_GETTER(ArmorUpgrade, "ArmorUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B364DNamed, "BaseUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B3A1CNamed, "CommandSetUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B3C2ANamed, "DelayedUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B3D5BNamed, "LevelUpUpgrade")
BFME_LITERAL_NAME_GETTER(LocomotorSetUpgrade, "LocomotorSetUpgrade")
BFME_LITERAL_NAME_GETTER(ObjectCreationUpgrade, "ObjectCreationUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B4719Named, "RadarUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B48F3Named, "StatusBitsUpgrade")
BFME_LITERAL_NAME_GETTER(DoCommandUpgrade, "DoCommandUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B4CFFNamed, "SubObjectsUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B53FFNamed, "UnpauseSpecialPowerUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B55E8Named, "WeaponBonusUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B56ABNamed, "WeaponSetUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B57EENamed, "GarrisonUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B59A9Named, "CostModifierUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B5D32Named, "SpellRechargeModifierUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B613CNamed, "ExperienceScalarUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B6279Named, "MaxHealthUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B63DDNamed, "ModelConditionUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B66D3Named, "AttributeModifierUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B67FCNamed, "CastleUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B79CDNamed, "TooltipUpgrade")
BFME_LITERAL_NAME_GETTER(RemoveUpgradeUpgrade, "RemoveUpgradeUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B82C5Named, "BuildableHeroListUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B850ANamed, "AllowBannerSpawnUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B85F4Named, "CommandPointsUpgrade")
class BoneFXDamage
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *BoneFXDamage::GetSnapshotName() const
{
	return "BoneFXDamage";
}
BFME_LITERAL_NAME_GETTER(Rva004BAB4FNamed, "ReflectDamage")
BFME_LITERAL_NAME_GETTER(Rva004BB0E5Named, "HordeTransportContainDamage")
BFME_LITERAL_NAME_GETTER(Rva004BB962Named, "SquishCollide")
BFME_LITERAL_NAME_GETTER(AODCrushCollide, "AODCrushCollide")
BFME_LITERAL_NAME_GETTER(Rva004BC33ENamed, "HordeMemberCollide")
BFME_LITERAL_NAME_GETTER(Rva004BC515Named, "CrateCollide")
BFME_LITERAL_NAME_GETTER(Rva004BD606Named, "CivilianSpawnCollide")
BFME_LITERAL_NAME_GETTER(Rva004BD7A8Named, "InactiveBody")
BFME_LITERAL_NAME_GETTER(Rva004C0A65Named, "SymbioticStructuresBody")
BFME_LITERAL_NAME_GETTER(Rva004C187FNamed, "FreeLifeBody")
BFME_LITERAL_NAME_GETTER(Rva004C1BCENamed, "DetachableRiderBody")
BFME_LITERAL_NAME_GETTER(Rva004C2293Named, "HeroDie")
BFME_LITERAL_NAME_GETTER(Rva004C8D3BNamed, "CritterEmitterUpdate")
BFME_LITERAL_NAME_GETTER(Rva004CC653Named, "TemporarilyDefectUpdate")
BFME_LITERAL_NAME_GETTER(Rva004DF34BNamed, "ObjectGuardingHelper")
BFME_LITERAL_NAME_GETTER(Rva004FA61DNamed, "LivingWorldBuildingNuggetSpawnArmy")
BFME_LITERAL_NAME_GETTER(AIGuardMachine, "AIGuardMachine")
BFME_LITERAL_NAME_GETTER(Rva005440C7Named, "AIDockMachine")
BFME_LITERAL_NAME_GETTER(Rva00544C5CNamed, "AIHarvestMachine")
BFME_LITERAL_NAME_GETTER(AIGuardRetaliateMachine, "AIGuardRetaliateMachine")
BFME_LITERAL_NAME_GETTER(AITNGuardMachine, "AITNGuardMachine")
BFME_LITERAL_NAME_GETTER(Rva005890A0Named, "SpecialPowerUpdateModule")
BFME_LITERAL_NAME_GETTER(Rva005CC5DFNamed, "StrategicDetailsRegion.swf")
BFME_LITERAL_NAME_GETTER(Rva005E39E0Named, "StrategicDetailsArmyRetinue.swf")
BFME_LITERAL_NAME_GETTER(Rva005E717ENamed, "StrategicDetailsBuildQueue.swf")
