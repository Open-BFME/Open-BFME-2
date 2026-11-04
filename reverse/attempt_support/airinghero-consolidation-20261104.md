# AIRingHeroTactic consolidation audit

Audited outgoing source-path batch: origin/master 7d7c23030171baa9ccfae22ec778f88339870946, parent f000081a14bf2dcc477b61cba525dbf594b547a9,
plus this staged merge. The batch absorbs only
`Code/GameEngine/Source/Common/Rva005AC98ACheck.cpp` into
`Code/GameEngine/Source/Common/AIRingHeroTactic.cpp`.

## Placement and source composition

The current in-memory TU map approves the two code bodies at 0x005AC98A and
0x005ACA28 for AIRingHeroTactic.cpp; their EH rows at 0x0079EA32/0x0079EA3A
follow the exact same-source parent graph. This uses the existing provisional
N ownership, with no new original-path assertion. `tu_skeleton.py --merge
--dry-run` accepted both units; apply reused and reverified its plan, retaining
all 20 rows and removing one source file. The committed map changes only four
source columns; no regenerated assignments are included.

The prerequisite commits adopted canonical AITactic/AITacticOffensive bases,
then aligned the donor's derived view. The +0x24 owner uses the canonical base
field cast to Player; +0x10 is the canonical running flag. The upgrade scan's
+0x5C Player store/read establishes the pointer type shared by both views.
No canonical class definition, pin, alias or escape hatch was added.

## Verification

- `./build.sh AIRingHeroTactic.cpp`: 20/20 rows, six literals, float/import
  checks pass; all four EH-bearing rows are EXACT (`eh_verify.py`).
- Frozen-file check: all defined functions already matched.
- `check_csv.py`: passes; all moved rows retain name, RVA, extent and status.
- `tu_ownership.py --staged`: passes.
- Code identity: 20 rows, zero new findings, shadow mode.
- Data identity: zero findings; converged check has zero second names or
  unjudged rows. No data, identity, duplicate-definition, gate or hatch keys
  name the removed donor, so no debt retirement or transfer is required.
- Header debt: three queue rows were retired by passing `header_adopt_lane.py
  accept` verdicts in the prerequisite commits (AITactic, AITacticOffensive,
  Player). The existing AICommandInterface debt remains at the destination;
  no Microsoft-header debt names either unit. Merge refreshed the queues.
- Link evidence uses the 2026-11-04 22:01 census index at 3fbce7bcb2. Before:
  both units LINKS, 937 + 172 = 1,109 census-linked bytes. After: destination
  LINKS with 1,109 bytes. The merge guard checks unresolveds, duplicates,
  selected COMDAT variants, variants affecting outside copies and dropped
  providers still referenced by outside units, and passed at dry run/apply.
  These are previews against that index, not a new census or real-link receipt.

## Tooling compatibility audit

Searched the old full path and case-insensitive basename across active tools,
hooks, workflows, sources, headers, root build/configuration files, registries
and docs. The engine repointed all four functions.csv owners and corresponding
map source columns. No active hard-coded consumer needs updating. Intentional
old mentions remain in the merge provenance comment, historical re_attempts
entries, the EH cohort's callee-proof/receipts, and the measured link_status.csv
snapshot. Historical measurement/evidence paths stay as recorded.

## Remaining prerequisites

The constructor, destructor and factory rows remain in three mixed files;
this merge neither splits them nor changes their ownership. AICommandInterface
adoption still needs to reconcile the embedded +0x20 command view with the
abstract canonical interface. No relevant existing linking-obstacle entry was
found for these two units. The scoped naming handoff uses the final TU path;
its review inventories 22 bindings, with the direct-initialized AsciiString
local outside the regex inventory and retained unchanged.
