### DieModule callback and finder header adoption (2026-10-30)

At base `04e74d7e4d`, CreateObjectDie_onDie now inherits canonical DieModule
and calls its protected helper as a member; RebuildHoleExposeDieFind uses
the canonical slot-4 getModuleNameKey. All four rows verify, the finder EH
graph is EXACT, and all three external COMDAT fingerprints, external
bindings and relocation graphs remain identical. Strict preparation passes;
both ordinary previews retain LINKS for 256 authored bytes against
`12b9e7a7c0` (2026-10-30 10:11). The owning acceptance tool retires two
header-queue rows. No census gain or source-file reduction is claimed.

The staged batch audit is INCONCLUSIVE on that older index and missing
current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Full
affected-consumer selection and loss checks remain pending; carry both
providers and wider consumers into the next scheduled census. Remaining
DieModule destructor-shape, field/accessor and linking prerequisites below
remain open. [Evidence and reference freshness boundary](../../reverse/attempt_support/diemodule-header-adoption-20261030-codex4.md).
