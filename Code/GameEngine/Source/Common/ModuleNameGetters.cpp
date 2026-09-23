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

BFME_LITERAL_NAME_GETTER(Rva0058A171Named, "DockUpdate")
BFME_LITERAL_NAME_GETTER(Rva0052BA04Named, "LWPlayerDef")
BFME_LITERAL_NAME_GETTER(Rva004FC55DNamed, "LivingWorldBuildPlot")
BFME_LITERAL_NAME_GETTER(Rva004F5BAANamed, "ResourceGatheringManager")
BFME_LITERAL_NAME_GETTER(Rva004F59ACNamed, "MissionStats")
BFME_LITERAL_NAME_GETTER(Rva004F5617Named, "TunnelTracker")
BFME_LITERAL_NAME_GETTER(Rva004F1116Named, "WorkOrder")
BFME_LITERAL_NAME_GETTER(Rva004EF600Named, "TeamInQueue")
BFME_LITERAL_NAME_GETTER(Rva004E4007Named, "ObjectivesMenu")
BFME_LITERAL_NAME_GETTER(Rva004DEA62Named, "FiringTracker")
BFME_LITERAL_NAME_GETTER(Rva004D86BBNamed, "TurretAI")
BFME_LITERAL_NAME_GETTER(Rva004D73F6Named, "SleepState")
BFME_LITERAL_NAME_GETTER(Rva004D73F0Named, "ContinueState")
BFME_LITERAL_NAME_GETTER(Rva004D73EANamed, "FailureState")
BFME_LITERAL_NAME_GETTER(Rva004C9E19Named, "AnimationSoundClientBehavior")
BFME_LITERAL_NAME_GETTER(Rva004C5013Named, "GrabPassengerSpecialPower")
BFME_LITERAL_NAME_GETTER(Rva004BF88DNamed, "ActiveBody")
BFME_LITERAL_NAME_GETTER(Rva004BB6FCNamed, "FireWeaponCollide")
BFME_LITERAL_NAME_GETTER(Rva004B8A22Named, "OathbreakersFadeAwayBehavior")
BFME_LITERAL_NAME_GETTER(Rva004B8797Named, "SpawnUnitBehavior")
BFME_LITERAL_NAME_GETTER(Rva004B7B81Named, "AudioLoopUpgrade")
BFME_LITERAL_NAME_GETTER(Rva004B2ECENamed, "AISpecialPowerUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B138DNamed, "EmotionTrackerUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B0876Named, "AIGateUpdate")
BFME_LITERAL_NAME_GETTER(Rva004B01D3Named, "SpecialDisguiseUpdate")
BFME_LITERAL_NAME_GETTER(Rva004AF15BNamed, "RespawnUpdate")
BFME_LITERAL_NAME_GETTER(Rva004AC93CNamed, "PartTheHeavensUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A9B4BNamed, "WorkerAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A8D93Named, "DelayedLuaEventUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A6A3ANamed, "SupplyTruckAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A3B8FNamed, "SpawnPointProductionExitUpdate")
BFME_LITERAL_NAME_GETTER(Rva004A18BANamed, "SlavedUpdate")
BFME_LITERAL_NAME_GETTER(Rva0049A6C1Named, "HordeAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva004987F4Named, "GateOpenAndCloseBehavior")
BFME_LITERAL_NAME_GETTER(Rva0049795ANamed, "BattlePlanUpdate")
BFME_LITERAL_NAME_GETTER(Rva004925D5Named, "WeaponFireSpecialAbilityUpdate")
BFME_LITERAL_NAME_GETTER(Rva00490019Named, "LargeGroupBonusUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048F456Named, "AssaultTransportAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048E8F1Named, "DeployStyleAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0048BDADNamed, "FireWeaponUpdate")
BFME_LITERAL_NAME_GETTER(Rva00489629Named, "DozerAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva00487A5ENamed, "BoneFXUpdate")
BFME_LITERAL_NAME_GETTER(Rva00486E76Named, "AssistedTargetingUpdate")
BFME_LITERAL_NAME_GETTER(Rva004867D7Named, "RebuildHoleExposeDie")
BFME_LITERAL_NAME_GETTER(Rva0048331CNamed, "RebuildHoleBehavior")
BFME_LITERAL_NAME_GETTER(Rva0048263BNamed, "FireWeaponWhenDamagedBehavior")
BFME_LITERAL_NAME_GETTER(Rva00482EF9Named, "PoisonedBehavior")
BFME_LITERAL_NAME_GETTER(Rva0047E325Named, "RiderChangeContain")
BFME_LITERAL_NAME_GETTER(Rva0047DB88Named, "TunnelContain")
BFME_LITERAL_NAME_GETTER(Rva0047D081Named, "HordeSiegeEngineContain")
BFME_LITERAL_NAME_GETTER(Rva0047C012Named, "SiegeEngineContain")
BFME_LITERAL_NAME_GETTER(Rva00478061Named, "GarrisonContain")
BFME_LITERAL_NAME_GETTER(Rva00467F26Named, "TransportContain")
BFME_LITERAL_NAME_GETTER(Rva00466444Named, "CaveContain")
BFME_LITERAL_NAME_GETTER(Rva004647BANamed, "OpenContain")
BFME_LITERAL_NAME_GETTER(Rva00461EE5Named, "GiantBirdSlowDeathBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045F6CDNamed, "SpawnBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045BFD3Named, "BezierProjectileBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045A3C8Named, "AutoAbilityBehavior")
BFME_LITERAL_NAME_GETTER(Rva004571EENamed, "BridgeBehavior")
BFME_LITERAL_NAME_GETTER(Rva004523A3Named, "AutoHealBehavior")
BFME_LITERAL_NAME_GETTER(Rva0044F099Named, "SpecialAbilityUpdate")
BFME_LITERAL_NAME_GETTER(Rva00448276Named, "LANGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0043C712Named, "SpellStore")
BFME_LITERAL_NAME_GETTER(Rva0043B696Named, "DOTManager")
BFME_LITERAL_NAME_GETTER(Rva00427603Named, "CaveSystem")
BFME_LITERAL_NAME_GETTER(Rva00426C69Named, "MapMissionObjectives")
BFME_LITERAL_NAME_GETTER(Rva00426737Named, "MissionObjectiveTracker")
BFME_LITERAL_NAME_GETTER(Rva00420B2FNamed, "DelayedExperienceLevelGrantSystem")
BFME_LITERAL_NAME_GETTER(Rva0041AC8ANamed, "GameStateMap")
BFME_LITERAL_NAME_GETTER(Rva0040E493Named, "ArmySummary")
BFME_LITERAL_NAME_GETTER(Rva0040DBA3Named, "ArmySummarySystem")
