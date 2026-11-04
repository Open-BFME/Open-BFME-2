# ToggleMountedSpecialAbilityUpdate constructor reconciliation

Target: `Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdate.cpp`
and its `ToggleMountedSpecialAbilityUpdateCtor.cpp` donor, before consolidation.

## Target evidence and change

The existing constructor calls `??0Rva0044EF5E@@QAE@PAVThing@@PBVModuleData@@@Z`
at RVA 0x0044EF5E, whose ledger provider is `Rva0044EF5EFinish.cpp`.
The semantic SpecialAbilityUpdate constructor spelling has no compiled provider;
changing that call's identity byte-matched but failed the link preview and was
reverted. Keep the existing provider identity rather than adding a pin or alias.

The two leaf declarations now agree on the inherited prefix through +0x88,
the slot pointer at +0x88 and the flag at +0x8C. These are reconstructed views,
not proof of a recovered donor layout or original declaration. The existing
SpecialAbilityUpdate view remains available for its explicitly qualified call.
The constructor retains its original store sequence, using explicit interface
slot writes for the secondary vptrs.

Composition hoisted the standalone intrinsic pragma above the declaration of
_ReadWriteBarrier, making VC emit an external call in the merged constructor.
Grouping declaration and pragma inside one extern-C block preserves their order;
the composed constructor then byte-matches. No hatches or provider aliases were
added or removed, and the seed's existing alternatename remains intact.

## Verification (2026-11-04)

- `./build.sh` on seed and constructor: 18/18 code rows exact, both string rows
  and both float rows exact (`build/toggle-mounted-final-reconcile-build.log`).
- Frozen-source checks: all defined functions matched in both sources.
- Class gate and `git diff --check`: pass.
- `link_check.py` on both sources: 2/2 link cleanly; predicted census-linked
  bytes 1,559 -> 1,559 (index 2026-11-04 12:23 at 40fe1783d7). This is a local
  prediction, not a new census measurement.
- `tu_skeleton.py --merge ... --dry-run`: accepts seed and constructor together,
  18 rows, with census link guard passing. Scratch report:
  `build/toggle-mounted-final-dry-run.log`.

## Remaining scope

The module-data constructor still fails composition because the selected
module-data view lacks its explicit declaration (C2600); the module-data deleter
still fails byte verification. They remain separate. Mixed rows in
`Object/Rva004ADB1BLerp.cpp` and `Update/ModuleUpdateDtors.cpp` are untouched.
The next action is the tool-driven seed/constructor merge, carrying six data
ledger keys and the hatch ownership without retiring debt.
