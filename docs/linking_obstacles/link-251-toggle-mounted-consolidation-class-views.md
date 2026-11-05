### LINK-251: ToggleMountedSpecialAbilityUpdate consolidation needs compatible lifetime views
Status: Blocked. Updated: 2026-11-04; inspected revision: `4ee23edebd`.
Scope: `ToggleMountedSpecialAbilityUpdate.cpp` and its constructor, ModuleData constructor and deleting-destructor donors; dry run accepts zero donors.
Completed / next: canonical Player adopted and one header debt row retired; reconcile the incompatible bases, anonymous union, novtable spelling and member initialization before retrying consolidation.
Evidence: [current trials, repair verification and remaining checks](../../reverse/attempt_support/toggle-mounted-player-adoption-20261104.md).
Clearance: consolidation pending; no source files removed and no census gain claimed.

2026-11-05: Thing adoption retires one header row (18/18 exact, preview LINKS); noinline does not emit the missing deleting destructor under novtable, and removing novtable adds a non-retail vptr store. Both trials reverted; reconcile lifetime emission before another merge. [Evidence](../../reverse/attempt_support/toggle-mounted-thing-lifetime-20261105-codex5.md).
