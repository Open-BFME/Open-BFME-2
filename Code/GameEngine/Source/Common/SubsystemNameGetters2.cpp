// Subsystem literal name getters, second unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split from
// Code/GameEngine/Source/Common/SubsystemNameGetters.cpp to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
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

BFME_LITERAL_NAME_GETTER(TerrainResourceClientBehavior, "TerrainResourceClientBehavior")
class UpdateModule
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *UpdateModule::GetSnapshotName() const
{
	return "UpdateModule";
}
BFME_LITERAL_NAME_GETTER(Rva00268CD6Named, "Squad")
BFME_LITERAL_NAME_GETTER(Rva0026E7E4Named, "LuaSpyData")
BFME_LITERAL_NAME_GETTER(AIUpdateInterface, "AIUpdateInterface")
BFME_LITERAL_NAME_GETTER(Upgrade, "Upgrade")
BFME_LITERAL_NAME_GETTER(GhostObject, "GhostObject")
BFME_LITERAL_NAME_GETTER(Rva00306A48Named, "Module")
BFME_LITERAL_NAME_GETTER(ObjectModule, "ObjectModule")
BFME_LITERAL_NAME_GETTER(Rva0031860DNamed, "GlobalWeatherSystem")
BFME_LITERAL_NAME_GETTER(Rva00318B7DNamed, "ArmyMoveCommand")
class BuildListInfo
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *BuildListInfo::GetSnapshotName() const
{
	return "BuildListInfo";
}
// The constructor installs Snapshot table VA 0x00C0DA88 at +0x0C.
// Its name slot holds this getter.
class SidesList
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *SidesList::GetSnapshotName() const
{
	return "SidesList";
}
class LuaScriptEngine
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *LuaScriptEngine::GetSnapshotName() const
{
	return "LuaScriptEngine";
}
BFME_SNAPSHOT_NAME_GETTER(ProjectileStreamUpdate, "ProjectileStreamUpdate")
BFME_LITERAL_NAME_GETTER(Rva0033F2F7Named, "AIInternalMoveToState")
BFME_LITERAL_NAME_GETTER(Rva0033F31ANamed, "AIBusyState")
BFME_LITERAL_NAME_GETTER(Rva0033F35ENamed, "AIBackAwayAndCowerState")
BFME_LITERAL_NAME_GETTER(AIAttackMeleeHordeWaitState, "AIAttackMeleeHordeWaitState")
BFME_LITERAL_NAME_GETTER(Rva0033F3B0Named, "AIAttackMeleeHordeWaitPathState")
BFME_LITERAL_NAME_GETTER(Rva00253DF7Named, "HordeNotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(Rva00253ED3Named, "NotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(ModelConditionSoundSelectorClientBehavior, "ModelConditionSoundSelectorClientBehavior")
// Drawable's Snapshot sub-vtable 0x00BFB0A4 (installed by ~Drawable
// 0x002793F0 at this+0x60) holds 0x00279669 in slot 2, the canonical
// Snapshot GetSnapshotName slot; the body returns the unique "Drawable"
// literal. Same six-byte body, real owner, as TerrainLogic below.
class Drawable
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *Drawable::GetSnapshotName() const
{
	return "Drawable";
}
// Native TerrainLogic ctor283FAA installs BFB2C8; its slot2 is28417C,
// returning the unique TerrainLogic literal. The canonical Snapshot header
// names that slot GetSnapshotName. Replace the placeholder owner directly;
// retain the same six-byte body and the existing source unit.
class TerrainLogic
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *TerrainLogic::GetSnapshotName() const
{
	return "TerrainLogic";
}
BFME_LITERAL_NAME_GETTER(Rva00214052Named, "LivingWorldManager")
BFME_LITERAL_NAME_GETTER(Rva001FD2AENamed, "Money")
class LivingWorldRegionManager { public: virtual const char *GetSnapshotName() const; };
const char *LivingWorldRegionManager::GetSnapshotName() const
{
	return "LivingWorldRegionManager";
}
BFME_LITERAL_NAME_GETTER(SkirmishGameInfo, "SkirmishGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0028CBDBNamed, "ObjectWeaponStatusHelper")
BFME_LITERAL_NAME_GETTER(ObjectSMCHelper, "ObjectSMCHelper")
BFME_LITERAL_NAME_GETTER(Rva002A7A23Named, "PlayerList")
BFME_LITERAL_NAME_GETTER(Rva002A92E4Named, "SkirmishAIManager")
BFME_LITERAL_NAME_GETTER(Rva002AC360Named, "LightPointSystem")
BFME_SNAPSHOT_NAME_GETTER(PlayerRelationMap, "PlayerRelationMap")
BFME_LITERAL_NAME_GETTER(Rva002B30A8Named, "DelayedAudioEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B30D3Named, "DelayedCameraEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B596CNamed, "DelayedWorldTextEventModule")
class LivingWorldLogic { public: virtual const char *GetSnapshotName() const; };
const char *LivingWorldLogic::GetSnapshotName() const
{
	return "LivingWorldLogic";
}
BFME_LITERAL_NAME_GETTER(Rva002BAE89Named, "DelayedSplineCameraEventModule")
// Slot 2 of native RadarObject table VA C035D0 returns this literal.
// The canonical BFME2 Snapshot interface names this slot GetSnapshotName;
// WB 1107320 and the adjacent RadarObject constructor establish its owner.
class RadarObject
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *RadarObject::GetSnapshotName() const
{
	return "RadarObject";
}
BFME_LITERAL_NAME_GETTER(Rva002DAB5ENamed, "TerrainVisual")
BFME_LITERAL_NAME_GETTER(Pathfinder, "Pathfinder")
class TAiData
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *TAiData::GetSnapshotName() const
{
	return "TAiData";
}
