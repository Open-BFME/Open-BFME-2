# BroadcastStealthUpdate composition, 2026-11-05

Inspected reconciliation revision: `0ee86a6050`. The current in-memory TU map
approves `Code/GameEngine/Source/GameLogic/Object/Update/BroadcastStealthUpdate.cpp`.
The consolidation planner's placement evidence is provisional naming evidence,
not an independently recovered original EA path or external donor attribution.

## Result and target evidence

- Reconcile the constructor, destructor and main file's private views around
  the existing canonical UpgradeMux header, one module-data view and one
  four-byte ObjectID-list view. Retail constructor/destructor stores and the
  existing matched update/xfer accesses determine the offsets used here.
- The list initializes through the existing 0x0029FB3B owner and tears down
  through the rowed PoolMember::Rva00268902 owner at 0x00268902. An intermediate
  inherited view exposed two shadow identity findings against the destructor
  COMDAT in Rva004DF418Finish.cpp. The follow-up reconciliation removes those
  references; its hook reports zero new identity findings. That other object's
  private view is outside this repair.
- `add_match.py --icf-owner` verified and rowed the compiler-emitted list
  destructor at the existing 0x00268AFF fold. The complete five-byte tail jump
  reaches 0x00268902, as does the existing PoolMember wrapper. The retail unwind
  callback at 0x0078DC6B establishes its use here. This adds zero unique bytes.
- `tu_skeleton.py --merge` accepts all three files and removes the constructor
  and destructor donor files: source-file count decreases by two. Its seven
  ledger repoints include the destructor fold. Only six source columns in the
  committed TU map change; assignments are not regenerated.

## Verification and provider audit

- `find_declared_unmatched.py` passes before editing and for the final TU.
- `./build.sh` verifies 21/21 rows in the final TU, one string reference and
  the parents' renumbered EH labels. The commit gate checks all four EH graphs.
- `check_csv.py` passes: 99,482 function rows, 9,320 symbols, 2,268 data rows.
- Original three-file link previews: 701 + 146 + 126 = 973 bytes, all LINKS.
  Final preview: main TU LINKS with 973 own bytes. The displayed 701 -> 973
  transition is donor ownership transfer, not new linked coverage. Index:
  2026-11-05 15:19, `f44cbcf5b0`, clean-tree metadata.
- Comparing the union of reconciled objects with the final object finds no
  lost external definition. All nine linker aliases survive, including both
  explicit destructor-unit aliases and seven canonical AsciiString aliases.
- A scan of all 23,308 cached objects checks every original cohort definition
  absent from the final object. The two absorbed objects are searched but
  excluded from surviving-provider decisions. PoolMember's destructor remains
  defined in PlayerDestructor and BridgeBehaviorDtor; the old ObjectIDList
  constructor/destructor remain in the two BezierProjectileBehavior objects.
  None has an external reference in another current cached object. The removed
  BroadcastStealthUpdate_B3 vtable and class-key-specific module-data getter
  have no remaining definition or reference. Census touches of these names
  add only the old cohort and those surviving providers. No unprovided
  external reference is found.
- Outgoing `link_batch_audit.py`, origin/master `898e88e98f` to staged source
  tree `09bcd13327d95124b148a3cee2f28cd9961094d9`, is **INCONCLUSIVE**:
  the index predates the base and three objects lack census-grade current
  receipts (first: the merged TU). Ordinary byte/dependency checks and local
  previews do not close that receipt gap. Carry this batch into the next
  census; no real-link or headline census change is claimed.

## Registers and path consumers

The combined old paths/basenames were searched across tools, hooks, workflows,
Code includes, build/configuration files, reverse registers and documentation.
No active build/tool consumer requires an update. Remaining mentions are
historical attempt inventories, the measured link_status snapshot, comments in
BridgeBehaviorDtor, and the merge tool's provenance comments; retain them.
The destination's two static data owners remain in data_ledger.csv.

No data/code-identity debt key belonged to either donor. The merge tool transfers
both alternatename hatch keys with their counts unchanged. The existing
Rva000421C8/PartitionFilter header-queue row remains at the destination; no
header debt is retired. The mixed ConstIntGetters4 and UpgradeMuxSlotOverrides
files remain outside the merge. Their approved fragments and the independent
0x004A33EE helper placement still need separate work.
