# ReplaceObjectUpdate consolidation prerequisite and remaining conflicts

Inspected 2026-11-04 at `2d0ce472f8880030dc110962ae9d412789e6b0cc`. The default picker claimed the TU and
three eligible donors. Original-path planner scope:
`Code/GameEngine/Source/GameLogic/Object/Update/`; target assignments were
recomputed in memory by `tu_skeleton.py`. No TU map was committed.

## Verified repair

`ReplaceObjectUpdateModuleDataCtor.cpp` now includes the canonical
`SpecialAbilityUpdateModuleData.h`, removes its empty private base and manual
vptr/padding fields, and lets the compiler install the derived table.
Declaring the already-rowed virtual destructor out of line prevents an
incorrect implicit destructor from being emitted in the constructor object.
Without that declaration, link_check reported a duplicate and a wrong selected
`??1ReplaceObjectUpdateModuleData@@UAE@XZ`; the declaration resolves both.

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateModuleDataCtor.cpp`:
  1/1 exact, complete 61-byte constructor at 0x004B2AC4; string/float/import checks pass.
- `find_declared_unmatched.py` on that source: all defined functions matched.
- `header_adopt_lane.py accept --class SpecialAbilityUpdateModuleData` on that
  source: PASS; retired exactly one header-queue row through its owning tool.
- `link_check.py` on that source: LINKS, 61 -> 61 bytes against the
  2026-11-04 02:25 census at 5a13f2cd61. This is a preview, not a new census.
- Normal pre-commit gate passed. Repair commit: `2d0ce472f8880030dc110962ae9d412789e6b0cc`.

## Remaining work

No source files were removed. The post-repair merge dry run still accepts no
extra donor. The main TU lacks the constructor/destructor declarations and
layout required by the donor bodies. `tu_views.py --dry-run` reports:

- `ReplaceObjectUpdate`: base clauses differ between `SpecialAbilityUpdate`
  in the TU and `Rva0044EF5E` in the constructor donor. Adopt/reconcile the
  canonical base before unifying the derived view; do not add a new private
  copy of the registered base.
- `ReplaceObjectUpdateModuleData`: the destructor donor inherits
  `Rva0044ECCE`, the repaired constructor inherits
  `SpecialAbilityUpdateModuleData`, and the main TU uses a flat array view.
  Reconcile the base identity and member representation while preserving the
  destructor's selected provider and all EH/fold rows.
- `Rva004B2B2F`: a superset view is proposed for the TU and destructor donor;
  it has not been applied or verified. Its by-value filter and vector
  dependencies must be available before its declaration.

Next work is verified donor/view reconciliation in separate commits, then a
fresh supported merge trial. `GapBodiesGE24.cpp` and `ModuleUpdateDtors.cpp`
remain mixed and must not be split inside a merge. Existing header debt in
the destination remains registered. No alternatename or pin was added or
removed; no path consumer changed.

## Post-repair merge receipt

Command: `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdate.cpp --dry-run`

Exit: 2 (no verified composition). All four objects are census-linked, so the
merge's link guard must continue to preserve their bindings.

```text
tu: Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdate.cpp
approved: 32
mixed: {'Code/GameEngine/Source/Common/GapBodiesGE24.cpp': 19, 'Code/GameEngine/Source/GameLogic/Object/Update/ModuleUpdateDtors.cpp': 23}
refused: {}
accepted: []
rejected: {'Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateModuleDataDtor.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\.ReplaceObjectUpdate.151d0b2716942a81.tu_skeleton.cpp(343) : error C2143: syntax error : missing ';' before '*' | Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\.ReplaceObjectUpdate.151d0b2716942a81.tu_skeleton.cpp(344) : error C2501: 'ReplaceObjectUpda", 'Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateCtor.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\.ReplaceObjectUpdate.4703d1baad7571e6.tu_skeleton.cpp(497) : error C2511: 'ReplaceObjectUpdate::ReplaceObjectUpdate(Thing *,const ModuleData *)' : overloaded member function not found in 'ReplaceObjectUpdate' | Code\\GameEngine\\Source\\GameLogic\\Object\\Up", 'Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateModuleDataCtor.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\.ReplaceObjectUpdate.c5b1153ce4feaf4d.tu_skeleton.cpp(667) : error C2600: 'ReplaceObjectUpdateModuleData::ReplaceObjectUpdateModuleData' : cannot define a compiler-generated special member function (must be declared in the class first) | Code\\GameEngine"}
adopt_first: {'Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdate.cpp': ['AIUpdateInterface', 'DamageInfo', 'FieldParse', 'INI', 'MultiIniFieldParse', 'PlayerList', 'Rva000421C8', 'SpecialAbilityUpdate', 'Thing']}
link_guard: census-linked: Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdate.cpp, Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateCtor.cpp, Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateModuleDataCtor.cpp, Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdateModuleDataDtor.cpp
blocked: no verified merge of two or more donors
reconcile_classes: ['ReplaceObjectUpdate', 'ReplaceObjectUpdateModuleData', 'Rva004B2B2F']
reconcile: python3 tools/tu_views.py Code/GameEngine/Source/GameLogic/Object/Update/ReplaceObjectUpdate.cpp --dry-run, then without --dry-run: the donors declare their own views of ReplaceObjectUpdate, ReplaceObjectUpdateModuleData, Rva004B2B2F (docs/consolidation.md, "Workflow per TU", step 4)
```
