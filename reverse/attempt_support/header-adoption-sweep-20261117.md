# Registered-variant header adoption: measured sweep yield (2026-11-17)

Seat: opencode (deepseek-v4.1-flash). Base when the sweep started: `8b06c04cd2`;
it ended published at `7147318e82`. Worktree `open-bfme2-pr140`.

## Method

For each class with fully-decided contract and queued rows in
`reverse/header_queue.tsv`:

```
python3 tools/header_adopt_lane.py run --class <C> --apply --skip-held
git checkout HEAD -- reverse/header_queue.tsv      # the tool rewrites/prunes the queue
python3 tools/header_adopt_lane.py accept --class <C> <each PASS source>
python3 tools/link_check.py <accepted sources>
git commit                                     # pre-commit byte check + data_check
```

Only `accept`-verified units were committed; a class whose every pass `accept`
refused left no change. Scratch driver: `build/long_sweep.py` (untracked).

## Yield

| class size (queued rows) | classes swept | winning classes | units adopted |
| --- | ---: | ---: | ---: |
| 1 (pilot, 24) | 24 | 1 | 1 |
| 1–4 | 250 | 0 | 0 |
| 5–9 | 107 | 14 | 31 |
| 6–13 | 45 | 7 | 16 |
| 14–79 | 40 | 6 | 16 |
| **total** | **391 unique** | **20** | **48** |

The 5–9 and 6–13 rows overlap by construction (the driver took the top N of a
range); the 48 units are distinct. 47 distinct source files (one file adopted
for two classes). Every unit preserved its census bytes at a freshly updated
index; the last three batches re-verified 16/16, 16/16 and 14/14 units.

Classes should therefore be ordered by queued-row count descending. A 1-row
class pays the same probe cost and has never passed: 0/274 including the pilot
(the pilot's one win, `AsciiStringPlusString`, was a 1-row class, so the rate
is ~0.4%, not 0).

## Why units are refused

Failure taxonomy over 252 unit verdicts in the 1–4 row sweep:

| reason | share |
| --- | ---: |
| `field renames` (rename guard refuses an ambiguous token) | 42.5% |
| `C2065` (canonical header does not declare the private view's names) | 29.4% |
| `bytes/callee identity` | 7.9% |
| `C2039` missing member | 5.2% |
| other compile shape (`C2259`, `C3861`, `C2512`, ...) | ~15% |

Two refusals now gate otherwise-valid units and are tool-level, not body-level:

- `accept: FAIL <unit>: link_check predicts a loss of census-linked bytes` —
  the unit compiles, matches its rows, and the canonical header is right, but
  changing the object's COMDAT copies makes another unit lose bytes. This is
  the selection coupling of LINK-133. Cost in this session: ~25 units, the
  worst case `FunctorWrapperHead` (10 tournament passes, 6 refused, 4 landed).
- `accept: FAIL <unit>: still declares a private body; does not #include <h>` —
  `Code/GameEngine/Source/GameLogic/System/GameLogic.cpp` under `ModuleInfo`,
  `Rva003B0D7C` and `Rva00056F61`: the tool cannot rewrite that unit's private
  view, so it blocks the whole class.

`run --apply` also prunes queue rows it judges stale even when it applies 0
units; the pre-commit hook correctly refuses those deletions. Restore the
queue from HEAD and retire only the accepted rows.

`link_check` must be re-run with `--update-index` after master merges units:
with a stale index it replaces the verdict with a stale-index warning, so the
adoption is not verified.

## Winning classes (this session)

`DX8Wrapper` 1, `AICommandInterface` 2, `W3DRadarResetSurface` 1,
`Rva003B0D7C` 3, `Rva000421C8` 5, `FunctorWrapperHead` 4, `Dict` 5,
`BfmeObject872Header` 1, `AptActionInterpreter` 2, `Rva0020E89C` 1,
`Rva00506B1B` 1, `Rva00065964ObjectPool` 3, `CommandSet` 3, `PoolMember` 4,
`Matrix4` 1, `CursorTextureSlot` 1, `ObjectModuleBase` 3,
`BfmeStringRecord002CF5B1` 3, `BfmeResultA` 2, `BfmeObjectDlinkPad` 1, plus
the targeted `AptValue` adoption in `LadderPreferencesDtor.cpp`.

`AptValue`'s link status did not change: `LadderPreferencesDtor.cpp` is still
charged on `??_GRva006D6470Owner@@UAEPAXI@Z` / `??_7Rva006D6470Owner@@6B@`,
whose wrong copy is emitted by the constructor unit `AptValue.cpp` (no private
view to adopt), as the unit's own comment says.

## Selected-COMDAT pool (unchanged, no new hatches)

132 non-linking units are blocked only by a selection, in 70 groups. Largest:
`??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` 28 (needs /G7 codegen per
TU, i.e. the `#pragma optimize` anchor, which is a hatch), `??_GGenericMultiListClass@@UAEPAXI@Z`
15, `?getCharAt@?$StringBase@D@@QBEDH@Z` 7 (hatch-locked handoff),
`??_GMultiListObjectClass@@UAEPAXI@Z` 6, `??_GRva006D6470Owner@@UAEPAXI@Z` 5.
