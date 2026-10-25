# Partition result Sort: TU approval remains unanchored

Inspected BFME 2 upstream `40b830025a`, with verified BFME 1 reference
`f633d0e97a`. The default TU-approval queue selected the proposed destination
`Code/GameEngine/Source/Common/BfmeThingVJX.cpp`; that file does not exist.
The actual, complete source is `Code/GameEngine/Source/Common/BfmeConv1395.cpp`.
It owns one matched body: `BfmeThingVJX::Sort`, RVA 0x006269E0, 70 bytes.

The whole source and its previous rename verdict were read. The frozen-file
check and normal `build.sh` pass (1/1 function, no reference findings). The
committed census already lists this source as linked. No code, ledger, pin,
name, baseline or TU-map change was attempted; no progress gain is claimed.

## Evidence and limits

- `wb_show.py 0x006269E0` pairs the body with WorldBuilder VA 0x0167F6A0.
  That body asserts `PartitionManager::Result::Sort` and the original path
  `Code/Libraries/Source/partitionmanager/partitionmanager_result.cpp`.
  Modes 2 and 1 call the two mapped sort drivers at 0x00626990 and 0x00626940.
- The existing rename already used that lead for the method word `Sort`,
  leaving the placeholder class. `name_evidence.py --kinds wb` currently
  grades the class proposal as **hint**, specifically `score 1 < 4`, with
  `nested=yes`. This pass does not lower that threshold or promote the hint.
- The current consolidation packet agrees on that possible destination but
  labels the WorldBuilder pairing an identity/file hint, not verified target
  routing. Its BFME 1 path evidence comes from `wb1`, not original BFME 2
  source. The packet also flags the existing `reverse/flag_overrides.csv`
  entry for BfmeConv1395 (`region default loses rows`).
- `tu_skeleton.py --plan` reports zero approved rows for both the served
  BfmeThingVJX path and the hinted partitionmanager_result path. The current
  map has only an N naming hint, with no F/Z/S anchor or approved brackets.
- `PartitionManager` is registered in `reverse/canonical_classes.csv` at
  `PartitionRangeQueryCallView.h`. A future nested-result reconciliation must
  respect that canonical owner rather than add a private outer-class copy.

## Next useful work

Establish admissible target routing and a name basis, then reconcile the nested
result declaration with its canonical outer class and current consumers.
Re-evaluate the protected flag override under the prospective TU's actual
compile environment before a move. Rebuild the consolidation packet after
those inputs change and require an approved `tu_skeleton.py` plan. A cleaner
class spelling or the WorldBuilder path alone does not approve the transfer.
