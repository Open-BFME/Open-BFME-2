# OathbreakersFadeAwayBehavior constructor consolidation, 2026-11-05

Scope: `Code/GameEngine/Source/Common/OathbreakersFadeAwayBehavior.cpp` absorbs
`Code/GameEngine/Source/GameLogic/Object/Behavior/OathbreakersFadeAwayBehaviorCtor.cpp`.
The prerequisite private-view reconciliation is commit `9b9c012ba6` (runner handoff).

## Evidence and result

- Current-map `tu_skeleton.py --merge` approved the constructor at RVA `0x004B8A8A`
  for this provisional TU. No original retail path is asserted by this merge.
- The supported `name_lane.py consolidate --under Code/GameEngine/Source/Common/`
  planner produced `build/consolidation`. Its destination record, original-path
  evidence and blockers were reviewed; the constructor donor is outside this
  Common/ survey scope. The destination remains unresolved in that planner;
  this is not independent TU approval. The merge uses tu_skeleton's rebuilt map.
- `tu_views.py --dry-run` identified the incompatible update donor base clause.
  The constructor and destination already use canonical UpdateModule; their
  declarations now agree, retaining the destination's existing field spellings.
- `tu_skeleton.py --merge --dry-run`, then application with `plan_reused: True`,
  accepted the destination and constructor. Its link guard preserved all three
  census-linked inputs. The constructor file is removed; one functions.csv source
  and one tu_map.csv source are repointed. The map was not regenerated on disk.
- `./build.sh` passes all eight destination rows, two string literals, one float
  literal and funclet parent-EH label resolution. Before merging, the same eight
  rows passed across both inputs. `find_declared_unmatched.py` and `check_csv.py`
  pass after application. The source path named by the new ledger row is tracked.
- `link_check.py` on the destination and untouched update donor reports 2/2 LINKS
  against census `c95fcfcfcd` (2026-11-05 05:17). Destination authored bytes are
  281 (previously 222 plus the constructor's 59); update remains 251. This is a
  preview preserving the same combined 532 bytes, not a census headline gain.

## Consolidation and tooling audit

Audited the constructor-to-destination path change and the prerequisite commit,
against fetched origin/master `48de9fad2a`, with the merge staged after
`9b9c012ba6`. Searches cover the old full path and basename across active tools,
hooks, workflows, Code includes, root build inputs, documentation and reverse
registers. No active tooling consumer requires adjustment. Remaining old-path
mentions are the merged source's donor-provenance comment, immutable attempt
history and reverse/link_status.csv's census record. LINK-168's table records the
historical constructor repair; that history is retained.

The deleted constructor owns no identity, data-check, hatch, flag-override or
header/MS-header queue key. Existing destination data-ledger ownership remains
unchanged. No alias, pin, hatch or protected debt is retired by deletion.
`tu_skeleton` refreshes header-source transfers and the MS-header queue; there
were no constructor keys to transfer and no MS-header changes. The destination's
existing AIUpdateInterface header queue row was stale: the canonical header is
already included. Its owning command
`header_adopt_lane.py accept --class AIUpdateInterface Code/GameEngine/Source/Common/OathbreakersFadeAwayBehavior.cpp`
reports PASS and retires exactly one queue row. No manual queue deletion is used.

Selected definitions and consumer bindings were checked by the merge link guard
and the final two-unit link preview. The pre-push batch audit remains the
publication check. Byte verification, source-claim checks, literal checks and the
unmatched/ledger audits all pass; existing shadow data findings are not claimed
as repaired.

## Remaining work

`Rva004B89C4Update.cpp` stays unchanged: its private triple-base view differs
from the canonical UpdateModule base. A merge still fails on missing
`calcSleepTime` and the incompatible field/base view. Reconcile that donor's
UpdateModule and Object declarations in an independently byte-verified change
before retrying. The mixed destructor and buildFieldParse files are untouched.
Net source count falls by one, header debt by one; no new matched bytes or
census link gain is claimed.
