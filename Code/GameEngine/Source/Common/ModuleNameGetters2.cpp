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
BFME_LITERAL_NAME_GETTER(Rva0033FB05Named, "AttackMeleeStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FB7ENamed, "AttackFireWhileMovingMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FBA0Named, "AttackFireWhileChargingMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FBB1Named, "AttackPositionStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FC15Named, "MoveOntoWallStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00340057Named, "AIAttackMOveStateMachine")
BFME_LITERAL_NAME_GETTER(Rva003402DBNamed, "BackAwayAndCowerStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00341456Named, "StateMachine")
BFME_LITERAL_NAME_GETTER(Rva003A49EANamed, "LifetimeUpdate")
BFME_LITERAL_NAME_GETTER(Rva003A4CC7Named, "StrafeAreaUpdate")
BFME_LITERAL_NAME_GETTER(Rva003B040CNamed, "TerrainFireSystemStorageModule")
BFME_LITERAL_NAME_GETTER(Rva00455070Named, "FoundationAIUpdate")
