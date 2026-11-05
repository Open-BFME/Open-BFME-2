# QueueProductionExitUpdate destructor merge audit

Prerequisite: `0a4c729003` (canonical seed headers). Audit base:
`e2c4e36c9b1043327d36a4cc9c25ff6abe5ecdb1` (`origin/master` when audited).
The complete pending path batch also contains RenderObjCtor.cpp into
rendobj.cpp and AiOrdersManagerPatrol.cpp into AiOrdersManager.cpp, covered by
their existing handoffs and the combined path audit below.

`tu_skeleton.py --merge` absorbed QueueProductionExitUpdateDtor.cpp into its
approved QueueProductionExitUpdate.cpp TU. Its destructor and compiler-generated
deleting destructor move together; the latter remains an inline/compiler
companion rather than receiving a new TU approval. The tool changes only two
ledger source columns and two TU-map source columns. It does not regenerate the
map. [Merge receipt and remaining donor diagnostics](queueproduction-dtor-merge-20261105.txt).

The final source also removes the old absent-from-retail emission anchor:
the merged destructor now emits the vftable and its inline isExitBusy provider.
The constructor consumer still resolves that table. C++ literals replace local
TRUE/FALSE/NULL definitions, and the owning Microsoft-header scanner refreshes
the queue back to zero findings for this source.

Final verification:

- `./build.sh <TU>`: 11/11 rows exact, including the renamed funclet at
  `0x0078DABF`; string, float and import checks pass.
- `find_declared_unmatched.py <TU>`: all definitions accounted for, with the
  three pre-existing present-unmatched bodies retained. `class_gate.py` passes.
- `check_csv.py`: pass, 99,474 function rows after the publisher's upstream
  refresh. This merge adds no row.
- Composition LinkGuard preserves the seed/destructor scope. Final current
  object previews: merged TU LINKS 265 bytes (205 + 60 before), constructor
  LINKS 106 bytes. Index `c95fcfcfcd`, census `2026-11-05 05:17`.
  The per-TU increase is moved ownership, with no predicted aggregate increase.

Debt/ownership audit: no donor keys exist in the code-identity baseline,
data-debt baseline, header queue or flag overrides. The three existing seed
present-unmatched hatch keys remain unchanged; no alias or pin is removed.
The merge tool refreshes Microsoft-header state and transfers any header keys;
neither queue has a remaining donor source. Active ledger/map ownership and fold
proofs have no removed donor reference. The old filename in one ledger notes
field is historical explanation, not an owner binding.

Tooling compatibility audit, complete pending path batch: searched the three
removed basenames across tools, hooks, workflows, Code, docs, source registers,
and build/configuration formats (including relative paths). No active include,
tool input, build list or directory-derived consumer requires a change.
Remaining hits are historical census link_status rows, attempt evidence,
source-provenance comments, and a synthetic RenderObjCtor test fixture. Those
are intentionally retained. The existing RenderObj and AiOrders handoffs also
record their scoped byte/link and register checks.

Result: one fewer Code source file, all 11 rows retained. Six Queue donor files
still require Object/Xfer-view or constructor-vftable reconciliation, as the
receipt records. This is source recovery with preview verification; real-link,
affected-consumer closure and census confirmation remain with the outgoing
audit and next census, including the pending mapper limitations already recorded
in LINK-289. No runtime/CRC result is claimed.
