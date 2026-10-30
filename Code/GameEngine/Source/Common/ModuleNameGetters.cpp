// Module literal name getters: six-byte const members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated Behavior/Update/Contain
// class-name string in .rdata. Each body VA carries exactly one .rdata
// reference from its module vtable (descriptor tail closed by the shared
// 0x004B3FD0 pair -- the same family marker as the Subsystem getters).
// Split from Code/GameEngine/Source/Common/SubsystemNameGetters.cpp into a
// contributor-local unit to keep concurrent landings conflict-free; the
// BFME_LITERAL_NAME_GETTER macro is verbatim, only the class names follow
// this tree's address-derived convention (identity unrecoverable from 6
// bytes, string carried in source where verify_string_refs re-reads it).
// No // cl: line (defaults match the frameless 6-byte shape).

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

BFME_LITERAL_NAME_GETTER(DockUpdate, "DockUpdate")
BFME_LITERAL_NAME_GETTER(Rva0052BA04Named, "LWPlayerDef")
BFME_LITERAL_NAME_GETTER(ResourceGatheringManager, "ResourceGatheringManager")
BFME_LITERAL_NAME_GETTER(Rva004F59ACNamed, "MissionStats")
#include "../GameLogic/AI/WorkOrder.h"
const char *WorkOrder::GetSnapshotName() const { return "WorkOrder"; }
#include "../GameLogic/AI/TeamInQueue.h"
const char *TeamInQueue::GetSnapshotName() const { return "TeamInQueue"; }
BFME_LITERAL_NAME_GETTER(Rva004E4007Named, "ObjectivesMenu")
BFME_SNAPSHOT_NAME_GETTER(FiringTracker, "FiringTracker")
BFME_LITERAL_NAME_GETTER(TurretAI, "TurretAI")
BFME_LITERAL_NAME_GETTER(AnimationSoundClientBehavior, "AnimationSoundClientBehavior")
BFME_LITERAL_NAME_GETTER(ActiveBody, "ActiveBody")
BFME_LITERAL_NAME_GETTER(Rva004BB6FCNamed, "FireWeaponCollide")
BFME_LITERAL_NAME_GETTER(Rva004B8797Named, "SpawnUnitBehavior")
BFME_LITERAL_NAME_GETTER(AudioLoopUpgrade, "AudioLoopUpgrade")
BFME_LITERAL_NAME_GETTER(AISpecialPowerUpdate, "AISpecialPowerUpdate")
BFME_LITERAL_NAME_GETTER(EmotionTrackerUpdate, "EmotionTrackerUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B0876Named, "AIGateUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B01D3Named, "SpecialDisguiseUpdate")
BFME_LITERAL_NAME_GETTER(RespawnUpdate, "RespawnUpdate")
BFME_LITERAL_NAME_GETTER(Rva004AC93CNamed, "PartTheHeavensUpdate")
BFME_SNAPSHOT_NAME_GETTER(WorkerAIUpdate, "WorkerAIUpdate")
BFME_LITERAL_NAME_GETTER(DelayedLuaEventUpdate, "DelayedLuaEventUpdate")
BFME_LITERAL_NAME_GETTER(SupplyTruckAIUpdate, "SupplyTruckAIUpdate")
BFME_LITERAL_NAME_GETTER(SpawnPointProductionExitUpdate, "SpawnPointProductionExitUpdate")
BFME_SNAPSHOT_NAME_GETTER(SlavedUpdate, "SlavedUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049A6C1Named, "HordeAIUpdate")
BFME_LITERAL_NAME_GETTER(GateOpenAndCloseBehavior, "GateOpenAndCloseBehavior")
BFME_LITERAL_NAME_GETTER(Rva0049795ANamed, "BattlePlanUpdate")
BFME_LITERAL_NAME_GETTER(WeaponFireSpecialAbilityUpdate, "WeaponFireSpecialAbilityUpdate")
BFME_LITERAL_NAME_GETTER(Rva00490019Named, "LargeGroupBonusUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048F456Named, "AssaultTransportAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048E8F1Named, "DeployStyleAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048BDADNamed, "FireWeaponUpdate")
BFME_SNAPSHOT_NAME_GETTER(DozerAIUpdate, "DozerAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva00487A5ENamed, "BoneFXUpdate")
BFME_SNAPSHOT_NAME_GETTER(AssistedTargetingUpdate, "AssistedTargetingUpdate")
BFME_LITERAL_NAME_GETTER(RebuildHoleExposeDie, "RebuildHoleExposeDie")
BFME_LITERAL_NAME_GETTER(RebuildHoleBehavior, "RebuildHoleBehavior")
BFME_LITERAL_NAME_GETTER(FireWeaponWhenDamagedBehavior, "FireWeaponWhenDamagedBehavior")
BFME_LITERAL_NAME_GETTER(Rva00482EF9Named, "PoisonedBehavior")
BFME_LITERAL_NAME_GETTER(RiderChangeContain, "RiderChangeContain")
BFME_LITERAL_NAME_GETTER(TunnelContain, "TunnelContain")
BFME_LITERAL_NAME_GETTER(HordeSiegeEngineContain, "HordeSiegeEngineContain")
BFME_LITERAL_NAME_GETTER(SiegeEngineContain, "SiegeEngineContain")
BFME_LITERAL_NAME_GETTER(GarrisonContain, "GarrisonContain")
BFME_LITERAL_NAME_GETTER(TransportContain, "TransportContain")
BFME_LITERAL_NAME_GETTER(CaveContain, "CaveContain")
BFME_LITERAL_NAME_GETTER(OpenContain, "OpenContain")
BFME_LITERAL_NAME_GETTER(Rva00461EE5Named, "GiantBirdSlowDeathBehavior")
BFME_LITERAL_NAME_GETTER(SpawnBehavior, "SpawnBehavior")
BFME_LITERAL_NAME_GETTER(BezierProjectileBehavior, "BezierProjectileBehavior")
BFME_LITERAL_NAME_GETTER(AutoAbilityBehavior, "AutoAbilityBehavior")
BFME_SNAPSHOT_NAME_GETTER(BridgeBehavior, "BridgeBehavior")
BFME_SNAPSHOT_NAME_GETTER(AutoHealBehavior, "AutoHealBehavior")
BFME_LITERAL_NAME_GETTER(Rva0044F099Named, "SpecialAbilityUpdate")
BFME_LITERAL_NAME_GETTER(Rva00448276Named, "LANGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0043C712Named, "SpellStore")
BFME_LITERAL_NAME_GETTER(Rva0043B696Named, "DOTManager")
BFME_LITERAL_NAME_GETTER(Rva00427603Named, "CaveSystem")
BFME_LITERAL_NAME_GETTER(Rva00426C69Named, "MapMissionObjectives")
BFME_LITERAL_NAME_GETTER(Rva00426737Named, "MissionObjectiveTracker")
BFME_LITERAL_NAME_GETTER(Rva00420B2FNamed, "DelayedExperienceLevelGrantSystem")
BFME_LITERAL_NAME_GETTER(Rva0041AC8ANamed, "GameStateMap")
BFME_LITERAL_NAME_GETTER(Rva0040DBA3Named, "ArmySummarySystem")
