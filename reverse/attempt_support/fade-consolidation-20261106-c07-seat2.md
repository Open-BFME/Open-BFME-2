> Recovery publication: historical investigation from 7e7a107cce89. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# FadeInTextRender consolidation: selected destructor blocks composition

2026-11-06, chat 07 seat 2; base `f15737ff46b`; owner `codex-fleet-20261106-c07-seat2`.

## Target facts and attempted work

Picker `python3 tools/next_work.py --claim --shard 19/30` served the approved
`Code/GameEngine/Source/Common/FadeInTextRender.cpp` TU and the draw donor
`Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/rva00596908Rva00596908Farm.cpp`.
Both files passed `tools/find_declared_unmatched.py`. `tools/check_csv.py` passed
99,515 function rows, 9,320 symbols and 2,272 data rows.

`tools/tu_skeleton.py --plan` re-derived 17 approved rows. Only the draw donor
is movable: draw 0x00596908 (481B), unwind 0x0079D34D (8B), handler 0x0079D355
(10B). Rva0059675ADtor.cpp remains refused because one row is unapproved.
No row, TU assignment or source was edited.

The required `tools/name_lane.py consolidate --under Code/GameEngine/Source/Common/`
planner completed with 7,135 selected source files and 735 groups. Its Fade packet
suggested the alternative GameClient/GUI path with incomplete-routing, include,
internal-linkage and compiler-setting prerequisites; those hints approve no move.
The planner used system Python and reported capstone unavailable, so its owner-level
image references are unverified. Existing live TU approval, independently re-derived
by tu_skeleton, controlled the attempted destination.

With supported runtime PATH, BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb, BUILD_POOL=1,
and the shared verification_slot.py wrapper, ran:

```
python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/FadeInTextRender.cpp --dry-run
```

Exit 2, accepted `[]`. Sole donor rejected:

```
link: .../rva00596908Rva00596908Farm.cpp links at the census;
the merged object would not: selected ??_GRva0059675ABase@@UAEPAXI@Z
blocked: no verified merge of two or more donors
```

This is a supported link guard refusal, not established false rejection.
The private base destructor is declaration-only in the constructor/draw views;
its dedicated destructor source defines it. That is a structural lead, not a
proven repair. Next inspect selected deleting-destructor identity and emitted
copies/flags, reconcile the provider in its own byte-verified commit, then retry
the merge. Do not bypass the guard or move the unapproved destructor row.

## Verification limits and audit gaps

No merge applied, no source files removed, no debt retired, no linked bytes gained.
No after-image, current whole-link, menu/skirmish/save-load or CRC comparison ran.
No outgoing path move exists to audit. Existing constructor/draw flags differ;
private-view, include-resolution, selected-COMDAT/provider/consumer and header-queue
checks remain prerequisites for a future successful move. The dry-run uses dated
census evidence, not runtime proof; broad current consumer verification remains
unmeasured. Prior shared-index consumer gaps must carry into the next census.
