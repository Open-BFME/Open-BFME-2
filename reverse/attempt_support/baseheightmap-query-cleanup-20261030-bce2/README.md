# BaseHeightMap query cleanup and consolidation prerequisite

Inspected base: b657c77a8b81. Source:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp`.

## Bounded cleanup

The seed carried an unrowed `Rva00069AF5Host::rva000670B8` implementation and
a present-unmatched exemption. Its only source occurrences are its declaration,
definition and exemption; no ledger row or pin names it and no active source
calls it. The complete native 0x000670B8 range is already owned by the matched
250-byte `BaseHeightMapRenderObjClass::getMaxCellHeight` in
BaseHeightMapCellQueries.cpp. This is cleanup of an existing alternate view,
not a lost-row repair or a new match. No original class identity is inferred
from the address-derived name.

Remove that unused declaration, 242-byte compiled implementation and exemption.
The counter owner's `hatch_counters.py --update` retires exactly one key:
present_unmatched 3660 -> 3659. The existing used x87 Sqrt helper and its
exemption remain unchanged. No source path, row, pin, class header or compiler
flag changes; no other register entry is retired.

Before editing, the declared-unmatched check passes all 42 claimed files.
Their normal build passes 132/132 rows, 14 strings plus two empty references,
152 float literals and 28 named imports. After cleanup, the complete seed and
the existing query owner pass 30/30 rows, all 64 normalized bindings are
identical, and all three EH graphs are EXACT. Every retained external COMDAT
fingerprint/verdict is identical. Only the unused method and its three
now-unused literal COMDATs leave the seed object; undefined references and
weak aliases are unchanged. The existing query-owner object is identical.
Strict current preparation passes both files. The query owner retains LINKS
for 939 authored bytes against the published index at 6fe1089c24.

## Consolidation remains blocked

The supported planner and class-view dry run are read-only. The current-input
map approves 186 rows; 132 rows are in the 42 complete files, and 13 mixed
files stay separate. The merge dry run stops before composition: its census
link guard cannot find the census-linked BaseHeightMap.cpp seed in the index.
The fetched release index identifies 6fe1089c24; the missing-source diagnostic
identifies embedded census 8716fcf38f. No donor is accepted and no move is
applied. A current census object for the seed is required before retrying the
merge. Class-view conflicts (including StringClass inline destruction,
RenderStateStruct fields, BaseHeightMap views and the WWMath kernel) remain
separate prerequisites. An approved row does not prove those views compose.
The measured elapsed time and blocker are recorded through re_log.py.

## Publication limits

The correctly based outgoing audit (b657c77a8b81 to the staged cleanup tree)
is INCONCLUSIVE: the index predates the base and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Full consumer
selection/loss checks and a seed LINKS prediction remain unverified. Carry
the removed provider and literals, existing query owner and affected consumers
into the next scheduled census. No census-linked, new exact-byte or source-file
reduction is claimed. The initial audit against moving origin/master also
included unrelated upstream changes; it is not the publication verdict.
