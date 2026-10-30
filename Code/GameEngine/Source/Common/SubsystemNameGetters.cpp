// Subsystem literal name getters: six-byte const members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated class-name string in
// .rdata. The vtable at each site carries the body at slot 2 (offset 8)
// behind a shared pair (slot 0 varies, slot 1 is 0xA9E440) and ahead of
// class-specific tails, closed by 0x5B5384 -- the Subsystem/Snapshot family
// pattern. Ported from Open-BFME-1
// (Code/GameEngine/Source/Common/LiteralNameGetters_01.cpp): the
// BFME_LITERAL_NAME_GETTER macro is verbatim; only the class names follow
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

BFME_LITERAL_NAME_GETTER(Rva006254A0Named, "PartitionManager")
class ModuleData
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *ModuleData::GetSnapshotName() const
{
	return "ModuleData";
}
BFME_LITERAL_NAME_GETTER(Rva00041FC9Named, "GameLogic")
BFME_LITERAL_NAME_GETTER(Rva000420D6Named, "ModuleFactory")
BFME_LITERAL_NAME_GETTER(Rva0004C457Named, "GameClient")
BFME_LITERAL_NAME_GETTER(Rva0004CE28Named, "FXParticleSystemManager")
BFME_LITERAL_NAME_GETTER(Rva0004FA11Named, "Radar")
BFME_LITERAL_NAME_GETTER(Rva000647CENamed, "W3DBuffLogic")
BFME_LITERAL_NAME_GETTER(Rva000665B9Named, "TScorch")
BFME_LITERAL_NAME_GETTER(Rva0006CE6BNamed, "UNNAMED")
BFME_LITERAL_NAME_GETTER(Rva0006D054Named, "BaseHeightMapRenderObjClass")
BFME_LITERAL_NAME_GETTER(Rva00078B7DNamed, "W3DHordeModelDraw")
BFME_LITERAL_NAME_GETTER(WaterRenderObjClass, "WaterRenderObjClass")
BFME_LITERAL_NAME_GETTER(Rva0008EFD2Named, "InGameUI")
class Eva
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *Eva::GetSnapshotName() const
{
	return "Eva";
}
BFME_LITERAL_NAME_GETTER(Rva002AA3AFNamed, "Energy")
BFME_LITERAL_NAME_GETTER(Rva00091AACNamed, "W3DTerrainVisual")
class W3DDebrisDraw
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *W3DDebrisDraw::GetSnapshotName() const
{
	return "W3DDebrisDraw";
}
BFME_LITERAL_NAME_GETTER(EventParameter, "EventParameter")
BFME_LITERAL_NAME_GETTER(Rva000B6DCCNamed, "LuaEventParameters")
BFME_LITERAL_NAME_GETTER(Rva001042C1Named, "Palantir")
BFME_LITERAL_NAME_GETTER(Rva001E3E56Named, "Locomotor")
BFME_LITERAL_NAME_GETTER(Rva001E70BCNamed, "LocomotorSet")
BFME_LITERAL_NAME_GETTER(Rva001EAE63Named, "LinearCampaign")
BFME_LITERAL_NAME_GETTER(Rva001EAE69Named, "LinearCampaignManager")
BFME_LITERAL_NAME_GETTER(Rva001FBEB1Named, "FXParticleSystem")
BFME_LITERAL_NAME_GETTER(ScriptEngine, "ScriptEngine")
class FireLogicSystem
{
public:
	virtual const char *GetSnapshotName() const;
};

const char *FireLogicSystem::GetSnapshotName() const
{
	return "FireLogicSystem";
}
BFME_LITERAL_NAME_GETTER(Rva002AE621Named, "Command")
BFME_LITERAL_NAME_GETTER(CarryoverUnit, "CarryoverUnit")
BFME_LITERAL_NAME_GETTER(Rva00414307Named, "ScoredKillEvaAnnouncer")
class LivingWorldBuilding { public: virtual const char *GetSnapshotName(); };
const char *LivingWorldBuilding::GetSnapshotName() { return "LivingWorldBuilding"; }
BFME_LITERAL_NAME_GETTER(Rva001F37BENamed, "FXParticleInfo")
BFME_LITERAL_NAME_GETTER(Rva001FC179Named, "FXParticle")
class SequentialScript { public: virtual const char *GetSnapshotName(); };
const char *SequentialScript::GetSnapshotName() { return "SequentialScript"; }
// LargeGroupAudio getter is owned by the complete subsystem unit.
class GeometryInfo
{
public:
	virtual const char *GetSnapshotName();
};

const char *GeometryInfo::GetSnapshotName()
{
	return "GeometryInfo";
}
BFME_LITERAL_NAME_GETTER(MilesAudioManager, "MilesAudioManager")
BFME_LITERAL_NAME_GETTER(Rva0008BC8BNamed, "View")
class DrawModule
{
protected:
    virtual const char *GetSnapshotName() const;
};
BFME_LITERAL_NAME_GETTER(Rva00226309Named, "SaveMapPreview")
BFME_LITERAL_NAME_GETTER(Rva002296E6Named, "GameSlot")
BFME_LITERAL_NAME_GETTER(Rva00229902Named, "LobbyGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0022CEF1Named, "SaveGameInfo")
BFME_LITERAL_NAME_GETTER(Rva002431A9Named, "InvisibilityManager")
class BehaviorModule
{
protected:
	virtual const char *GetSnapshotName() const;
};
BFME_LITERAL_NAME_GETTER(GateProxyBehavior, "GateProxyBehavior")
BFME_LITERAL_NAME_GETTER(SpawnedModelConditionCreate, "SpawnedModelConditionCreate")
BFME_LITERAL_NAME_GETTER(Rva00251C76Named, "SpecialPowerTimerRefreshSpecialPower")
BFME_LITERAL_NAME_GETTER(Rva00252B84Named, "DrawableModule")
BFME_LITERAL_NAME_GETTER(UpgradeSoundSelectorClientBehavior, "UpgradeSoundSelectorClientBehavior")
BFME_LITERAL_NAME_GETTER(Rva0028C9D7Named, "ObjectDefectionHelper")
BFME_LITERAL_NAME_GETTER(Rva0028CA92Named, "ObjectRecoveryHelper")
BFME_LITERAL_NAME_GETTER(Rva0028CB23Named, "ObjectRepulsorHelper")
