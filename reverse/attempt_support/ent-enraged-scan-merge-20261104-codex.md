# EntEnragedUpdate scan consolidation

Inspected base: `5bb3050edd` (2026-11-04). The approved destination is
`Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`; its provisional TU name
remains provisional. No donor source path is claimed as a retail path.

The canonical PartitionFilter adoption (`ce228d0701`) and shared EntEnragedUpdate
view (`d1b3e37cb1`) now permit the scan merge that the 2026-11-03 handoff blocked.
The current scan donor includes PartitionFilter.h and has no private base copy.
No gate changes or preprocessor workarounds were needed.

`name_lane.py consolidate --under Code/GameEngine/Source/Common/` refreshed the
original-path/evidence catalogue. `tu_skeleton.py --merge ... --dry-run` accepted
the seed and scan donor; the applied merge reused that verified composition.
It deletes EntEnragedUpdateScan.cpp, repoints 11 functions.csv source entries
(including the preexisting ICF-folded destructor and its fold-proof path), and
repoints 10 tu_map.csv source cells. TU assignments and evidence were not
regenerated or changed. The final unit contains 26 ledger rows, including the
existing fold. Source-file count falls by one; no new matched bytes are claimed.

Verification:

- `./build.sh Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`: 26/26 exact;
  three string literals and one float literal verified.
- Frozen-source check: all defined functions already matched.
- `class_gate.py --staged`: passes; `tu_ownership.py --staged --shadow`: clean.
- `check_csv.py`: passes, with 99,450 function rows unchanged in count.
- `data_check.py --staged`: zero findings.
- `eh_verify.py`: all five parent EH graphs EXACT, no missing objects.
- Published-index link preview (census 2026-11-04 17:56 at `8c757ea0db`):
  destination LINKS, 524 -> 866 authored bytes; the extra bytes already belonged
  to the absorbed donor. This is a preview, not a census gain.

Consolidation audit, covering the sole source move in this batch:

- No donor keys exist in code-identity, data-check, hatch, header or MS-header
  registers. The seed's existing ModuleData header-queue entry remains pending;
  no debt key was retired. Its data-ledger globals already belong to the seed.
- Combined path/basename search across tools, hooks, workflows, Code, build.sh,
  doxygen configuration and reverse registers found no active tooling or include
  consumer needing a path update. Remaining old-path mentions are the merge's
  provenance comment, historical attempt evidence and the published census's
  link_status.csv; these intentionally preserve history.
- Source bodies compile and EH-bind at the destination. Core row/fold-proof
  ownership follows the merger; no alias, pin or hatch was removed or added.

Remaining donors retain their earlier prerequisites: the deleting-dtor donor
requires a compatible EmitVtableTag constructor, the update donor needs Object
view reconciliation (getControllingPlayer/m_pos), and the module-data destructor
fails the composed byte check. Their files remain separate. Next work should
reconcile those views in separately verified commits before another merge.
Full consumer verification and scheduled census confirmation remain separate
from the clean destination preview.

The stricter `link_check.py --refresh --current-ledger` was inconclusive:
13,771 unrelated current-ledger objects lack current compiler evidence in this
checkout. No clean all-current-provider result or full consumer clearance is
claimed; carry this batch into the next scheduled census. The publication hook
runs the affected-consumer audit on the outgoing batch.

Scoped naming covered the two complete scan functions: four local renames
(obj -> ownerObject and md -> enragedData in each), with the uncertain third
filter and the clear alive filter retained. The parent reviewed all six
inventoried bindings; enragedData avoids the moduleData macro in an included
header. Constructor-style locals same, allies and player were omitted by the
regex inventory and remain unchanged. Application verified all 26 rows again.
