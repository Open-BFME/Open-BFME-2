# AISpecialPowerSelfBuff: no independent TU anchor

Served item: `bfme2/next-work-003.log`, proposed TU `Code/GameEngine/Source/GameLogic/SkirmishAI/AISpecialPowers/AISpecialPowerSelfBuff.cpp`. The destination file does not exist. The actual 334-byte body at RVA `0x005DA37A` remains in mixed `AISpecialPowerPickers.cpp`.

No production file, ledger, name record, claim, Git index, gate or generated TU map was modified. All evidence collection was read-only, apart from ignored diagnostic reports/caches.

## Current native result

`tools/tu_skeleton.py --plan <served TU>` lists four *already approved* P-group EH companions at RVAs `0x007A2A1D`, `0x007A2A25`, `0x007A2A2D`, `0x007A2A35`, totaling 34 existing bytes. It does not list the parent as approved. Those companions do not satisfy the selected item's pass condition for its one proposed parent row.

The committed map's parent evidence is solely `N=<served TU>`, confidence `proposed`. The planner rebuilds stale inputs internally; its fresh plan still approves only those companions. No map output was written or staged.

## Evidence checked

* The existing real spelling `AISpecialPowerSelfBuff::shouldActivate` already came from a WorldBuilder callgraph lead in the ledger notes. It is not an unrenamed placeholder that a simple naming change would repair.
* `tools/wb_show.py 0x005DA37A` confirms WB body `0x0159CAD0`, size739, callgraph score5 and the EA diagnostic path `C:\Projects\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AISpecialPowers\AISpecialPowerInstances\AISpecialPowerSelfBuff.cpp`, assertion line59. This is a WB fact, not a retail file assertion. The served N path also lacks the `AISpecialPowerInstances` directory.
* Current `tools/name_evidence.py --kinds wb` emits no naming candidate for the existing SelfBuff spelling or for the related placeholder constructor class `Rva005DA353`.
* The related native constructor at `0x005DA341` and destructor at `0x005DA353` have WB matches, but both WB bodies are unnamed and score1. They provide no independently canonical SelfBuff class name or file anchor.
* No Zero Hour definition of this BFME2-specific class was found. The selected parent has no entry in current retail string-xrefs naming a `.cpp`, export-name anchor, module-factory class-name entry or direct canonical name-basis record that would establish a retail TU.
* The required `name_lane.py consolidate --under .../AISpecialPowers/` survey covers16 sources and reports SelfBuff's current placement unresolved in `AISpecialPowerPickers.cpp`; the file has72 rows and is mixed/incomplete, with no verified merge. The survey's source packet is under ignored `build/consolidation/files.jsonl`.
* Native `find_declared_unmatched.py AISpecialPowerPickers.cpp` reports all defined functions already matched. No missing body was found to reconstruct in this file from this task.

## Why no rename/move is proposed

WorldBuilder may corroborate an independent naming/TU hint; the same lead that supplied the current name must not be recycled as independent approval. A WB diagnostic path alone also does not authorize changing the retail destination by hand. Rewriting the candidate path, renaming a placeholder constructor only to create a second N vote, or treating P-group EH rows as new independent body anchors would not supply the missing evidence.

The constructor's vtable and the existing override are useful leads for a later proper class-identity reconciliation, but no canonical constructor name was established here. That work needs its normal native naming evidence/agreement and coordinated actual source claims, not a provisional-approval shortcut.

Recommendation: record the parent as blocked for lack of an independent F/Z/S/W anchor, with this handoff, and continue the native picker. Revisit if fresh retail `.cpp` xrefs, independently proven same-TU names, or an approved class-identity reconstruction supplies new evidence. Do not regenerate/commit `reverse/tu_map.csv` from this lane.

Diagnostic files: `selfbuff-native-plan.log`, `selfbuff-wb-show.log`, `selfbuff-ctor-wb.log`, `selfbuff-dtor-wb.log`, `selfbuff-consolidation.log`, `selfbuff-name-evidence.log`, `selfbuff-file-unmatched.log`. Name candidates are in ignored `build/codex-thing-agent-20261120/selfbuff-wb-name-evidence.tsv`.

Result: zero completed served items, zero new bytes, no source changes, no runtime or full-image link test.
