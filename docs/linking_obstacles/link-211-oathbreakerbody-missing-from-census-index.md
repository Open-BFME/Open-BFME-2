### LINK-211: census-linked units are absent from the index used by LinkGuard
Status: Blocked. Updated: 2026-11-05; inspected revision: 463674729a.
Evidence / affected units: `OathbreakerBody.cpp` and `OathbreakerBodyAttemptDamage.cpp`; `Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp`; [Oathbreaker scoped dry-run](../../reverse/attempt_support/oathbreaker-body-linkguard-20261104-codex.md), [DelayedDeathBody dry-runs](../../reverse/attempt_support/delayed-death-body-linkguard-20261104-codex.md) and [current compile blockers](../../reverse/attempt_support/delayed-death-body-consolidation-20261105-codex.md).
Completed: current DelayedDeathBody allocation and planner checks passed; dry run accepted no donors and exposed missing constructor and `xfer` declarations/members in two pull donors. Current LinkGuard output lists the three census-linked units but did not reproduce the prior missing-index diagnostic.
Remaining / next check: A source/header owner must reconcile the DelayedDeathBody declarations and members; rerun the merge dry run and inspect LinkGuard after that repair. OathbreakerBody also retains its canonical `BehaviorModule` header-adoption prerequisite.
Clearance: pending; no merge or consumer-binding verification was possible.
Census confirmation: not claimed.
