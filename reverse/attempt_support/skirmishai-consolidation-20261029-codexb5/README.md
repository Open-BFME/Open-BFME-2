# SkirmishAI consolidation probe

Base: `1c16abe8f6` (2026-10-29). The default picker claimed the destination
`Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAI.cpp` and six whole-file
donors. The scoped naming planner reported 24 groups and no missing inputs; its
snapshot is local build evidence, not TU approval. The picker reported 28 donor
rows and five mixed files that remain outside this merge.

`tu_views.py` applied byte-verified private-view reconciliations for PlayerList,
Rva002A8F24 and Rva002A8AB1Record, but its own merge dry run accepted zero
of six donors both before and after those changes. The trial changes were
restored. No rows or paths moved and no linking improvement is claimed.

The remaining compile boundaries in that probe were:

- `Rva002C6E4EDtor.cpp`: `_Rb_tree` explicit specialization after instantiation;
  the AIBuilder layouts also overlap incompatibly in the automatic view plan.
- `Rva002C6EA4Method.cpp`: duplicate `_Rb_tree_iterator` operator template.
- `SkirmishAI_isAPartialBrain.cpp`: the destination's SkirmishAI class lacks the
  `isAPartialBrain` declaration.
- `SkirmishAI_resetMaster.cpp` and `SkirmishAI_updatePhase.cpp`: their member
  spellings differ from the destination's fields at corresponding offsets.
- `Rva002A8AB1RecordGet.cpp`: the destination's Player view lacks the donor's
  `m_164` member spelling.

The automatic Player reconciliation failed to compile its donor because the
proposed base and a by-value member were undefined. Automatic SkirmishAI
reconciliation refused a token rename because `m_178` also names a member of
Rva002A8AB1Record. Next investigate those views with explicit type and field
ownership, then verify each donor and its object bindings before repeating the
supported merge probe. The earlier declaration-only trial is not evidence of a
successful composition or consumer-wide link closure.
