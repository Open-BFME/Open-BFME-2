### LINK-211: census-linked units are absent from the index used by LinkGuard
Status: Blocked. Updated: 2026-11-04; inspected revision: 5aa18aaf53.
Evidence / affected units: `OathbreakerBody.cpp` and `OathbreakerBodyAttemptDamage.cpp`; `Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp`; [Oathbreaker scoped dry-run](../../reverse/attempt_support/oathbreaker-body-linkguard-20261104-codex.md), [DelayedDeathBody dry-run](../../reverse/attempt_support/delayed-death-body-linkguard-20261104-codex.md).
Completed: current-input planner and eligible-TU checks passed for both trials; neither dry run changed files or accepted donors.
Remaining / next check: LinkGuard reported the census-linked destination missing from its census index for both OathbreakerBody and DelayedDeathBody. Retry after the index or guard inputs change. OathbreakerBody also retains its canonical `BehaviorModule` header-adoption prerequisite.
Clearance: pending; no merge or consumer-binding verification was possible.
Census confirmation: not claimed.
