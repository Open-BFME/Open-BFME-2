### LINK-440: InheritUpgradeCreate donors lack matching class declarations
Status: Blocked. Updated: 2026-11-05; inspected revision: 463674729a.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Create/InheritUpgradeCreate.cpp` and its ctor, xfer, module-data ctor and OnBuildComplete donors; [allocated consolidation dry run](../../reverse/attempt_support/inherit-upgrade-create-consolidation-20261105-codex.md).
Completed: allocation, scoped planner and TU plan passed; dry run accepted no donors because class declarations and base views disagree. LinkGuard lists the destination and all four donors as census-linked.
Remaining / next check: reconcile the `InheritUpgradeCreate` and module-data declarations, including the reported `CreateModule` and member-view prerequisites; rerun the supported merge and provider/consumer checks.
Clearance: pending; no merged object or consumer-binding verification was possible.
Census confirmation: not claimed.
