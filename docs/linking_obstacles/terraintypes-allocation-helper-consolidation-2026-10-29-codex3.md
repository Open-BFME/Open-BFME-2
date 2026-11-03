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
