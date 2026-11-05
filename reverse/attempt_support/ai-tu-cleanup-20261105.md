# AI TU cleanup and consolidation prerequisites, 2026-11-05

Inspected source revision: `ffb486dac9`. Worker: `yasinschroeder-codexb`.

## Consolidation trial

The default picker claimed `Code/GameEngine/Source/GameLogic/AI/ai.cpp`
and 26 potential donor files. The supported planner surveyed the AI directory:
329 sources, 48 groups, no statically clear group. Its original-path catalogue
records the WorldBuilder/Zero Hour spelling `AI.cpp`; the existing target path
is `ai.cpp`. These donor path facts do not authorize a case rename.
The committed TU map was stale; `tu_skeleton` rebuilt routing in memory.
No regenerated map was written or committed.

`python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/ai.cpp --dry-run`
returned exit 2: 163 approved rows, nine mixed sources, no accepted donor,
`no verified merge of two or more donors`. No source move was applied.

Most donor compositions fail with C2953/C2955: `StringBase` is defined twice,
including `reference/shims/bfme2_ascii/string_base.h`. Other specific diagnostics:

- `AIClosestObjectQueries.cpp` / `AIClosestEnemySearch.cpp`: `Coord3D`
  redefinition; `AIAreaEnemySearch.cpp` also redefines `PartitionManager`.
- `TAiDataXfer.cpp`: `Xfer` redefinition and missing `Xfer::Version`.
- `AIRva002FE712.cpp`: incompatible list iterator and MemoryPool call signature.
- `Rva0014C090ParseNamedDefinition_Rva002FE9FC.cpp`: `Gen0014AE40 *`
  cannot bind the `AISideBuildList *` parameter of `TAiData::addFactionBuildList`.
- `StlSweepR3Rva002FED53.cpp`: the link guard refuses the merged object because
  it breaks another unit's copy of `list<Rva002FED53PointerTarget *>::insert`.
  This is a merge failure; the original matched fragment still links.

Next work: reconcile the seed/donor string-header environment and canonical
header prerequisites in separate verified changes. Retest the STL fragment
only with evidence that its insert COMDAT and affected consumers are preserved.
Do not weaken the guard or delete a donor. No prior AI-specific entry was found
by path, constructor/data-helper names or the pointer-target symbol.

## Applied cleanup

Removed two repeated Matrix4x4/pool-glue macro blocks and their empty internal
comment blocks after `<list>`. Kept the initial definition and the definition
after the game headers. Removed the consecutive `optimize("s", off)`,
`optimize("t", on)`, `optimize("", on)` directives with no intervening code.
57 source lines disappear; three pragma escape-hatch occurrences disappear.
No function, data, pin, alias, TU path or ownership row changed.

The hatch baseline was refreshed through `hatch_counters.py --update`; only
this TU's three pragma counts are included in the change. Its unrelated stale
pin removal was excluded. Data/identity/header debts remain in their registers.

## Verification

- Baseline and changed source: `./build.sh Code/GameEngine/Source/GameLogic/AI/ai.cpp`
  passed, eight code rows (519 bytes) and one data row verified.
- `find_declared_unmatched.py` before/after: all defined functions already matched;
  the existing 16 marked unclaimed definitions are unchanged.
- `class_cleanup.runtime_graph` on the before/after objects is exactly equal:
  589 non-debug sections, 581 external definitions, zero weak defaults.
  This compares all runtime bytes, relocations/bindings, section characteristics,
  COMDAT selections/associations and external definitions. Object files differ in
  non-runtime metadata, so raw-file identity is not claimed.
- Both runtime graph SHA-256 values (sorted-key JSON):
  `e57d86486ab91972aa496ed08a0a96db154a3e30e21ac93e7a4da612d0869e94`.
- `link_check.py` reports LINKS, 519 -> 519 bytes, using the census index from
  2026-11-05 15:52 at `112a456a2c`. This is a local prediction, not a new census.

No path consumers need repointing: the failed trial moved/deleted nothing.
No link gain, source-file reduction or real-game smoke result is claimed.
