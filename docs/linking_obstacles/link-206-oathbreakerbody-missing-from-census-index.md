### LINK-206: OathbreakerBody is absent from the census index used by LinkGuard
Status: Blocked. Updated: 2026-11-04; inspected revision: 44e9b309d9.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp` and `OathbreakerBodyAttemptDamage.cpp`; [scoped dry-run evidence](../../reverse/attempt_support/oathbreaker-body-linkguard-20261104-codex.md).
Completed: current-input planner and eligible-TU checks passed; the merge dry-run made no changes.
Remaining / next check: LinkGuard reported that census-linked `OathbreakerBody.cpp` is missing from its census index and blocked the trial. Retry after the index or guard inputs change; preserve the existing canonical `BehaviorModule` header-adoption prerequisite.
Clearance: pending; no merge or consumer-binding verification was possible.
Census confirmation: not claimed.
