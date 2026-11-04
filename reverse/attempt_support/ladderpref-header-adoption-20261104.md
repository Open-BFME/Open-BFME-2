# LadderPref header adoption, 2026-11-04

Inspected base: `c3dbd860c8e7630e453224c2c6ab56c4b3c1a26a`.
Scope: the three remaining `LadderPref` header-queue units. This is
header debt retirement, with no source moves or new census claim.

## Changes and evidence

- `AptOnlineQuickMatch.cpp`: replace the private class with
  `GameNetwork/LadderPref.h`, preserving the inline default constructor used
  by the recent-ladder temporary. A plain header swap failed the row at
  `0x005BBF15`; retaining the constructor body restores all 39 matched rows.
- `UserPreferences_LadderPreferences_addRecentLadder.cpp`: use the canonical
  `LadderPref` and `UserPreferences` headers, preserve member assignment and
  destruction as inline definitions, and remove unused donor includes, views,
  static helpers and unrelated preference keys. The old include cohort
  collided with the canonical string definitions. All 5 rows still match.
- `LadderPrefMapSubscript.cpp`: replace the private record and old string shim
  includes with the canonical header and inline default construction and
  destruction. All 4 rows still match, including parent-bound EH funclets.

These changes retain the existing names and layouts. The donor provenance of
`addRecentLadder` remains Open-BFME-1 `game/GameEngine/Source/Common/UserPreferences.cpp`
at `6d943426`; donor provenance does not establish the target TU path.
No pin or alternatename is removed or added.

## Verification

- `./build.sh` on each source: 39/39, 5/5 and 4/4 matched rows, respectively;
  string, float and import checks passed for each unit.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class LadderPref` on the three sources:
  PASS for each; the tool retired exactly three `reverse/header_queue.tsv`
  entries after structural, byte and combined link checks.
- Explicit combined `link_check.py` against census `f12552d0a7`
  (2026-11-04 20:47): 3/3 link cleanly; LINKED 3,185 -> 3,185 bytes.
  Per-unit bytes: recent-ladder 177 -> 177; quick-match 2,864 -> 2,864;
  map subscript 144 -> 144. Three unreferenced MapMetaData allocator/vector
  relocation diagnostics remain nonblockers in the quick-match unit.
- `git diff --check`: passed.

LINK-230 remains open: these adoptions remove private LadderPref definitions
in this cohort, but do not verify the five outstanding donor compositions.
The remaining declaration ordering, FunctorMethod and GameSpyStagingRoom
prerequisites still require their own composition trials.
