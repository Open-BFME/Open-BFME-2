# SiegeDeploy transfer: current-receipt batch audit, 2026-11-04

The source consolidation and remaining composition prerequisites are in
[the merge handoff](siegedeployspecialpower-consolidation-20261104.md).
The runner has accepted the reconciliation and merge commits for publication;
their subjects identify them across the fleet publisher's rebases.

After the merge, the first `link_batch_audit.py --base origin/master --tip HEAD
--sources-from build/siege-recovery/verified-sources.nul` returned 2: the TU
lacked a strict reusable receipt. The explicit source list contained only
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPower.cpp`.

`link_check.py --prepare-current` for that single TU then passed: one provider
has a strict reusable compiler receipt, with all 20 code rows, one data row,
two strings, three floats and five renumbered EH funclets verified. This mode
changed no census, index or status and compiled no additional provider.

The justified retry inspected merge revision `ad070ea612` and outgoing base
`173e734df9`, against the 2026-11-04 17:56 index at `8c757ea0db`. It returned 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 8c757ea0db, outgoing base origin/master; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

This is the same wider-consumer boundary already recorded by the SiegeDeploy
pool-key entry. Do not claim external consumer clearance, a link regression,
or a census-linked-byte gain from this audit. Carry the absorbed transfer donor
and composed provider into the next scheduled census. No maintainer-only
measurement or unrelated consumer reconstruction was started.
