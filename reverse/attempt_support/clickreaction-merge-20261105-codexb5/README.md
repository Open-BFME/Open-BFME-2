# ClickReactionBehavior supported merge, 2026-11-05

Parent: `6ec7cfa0e8` (shared interface prerequisite). LINK-238 composition
clearance is scoped to the two accepted units; complete retail vtable recovery
remains outside this change.

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Behavior/`
was regenerated immediately before `tu_skeleton.py --merge`. The supported
merge accepted ClickReactionBehavior.cpp and ClickReactionBehaviorCtorThunk.cpp,
rejected none, and preserved both census-linked units through its link guard.
It moved the constructor and its two EH rows into their approved TU, in retail
order. Source files decrease by one; all 11 matched rows remain. The two mixed
sources (Rva0024A797Grandchildren.cpp and BehaviorModuleDataBuildFieldParse.cpp)
remain outside this batch. No TU assignments or approvals changed.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehavior.cpp`:
  11/11 exact, strings/imports/float references pass. Renumbered unwind labels
  resolve through their exact parent EH graphs.
- `eh_verify.py`: EXACT 2/2 parent graphs. `find_declared_unmatched.py`: all
  defined functions matched. `check_csv.py`: OK, 99469 function rows.
- `link_check.py`: merged TU LINKS, 728 bytes, preserving the original 616+112
  census-linked bytes (index 2026-11-05 05:17 at c95fcfcfcd). This is a preview,
  not a new census. The merge link guard also checks selected providers and
  COMDAT losses in the affected census-linked scope.
- [COFF symbol comparison](symbol-delta.json): union of original two-unit
  definitions and external requirements equals the merged object's. Every
  alias mapping, including the three donor link-wide aliases, is retained.
- `data_check.py`: the same three pre-existing shadow findings (DRAWABLE_FRAMES_PER_FLASH
  duplicate/wrong name and module-name compiler guard spelling). No new finding
  or debt retirement. No data/identity baseline keys name these units.
- Supported register transfer moves all three hatch keys, retaining their
  counts; no baseline debt is dropped. Header queue transfer and Microsoft-header
  rescan ran through tu_skeleton.refresh_reports; neither queue changed and
  neither contains these units.

Tooling compatibility audit for the entire pending path-change batch:
ClickReactionBehaviorCtorThunk.cpp -> ClickReactionBehavior.cpp (only move),
including the published prerequisite stacked above origin/master. Reviewed
`git diff --name-status --find-renames origin/master`, combined full-path and
basename searches across tools, hooks, workflows, Code includes, root/config
files, docs and reverse registers. No active tooling/build/include consumer
needs the donor path. Functions and TU-map source columns now name the approved
owner; hatch keys transferred. Remaining donor mentions are the TU provenance
comment, historical link_status.csv census, a blocked name_agreed.csv explanation,
and old attempt/runtime-vtable-survey evidence; these are retained as history.
Header/data/identity queues have no old-path keys. No tooling consumer changed.
The interface remains partial as documented by the prerequisite: this merge
claims source-file consolidation, not complete interface recovery or runtime
smoke success.
