# QueueProductionExitUpdate header debt and consolidation handoff

Inspected base: `785e1bf93f`. No translation-unit merge or source-path move was applied.

The TU now includes the canonical `ExperienceTracker.h` instead of its private
eight-byte declaration. Its only use is the out-of-line `isTrainable()` call;
it accesses no tracker fields and does not construct a tracker. The canonical
header supplies the existing member spelling without a new layout assumption.
`header_adopt_lane.py accept` passes and retires that source's ExperienceTracker
queue row. The notifyProductionBurstFinished donor already included canonical
`Player.h`; its separate acceptance passes and retires the stale Player row.
Neither retirement was made by hand. No shared header changed.

Validation:

- Normal source builds before and after: 9/9 matched rows, including the
  renumbered unwind label verified through its parent's EH data.
- Frozen-file check with `--fail`: passes after the change; its four existing
  unmatched markers are retained.
- `class_cleanup.runtime_graph` / `same_runtime`: all 566 non-debug sections,
  558 external definitions, relocations, weak bindings and COMDAT policies
  unchanged (see runtime-proof.json). No provider or alias was removed.
- Both header acceptance commands pass their structural, byte and link checks.
- Final two-unit link preview: both LINKS, 502 -> 502 bytes, against census
  index 8661f15284 (2026-11-03 20:03). This is a preview, with no new census,
  full-image or runtime claim.
- `check_csv.py` and `git diff --check`: pass. No data/identity/flag-override
  register keys or Microsoft-header queue entries name this target family.
  Remaining header queue entries remain with their existing owners.

The supported planner snapshot under build/consolidation covered
`Code/GameEngine/Source/GameLogic/Object/` and passed `consolidate --check`
before the trial. Its evidence was selection context, not TU approval.
`tu_skeleton.py` rebuilt the stale committed map in memory and planned 24
approved rows from eight files, plus the mixed ModuleNameGetters3.cpp.
The supported merge dry run accepted no donors, made no source/ledger changes,
and preserved all eight census-linked input units.

Remaining merge prerequisites (see the dry-run and tu_views logs):

- Coord3D/Xfer declarations collide with the seed's include environment.
- The destructor's BitFlags template parameter and constructor's explicit
  vtable declarations disagree with that environment.
- Object's query-rally view places a field at +0x38 under bases ending at +0x48.
- QueueProductionExitUpdate views disagree on their base clauses; the notify
  donor represents the adjusted interface receiver, while other views use
  UpdateModule with or without ExitInterface. These require ABI reconciliation,
  not a mechanical union of members.

Next: reconcile those views in separately verified donor changes before retrying
the merge. The completed ExperienceTracker adoption does not resolve those
independent conflicts. No alias/pin/hatch was added or removed. Current coverage
and source ownership are unchanged; header queue debt falls by two entries.
