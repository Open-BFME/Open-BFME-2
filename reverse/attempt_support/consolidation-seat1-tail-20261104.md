# Consolidation shard 1 continuation handoff (2026-11-04)

Only allocated BFME 2 mechanical consolidation was in scope. These candidates
passed their allocation checks; the current narrow planner snapshots passed
`name_lane.py consolidate --check` before plans and trials. No merge or split
from this continuation was retained except the inherited PlayerAITypeSet commit
already described in `consolidation-playeraitypeset-20261104.md`.

## Candidates inspected

- `ArmyPlacer.cpp`: the tool-applied merge built and all 27/27 rows passed
  `find_declared_unmatched.py`. Staged `tu_ownership.py --shadow` rejected the
  moved fold row `0x0007FAB3`: approved TU is
  `Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp`, while
  the merged source is `Code/GameEngine/Source/GameLogic/System/ArmyPlacer.cpp`.
  Restored only this trial and released its 35 acquired claims. Do not retry
  without reconciling the approved assignment/path-keyed identity accounting.
- `MultiplayerSettings.cpp`: 47 approved rows, three donors, two mixed files;
  no donor accepted. Two donors fail `_STL::allocator<_Tp>::allocate` matching
  (`C2244`); `stlport_rb_tree_int_colormap.cpp` fails bytes. The
  `MultiplayerColorMapOperator.cpp` split carves `0x003812E6` but the residual
  loses rows; other candidates have no matching definition spelling. The
  `stlport_construct_stl_types2.cpp` candidate `0x00380E07` has no definition
  spelling. LinkGuard reports the involved sources census-linked.
- `AptMpChat.cpp`: the only donor fails `C2511`; its constructor
  `Rva0057FE6B(TargetRef00217D4C*, int, bool)` is absent from the target view.
  `tu_views.py` reconciliation is the stated next prerequisite. Both sources
  are census-linked.
- `GameSorter.cpp`: the comparison donor fails `C2511` because the target view
  lacks `Rva000795C1Record(void*, unsigned int)`; reconciliation is required.
  No merge accepted. The four mixed splits were inspected: FXParticleSystem's
  row has no definition spelling; LinearInsert carves `0x00580776` but its
  residual no longer compiles (`unguardedLinearInsert` undeclared); SiftHeap
  carves `0x005807CE` but target compilation lacks
  `Rva000795C1Record::compareRva005803C0`; Sort carves two rows but combined
  compilation redefines `_STL::allocator` and `_STL::vector`. Do not split
  without a merge it enables.
- `ModelConditionSpecialAbilityUpdate.cpp`: the only ordinary donor fails
  bytes; the mixed `ModuleUpdateDtors.cpp` has no row approved for this TU, so
  no split is available. LinkGuard reports the target and donor census-linked.

The preceding inspections of EmotionNugget, ChatWindowsLan and AITactic are
in the session's earlier trial handoff. The remaining allocated candidates in
the full shard listing already have recorded prerequisite/blocker evidence;
there was no clean mechanical composition available in this reassessment.

Additional current-shard trials and their exact prerequisites are recorded in
`consolidation-seat1-continuation-20261104.md`.
