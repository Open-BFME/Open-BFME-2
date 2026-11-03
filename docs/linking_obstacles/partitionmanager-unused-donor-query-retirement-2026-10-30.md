### PartitionManager unused donor-query retirement (2026-10-30)

Remove four debug-only legacy query entries (iterateAllObjects, tryPosition,
getMostValuableLocation and getNearestGroupWithValue), plus their private
cellValueProc callback/declaration/parameter struct. The callback's only live
address reference belonged to the removed nearest-group query. Retire four
existing marker keys with the bodies. No native body or retail dead stripping
is claimed. The four source rows, 549 retained code definitions and 31 retained
parent EH graphs are unchanged; only two removed-parent EH graphs, their
SafeSEH entries, five naturally unused helpers and the exclusively owned
99999.0 literal disappear. Parent ownership is proven by COFF associations.

Fresh controls retain the 35-byte native coordinate owner before Partition
and the identical seven-byte AI getter. Both remaining enum-getter copies
are current and debug-only; their dword+0x0C shape differs from the removed
byte+6 copy, so no equivalence/native identity is claimed. The five-source
preview retains 4,593 authored linking bytes and all other blockers, taking
Partition U8 -> U6. Preserve PossibleToEnter, FreeOfFog, distance dispatch,
getClosestObjects, AcceptOnSquad and contact/update users of the six remaining
names. Full-image selection/loss clearance and census confirmation remain.
[Closure, current providers and exact graph evidence](../../reverse/attempt_support/partition-unused-queries-retirement-20261030/README.md).
