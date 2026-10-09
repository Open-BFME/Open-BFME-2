// Subsystem literal name getters, second unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split from
// Code/GameEngine/Source/Common/SubsystemNameGetters.cpp to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
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

BFME_LITERAL_NAME_GETTER(Rva00252E50Named, "TerrainResourceClientBehavior")
BFME_LITERAL_NAME_GETTER(Rva002533CDNamed, "UpdateModule")
BFME_LITERAL_NAME_GETTER(Rva00268CD6Named, "Squad")
BFME_LITERAL_NAME_GETTER(Rva0026E7E4Named, "LuaSpyData")
BFME_LITERAL_NAME_GETTER(Rva0026E982Named, "AIUpdateInterface")
BFME_LITERAL_NAME_GETTER(Rva0026EDF9Named, "Upgrade")
BFME_LITERAL_NAME_GETTER(Rva00305B30Named, "GhostObject")
BFME_LITERAL_NAME_GETTER(Rva003067C4Named, "BuffLogic")
BFME_LITERAL_NAME_GETTER(Rva00306A48Named, "Module")
BFME_LITERAL_NAME_GETTER(Rva00306B13Named, "ObjectModule")
BFME_LITERAL_NAME_GETTER(Rva0031860DNamed, "GlobalWeatherSystem")
BFME_LITERAL_NAME_GETTER(Rva00318B7DNamed, "ArmyMoveCommand")
BFME_LITERAL_NAME_GETTER(Rva00319E76Named, "LivingWorldArmy")
BFME_LITERAL_NAME_GETTER(Rva00329EE3Named, "BuildListInfo")
BFME_LITERAL_NAME_GETTER(Rva0032ED53Named, "SidesList")
BFME_LITERAL_NAME_GETTER(Rva00337AA2Named, "LuaScriptEngine")
BFME_LITERAL_NAME_GETTER(Rva0033EE7ENamed, "ProjectileStreamUpdate")
BFME_LITERAL_NAME_GETTER(Rva0033F2F7Named, "AIInternalMoveToState")
BFME_LITERAL_NAME_GETTER(Rva0033F31ANamed, "AIBusyState")
BFME_LITERAL_NAME_GETTER(Rva0033F35ENamed, "AIBackAwayAndCowerState")
BFME_LITERAL_NAME_GETTER(Rva0033F385Named, "AIAttackMeleeHordeWaitState")
BFME_LITERAL_NAME_GETTER(Rva0033F3B0Named, "AIAttackMeleeHordeWaitPathState")
BFME_LITERAL_NAME_GETTER(Rva00253DF7Named, "HordeNotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(Rva00253ED3Named, "NotifyTargetsOfImminentProbableCrushingUpdate")
BFME_LITERAL_NAME_GETTER(Rva00254BF1Named, "ModelConditionSoundSelectorClientBehavior")
BFME_LITERAL_NAME_GETTER(Rva00279669Named, "Drawable")
BFME_LITERAL_NAME_GETTER(Rva0028417CNamed, "TerrainLogic")
BFME_LITERAL_NAME_GETTER(Rva00214052Named, "LivingWorldManager")
BFME_LITERAL_NAME_GETTER(Rva001FD2AENamed, "Money")
BFME_LITERAL_NAME_GETTER(Rva002104B0Named, "LivingWorldRegionManager")
BFME_LITERAL_NAME_GETTER(Rva0022C4D9Named, "SkirmishGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0028CBDBNamed, "ObjectWeaponStatusHelper")
BFME_LITERAL_NAME_GETTER(Rva0029288ENamed, "ObjectSMCHelper")
BFME_LITERAL_NAME_GETTER(Rva002A7A23Named, "PlayerList")
BFME_LITERAL_NAME_GETTER(Rva002A92E4Named, "SkirmishAIManager")
BFME_LITERAL_NAME_GETTER(Rva002AC360Named, "LightPointSystem")
BFME_LITERAL_NAME_GETTER(Rva002AD0C0Named, "PlayerRelationMap")
BFME_LITERAL_NAME_GETTER(Rva002B30A8Named, "DelayedAudioEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B30D3Named, "DelayedCameraEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B596CNamed, "DelayedWorldTextEventModule")
BFME_LITERAL_NAME_GETTER(Rva002B9641Named, "LivingWorldLogic")
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
BFME_LITERAL_NAME_GETTER(Rva002DE57FNamed, "GameState")
BFME_LITERAL_NAME_GETTER(Rva002F21EBNamed, "Pathfinder")
BFME_LITERAL_NAME_GETTER(Rva002FE03BNamed, "TAiData")
