# BuildableHeroListUpgrade ctor on the canonical UpgradeModule (2026-11-04)

Inspected revision 3fb65a79b9. Target: tu-merge of
`Code/GameEngine/Source/GameLogic/Object/Upgrade/BuildableHeroListUpgrade.cpp`
(picker draw), donor `BuildableHeroListUpgradeCtor.cpp` (0x004B8332, 49 B).

## What works (target fact, byte gate)

[`BuildableHeroListUpgradeCtor.canonical.cpp.txt`](BuildableHeroListUpgradeCtor.canonical.cpp.txt)
derives `BuildableHeroListUpgrade` from the registered
`Include/GameLogic/Module/UpgradeModule.h` with an empty ctor body (no
opaque base, no explicit `m_vtable`, no static table dummies). `./build.sh`
on it: Functions OK 1/1 matched; pre-commit gate passed. After
`tools/tu_views.py` gave both donors one superset declaration, the merge
dry run's only refusal was the link guard.

## Why it was reverted (link guard / link_check)

The compiler-emitted `??_7BuildableHeroListUpgrade@@...` tables reference
canonical slot names that have no provider:

- `?vslot07@UpgradeModule@@UBE_NXZ`: slot 7 of the +0x10 table, body
  0x00460AE2, rowed as the placeholder `?get@Rva00460AE2ByteChase32Field@@QBEEXZ`
  in `DynamicPortalBehaviour.cpp` (macro `BFME_DISP8_BYTECHASE_BEFORE_GETTER`,
  also referenced by name from `StatusBitsUpgradeIfEldestKindof.cpp`).
- `?processUpgradeRemoval@UpgradeModule@@MAEXXZ`: slot 15, which shares
  0x00460AD3 with slot 12 (`?performUpgradeFX@UpgradeModule@@MAEXXZ`, rowed in
  `Code/GameEngine/Source/Common/VslotSmallBodiesU.cpp`): needs a fold-proved
  provider.
- The merged TU also listed `?crc@UpgradeModule@@MAEXPAVXfer@@@Z` (the TU does
  not define `BFME_SNAPSHOT_NAME_SLOT`; the standalone ctor did not).

`link_check.py` on the standalone canonical ctor: does not link, LINKED
49 -> 0 (census 2026-11-04 22:40 at 3a95b274a2). The census-linked
explicit-store ctor was therefore kept; no source, ledger or register change.

## Next

Provide the two names (rename the 0x00460AE2 owner to `UpgradeModule::vslot07`
with the canonical class in its TU; fold-prove `processUpgradeRemoval` onto
0x00460AD3), then re-apply the canonical ctor, `tu_views.py`, and the merge.
Related: LINK-218 (UpgradeMux slot providers), LINK-246 (UpgradeModule
provider closure for LocomotorSetUpgrade).
