# TeamPrototype canonical header in six Player consumers

Base: `de3005f265`. The six consumers are PlayerAddScience.cpp,
PlayerKillPlayer.cpp, PlayerRva002AD93A.cpp, PlayerSetObjectsEnabled.cpp,
PlayerTransferAssets.cpp and PlayerUpdate.cpp under
`Code/GameEngine/Source/Common/RTS/`.

Each replaces its private TeamPrototype declaration with Common/Team.h.
The existing iterator body remains an inline out-of-class definition against
canonical m_dlinkhead_TeamInstanceList, matching the established pattern in
TeamPrototypeFindAndCountInstances.cpp. A declaration-only iterator changes
code generation; preserving its body is required by these consumers.
The shared header, other classes and source paths are unchanged.

Verification:

- Normal `./build.sh` over the six consumers passes 21/21 function rows,
  four renumbered funclet checks through parent EH data, 13 literals,
  float and import checks. Declared-unmatched checks pass before and after.
- One `header_adopt_lane.py accept --class TeamPrototype` over all six
  passes and retires exactly six rows through the owning tool. The other
  19 selected cohort consumers remain untouched with their existing queue
  entries; automatic trials were fully restored.
- Combined ordinary `link_check.py` preview: 6/6 LINKS and 2,948 -> 2,948
  authored linked bytes against census f44cbcf5b0, 2026-11-05 15:19 UTC.
  Per-unit bytes: 505, 499, 393, 145, 1,045 and 361 respectively.
- Original-object comparison finds no removed external definition in any
  changed unit. All 186 external COMDAT copies retain their symbol sets
  and normalized digests. PlayerUpdate's initial cached object predated an
  upstream freelist-global migration; rebuilding its HEAD source through
  the normal build and then rebuilding the adoption confirms equality.
  No alias, data definition or provider is removed.
- `git diff --check` passes. No source-path move requires a tooling audit.

This clears these six header-debt entries only. Wider Team.cpp consolidation
still needs its recorded class/layout prerequisites; no census, real-link or
runtime gain is claimed.
