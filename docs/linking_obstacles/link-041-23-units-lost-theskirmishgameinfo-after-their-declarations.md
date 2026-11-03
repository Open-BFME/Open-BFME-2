### LINK-041: 23 units lost `TheSkirmishGameInfo` after their declarations were respelled `GameInfo *`

**Status: Repair landed, awaiting census. Updated: 2026-10-26; inspected revision: 35efd22768.**

- **Evidence / scope:** the census at d1f046749a (97.47 %, after 98.11 % at 47e030bafc)
  lost 33 units. 23 of them (71,793 B, led by `GameLogicInit.cpp` 28,160 B and
  `GameEngineInit.cpp` 9,424 B) have one unresolved name,
  `?TheSkirmishGameInfo@@3PAVGameInfo@@A`. 3a8ff9f8e0 respelled their declarations
  `extern GameInfo *TheSkirmishGameInfo;` to match the data ledger's provisional name for
  0x00A02EF0, but the only definition is `SkirmishGameInfo *TheSkirmishGameInfo` in
  `SkirmishGameOptionsMenu.cpp` (`?TheSkirmishGameInfo@@3PAVSkirmishGameInfo@@A`), the type
  Zero Hour's and BFME 1's `GameInfo.h` declare.
- **Completed:** 3a8ff9f8e0 reverted (`Recorder.cpp` by hand, since files were merged into it
  afterwards). `./build.sh` 728/728 rows across the 23 units; `tools/link_check.py` against
  the d1f046749a index: 23/23 link, 0 -> 71,793 B.
- **Current-input follow-up (2026-10-26, `ff4455c2af`):** the default picker
  served `SkirmishPreferencesLoad.cpp`, whose unchanged current source already
  previews LINKS against the 19:02 index at `5ce093a71a` (299 authored
  nonpadding bytes). All six rows / 342 ledger bytes and its one EH graph pass;
  every defined function is matched. This confirms the existing repair for
  that consumer, without a new source repair or census gain. See
  [the bounded check and reference comparison](../../reverse/attempt_support/bfme1-reference-4fa9d591-20261026/readme.md).
- **Remaining / next check:** the ledger row at 0x00A02EF0 is derived and provisional (it
  lists both spellings); regenerate it with `tools/data_ledger.py` so it names the defined
  `SkirmishGameInfo *` spelling, rather than respelling consumers to its current name. The
  census's other 10 lost units (3,997 B: `GameFont.cpp` 1,758 B, `statistics.cpp` 986 B, five
  `WW3D*` units, `CrateSystem.cpp`, `MultiplayerSettings.cpp`,
  `MultiplayerColorDefinitionCopy.cpp`, `GapBodiesGE41_Rva00118610.cpp`) have other causes
  and were not investigated here.
- **Recheck (2026-10-26, HEAD 8f71fe0657):** the census at 5ce093a71a still lists the 23
  units, but it predates the revert (f598ec4226 is not its ancestor; its tree still spells
  `extern GameInfo *TheSkirmishGameInfo;` in ten `Common/` units), so it is not evidence
  against the repair. No `Code/` declaration spells `GameInfo *` at HEAD, and
  `link_check.py` against that census previews `Rva005216A6.cpp` 0 -> 37 B and
  `SkirmishPreferences.cpp` 0 -> 2,175 B. The data-ledger step above is not a link
  prerequisite: `link_census.data_ledger()` reads `reverse/data_rows.csv`, which since
  e40a67706e holds the matched `?TheSkirmishGameInfo@@3PAVSkirmishGameInfo@@A` row at
  0x00E02EF0; `reverse/data_ledger.csv` is a derived register that needs every matched
  object built to regenerate (`data_ledger.py --check`: 1,037 sources without objects here).
- **Census confirmation:** awaiting the next census.
