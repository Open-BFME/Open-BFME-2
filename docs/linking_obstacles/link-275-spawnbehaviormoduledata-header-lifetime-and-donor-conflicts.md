### LINK-275: SpawnBehaviorModuleData header lifetime and donor conflicts
Status: Open. Updated: 2026-11-04; inspected revision: `4db5a76637`.
Completed: three SpawnBehavior consumers adopt the canonical header; acceptance retires three queue rows; ordinary previews preserve 1,249 linked bytes.
Remaining / next check: reconcile FamilyDeletingDtors vtable emission, ModuleFactoryInit donor ModuleData conflict, and constructor/destructor vector and base lifetime representation; four queue rows remain.
Evidence: [scoped checks and remaining diagnostics](../../reverse/attempt_support/spawnbehaviormoduledata-header-20261104.md).
Clearance: the three adopted consumers pass byte and link checks; lifetime/factory scope remains open. Census confirmation: not claimed.
