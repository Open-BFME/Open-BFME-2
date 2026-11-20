### LINK-438: Snow consolidation private base prerequisites
Status: Open. Updated: 2026-11-05; inspected revision: 0cf7c10a0b.
Completed / next: Canonical Overridable adoption retires one header row; canonical subsystem slots enable the applied Snow_Unresolved.cpp -> Snow.cpp merge. Ten code rows, one data row, EXACT destructor EH, provider/callee preservation and the 1,118-byte link preview pass. Next reconcile the remaining WeatherSetting donors' distinct base/special-member prerequisites. [Evidence](../../reverse/attempt_support/snow-consolidation-20261105-codex5.md).
Clearance: seed header adoption and lifetime-donor composition verified; remaining donors and census confirmation pending.

2026-11-20, base `179f73d302`: WeatherSettingAssign.cpp now uses canonical
Overridable for its first base rather than a private
FXParticleSystem::StreakDrawModuleTemplate. Constructor 0x00201618 and
destructor 0x0020182B independently establish that base; assignment's native
first call is 0x001FD28E, where both names already have rowed providers.
The complete 345-byte assignment still matches, including the null-checked
secondary-base adjustment. Scoped link prediction stays 345 -> 345 against
the stale `b2ee5962a6` index; no real-link improvement is claimed.

The four donors still require reconciliation of secondary-base identity,
special-member declarations and full member storage. Parser composition also
fails on declaration ordering. The current read-only planner and merge dry
run accept zero donors; correcting the first base alone is not a completed
TU merge.
