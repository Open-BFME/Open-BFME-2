### LINK-433: PlayerUpgradeSpecialPower merge needs derived virtual and data destructor contracts
Status: Blocked. Updated: 2026-11-05; inspected revision: `42fef5c787`.
Evidence / affected units: PlayerUpgradeSpecialPower.cpp, PlayerUpgradeSpecialPowerDoSpecialPower.cpp and PlayerUpgradeSpecialPowerModuleDataDtor.cpp; [repair and verification](../../reverse/attempt_support/player-upgrade-special-power-20261105.md).
Completed: canonical interface/base adoption retires one header-queue row; 11/11 changed-source rows match; both changed units predict clean linking (408 bytes retained).
Remaining / next check: establish the derived doSpecialPower declaration's virtual/provider contract (tu_views reverts its external-symbol change), then reconcile the data constructor/destructor novtable mismatch; merge still accepts zero donors.
Clearance: header adoption accepted for the action donor only; TU consolidation remains blocked.
Census confirmation: awaiting; local predictions do not change the headline.
