# SiegeDeployHordeSpecialPower mechanical consolidation trial (2026-11-04)

Allocated TU: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp` (shard 1/5; allocation check passed). The scoped `name_lane.py consolidate` report was current, and `find_declared_unmatched.py` found no unrowed definitions.

`tu_skeleton.py --plan` found 17 approved rows, 7 donors, and one mixed donor (`ConstIntGetters4.cpp`, left untouched). The single dry run accepted no unchanged donor. It rejected:

- `SiegeDeployHordeSpecialPowerCtor.cpp`: C2511, constructor overload not declared in `SiegeDeployHordeSpecialPower`.
- `SiegeDeployHordeSpecialPowerRva004C63DE.cpp`: C2039, `Rva004C63DE` is not a member of `SiegeDeployHordeSpecialPower`.
- `SiegeDeployHordeSpecialPowerDtor.cpp`: C2600, destructor cannot be defined because the special member is compiler-generated / undeclared.
- `SiegeDeployHordeSpecialPowerXfer.cpp`: C2039, `xfer` is not a member of `SiegeDeployHordeSpecialPower`.
- `SiegeDeployHordeSpecialPowerUpdate.cpp`: C2039, `update` is not a member of `SiegeDeployHordeSpecialPower`.
- `SiegeDeployHordeInitiate.cpp`: C2509, `getModuleNameKey` is not declared in `SiegeDeployHordeSpecialPower`.

The dry run reported `blocked: no verified merge of two or more donors`; LinkGuard listed all seven inputs as census-linked. No source or ledger changes were made. Manual base/interface declarations are outside this mechanical seat; do not retry these donors unchanged. Existing obstacle `siegedeployhorde-module-data-composition-2026-10-28.md` retains its independent module-data merge record and census caveat.

## Other allocated refusal: Made002CCA37 (2026-11-04)

Allocation check passed for `Code/GameEngine/Source/GameLogic/Object/Made002CCA37.cpp`. The current scoped planner snapshot passed `--check`; the TU has 3 approved rows, 2 donor files, and no mixed files. `find_declared_unmatched.py` found no unrowed definitions. Its single dry run accepted no donor: `Made002CCA37Dot.cpp` fails with C2504 (`DamageNugget` base undefined) and C3861 (`generateDamageInfo` not found). The report requires reconciling `DamageNugget` and `Made002CCA37` views. LinkGuard lists both inputs as census-linked, then reports `blocked: no verified merge of two or more donors`. No source or ledger changes were made; manual declarations are outside this seat.

## Other allocated refusal: DeletionUpdate (2026-11-04)

Allocation check and scoped planner checks passed for `Code/GameEngine/Source/GameLogic/Object/Update/DeletionUpdate.cpp`. Plan: 12 approved rows, 4 donor files, 2 mixed files. `find_declared_unmatched.py` passed. The single dry run accepted no unchanged donor. `DeletionUpdate_calcSleepDelay.cpp` conflicts on duplicate `GameLogic` view (`GameLogicObjectLookupView.h`, C2011); `DeletionUpdatePoolKey.cpp` conflicts on duplicate `SubsystemInterface` view (C2011); `DeletionUpdateXfer.cpp` conflicts on duplicate `Xfer` and `Module` views (C2011). Both mixed files were left untouched. LinkGuard lists the TU and all three donors as census-linked and reports `blocked: no verified merge of two or more donors`. Manual private-view reconciliation is outside this seat; no source or ledger changes were made.

## Other allocated refusal: OathbreakersFadeAwayBehavior (2026-11-04)

Allocation check and current scoped planner check passed for `Code/GameEngine/Source/Common/OathbreakersFadeAwayBehavior.cpp`. Plan: 12 approved rows, 3 donors, 2 mixed files; `find_declared_unmatched.py` passed. The single dry run accepted no unchanged donor. `OathbreakersFadeAwayBehaviorCtor.cpp` fails C2511 because its `Thing *, const ModuleData *` constructor is not declared in the target class; `Rva004B89C4Update.cpp` fails C2039 because `getModuleNameKey` is not a target-class member (also C2270 on the related out-of-class definition). Mixed donors remained untouched. LinkGuard lists the target and both donors as census-linked and reports `blocked: no verified merge of two or more donors`. It recommends reconciling the target class view; this manual declaration work is outside this seat, so no source or ledger changes were made.

## Other allocated refusal: HordeMemberCollide (2026-11-04)

Allocation check and current scoped planner check passed for `Code/GameEngine/Source/GameLogic/Object/Collide/HordeMemberCollide.cpp`. Plan: 3 approved rows, one donor, one mixed file. `find_declared_unmatched.py` passed. The single dry run accepted no unchanged donor: `HordeMemberCollideOnCollide.cpp` fails C2511 because the target class does not declare its `Thing *, const ModuleData *` constructor. The mixed donor was left untouched. LinkGuard lists both target and donor as census-linked and reports `blocked: no verified merge of two or more donors`. It requires reconciling the `HordeMemberCollide` class view; manual declaration work is outside this seat, so no source or ledger changes were made.

## Other allocated refusal: RampageBehavior (2026-11-04)

Allocation check and current scoped planner check passed for `Code/GameEngine/Source/GameLogic/Object/Behavior/RampageBehavior.cpp`. Plan: 21 approved rows, 5 donor files, 2 mixed files; `find_declared_unmatched.py` passed. The dry run accepted no unchanged donor. `Rva00458AAEXfer.cpp` fails C2504 (`UpdateModule` base undefined) and C2614; `RampageBehaviorPoolKey.cpp` fails C2039 (`getModuleNameKey` absent); `RampageBehaviorModuleDataDtor.cpp` fails C2511 (module-data constructor absent); `RampageBehavior_update.cpp` fails C2039 (`update` absent). Both mixed files were left untouched. LinkGuard lists all five regular inputs as census-linked and reports `blocked: no verified merge of two or more donors`. The class views need manual reconciliation, outside this seat; no source or ledger changes were made.

## Other allocated refusal: W3DTornadoDraw (2026-11-04)

Allocation check and current scoped planner check passed for `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTornadoDraw.cpp`. Plan: 13 approved rows, 3 donors, one mixed file; `find_declared_unmatched.py` passed. The dry run accepted no unchanged donor: `W3DTornadoDraw_xfer.cpp` fails C2039 because `xfer` is not a target-class member; `W3DTornadoDrawModuleDataDtor.cpp` fails byte verification. Mixed `W3DDrawModuleDeletingDtors.cpp` was left untouched. LinkGuard lists target and both donors as census-linked and reports `blocked: no verified merge of two or more donors`; class reconciliation is recommended. Do not retry the byte-rejected donor unchanged; manual class work is outside this seat. No source or ledger changes were made.

## Other allocated refusal: SupplyWarehouseCripplingBehavior (2026-11-04)

Allocation check and current `Object/Behavior` planner check passed for `Code/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior.cpp`. Plan: 8 approved rows, one donor, one mixed file; `find_declared_unmatched.py` passed. The dry run accepted no unchanged donor: `SupplyWarehouseCripplingBehaviorCtor.cpp` fails C2511 because the target class lacks its `Thing *, const ModuleData *` constructor declaration. The mixed field-parse donor remained untouched. LinkGuard lists the target and donor as census-linked and reports `blocked: no verified merge of two or more donors`. Manual class view reconciliation is outside this seat; no source or ledger changes were made.

## Other allocated refusal: TooltipUpgrade (2026-11-04)

Allocation check and fresh `Object/Upgrade` planner check passed for `Code/GameEngine/Source/GameLogic/Object/Upgrade/TooltipUpgrade.cpp`. Plan: 8 approved rows, 3 donor files, 2 mixed files; `find_declared_unmatched.py` passed. The dry run accepted no unchanged donor. `TooltipUpgradePoolKey.cpp` fails C2509 because `getModuleNameKey` is undeclared in the target class; `TooltipUpgradeRemoval.cpp` fails C2504 (`UpgradeModule` base undefined) and C2011 (duplicate `Drawable` view). Both mixed files were left untouched. LinkGuard lists target and both donors as census-linked and reports `blocked: no verified merge of two or more donors`. The target class view needs manual reconciliation; no source or ledger changes were made.

## Verified merge: W3DFloorDraw (2026-11-04)

Allocation and scoped planner checks passed for `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DFloorDraw.cpp`; `find_declared_unmatched.py` passed before and after. The dry run accepted exactly the destination plus `W3DFloorDrawXfer.cpp` and `W3DFloorDrawPoolKey.cpp` (24 rows), rejecting the constructor on undeclared `m_10`/`m_10` helper identifiers, and the dtor/draw-module donors on missing declarations. Seven mixed files were untouched. The merge tool applied only those accepted donors, carried two data-ledger rows, and LinkGuard listed all six census-linked units (destination plus five donor objects); it did not report a link refusal.

`./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DFloorDraw.cpp` passed: 24/24 matched rows, four funclet pins, STLport fold, string/float/import refs. `find_declared_unmatched.py` passed. `tu_ownership.py --staged --shadow` passed. Shadow audits surface existing/remaining identity concerns in the moved composition: `code_identity_gate.py --staged` reports duplicate `?size@Rva000CF0FF@@QBEHXZ`; `data_check.py --staged` reports duplicate `_DRAWABLE_FRAMES_PER_FLASH` at `0x009EBBD4` and wrong-name `$S3@?1??getModuleNameKey@W3DFloorDraw...` and `_DRAWABLE_FRAMES_PER_FLASH` at `0x009EBBD0`/`0x009EBBD4`. No identity debt was retired or claimed clean. Reconcile those findings in the identity/data lanes.

Path-consumer audit for this batch and the pending WeaponSet move range searched the old donor basenames through `tools/`, `.githooks/`, `.github/`, `Code/`, and `docs/`; active result was the doxygen target entry only (merge tool retains/repoints it), plus historical donor comments in composed sources. No manual consumer change was required. The pre-push `link_batch_audit.py` remains the authoritative changed-provider/consumer check and is pending the publication hook; no census gain is claimed. The full outgoing range is `origin/master..HEAD` plus these staged W3DFloorDraw paths; upstream has advanced by four commits, and `/opt/runner/publish` will rebase and run the hook.
