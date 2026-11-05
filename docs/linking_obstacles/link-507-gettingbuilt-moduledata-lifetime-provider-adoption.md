### LINK-507: GettingBuiltBehaviorModuleData lifetime-provider header adoption

Status: Open for three queued units; two consumers accepted on 2026-11-05 at base `a83333646ee7f2d2bb527a6d991f8415f805d590`.
Completed: GettingBuiltBehavior.cpp and GettingBuiltBehaviorResume.cpp use the canonical header; 34/34 rows match, acceptance retires two queue keys, and current-object previews retain 2,342/2,342 census-linked bytes.
Remaining / next check: reconcile the ctor/dtor base includes and ObjectFilter special-member identity before preserving their member cleanup/EH graph; audit provider/table consumers together. ModuleFactoryInit retains the base-header prerequisite in LINK-467. The ctor's wrong ThingRef callee remains unpinned.
Evidence: [consumer checks and lifetime-provider prerequisites](../../reverse/attempt_support/gettingbuilt-moduledata-adoption-20261105-codex3.md).
Clearance: two consumer adoptions verified; constructor, destructor and factory remain queued. Census confirmation: no new census claimed.
