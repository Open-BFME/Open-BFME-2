// Module literal name getters (state-machine/behavior/update names): six-byte
// const members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated class-name string in
// .rdata. Contributor-local unit split from ModuleNameGetters.cpp to keep
// concurrent landings conflict-free; the BFME_LITERAL_NAME_GETTER macro is
// verbatim, only the class names follow this tree's address-derived
// convention (identity unrecoverable from 6 bytes, string carried in source
// where verify_string_refs re-reads it).
// No // cl: line (defaults match the frameless 6-byte shape, same as the
// ModuleNameGetters.cpp precedent).

#include "../../../Libraries/Include/Lib/Coord3D.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "../../../../reference/shims/bfme2_statemachine/StateMachineView.h"

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

BFME_LITERAL_NAME_GETTER(Rva0033FAF4Named, "AttackStateMachine")
BFME_LITERAL_NAME_GETTER(AttackMeleeStateMachine, "AttackMeleeStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FB7ENamed, "AttackFireWhileMovingMachine")
BFME_LITERAL_NAME_GETTER(AttackFireWhileChargingMachine, "AttackFireWhileChargingMachine")
BFME_LITERAL_NAME_GETTER(AttackPositionStateMachine, "AttackPositionStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FC15Named, "MoveOntoWallStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00340057Named, "AIAttackMOveStateMachine")
BFME_LITERAL_NAME_GETTER(BackAwayAndCowerStateMachine, "BackAwayAndCowerStateMachine")
const char *StateMachine::GetSnapshotName() const
{
	return "StateMachine";
}
BFME_LITERAL_NAME_GETTER(Rva003A49EANamed, "LifetimeUpdate")
BFME_LITERAL_NAME_GETTER(Rva003A4CC7Named, "StrafeAreaUpdate")
BFME_LITERAL_NAME_GETTER(Rva003B040CNamed, "TerrainFireSystemStorageModule")
BFME_LITERAL_NAME_GETTER(Rva00455070Named, "FoundationAIUpdate")
BFME_LITERAL_NAME_GETTER(HitReactionBehavior, "HitReactionBehavior")
BFME_LITERAL_NAME_GETTER(Rva00459573Named, "ClickReactionBehavior")
BFME_LITERAL_NAME_GETTER(DualWeaponBehavior, "DualWeaponBehavior")
class SlowDeathBehavior
{
protected:
	virtual const char *GetSnapshotName() const;
};

const char *SlowDeathBehavior::GetSnapshotName() const
{
	return "SlowDeathBehavior";
}
BFME_LITERAL_NAME_GETTER(Rva0047F946Named, "CivilianSpawnUpdate")
BFME_LITERAL_NAME_GETTER(Rva0047FE45Named, "ShareExperienceBehavior")
BFME_LITERAL_NAME_GETTER(Rva0048182CNamed, "PropagandaTowerBehavior")
BFME_LITERAL_NAME_GETTER(Rva00481FA9Named, "TerrainResourceBehavior")
BFME_LITERAL_NAME_GETTER(Rva004839F3Named, "SupplyWarehouseCripplingBehavior")
BFME_LITERAL_NAME_GETTER(ClearanceTestingSlowDeathBehavior, "ClearanceTestingSlowDeathBehavior")
BFME_LITERAL_NAME_GETTER(Rva00485956Named, "CreateObjectDie")
