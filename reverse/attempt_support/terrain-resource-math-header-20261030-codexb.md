# Terrain resource math header cleanup

Base: `89295774ff`. Scope:
`Code/GameEngine/Source/GameLogic/System/TerrainResourceManager.cpp`.

Replace the local `static floorf` prototype with the existing project pattern
that gives `math.h`'s inline float adapters internal linkage. A push/pop macro
scope restores any incoming definition of `inline`. The compiler flags and
function/data ledgers remain unchanged. The owning Microsoft-header scanner's
scoped `refresh_queue` removes exactly this source's one `floorf:same` queue
record; its analysis is clean.

Verification:

- `./build.sh` verifies all 23 rows, one string literal, 21 compiler float
  literals and six named imports.
- `find_declared_unmatched.py` passes before and after the edit.
- `eh_verify.py` reports four EXACT graphs before and after, zero baseline
  exceptions. Both naturally renumbered funclet rows remain verified through
  their parent EH graphs.
- All 47 retained external COMDAT byte-and-relocation digests and sizes are
  unchanged. Three 18-byte COMDATs cease to be external providers:
  `?ceil@@YAMM@Z`, `?floor@@YAMM@Z` and `_ceilf`. The 18 exclusive definitions,
  27 undefined externals and one weak external are unchanged.
- Strict current provider preparation passes. Both the census-only and current
  ordinary previews report LINKS, 2,547 -> 2,547 authored bytes, against the
  index dated 2026-10-30 10:11 at `12b9e7a7c0`.
- `check_csv.py` passes.

The removed adapters keep their selected providers in a scoped overlay of
that index: `DumbProjectileBehavior.cpp` for the float `ceil` overload and
`_ceilf` (verdict unknown), and `TerrainLogicAmbientColorRva0027DA6A.cpp` for
the float `floor` overload (verdict ok). This proves no selected-provider
change in that overlay; it is not a current census result.

The outgoing batch audit is INCONCLUSIVE: the index predates the outgoing
base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this provider and that consumer into the next scheduled census.
The ordinary preview and retained object facts establish the scoped cleanup
only. No measured linking or image-ownership gain is claimed.

Publication rebased onto `b4c2cc394c`; the only conflict was the obstacle
register's concurrent appended entries, both retained. Neither inspected
source changed upstream. `check_csv.py` and the combined terrain/restored
initializer build pass again (54/54 rows, one data row). The older-index
batch-audit limitation above remains for the scheduled census.
