### TerrainTypes allocation-helper consolidation (2026-10-29, codex3)

At base `be006165be`, the normal current-map merger absorbs the allocation
helper at `0x00317D5C` into `Common/TerrainTypes.cpp`, removing one source file
and preserving 24/24 rows and parent EH graphs. Ordinary preview retains LINKS
for 841 authored bytes against index `85f6b7f40c` (2026-10-29 15:08); the 45
additional bytes are existing donor ownership transferred into the TU.
The six candidate units pass the merge guard. Private TerrainType layout and
STLport declarations still prevent four donors from composing; the full-header
assignment trial also hits VC7.1 C1001 at its member-template call. Keep LINK-095's
`uw_0077a797` destructor-binding prerequisite open.

The batch path/register/queue audit finds no active old-path consumer. Strict
preparation passes 202/202 rows in the five pending changed providers, plus the
affected assignment provider's row. The outgoing link audit is INCONCLUSIVE:
the index predates the base and `Common/0CreateAHeroManager21FE49.cpp` lacks a
current consumer receipt. Carry that consumer and the changed providers into
the next scheduled census; no measured linking gain or full consumer closure
is claimed. [Scoped evidence and remaining donors](../../reverse/attempt_support/terraintypes-consolidation-20261029-codex3.md).

2026-11-04: the assignment's private STL declarations and VC7.1 C1001 are resolved ([repair evidence](../../reverse/attempt_support/terraintypes-stl-reconcile-20261104-codexb4.md)); supported consolidation removes its donor file, preserving 31/31 rows and local LINKS. Next reconcile TerrainType's vector-base destructor; LINK-095 remains. [Merge and audit evidence](../../reverse/attempt_support/terraintypes-assignment-merge-20261104-codexb4.md).

2026-11-04: the seed now shares the destructor donor's inline scalar-vector cleanup; 31/31 rows pass and preview retains LINKS. Composition still accepts no donor; next resolve canonical vector/storage adoption without assuming element identity. LINK-095 remains; carry the inconclusive 0CreateAHeroManager21FE49 consumer audit into the next census. [Evidence](../../reverse/attempt_support/terrain-scalar-cleanup-20261104-codexb5.md).
