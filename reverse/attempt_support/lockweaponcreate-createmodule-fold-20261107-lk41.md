# `?onBuildComplete@LockWeaponCreate@@UAEXXZ`: the `~CreateModule` fold now stops at `~BehaviorModule` (lk41, 2026-11-07)

Follows `004b8c0e-lockweaponcreate-canonical-view-20261105.md` and
`004b8cc9-lockweaponcreate-fold-class-gate-20261105-claudeb.md`. Base `4b2bb61eb1d`.
Target facts are retail bytes and rows; inferences are marked.

## What landed

`396dd703351` adds `rename.py class --fold ... --access protected` (tests in
`tools/tests/test_rename_fold.py`). `CreateModuleClass.h` declares `~CreateModule` protected,
`??1CreateModule@@MAE@XZ`, the spelling all six Zero Hour-view consumers reference
(GrantUpgradeCreate, LockWeaponCreate, PreorderCreate, SpecialPowerCreateConstructor,
SupplyCenterCreateConstructor, SupplyWarehouseCreate; five of them LINK at census `94d8ffa1ad`).
The placeholder rows spell it public (`??1Rva004B8CDE@@UAE@XZ`), so a plain fold could not land.

## The fold, measured (not landed)

`rename.py class --fold Rva004B8CDE --into CreateModule --access protected` plans:

- `0x004B8CDE ??1Rva004B8CDE@@UAE@XZ -> ??1CreateModule@@MAE@XZ`
- `0x004B8D32 ??_GRva004B8CDE@@UAEPAXI@Z -> ??_GCreateModule@@MAEPAXI@Z`

Five units come prepared on `CreateModuleClass.h`:

- CreateModule.cpp: the opaque `Rva004B8CDE`/`PrimaryP4B8CDE` model, its anchor and the `f2`
  alternatename go; `CreateModule::~CreateModule() {}` is the row.
- Rva004B8CDEDerived.cpp: `class X : public CreateModule { virtual ~X(); }` for LockWeaponCreate
  and the six `Rva004B8xxx` placeholders; the seven `f2` alternatenames go.
- TailJumpWrappers5B.cpp: `class __declspec(novtable) Rva004851A8 : public CreateModule`.
- TailJumpWrappers5B_~Rva002563CE.cpp, W3DAptComponentView3D.cpp: their unused
  `Rva004B8CDE`/`Rva004851A8` declarations go.

Result: **112/112 rows exact** over the five sources (the build inside `rename.py`), and in a scratch
compile `??1CreateModule@@MAE@XZ` (25 B), `??_GCreateModule@@MAEPAXI@Z` (28 B) and the constructor
(53 B) are exact against 0x004B8CDE/0x004B8D32/0x004B8CF7.

**Refused by the commit checks, every file restored:** `find_declared_unmatched` flags
`BehaviorModule::~BehaviorModule` in CreateModule.cpp.

## Why: `~CreateModule` needs `~BehaviorModule` inline, and that body has no row

- Retail 0x004B8CDE keeps only the +0x10 store of CreateModule's own tables (0x00C59358), then
  stores BehaviorModule's 0x00BEEA7C/+0 and 0x00BEE9C0/+0x0C and jumps to 0x0049B47C. That is
  `~BehaviorModule` inlined (structural inference, as `BehaviorModule.h`'s header notes say for
  `~DieModule`). With `BehaviorModule.h`'s declaration only (`virtual ~BehaviorModule();`), MSVC
  stores all three CreateModule tables and tail-calls `~BehaviorModule` instead.
- Supplying `inline BehaviorModule::~BehaviorModule() {}` in the unit (as BehaviorModule.h's comment
  suggests) gives the exact bytes, but the unit then emits an out-of-line
  `??1BehaviorModule@@MAE@XZ` COMDAT too (`??_GBehaviorModule`, slot 0 of the BehaviorModule table
  that the unit's inline BehaviorModule constructor row 0x00253330 installs, calls it). No row names
  `??1BehaviorModule@@`, so `find_declared_unmatched` refuses it, and a new `present-unmatched`
  marker would be an unadmitted hatch.
- Retail's out-of-line `~BehaviorModule` is **0x004607E1**, rowed as `??1Rva004607E1@@UAE@XZ`
  (Rva0049B47CDerived.cpp). Target fact: `??_GRva004607E1@@UAEPAXI@Z` 0x0025335A is slot 0 of
  BehaviorModule's own table 0x00BEEA7C, which `??0BehaviorModule` 0x00253330 installs, and it calls
  0x004607E1.
- `rename.py class --fold Rva004607E1 --into BehaviorModule --dry-run` refuses: 0x00BEEA7C is also
  named for `PrimaryP`, `PrimaryP24A797`, `PrimaryP4B8CDE` and `UpgradeBehaviorBaseView`
  (data_ledger.csv). `PrimaryP4B8CDE` goes with the CreateModule fold; the others are private
  views in other units, and data_ledger.csv must be regenerated after they go.
- `class:BehaviorModule` reads as held through Burachi-3D's `class:UpdateModule` claim (header
  adoption); this seat did not touch it.

## Order of work from here

1. Give `~BehaviorModule` its row: retire the third names on 0x00BEEA7C, regenerate
   data_ledger.csv, then `rename.py class --fold Rva004607E1 --into BehaviorModule --access protected
   --prepared` (UpgradeModuleCtor.cpp, Rva0049B47CDerived.cpp). Or, the BehaviorModule owner defines
   the empty destructor in the class body of `BehaviorModule.h` (an opt-in macro, as
   `BFME_BEHAVIORMODULE_LOADPOSTPROCESS` does), so an inline-only use is no unrowed definition.
2. Re-run the CreateModule fold above (the prepared units are reproducible from this note).
3. LockWeaponCreate.cpp on `CreateModuleClass.h`, sharing one LockWeaponCreate view with
   Rva004B8CDEDerived.cpp (both emit `??_7LockWeaponCreate@@6BObjectModule@@@`, `...6BBehaviorModuleInterface@@@`
   and `...6B@`, so the copies must be identical):
   - `onBuildComplete`: `function --to-class LockWeaponCreate --new onBuildComplete` for 0x004B8CC9
     (`BfmeThing940G::bfmeGo940G`, BfmeConv940.cpp). The body is
     `CreateModule::onBuildComplete(); getObject()->setWeaponLock(slot, 2)` with `this` at +0x10.
   - `xfer`: an ICF twin at 0x004851E3 (shared with AnnounceBirthAndDeathBehavior,
     SupplyCenterCreate, SupplyWarehouseCreate).
   - `GetSnapshotName`: 0x004B8C38 is the scaffold `?Rva004B8C38Get@@YAHXZ` (ConstIntGetters4.cpp,
     approved C into LockWeaponCreate.cpp): `add_match.py --replace-rva`, as 1a7053eb7cd did for
     CreateModule.
   - `getModuleNameKey`: the row is the static `?rva004B8C57@LockWeaponCreate@@SA...`; no rename
     mode respells a static as a virtual. Retail slot 4 holds it, so it must stay declared.
   - `loadPostProcess`: slot 1 is 0x00497805 (`jmp 0x0058B03E`), so inheriting CreateModule's
     row is runtime-equivalent.
