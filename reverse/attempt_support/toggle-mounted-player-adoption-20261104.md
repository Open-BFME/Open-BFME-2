# ToggleMountedSpecialAbilityUpdate: Player adoption and consolidation boundary

Inspected revision: `4ee23edebd`; worker `yasinschroeder-codex`;
2026-11-04; model `gpt-6.1-sol`.

## Completed repair

`Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdate.cpp`
now includes canonical `Code/GameEngine/Include/Common/Player.h` instead of
declaring a second Player class. The existing score-record access remains an
explicit `ScoreKeeper *` cast at Player +0x3BC. The canonical Player header does
not expose that record as a field; this change adds no claim about its layout
beyond the original access.

`./build.sh` reports 17/17 matched rows, two checked string literals, two checked
floating literals, and four funclet labels verified through their parent EH data.
`find_declared_unmatched.py` passes. `header_adopt_lane.py accept --class Player`
passes its structural, byte and link-preservation verdict and retires exactly
one row from `reverse/header_queue.tsv`. No linking headline gain is claimed.

## Consolidation trial

The subsystem evidence planner ran with
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`.
Its WorldBuilder path alternative is donor evidence, not approval to move the
unit to Object/SpecialPower. `tu_skeleton.py --merge ... --dry-run` rebuilt the
current TU assignments, reported 21 approved rows, and accepted no donors.
No source paths or ledger rows were moved.

Current compiler and view evidence:

- `ToggleMountedSpecialAbilityUpdateCtor.cpp`: its class inherits the opaque
  `Rva0044EF5E`, whereas the destination inherits a virtual SpecialAbilityUpdate
  view. The constructor's anonymous union also prevents mechanical `tu_views`
  reconciliation. The merge trial reports `getModuleNameKey` missing from the
  selected view.
- `ToggleMountedSpecialAbilityUpdateModuleDataCtor.cpp`: its class inherits
  canonical SpecialAbilityUpdateModuleData and uses raw timer storage plus an
  explicit vector constructor. The destination inherits `Rva0044ECCE`, spells
  the derived class `novtable`, and holds AsciiString/vector<AsciiString>
  members. `tu_views` refuses the declspec conflict; the merge trial reports a
  constructor definition without a matching declaration.
- `ToggleMountedSpecialAbilityUpdateModuleDataDeleter.cpp`: the merge trial
  compiles but fails bytes. It forces a vtable through an EmitVtableTag
  constructor; the destination suppresses constructor/destructor table stores
  with `novtable`. The exact differing body has not been isolated.

The same TU had an earlier zero-donor trial in `reverse/re_attempts.log`.
This pass identifies the conflicting declarations but does not resolve their
ABI or lifetime semantics. All attempted compositions stayed in the tool's
scratch area; no nonmatching body was left in Code/.

Next work: reconcile the constructor and destructor views from retail's vtables,
base calls and EH ownership in separately byte-verified changes, then repeat the
merge dry run and its link guard. Player adoption removes one canonical-class
prerequisite but does not resolve those disagreements. Other queued canonical
adoptions (Drawable, InGameUI, SpecialAbilityUpdate and Thing) remain untouched.
