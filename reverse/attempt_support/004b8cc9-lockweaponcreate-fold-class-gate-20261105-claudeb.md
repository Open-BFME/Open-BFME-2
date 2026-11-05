# LockWeaponCreate.cpp real link: where the `~CreateModule` fold stops now (2026-11-05, seat claudeb)

Follows `004b8c0e-lockweaponcreate-canonical-view-20261105.md`. No source changed for this step.
Landed alongside it: d0e5bccac9 folded `Rva004B8C3E` into `LockWeaponCreate` (0x004B8C3E dtor,
0x004B8CAD deleting dtor).

## Step 1 of the earlier order is done

`86cd001293` (rename.py: accept a destructor whose own stores died under an inlined base
destructor) clears the false reject. `rename.py class --fold Rva004B8CDE --into CreateModule
--dry-run` now passes `fold_evidence` and stops on the next check:

    refused: CreateModule is registered in reverse/canonical_classes.csv: the fold would turn
    Code/GameEngine/Source/Common/Rva004B8CDEDerived.cpp, .../TailJumpWrappers5B.cpp,
    .../TailJumpWrappers5B_~Rva002563CE.cpp's class Rva004B8CDE into a private copy of CreateModule

The fourth declarer is CreateModule.cpp, which holds the Zero Hour view and the opaque `Rva004B8CDE`.

## Why "adopt the header first" cannot be done before the fold

- Each declarer defines a body that tail-calls `??1Rva004B8CDE@@UAE@XZ` (0x004B8CDE). Adopting
  `CreateModuleClass.h` there respells that call `??1CreateModule@@UAE@XZ`, which no row names
  until the fold. The byte gate resolves relocations only through ledger names.
- `plan_fold` takes `--prepared` only for a nested NEW (rename.py: "a global NEW is a token
  rewrite"). A registered global NEW therefore has no path. Tool change needed: accept
  `--prepared` for a registered global NEW. Every unit that spells OLD must then come prepared,
  on the canonical header and spelling OLD nowhere. The nested-NEW branch already does this.

## What the prepared units then need (structural inference, not yet compiled)

- In `Rva004B8CDEDerived.cpp`, `X : public CreateModule { virtual ~X(); }` gives each of the 7
  destructors the retail shape: stores at +0, +0x0C and +0x10, then `jmp ~CreateModule`. The 7
  `?f2@*_B2@@UAEXXZ` alternatenames become unreferenced. Prove that across all objects before
  dropping them.
- Those destructors emit the canonical tables, which reference `CreateModule` virtuals no row
  names yet: `?loadPostProcess@CreateModule@@MAEXXZ` and `?GetSnapshotName@CreateModule@@MBEPBDXZ`
  (there is no row or pin for either). They also reference the inline `getCreate` /
  `onBuildComplete` / `slot02` / `shouldDoOnBuildComplete` COMDATs.
  `?loadPostProcess@BehaviorModule@@MAEXXZ` is rowed (0x000B3FD0). Without rows for those two
  names, the unit stops linking, and the pre-push link audit refuses that loss.
  `InheritUpgradeCreate.cpp` avoids emitting the tables only through `novtable` plus static vptr
  stand-ins; that is not a model to copy.
- So the provider rows come first: `CreateModule::loadPostProcess` (an ICF twin at the
  0x0058B03E fold, as `DamageModule::loadPostProcess`) and `CreateModule::GetSnapshotName` (slot 2
  of CreateModule's own table 0x00C59368). Then the prepared fold. Then LockWeaponCreate's
  dtor rows move home into LockWeaponCreate.cpp (approved C), and finally
  `function --to-class LockWeaponCreate` for 0x004B8CC9 / 0x004B8C38.

## Why not keep the dtor rows in Rva004B8CDEDerived.cpp

`--to-class` (`to_class_slot_problems`) needs every installer unit of the table to compile a
`LockWeaponCreate` table that agrees with retail and names the new member in the slot. The
opaque view there has one virtual per base, so it cannot name slot 2 of 0x00C592FC
(GetSnapshotName). For 0x00C592EC it agrees on no slot: `?f2@Rva004B8C3E_B2@@UAEXXZ` is no
row. A slot-agreeing private view there would be an invented copy of CreateModuleInterface.
