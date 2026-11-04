# TU evidence gap 0x003B1820..0x003B23A5 (2026-11-04, claudeb2)

Served by `next_work.py` (TU evidence, 7 rows in 6 sources without a signal).

## Target facts (ledger and tu_map at 4ee23edebd)

- 0x003B18F4..0x003B2389 is a contiguous run of about 30 rows whose ledger names are
  Zero Hour definitions from `Common/UserPreferences.cpp`, among them intAsStr, realAsStr,
  boolAsStr, the UserPreferences ctor/dtor/load/write/get*/set* methods, IgnorePreferences
  ctor/dtor/getIgnores and deleteFileInGlobalDataDir. Their own Z, S and N signals agree on
  `Code/GameEngine/Source/Common/UserPreferences.cpp`.
- `tools/tu_map.py` marks every one of these rows `displaced`, because that TU's main
  cluster is chosen at 0x00535781..0x00537C3F (106 approved rows, all by S).
- Those 106 rows are address-named placeholders, `?rva0053xxxx@UserPreferences@@...`.
  Their notes describe profile stat accessors: Wins, WorstLossStreak,
  StructuresCreatedRTS, BattlesWonRTS, ResourcesGatheredRTS, AverageGameTurns,
  Honors, LossesVs<faction> and ProfileCreatedDate. Each goes through the
  getInt/setInt virtual slots (0x18, 0x28, 0x2C).
- The same address block holds the BFME2-only ProfilePreferences,
  StrategicStatsPreferences and RealTimeStatsPreferences ctors, loaders and deleters
  (0x00535762, 0x00537D33..0x00537E60).

## Inference (not proven)

The 106 accessors belong to the stats-preferences TU, not to class UserPreferences. Their
placeholder class `UserPreferences` makes S, the ZH site of `UserPreferences::`, fire on
them. That outvotes the Z-anchored 0x003B block in `build()`'s cluster choice,
`max(clusters, key=hard count, ...)`.

## Next step

1. Re-identify the 0x0053 accessors' class through `tools/rename.py` (docs/naming.md).
   Prove `this` from the callers: a ProfilePreferences, StrategicStatsPreferences or
   RealTimeStatsPreferences object.
2. Once those rows no longer read as `UserPreferences::`, rebuild the map in memory
   (`tu_map.py --dir`). The 0x003B block should become UserPreferences.cpp's main cluster,
   and the C brackets may then reach 0x003B1820..0x003B18F3 and 0x003B238A.

Do not edit tu_map.py's cluster rule for this: the misattribution is in the ledger names.
