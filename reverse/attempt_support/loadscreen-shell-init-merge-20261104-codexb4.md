# LoadScreen shell-init consolidation, 2026-11-04

Base: `91a4f16d0e70189ad6de4dc1fea7200824d17b0a`.

Prerequisite `5e7535d0ed` adopted the canonical ImageCollection header in the
donor. Its five rows byte-matched, and `header_adopt_lane.py accept` retired
the ImageCollection queue row. The initial merge was refused by class_gate;
no merge commit preceded this prerequisite. The planner and merge checks were
then rerun against the adopted header.

`tools/name_lane.py consolidate --under Code/GameEngine/Source/GameClient/GUI/`
catalogued the original-path evidence and alternatives. Its LoadScreen packet
flagged private declarations, compiler context and path-keyed registers; it
approved no placement. `tu_skeleton.py` rebuilt its stale TU-map inputs in
memory and admitted only approved rows.

`tu_views.py` applied no changes. A fresh merge dry run accepted the existing
TU and `LoadScreen_ShellGameInit.cpp`; application reused that verified plan.
The donor's five rows (init at 0x00356541 and four EH rows) now reside in the
approved `Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp`. One source file
is removed, with no added rows or recovered-byte claim.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp`: 17/17
  matched; five string literals, two imports and the renumbered EH labels
  verified.
- `find_declared_unmatched.py` before and after: all defined functions already
  matched; the existing counted destructor marker remains unchanged.
- `check_csv.py`: OK, 99,449 function rows, 9,331 symbols, 2,268 data rows.
- Merge LinkGuard accepted the composition against census-linked inputs,
  including provider/consumer bindings and selected COMDAT checks.
- `link_check.py --staged`: one of one link cleanly; the combined TU owns
  1,046 bytes. Its comparison is against the 2026-11-04 12:23 census at
  `40fe1783d7`. This is a prediction, not a new census or headline gain.
- `git diff --cached --check`: passed.

Batch path/debt audit (the only pending source-path change):

- The five ledger and TU-map source cells were repointed; the committed map
  changes only those source cells, not regenerated assignments.
- The static `firstLoad` data owner at 0x009BFAA4 follows the code through
  `data_ledger.csv`. No data/identity baseline keys were removed or added.
- The remaining Rva00355D66 header-queue row was transferred through the
  merge tool, not retired. ImageCollection was retired by its owner workflow
  in the prerequisite commit. The merge tool's Microsoft-header refresh
  left no affected queue entries. Hatch counters were refreshed by the owning
  tool and produced no changes. No pins or alternatename aliases were removed.
- Searched the removed basename across tools, hooks, workflows, game includes,
  build/configuration files, ledgers, registers and documentation. No active
  path consumer needs an edit. Remaining references are the TU's provenance
  comment, the historical census in `link_status.csv`, GlobalData's frozen
  field-provenance contract and historical attempt/log evidence. These retain
  their original paths intentionally.
- Fresh scoped packet `loadscreen-codexb4-20261104` inventoried the complete
  init function. A native child proposed retaining all four clear/donor names
  (`game`, `firstLoad`, `win`, `showTime`); the parent scanned the whole mapping
  and applied the reviewed batch: zero renames, four explicitly retained, no
  coverage warnings.

Remaining donors were not edited:

- `Rva003560EDDtor.cpp`: merged declaration ordering loses Display before
  `TheDisplay`; private Rva003560ED views also disagree on the string members.
- `Rva003561BEDtor.cpp`: merged declaration ordering loses AudioManager before
  `TheAudio`; Display and Rva0036CA00Str canonical adoption remain prerequisites.
- `LoadScreen_MapTransferProcessProgress.cpp`: its one-argument
  `winCreateFromScript` call disagrees with the canonical three-argument
  GameWindowManager declaration. Reconcile the donor through the header lane
  and verify its rows independently before retrying the merge.

The two mixed donors remain satellites. No existing obstacle family is declared
cleared by this consolidation.

Publication accounting: the runner rebased the prerequisite and merge to
`5614b976b6` and `830bc73f09`. The batch's final-state debt gate then refused
the vanished donor's ImageCollection retirement despite its earlier acceptance.
`header_adopt_lane.py accept --class ImageCollection
Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp` also passes on the final TU.
A follow-up commit supplies the documented per-key `Debt-Retired` explanation
for this vanished-source case; neither existing commit was manually rewritten,
and no register key or verifier code is changed by that accounting.
