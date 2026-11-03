# AIBaseBuilder view reconciliation and consolidation

Base: `90f1c538e1`. Scope: Common/AIBaseBuilder.cpp and
Common/Rva00506CF5HomePoint.cpp. Both file scopes claimed before editing.

## Reconciliation

The approved in-memory TU map assigns the donor's six code rows to
Code/GameEngine/Source/Common/AIBaseBuilder.cpp. The unchanged seed has 27
rows, including the shared vector destructor at 0x0007FAB3. No new recovery,
name, retail path or coverage is inferred from the merge.

`tools/tu_views.py --class Rva00506C82Arg` reconciled the existing +0x50
argument views. The seed's existing GameSlot view exposes the donor's +0x10
start field without moving its +0x34 AsciiString. The donor's initial value
uses the same three scalar stores rather than the constructor companion's
inline-only set overload. The seed includes the existing Coord3DCtorView.h
companion so its eventual combined definition preserves memberwise returns.

The seed's private TerrainLogic view called primary vtable slot 9 (+0x24)
under the misleading name getExtent. The existing canonical header calls
that slot slot09; its getExtent is slot 8. Including that header and using
slot09 preserves the target call. This establishes a slot mapping, not a
recovered donor name for slot09. `header_adopt_lane.py accept --class
TerrainLogic` passed and retired exactly the seed's queue entry.

Checks before the reconciliation commit:

- `./build.sh` on both sources: 33/33 code rows and the seed's data row exact;
  eight renumbered funclet pins verified through their parent EH graphs.
- `find_declared_unmatched.py --fail` on both: all definitions already matched.
- Ordinary `link_check.py` against index 8661f15284 (2026-11-03 20:03): both
  LINKS, seed 1,782 -> 1,782 B; donor 763 -> 763 B. This is a prediction,
  not a new census or real-link measurement.
- [Object comparison](reconciliation-objects.json): all 90 original seed and
  29 donor external COMDAT fingerprints unchanged, with no removed definitions,
  changed undefined symbols or weak aliases. The seed additionally emits the
  existing companion's empty default constructor; the ordinary preview passes.
- Supported `tu_skeleton.py --merge ... --dry-run` accepts both donors, all
  33 rows, zero rejected donors after the reconciliation. Earlier failed
  compositions were scratch trials only.

The name-lane planner records mixed/incomplete original-path evidence;
WorldBuilder SkirmishAI paths are donor leads, not BFME 2 path proof. Only the
fresh in-memory TU map approves this Common destination. No tu_map edit.

LINK-018's historical home-point missing-provider preview prerequisite is
cleared for these two units by the current index and explicit per-unit
results above. Other classes and inherited COMDAT selection prerequisites
in that entry remain outside this scope.

## Application handoff

The reconciliation was handed to the fleet publisher as `bea7681e11` (the
publisher rebased its original local SHA). The subsequent supported merge
application stopped before composition or writes: shared ICF row 0x0007FAB3
is held by `codex-01a1071d-root-recovery-oct11` for RespawnUpdate.cpp. The merge
tool released the other claims it had acquired, including the two file scopes.
[Application report](merge-attempt.txt). No source file was removed and no
ledger path moved; source-file reduction and merge link-guard success are not
claimed. Do not override the other worker's claim.

Next pass: regenerate the name-lane consolidation packet (the publisher's
rebase changed map/ledger inputs), claim the available merge scope, and rerun
the normal merge application, byte checks and batch path-consumer audit. The
pre-rebase scratch dry run accepted the reconciled composition; the current
application still needs its full link guard. No TU-map regeneration was
committed. Remaining GameSlot/Waypoint/LivingWorldBattle header debt stays
registered. Neither source owns a code-identity/data-check baseline key, flag
override, MS-header queue row or source-local hatch that requires transfer.
Historical naming approvals, STLport trials and census paths remain attached
to the existing files. The hook's shadow asBase divergence has the same
original seed COMDAT fingerprint in reconciliation-objects.json; no identity
retirement or new census gain is asserted.
