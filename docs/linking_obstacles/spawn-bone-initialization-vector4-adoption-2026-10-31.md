### Spawn-bone initialization Vector4 adoption (2026-10-31)

SpawnPointInitializeBonePositions.cpp now uses the existing Vector4 storage,
empty ctor and Set header. Its 340-byte row and all ten external code bodies
and relocations are unchanged, with no new helper. Strict preparation and
owning acceptance retire one key; bounded LINKS/340 is preserved. With
offset/shroud transforms, two keys are retired, 3/3 rows pass, and bounded
cohort 1,133 -> 1,133 stays unchanged. Private Matrix3D/Thing adoption and
complete affected-consumer/census validation remain separate.
[Controls and scope](../../reverse/attempt_support/spawn-bone-vector4-adoption-20261031.md).

The offset/shroud unit's retained Matrix3D const accessor remains divergent
in the shadow identity check. Its before/after body and relocations are
identical; that existing provider reconciliation remains open.

The outgoing two-source audit with fresh owned-provider receipts is
INCONCLUSIVE: `3c7a254a38` predates explicit base `59018891cc`, and affected
consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
Carry that scope into the next scheduled census; complete consumer-loss
clearance remains unproven.
