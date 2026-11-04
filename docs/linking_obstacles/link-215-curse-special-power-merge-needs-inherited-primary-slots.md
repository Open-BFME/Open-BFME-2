### LINK-215: CurseSpecialPower merge needs inherited primary slots
Status: Blocked. Updated: 2026-11-04; inspected revision: 0201cbc134.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Update/CurseSpecialPower.cpp` and `SpawnPointProductionExitUpdateCtor.cpp`; [trial and native slots](../../reverse/attempt_support/curse-special-power-consolidation-20261104.md).
Completed: reconciled the pool-key owner's opaque base view; five code bodies, one data row and EH remain exact; source link preview retains 153 census-linked bytes.
Remaining / next check: recover primary slots 1-3 and their provider identities; the merge currently emits getModuleNameKey at slot 1 instead of native slot 4 and is refused for first-selected `??_7CurseSpecialPower@@6B@`.
Clearance: pending; donor retained and no merge applied.
Census confirmation: no new measurement claimed.
