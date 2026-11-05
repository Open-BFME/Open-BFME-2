# Upgrade duplicate destructor cleanup — 2026-11-05

Inspected revision: `9415065957` (master before this cleanup).
Scope: `Code/GameEngine/Source/Common/System/Upgrade.cpp` and its approved
`UpgradeCtor.cpp` lifecycle donor. No rows, pins, aliases or source paths move.

## Target facts

The ledger assigns `??1Upgrade@@UAE@XZ` at RVA `0x0026EDFF` (18 bytes),
its constructor at `0x0026EDDC` (29 bytes), and its deleting destructor at
`0x0026EF34` (28 bytes) to `UpgradeCtor.cpp`. That donor clears the previous,
next and template pointers in its destructor. The destination instead retained
an empty Zero Hour destructor with the same name, plus stale constructor and
UpgradeCenter destructor markers with no definitions. These are existing
placeholder/duplicate cleanup, not missing retail coverage.

## Investigation and change

The consolidation planner surveyed Common/System. The initial guarded merge
accepted no donors. `tu_views.py` changed no source: OpaqueRefPtr and Rva002A9BF2
were already shared; Rva0026F684 conflicts because its +0x1C vector spans twelve
bytes in the seed but only four bytes in the destructor view. Canonical
UpgradeTemplate/UpgradeCenter declarations require the header lane.

The initial UpgradeCtor trial failed C2084, duplicate Upgrade destructor body.
Removed the empty destination destructor and the three stale lifecycle markers.
Kept the donor bodies, every ledger owner, and the existing push_back alias.
`hatch_counters.py --update` shrank present_unmatched from 2,268 to 2,265.
No gate/data/identity/header debt is retired by this change.

## Verification

- `check_csv.py`: OK, 99,458 function rows, 9,319 symbol rows, 2,268 data rows.
- `./build.sh Code/GameEngine/Source/Common/System/Upgrade.cpp`: 27/27
  matched; string/float/import references pass, including EH parent-based label
  resolution after compiler label renumbering.
- `find_declared_unmatched.py` on the destination and lifecycle donor: pass.
  Destination unclaimed-definition/marker notes fall from eleven to eight.
- Freshly fetched published index: c95fcfcfcd, 2026-11-05 05:17,
  retail-truth-5. Ordinary `link_check.py` reports LINKS, 754 -> 754 bytes,
  one current cached destination object. This is a preview, not a new census
  or a full-game link result.
- `git diff --check`: pass.

## Remaining work

Retry the approved TU merge after the duplicate-body removal. Other original
rejections remain separate: canonical subsystem declarations collide with the
seed's donor headers, lookup declarations lack rva0026EEA0, parser INI views
conflict, template specializations are ordered inconsistently, image fields
have different types, and the two Rva0026F684 lifetime/assignment donors lose
bytes. Do not force these donors into the destination or claim a file-count gain.

## Guarded retry after the cleanup

The second ordinary `tu_skeleton.py --merge ... --dry-run` completed after
cleanup commit `6148b07c88`; it started with the same source cleanup before
that commit. It refused with `no verified merge of two or more donors` and
accepted no donors. The complete structured verdict is retained in
[upgrade-merge-retry-20261105.json](upgrade-merge-retry-20261105.json).
UpgradeCtor's verdict changed from duplicate-definition C2084 to `bytes`.
The check does not identify which of its three rows differs, so no individual
function's failure is asserted. An independent `./build.sh UpgradeCtor.cpp`
still passes all three lifecycle rows and all reference checks. The next useful
lifecycle check is to compare those rows in the composed TU against that
standalone object, including its Snapshot and memory-pool declarations and the
carried compiler environment. The other donor rejection families remain as
listed above. No merge is applied and no source path changes.

The cleanup commit's hook also passes exact EH verification (4/4), ledger and
flag-override checks and converged data enforcement. Code identity, which is in
shadow mode, reports two divergent AsciiString destructor bindings in
getVetUpgradeName and findVeterancyUpgrade; this cleanup does not reconcile or
retire them. `/opt/runner/publish` reports that maintainers have locked master;
the commit is retained locally for the runner's later publication retry.
