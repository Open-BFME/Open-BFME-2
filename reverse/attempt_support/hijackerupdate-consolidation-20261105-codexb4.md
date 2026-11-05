# HijackerUpdate partial TU consolidation, 2026-11-05

Base: `d83d5ea7e0`, after the header-environment prerequisite repair.
`tu_skeleton.py --merge` absorbed `Code/GameEngine/Source/Common/Rva004A3F8BXfer.cpp`
and `Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdatePoolKey.cpp`
into the approved `Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp`.
This removes two source files and preserves ten matched rows. The planner's
original-path evidence is a lead; the current TU map approves this destination.
No donor-source identity or layout claim follows from the byte match alone.

## Verification

- `./build.sh` on the destination: 10/10 byte matches and two string literals.
- `find_declared_unmatched.py`: no unrowed body; the two existing emission-anchor
  declarations remain marked absent from retail.
- `eh_verify.py`: one EXACT parent, no unverified EH or baseline dependency.
- Strict `link_check.py --prepare-current` accepted the destination receipt.
  Destination, constructor and update all LINKS in the current-object preview:
  285 + 74 + 313 = 672 owned bytes, preserving the five-input 672-byte scope.
  Index census: 2026-11-05 05:17 UTC, revision `c95fcfcfcd`. This is a scoped
  prediction, not a new census gain or a real-game link result.
- `tu_skeleton`'s link guard preserved all five census-linked input units.
  `check_csv.py`, `tu_ownership.py --staged` and `git diff --check` passed.
- Refreshed the supported consolidation planner after composition.

## Ownership and complete pending-batch path audit

Audited `origin/master..d83d5ea7e0` plus this staged merge. The other pending
move is OathbreakersFadeAwayBehaviorCtor.cpp into its existing Common behavior
TU; its verification and header-queue retirement are recorded in
`oathbreakers-consolidation-20261105-codexb4.md`.

The merge tool repointed four function/map source rows and transferred both
data-ledger keys (the cached pool key at 0x00A03BFC and guard at 0x00A03C00).
Neither removed Hijacker donor owns header, ms-header, code-identity, data-check,
gate, hatch or flag-override debt. Constructor/update header-queue prerequisites
remain with those surviving files. No pins or link-wide aliases were removed.

Combined searches for all three absorbed basenames and paths found no active
tool, hook, workflow, include or build/config consumer requiring edits. Remaining
old paths are source provenance, immutable attempt evidence, deleted-row history
and census-owned link-status history. These intentionally retain their old
paths. Current ledgers and map resolve to the destination; no fold proof needs
repointing. The stale live xfer comment was corrected.

## Remaining work

The constructor still uses opaque vptr stores and needs canonical UpdateModule
reconciliation. The update fragment needs ObjectID/interface reconciliation,
including AICommandInterface; both were rejected by the supported merge and
remain intact. The mixed Rva0024A797Derived.cpp was not split or moved. Next work
should reconcile each residual under its own claim and byte/link verification,
then retry the supported merge. Await the next census for confirmation.
