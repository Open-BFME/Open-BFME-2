### LINK-467: AttributeModifierAuraUpdateModuleData header adoption prerequisites

Status: Open for four queued units; two consumers accepted on 2026-11-05 at base `0724c901648b5adec4dce7288eb4386718729f95`.
Completed: AttributeModifierAuraUpdate.cpp and UpgradeMuxSlotOverrides.cpp use the canonical header; 32/32 rows match, acceptance retires two queue keys, and the current-object preview retains 1,860/1,860 census-linked bytes.
Remaining / next check: reconcile ModuleFactoryInit's ModuleData include chain, the ctor's layout-discovery C1001, the dtor's typed vector versus opaque storage, and the deleting-dtor holder's synthetic ctor; audit table consumers before changing providers (LINK-177).
Evidence: [cohort results and verification scope](../../reverse/attempt_support/attribute-aura-moduledata-adoption-20261105-codex3.md).
Census confirmation: no new census claimed; unchanged four units retain their header debt.
