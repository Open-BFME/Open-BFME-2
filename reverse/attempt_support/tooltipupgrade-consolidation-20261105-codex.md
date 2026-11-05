# TooltipUpgrade consolidation (2026-11-05)

Inspected revision: `1f4fc749e9`; prerequisite: that commit declares the
already-rowed `getModuleNameKey` override in the seed. The supported
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Upgrade/`
planner was regenerated after this edit. Its path evidence is unresolved;
the merger separately rebuilt current TU approvals in memory. These are
provisional N/P approvals, not a recovered original filename claim.

`tu_skeleton.py --merge .../Upgrade/TooltipUpgrade.cpp --dry-run` then accepted
the seed and `TooltipUpgradePoolKey.cpp`. Application reused the verified
composition, removed that donor and moved its three function/EH rows and
two data-ledger owners into `TooltipUpgrade.cpp`. Only existing source cells
in `tu_map.csv` changed; the map was not regenerated on disk. Source files
decrease by one, with six matched rows in the resulting TU.

Verification:

- `./build.sh .../Upgrade/TooltipUpgrade.cpp`: 6/6 byte-exact; the old `$L310`
  unwind label is verified as `$L2596` through the parent's EH graph. String,
  float and import checks pass. Before/after declaration checks pass.
- `eh_verify.py` on the destination: one EH-bearing parent, EXACT.
- The merger's combined census-link guard passes with the donor removed.
  Local `link_check.py` previews LINKS for both the destination (206 authored
  bytes) and unchanged removal fragment (69), against the 2026-11-05 05:17
  index at `c95fcfcfcd`. The moved bytes already linked in their donor; this
  is no new linked-byte or census gain.
- `check_csv.py`, staged TU ownership and staged whitespace checks pass.
  Staged data checking remains shadow: duplicate/wrong-name findings for
  `DRAWABLE_FRAMES_PER_FLASH` were present before this merge; the merged
  compiler now spells the local-static guard `$S3` rather than the data
  ledger's `$S1`. Its address and ownership remain recorded, and EH verification
  passes. No data debt or other register key was retired.

Path-consumer audit covers `origin/master` at `f44cbcf5b0` through the pending
merge, including the earlier published-to-runner W3DShadow assignment move.
Combined searches for `AudioEventRTSAssign.cpp` and `TooltipUpgradePoolKey.cpp`
in tools, hooks, workflows, source/header includes, documentation and reverse
registers found no additional active consumer needing repair. The W3DShadow
move's verification is in `w3dshadow-consolidation-20261105-codex.md`.
Remaining old-path mentions are source provenance, historical attempt evidence,
the historical deleted-row explanation and the census snapshot. Function, TU
and data ownership ledgers point to the destination; no pin/fold proof or
doxygen entry needs repointing. Neither TooltipUpgrade source has code/data
identity, hatch, flag, header-queue or Microsoft-header debt. The merger
refreshed the header/MS-header reports and carried the two data-ledger keys
through its normal transfer path. No alternatename was removed.

Remaining consolidation prerequisite: `TooltipUpgradeRemoval.cpp` still fails
the composition with C2504 (`UpgradeModule` base undefined) and C2011
(duplicate `Drawable`). Reconcile its canonical UpgradeModule/Drawable includes
with the seed's private bases in a separate byte- and link-verified change.
The two mixed files remain intact. This narrows the older refusal recorded in
`siegedeploy-consolidation-20261104.md`: the pool-key declaration blocker is
resolved; the removal-fragment prerequisite remains.
