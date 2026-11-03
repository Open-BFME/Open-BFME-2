### LINK-151: FlightDeckBehavior.cpp's override drop made its FlightDeckInfo copies the kept ones (2026-10-29)

Status: repaired, pending census confirmation. 540ec8bf62 dropped
FlightDeckBehavior.cpp's `-G7 -arch:SSE` flag override as stale
(flag_defaults.py: both rows keep matching under the region default). The
unit's rows are 35 B, but the whole TU now compiles under the region default,
and every one of its 941 COMDAT copies changed digest. The unit's lowest row
(0x0008A64A) puts it ahead of the rowed FlightDeckInfo helpers. Its new
`_Construct<FlightDeckInfo>` (22 B `rep movsd`; retail 0x00626E10 is 47 B of
field moves) and `__uninitialized_copy<FlightDeckInfo *>` copies became the
kept ones. Its `_Vector_base<FlightDeckInfo>(const allocator &)` copy no longer
matches FlightDeckInfoVectorInsertOverflow.cpp's. So partitionmanager_impl.cpp
(2,620 B, which owns both helper rows) and FlightDeckInfoVectorInsertOverflow.cpp
(441 B) stopped linking: wrong_selected and a first-copy COMDAT loser.
Repair: FlightDeckBehavior.cpp declares those three templates without a body,
next to its existing declaration-only FlightDeckInfo growth path. It now
references the rowed copies and FlightDeckInfoVectorInsertOverflow.cpp's base
constructor (2/2 rows exact). Five COMDATs leave the object: the three, the
proxy constructor and the allocator copy constructor; each keeps another
provider. `link_check.py` on the unit, the index consumers of those names and
every source changed since the census predicts LINKS for both victims (441 and
2,620 B again), with no other unit changing.
Open: the rest of the TU still compiles differently from the census. Restoring
the override would return it to its census-time code, but that is a flag change
(full gate). SlowDeathBehavior.cpp and MultiplayerSettings.cpp lost the same
override in that commit; neither links yet.

2026-10-30 header follow-up: partitionmanager_impl.cpp already previews LINKS
before this cleanup. Its local `ceil`/`floor` declarations now come from the
toolchain headers, retaining retail's indirect IAT calls. Its FlightDeckInfo
release helpers explicitly use the existing GameMemory provider at RVA
`0x00030830`, matching the native growth call. All 13 rows and strict preparation
pass. The 93 external COMDAT bodies retain their bytes; four change only the
release relocation identity. Paired preview retains 2,620 and 441 authored bytes.
The seven-source outgoing audit remains INCONCLUSIVE: its index predates base
`3ff66d3dd92a`, and two earlier batch sources lack current strict receipts,
first AptPlayerStatusDtor.cpp. Full consumer selection/loss verification and
census confirmation remain open; no linked-byte gain is claimed.
[Target facts and remaining header debt](../../reverse/attempt_support/partition-math-headers-20261030-codexb4.md).

2026-10-30 allocator follow-up (`46af8b351c90`): replace PartitionManager's
remaining `free` macro with explicit vector allocator specializations. All 13
rows and strict preparation pass; all 93 external COMDAT bodies, relocation
fingerprints and external symbols are unchanged. The owning header auditor
retires the file's last queued finding. Three unresolved include inventory
notes remain. The paired preview retains 2,620 and 441 authored bytes against
`12b9e7a7c0`; wider consumer verification and census confirmation remain open.
[Scope and checks](../../reverse/attempt_support/partition-allocator-release-20261030-codexb5.md).
