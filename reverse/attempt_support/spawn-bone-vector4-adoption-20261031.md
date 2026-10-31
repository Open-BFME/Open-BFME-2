# Spawn-bone initialization: canonical Vector4 storage and Set

Base `a70298122`; claimed Vector4 and source scopes. Replace the private
Vector4 class in `ProductionExitUpdate/SpawnPointInitializeBonePositions.cpp`
with the existing canonical Vector4Data.h. Its four-float storage, empty
constructor and Set implementation match the target's existing row layout.
The three 16-byte rows form each 48-byte local Matrix3D, and ten transforms
are initialized before querying bone positions. Native behavior and the
existing constructor/Set bodies decide this change; no layout is inferred
from byte equality alone.

The 340-byte initializeBonePositions row at `004A3CEA` remains exact.
Every byte and relocation of all ten retained external code definitions is
identical, including the row ctor/Set and matrix/translation helpers. No
code definition is added or removed, and no standalone helper is introduced.
Shared headers, flags, source paths, pins, aliases, data rows and baselines
are unchanged. Private Matrix3D and Thing views remain separate adoption
work; their queue entries are not claimed retired.

Normal/frozen verification, fresh strict provider preparation and owning
Vector4 acceptance pass. Exactly this source's one queue key is retired by
the owning tool. Bounded `3c7a254a38` preview (2026-10-31 13:43) retains
LINKS/340 authored bytes. With the separate offset/shroud transform task,
the batch retires two Vector4 keys, verifies 3/3 rows and retains bounded
cohort 1,133 -> 1,133. This is header-debt retirement, not new matched or
census-linked bytes or runtime proof.

The offset/shroud unit's shadow identity check still reports the existing
divergent Matrix3D const row accessor. The before/after COFF comparison
proves that body/relocations unchanged; it belongs to the separately open
Matrix3D provider reconciliation. Scoped LINKS does not clear full provider
selection, affected-consumer verification or the next census.

Original source/object, final COFF comparison, normal/strict/acceptance
controls and bounded preview are retained under ignored
`build/two-each-no-qwen-20261031-1756` and the matching diagnostic package.
Qwen and other local inference remain off; the shared ten-worker cap stays
in place without changing an Unreal process.

## Outgoing consumer audit

After fresh strict preparation of both owned sources, the audit at explicit
base `59018891ccdaea4b6cdabfa0c100ffc09d4369c3`, tip `26b4f1671`, with
the NUL-delimited two-source list returns INCONCLUSIVE, exit 2. The index
`3c7a254a38` predates that base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. The owned providers themselves have fresh receipts.
Carry this provider/consumer scope into the next scheduled census; the two
retired keys do not establish complete consumer-loss clearance. The
publisher hook audits the final rebased outgoing range again.
