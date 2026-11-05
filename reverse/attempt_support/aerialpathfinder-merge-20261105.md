# AerialPathfinder consolidation receipt

Base: `01539a0c2e` (outside-unit unreferenced-copy guard repair).
Source-move audit range: `9f8815d896` through this staged merge, including the
preceding tooling commit. Census index: `c95fcfcfcd`, 2026-11-05 05:17.

The supported `tu_skeleton.py --merge` applies the previously accepted dry-run
composition: absorb `Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp`
into `Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp`. Both donors are
census-linked. All 12 approved code rows remain, seven moving from the donor;
the destination's global remains owned there. Source files decrease by one.
This recovers no new bytes and claims no census gain.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp`:
  12/12 functions and one data row byte-verified; nine string literals and
  29 float literals verified. Renumbered funclets resolve through the exact
  parent EH data. `find_declared_unmatched.py` passes.
- `eh_verify.py`: both EH graphs EXACT, no missing object or baseline debt.
- `check_csv.py`: passes, unchanged 99,469 function rows.
- `link_check.py`: merged TU LINKS, 3,278 authored bytes, equal to the two
  original units' 1,138 + 2,140. The six-byte profiler Id constructor remains
  an unreferenced diagnostic, not a blocker. The supported merge guard accepts
  the composition without losing any protected input's preview.
- Code identity remains shadow: two divergent-definition diagnostics,
  `??0Id@ProfileHighLevel@@QAE@XZ` and
  `?asBase@@YAAAUCoord3DBase@@AAUCoord3D@@@Z`. Their merged digests/sizes
  (`595907fb5146`/6 and `341dc3ec187f`/5) equal the donor's census copies.
  No new call-binding finding is reported; no baseline key is retired.
- `data_check.py` reports zero findings; converged checking reports no second
  global or unjudged row. `tu_ownership.py --staged` and
  `ms_header_audit.py check` pass.
- `link_batch_audit.py`, against the staged tree and base `9f8815d896`, returns
  **INCONCLUSIVE (2)**: index baseline `c95fcfcfcd` differs from the outgoing
  base, and two source objects lack census-grade include-inventory receipts
  (first: the merged TU). Ordinary byte-gate receipts do not prove that stronger
  condition. External-consumer preservation is therefore not fully verified
  by this batch audit. Carry this scope into the next scheduled census; no
  direct census, nightly, real-link or smoke run was started.

Path and register audit:

- The outgoing source scope contains only this destination and absorbed donor.
  Seven `source` cells each in functions, TU map and naming basis are repointed
  by the merge tool. TU assignments/confidence/evidence are unchanged; no map
  regeneration is committed.
- Neither source owns header-queue, Microsoft-header-queue, gate, identity,
  data-check, flag-override or hatch register keys. The supported merge refreshes
  header/MS-header reports and requires no changes or transfers. Data ownership
  stays with the destination; no removed source remains in the active code/data
  ledgers or body-owner/fold-proof registries.
- Combined old-path/basename search finds no active tool, hook, workflow,
  include, build configuration or doxygen consumer needing an update. The
  remaining donor mention in the merged source is its provenance comment.
  Old references in `reverse/attempt_support/` are historical evidence.
  `name_votes.csv` is append-only voting history; `name_bindings.csv` retains
  the old source/context-hashed landing receipt, which cannot authorize a new
  destination-context reuse. `link_status.csv` is census output and awaits
  the next census rather than a hand edit.

Local logs: `build/codex-aerial-{merge-apply,build,link-preview,identity,data,eh,
ownership,ms-headers,link-batch}.log`. LINK-189 is cleared for the merge guard,
byte checks and merged-unit preview scope; census and full batch confirmation
remain pending.
