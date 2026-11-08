// Subsystem literal name getters, second unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split from
// Code/GameEngine/Source/Common/SubsystemNameGetters.cpp to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
// No // cl: line (defaults match the frameless 6-byte shape).

#include "../../Include/Common/BfmeAccessorMacros.h"


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
#include "../../Include/GameLogic/Bfme2BuildListInfo.h"

const char *BuildListInfo::GetSnapshotName() const
{
	return "BuildListInfo";
}
// The constructor installs Snapshot table VA 0x00C0DA88 at +0x0C.
// Its name slot holds this getter.
#include "../../Include/Common/SidesList.h"

const char *SidesList::GetSnapshotName() const
{
	return "SidesList";
}
#include "../../Include/GameLogic/LuaScriptEngine.h"

const char *LuaScriptEngine::GetSnapshotName() const
{
	return "LuaScriptEngine";
}
BFME_SNAPSHOT_NAME_GETTER(ProjectileStreamUpdate, "ProjectileStreamUpdate")
BFME_LITERAL_NAME_GETTER(Rva0033F2F7Named, "AIInternalMoveToState")
BFME_LITERAL_NAME_GETTER(Rva0033F31ANamed, "AIBusyState")
BFME_SNAPSHOT_NAME_GETTER(AIBackAwayAndCowerState, "AIBackAwayAndCowerState")
BFME_LITERAL_NAME_GETTER(AIAttackMeleeHordeWaitState, "AIAttackMeleeHordeWaitState")
BFME_LITERAL_NAME_GETTER(Rva0033F3B0Named, "AIAttackMeleeHordeWaitPathState")
BFME_LITERAL_NAME_GETTER(Rva00253DF7Named, "HordeNotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(Rva00253ED3Named, "NotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(ModelConditionSoundSelectorClientBehavior, "ModelConditionSoundSelectorClientBehavior")
// Drawable's Snapshot sub-vtable 0x00BFB0A4 (installed by ~Drawable
// 0x002793F0 at this+0x60) holds 0x00279669 in slot 2, the canonical
// Snapshot GetSnapshotName slot; the body returns the unique "Drawable"
// literal. Same six-byte body, real owner, as TerrainLogic below.
#include "../../Include/GameClient/Drawable.h"

const char *Drawable::GetSnapshotName() const
{
	return "Drawable";
}
// Native TerrainLogic ctor283FAA installs BFB2C8; its slot2 is28417C,
// returning the unique TerrainLogic literal. The canonical Snapshot header
// names that slot GetSnapshotName. Replace the placeholder owner directly;
// retain the same six-byte body and the existing source unit.
#include "../../Include/GameLogic/TerrainLogic.h"

const char *TerrainLogic::GetSnapshotName() const
{
	return "TerrainLogic";
}
BFME_LITERAL_NAME_GETTER(Rva00214052Named, "LivingWorldManager")
BFME_LITERAL_NAME_GETTER(Rva001FD2AENamed, "Money")
#include "../../Include/GameLogic/LivingWorldRegionManager.h"
const char *LivingWorldRegionManager::GetSnapshotName() const
{
	return "LivingWorldRegionManager";
}
BFME_LITERAL_NAME_GETTER(SkirmishGameInfo, "SkirmishGameInfo")
// Slot 2 of ObjectWeaponStatusHelper's primary table 0x00BFBE48.
class ObjectWeaponStatusHelper
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *ObjectWeaponStatusHelper::GetSnapshotName() const
{
	return "ObjectWeaponStatusHelper";
}
BFME_LITERAL_NAME_GETTER(ObjectSMCHelper, "ObjectSMCHelper")
BFME_LITERAL_NAME_GETTER(Rva002A92E4Named, "SkirmishAIManager")
BFME_LITERAL_NAME_GETTER(Rva002AC360Named, "LightPointSystem")
BFME_SNAPSHOT_NAME_GETTER(PlayerRelationMap, "PlayerRelationMap")
BFME_LITERAL_NAME_GETTER(Rva002B30A8Named, "DelayedAudioEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B30D3Named, "DelayedCameraEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B596CNamed, "DelayedWorldTextEventModule")
#include "../../Include/GameLogic/LivingWorldLogic.h"
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
BFME_LITERAL_NAME_GETTER(Rva002DAB5ENamed, "TerrainVisual")
BFME_LITERAL_NAME_GETTER(Pathfinder, "Pathfinder")
#include "../../Include/GameLogic/TAiData.h"

const char *TAiData::GetSnapshotName() const
{
	return "TAiData";
}
