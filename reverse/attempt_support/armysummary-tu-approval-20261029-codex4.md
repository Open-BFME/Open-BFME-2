# ArmySummary TU approval inspection, 2026-10-29

Base: `4148355b12` (picker tuning snapshot `8716fcf38f`). Selected by `next_work.py --claim` (TU approval,
50 proposed rows in 29 files); file claim released after inspection.
No source, row, name, TU assignment or register was changed.

`check_csv.py` passes (99,007 function rows); the seed's
`find_declared_unmatched.py` reports all definitions matched. The required
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/System/`
packet was generated against current inputs. Its ArmySummary packet flags
incomplete routing, differing compiler contexts, duplicate private views and
quoted includes. Its old-map annotations are hints; the following counts use
`tu_skeleton.map_rows()` and its current-input in-memory rebuild instead.

| Proposed destination | Main code | Approved funclets |
| --- | --- | --- |
| GameLogic/System/ArmySummary.cpp | N 16, K 4, C 30 | P 52 |
| Common/ArmySummaryEntry.cpp | N 12, U 10, C 15 | P 4 |
| WWLib/ArmySummary.cpp | N 5, U 2, C 2 | P 16 |

The selected destination also has three proposed data rows. The Common and
WWLib destinations have five and zero proposed data rows, respectively.
`tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/System/ArmySummary.cpp`
therefore lists 52 approved P rows, six whole donors and three mixed sources,
without approving their parent code rows. This does not authorize moving a
whole donor whose main code remains proposed.

Target facts: the current ledger names the constructor at 0x0040E3EE in
Common/ArmySummaryEntry.cpp, the destructor at 0x0040E499 in the selected seed,
and GetEntries at 0x0040E88B in WWLib/ArmySummary_GetEntries.cpp. N derives
from the source directory and class name, so these are competing hints rather
than three established retail units. The 0x0040E493 getter returns ArmySummary;
this establishes class identity, not an original source path.

Donor facts: WB pairs such as HasDelayedCarryoverUnitOfTypes 0x0040CC3C,
RemoveEntry 0x0040DD3A, and GetEntries 0x0040E88B cite the editor's
GameLogic/System/ArmySummary.cpp. These named rows were themselves recovered
using WB. `tu_map.wb_self` intentionally refuses to let that same pairing
corroborate its own naming hint. No independent F/Z/S/L anchor was found.

Remaining prerequisite: obtain an independent target TU anchor, or a properly
supported naming/placement repair that resolves the interleaved hints. Then
rebuild the map in memory and require approval of the parent bodies before a
merge trial. Do not remove the WB provenance, turn a getter into filename
proof, move proposed rows or commit a regenerated map to force approval.
The selected pass test is still open. No TU-approved, source-file, debt,
matched-byte, link or ownership improvement is claimed. t=10 model=gpt-6.1-sol.
