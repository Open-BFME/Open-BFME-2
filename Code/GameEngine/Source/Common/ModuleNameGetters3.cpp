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

BFME_LITERAL_NAME_GETTER(Rva0033FB8FNamed, "AttackContesterStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00367F98Named, "GiantBirdGuardMachine")
BFME_LITERAL_NAME_GETTER(Rva00398525Named, "CastleBehavior")
BFME_LITERAL_NAME_GETTER(Rva0039ADFENamed, "ExperienceTrackerObject")
BFME_LITERAL_NAME_GETTER(Rva003A433BNamed, "FadeAndDieOrnamentUpdate")
BFME_LITERAL_NAME_GETTER(Rva003ABCEENamed, "DefaultModule<CAT_COLOR>")
BFME_LITERAL_NAME_GETTER(Rva0044E000Named, "BloodthirstyUpdate")
BFME_LITERAL_NAME_GETTER(Rva00452D72Named, "WallHubBehavior")
BFME_LITERAL_NAME_GETTER(Rva004561BBNamed, "BuildingBehavior")
BFME_LITERAL_NAME_GETTER(Rva00458AC7Named, "RampageBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045B14DNamed, "AimWeaponBehavior")
BFME_LITERAL_NAME_GETTER(Rva0045CE86Named, "InstantDeathBehavior")
BFME_LITERAL_NAME_GETTER(Rva00481273Named, "ProductionQueueHordeContain")
BFME_LITERAL_NAME_GETTER(Rva00485217Named, "RefundDie")
BFME_LITERAL_NAME_GETTER(Rva0048543ENamed, "CreateCrateDie")
BFME_LITERAL_NAME_GETTER(Rva0048599CNamed, "CreateObjectDieIfEldestKindof")
BFME_LITERAL_NAME_GETTER(Rva00485EE3Named, "DamageFilteredCreateObjectDie")
BFME_LITERAL_NAME_GETTER(Rva0048614FNamed, "CrushDie")
BFME_LITERAL_NAME_GETTER(Rva004864C3Named, "DestroyDie")
BFME_LITERAL_NAME_GETTER(Rva00486592Named, "FXListDie")
BFME_LITERAL_NAME_GETTER(Rva00486A15Named, "SpecialPowerCompletionDie")
BFME_LITERAL_NAME_GETTER(Rva00486B6FNamed, "UpgradeDie")
BFME_LITERAL_NAME_GETTER(Rva00486C8FNamed, "KeepObjectDie")
BFME_LITERAL_NAME_GETTER(Rva00487F5ANamed, "DefaultProductionExitUpdate")
BFME_LITERAL_NAME_GETTER(Rva00488288Named, "DelayedWeaponSetUpgradeUpdate")
BFME_LITERAL_NAME_GETTER(Rva00488351Named, "DeletionUpdate")
