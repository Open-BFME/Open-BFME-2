# WorldHeightMap lookup header adoption, 2026-11-04

Inspected checkout `12e41325a1` after rebasing onto upstream `50c527824d`.
Claim owner: `yasinschroeder-codex4`. The supported consolidation planner and
fresh in-memory TU map selected
`Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp`.

## Completed scope

- `Code/GameEngine/Source/Common/WorldHeightMapGetTerrainNameAt.cpp`:
  `?getTerrainNameAt@WorldHeightMap@@QAE?AVAsciiString@@MM@Z`, RVA `0x000AEC4E`, 224 bytes.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva000AC4C6Finish.cpp`:
  `?rva000AC4C6@WorldHeightMap@@QAEHH@Z`, RVA `0x000AC4C6`, 78-byte extent.

Both consumers now include the existing canonical WorldHeightMap header instead
of defining private copies. No header, function identity, ledger extent, pin or
compiler flag changed. `header_adopt_lane.py accept --class WorldHeightMap`
passed both sources and retired their two header-queue rows through that lane.

Target facts already documented by the canonical header establish allocation
size `0x120F0`, the RefCountClass prefix and the third virtual slot via callback
`0x000AF012`. Its count at `+0x80C8` and neutral aggregate at `+0x80CC` support
these two existing lookup projections. The interval lookup keeps result/start/
extent at record offsets 0/4/8 with stride `0x28`. The terrain-name projection
starts four bytes later, preserving its firstTile/numTiles/AsciiString accesses.
These are target access facts, not recovery of a complete donor record layout;
the canonical aggregate retains its neutral name.

Scoped naming used packet `codex4-worldheightmap-header-20261104`, a native child
proposal and parent review followed by `name_lane.py scoped apply`: 11 parameter/
local bindings renamed, nine retained out of 20 inventoried bindings. The
inventory also surfaced four local-struct members; those were retained rather
than treating them as locals. Local `s` was retained after the tool reported a
macro-binding guard. Names describe operations and are recorded as inferred.

## Verification

`./build.sh` passed both rows before and after adoption and after scoped naming.
Final `header_adopt_lane.py accept` passed both final sources. The final scratch
`tu_skeleton.Verifier` comparison preserved each matched RVA and
`class_cleanup.same_runtime` found equivalent complete non-debug COFF contents:
bytes, relocations, external definitions, weak aliases and COMDAT policy.
Scratch object pairs (under `build/tu_skeleton/`):

- Terrain name: `bbfe111c4706cd81.obj` -> `2de27f63eb46a94a.obj`.
- Interval: `fb4aeb7455e345b5.obj` -> `911695307d2dbff7.obj`.

`find_declared_unmatched.py` reports all defined functions matched;
`check_csv.py` and `git diff --check` pass. `link_check.py` predicts both units
link, preserving 224 and 77 census-counted bytes respectively (301 total).
The index census was recorded at `f6d845ecd4`, 2026-11-04 13:15 UTC. This is a
current-input prediction, not a new census or a real-link improvement.

## Remaining consolidation boundary

The supported `tu_skeleton.py --merge ... --dry-run` found 225 approved rows,
19 mixed donors and accepted no donor. Existing seed override `-G7 -arch:SSE`
conflicts with the `-O1 -G7` override on WorldHeightMapRva000B0DA8.cpp. Under the
carried seed flags, constructor and parser donors lose 35 and 29 rows; other
donors lose rows or lack a baseline match under those flags. No merge, deletion,
TU-map edit or source-file reduction was retained. This recheck used the current
expanded 225-row scope and canonical header rather than the older 79-row attempt.

Next useful work is a separately verified compiler-flag reconciliation, followed
by remaining canonical-header/private-view reconciliation (including the seed's
legacy declarations). `tu_views.py --dry-run` also reports GDIFileStream inline
body conflicts, EvaMessageInfo import differences and overlapping blend-tile
views; no mechanical view rewrite was applied. Do not repeat the unchanged
merge or treat these two adoptions as clearance of the full WorldHeightMap family.
