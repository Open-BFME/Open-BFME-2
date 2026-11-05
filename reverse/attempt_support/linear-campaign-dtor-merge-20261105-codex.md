# Linear campaign destructor consolidation, 2026-11-05

Base: 541bd3ad0148. Owner: yasinschroeder-codex.

After the separately verified declaration cleanup, the refreshed consolidation
planner and supported `tu_skeleton.py --merge` probe accepted Rva001EC349Dtor.cpp.
The application reused that verified plan, absorbed the donor into
Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp and repointed
its six rows: destructor 0x001EC349 (108 bytes) and five parent-graph-bound
funclets 0x0076A682..0x0076A6AB (52 bytes). One source file is removed. The
destructor's current TU-map assignment is approved; the map edits only update
the six source columns, without regenerating assignments or approving funclets.

Verification:

- Final ordinary `./build.sh` passes 54/54 rows, one data row and three strings.
  Renumbered funclet labels resolve through their exact parent EH graphs.
- `find_declared_unmatched.py` is clean; `check_csv.py` preserves all 99,455
  function rows, 9,324 symbol rows and 2,268 data rows.
- The merge's LinkGuard accepts the composition against census index c95fcfcfcd
  (2026-11-05 05:17), including selected COMDATs and outside-provider protection.
  Ordinary final-TU preview reports LINKS, 2,721 authored bytes. This is a
  preview, not a census gain.
- `data_check.py --staged`: zero findings; `code_identity_gate.py --staged`:
  54 rows, zero new findings (shadow). No debt is retired. The absorbed donor
  has no keys in the code/data identity registers, data ledger, gate baseline,
  header queue, Microsoft-header queue or unclaimed-source whitelist. The
  merger refreshes both header queues; eight existing destination adoption
  items remain, and no queue file changes.
- Strict receipt preparation covers the final TU and affected STLport vector
  destructor/growth/push-back providers: 188/188 rows pass, with one data row
  and three strings. The broader outgoing audit remains INCONCLUSIVE: the
  census predates the outgoing base, and unchanged consumer
  Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
  receipt. This is the same consumer limitation recorded by the earlier
  header-selection handoff. Carry these providers and their consumers into
  the next scheduled census; no complete outgoing-link verification is claimed.

Tooling compatibility audit covers the declaration-cleanup commit plus this
staged merge. The only removed path is
Code/Libraries/Source/WWVegas/WWLib/Rva001EC349Dtor.cpp. Searches for its path
and basename across tools, hooks, workflows, game sources/includes, root build
scripts, reverse registries and documentation found no active hard-coded
consumer needing an update. The function ledger and TU-map source columns are
repointed by the merger. Remaining mentions are the TU's provenance comment,
the measured census's historical link_status.csv, the obstacle history and
attempt evidence (including an older header-adoption proposal). These remain
historical; no alias or pin is removed and no directory is moved.

Eighteen donors remain rejected by the refreshed supported probe: incompatible
private class/STL declarations or merged byte differences. CarryoverUnit's
identity/ABI prerequisite in LINK-040 remains open. The earlier view-reconcile
pass retained no changes; no failed reconstruction is left in Code/.
