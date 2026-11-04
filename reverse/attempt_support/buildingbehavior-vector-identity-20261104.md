# BuildingBehavior window-vector destructor identity

Inspected revision: `d0bd44e76e`. Date: 2026-11-04.

## Target facts and change

The module-data destructor at RVA `0x004564E6` passes the element destructor
at RVA `0x0002CC70` to the EH vector destructor iterator for four 12-byte
elements at offset `0x08`. The ledger names that element destructor
`_STL::vector<AsciiString, _STL::allocator<AsciiString> >::~vector`.
The constructor at RVA `0x00456489` already uses that vector declaration;
its identity repair is recorded in `f50d60f78c`.

`BuildingBehaviorModuleDataDtor.cpp` now uses the same minimal vector and
allocator declarations as the constructor TU. This replaces its private
`BuildingWindowName` class (an AsciiString and eight padding bytes) with a
typedef to the vector. The emitted EH iterator argument names the existing
vector destructor directly. No function rows, pins, aliases or hatches change.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/BuildingBehaviorModuleDataDtor.cpp`:
  1/1 functions matched, including the complete 58-byte row.
- `find_declared_unmatched.py` reports all definitions matched.
- `link_check.py` before and after: LINKS, LINKED 57 -> 57 bytes. The final
  preview uses census 2026-11-04 11:27, revision `3a8028f34e`. This is a
  unit preview, not a new census or a headline linking increase.
- `allowed_symbols.py --source` reports four references: three owner, one EH,
  zero rows with a wrong binding.
- The first `repair_queue.py retire identity` refused stale provider objects
  and two missing objects. After fetching the published index/object bundle,
  the required 387 provider/missing-source byte gates passed: 5,720/5,720
  functions and 64 data rows. Of 349 stale TUs, 312 restored from the object
  store; 38 TUs were already current.
- The subsequent owning-tool retirement passed: one key removed from
  `reverse/code_identity_baseline.tsv`, zero findings remaining for this source.
- `check_csv.py` and `git diff --check` pass. Source paths and ledger ownership
  remain unchanged; the header queues have no entry for the four claimed files.

## Consolidation boundary

The default picker claimed `BuildingBehavior.cpp` and its constructor,
module-data-destructor and update donors. The subsystem evidence planner ran
under `Code/GameEngine/Source/GameLogic/Object/Behavior/`; its four packets
flag include/context review, with the constructor's alias register and the
destructor's identity register additionally noted. No source move was applied.

The post-fix `tu_skeleton.py --merge .../BuildingBehavior.cpp --dry-run` accepts
no donor. The constructor donor fails C2511 because the seed has no constructor
declaration; the update composition fails C2509 because the selected class has
no `getModuleNameKey` declaration. The destructor donor now reaches byte
verification and is rejected as `bytes` (the earlier placeholder-type
composition instead triggered compiler C1001).

`tu_views.py --dry-run` identifies the remaining common-class prerequisites:
the seed's BuildingBehavior has no base while both other views derive from
UpdateModule, and BuildingBehaviorModuleData differs in novtable annotation
and base representation. Reconcile those views in separately verified source
commits, preserving every existing provider and alias, then retry composition
and its link guard. The mixed parse-procedure and Rva0024A797Derived files stay
outside this merge. No source-file reduction or class-wide clearance is claimed.
