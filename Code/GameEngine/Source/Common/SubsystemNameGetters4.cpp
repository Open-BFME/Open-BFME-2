#include "../../Include/Common/Rva003AE07D.h"
#include "../GameClient/BuffManager.h"
// Subsystem literal name getters, fourth unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
// Each body returns a pointer to a NUL-terminated class-name string in .rdata
// with exactly one vtable (body-VA) reference behind a C3 predecessor;
// verify_string_refs re-reads the string.
// No // cl: line (defaults match the frameless 6-byte shape).

#include "../../Include/Common/BfmeAccessorMacros.h"

BFME_LITERAL_NAME_GETTER(Rva00271892Named, "TintEnvelope")
// RegionAwardDispute::GetSnapshotName is owned by Rva002B644ACtor.cpp.
BFME_LITERAL_NAME_GETTER(Rva0033F517Named, "AIAttackSquadState")
BFME_LITERAL_NAME_GETTER(Rva0033FB6DNamed, "AttackHordeStateMachine")
BFME_LITERAL_NAME_GETTER(AttackPositionHordeStateMachine, "AttackPositionHordeStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00340C27Named, "AIAttackMeleeEngageState")
BFME_LITERAL_NAME_GETTER(Rva00340D6ANamed, "AIFollowPathAsTeamState")
BFME_LITERAL_NAME_GETTER(Rva00345CFANamed, "AIAttackMoveToState")
BFME_LITERAL_NAME_GETTER(Rva00345F70Named, "AIAttackFollowWaypointPathState")
BFME_LITERAL_NAME_GETTER(Rva0034B172Named, "AIAttackState")
BFME_LITERAL_NAME_GETTER(Rva00354EF6Named, "AiOrdersManager")
BFME_LITERAL_NAME_GETTER(Rva0035701FNamed, "AttackPriorityInfo")

BFME_LITERAL_NAME_GETTER(Rva00367929Named, "GiantBirdDieState")
BFME_LITERAL_NAME_GETTER(GiantBirdAIUpdate, "GiantBirdAIUpdate")
BFME_LITERAL_NAME_GETTER(AIGroup, "AIGroup")
BFME_LITERAL_NAME_GETTER(Rva00373411Named, "MineshaftPortalNetworkManager")
BFME_LITERAL_NAME_GETTER(Rva00373D0FNamed, "StealthUpdate")
BFME_LITERAL_NAME_GETTER(ObjectTypes, "ObjectTypes")
BFME_LITERAL_NAME_GETTER(PhysicsBehavior, "PhysicsBehavior")
BFME_LITERAL_NAME_GETTER(RadiusDecalUpdate, "RadiusDecalUpdate")
BFME_LITERAL_NAME_GETTER(CastleMemberBehavior, "CastleMemberBehavior")
// ScoreKeeper::GetSnapshotName is owned by RTS/ScoreKeeperDtor.cpp.
// Slot 2 of TeamRelationMap's vftable 0x00C1ADFC: the Snapshot name slot.
class TeamRelationMap
{
protected:
	virtual const char *GetSnapshotName() const;
};
const char *TeamRelationMap::GetSnapshotName() const
{
	return "TeamRelationMap";
}
// TeamFactory::GetSnapshotName is owned by RTS/TeamFactoryDtor.cpp.
BFME_LITERAL_NAME_GETTER(Rva003B03EDNamed, "GPUParticleSystemStorageModule")
// Rva003B3662 "Script" is Script::GetSnapshotName, rowed under its real
// name from Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptDtor.cpp.
BFME_SNAPSHOT_NAME_GETTER(ScriptGroup, "ScriptGroup")
// ScriptList::GetSnapshotName is owned by ScriptListDestructor.cpp.
BFME_LITERAL_NAME_GETTER(Rva003B9124Named, "LivingWorldCampaignManager")
class Xfer;
class LivingWorldRegion
{
public:
    virtual ~LivingWorldRegion();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *);
};
const char *LivingWorldRegion::GetSnapshotName() const
{
    return "LivingWorldRegion";
}
BFME_LITERAL_NAME_GETTER(Rva003F6A8BNamed, "LivingWorldBattle")
BFME_LITERAL_NAME_GETTER(Rva003F9CCCNamed, "LivingWorldEyeTower")
BFME_LITERAL_NAME_GETTER(Rva003FD374Named, "DelayedRegionFlashModule")
BFME_SNAPSHOT_NAME_GETTER(AttributeModifierPoolUpdate, "AttributeModifierPoolUpdate")
// VictorySystem::GetSnapshotName is owned by Rva004053C2Dtor.cpp.
BFME_LITERAL_NAME_GETTER(Rva005C43C9Named, "LivingWorldBuildingNuggetIncreaseCommandPoints")
BFME_LITERAL_NAME_GETTER(Rva00351753Named, "AIStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0037BB4DNamed, "GameInfo")
const char *Rva003AE07D::GetSnapshotName() const
{
    return "ParticleWindModuleInfo";
}
BFME_LITERAL_NAME_GETTER(Rva003ABE7FNamed, "RenderObjectUpdateModule")
class CreateAHeroData
{
public:
 virtual const char *GetSnapshotName() const;
};

const char *CreateAHeroData::GetSnapshotName() const
{
 return "CreateAHeroData";
}
