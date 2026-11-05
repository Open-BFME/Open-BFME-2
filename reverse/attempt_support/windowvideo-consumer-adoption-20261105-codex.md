# WindowVideoManager consumer adoption, 2026-11-05

Inspected revision: `289c876e17a744563f4fa302b545583c70671573`.

Four queued consumers now include the existing canonical
`Code/GameEngine/Include/GameClient/WindowVideoManagerClass.h`.
The ControlBar consumers only allocate or call the manager; their opaque
private tails had no member accesses to translate. The armor-store destructor
uses the nested hash type and now gets SubsystemInterface from the canonical
header instead of the conflicting spline_service.h shim. No shared header,
compiler flags, function body, ledger identity or alias was changed.

## Verification

- `./build.sh` over all four sources: 159/159 matched functions, two data rows,
  68 funclet pins and one complete STLport constructor fold verified.
- `find_declared_unmatched.py` over all four: all definitions already matched.
- One `header_adopt_lane.py accept --class WindowVideoManager` over all four:
  four PASS verdicts and four header-queue rows retired by the tool. Its joint
  ordinary link preview preserved each unit's census-linked bytes.
- `git diff --check`: clean.

## Provider preservation

Compared emitted external definitions and link-wide aliases before and after.
The three manually adjusted consumers use their original byte-verified objects
as the before state. PlayerInitFromDict uses census `f44cbcf5b0` definitions;
its replaced private view had only an out-of-line hash-operator declaration
and supplied no body. The objects retain every prior external definition and
every alias, so no removed provider needs a caller migration.

| Consumer | Before definitions | After definitions | Removed definitions / aliases |
| --- | ---: | ---: | ---: |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp` | 199 | 199 | 0 / 0 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarConstructor.cpp` | 35 | 35 | 0 / 0 |
| `Code/GameEngine/Source/GameLogic/Object/Rva001D92C0Dtor.cpp` | 26 | 26 | 0 / 0 |
| `Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp` | 53 | 53 | 0 / 0 |

This is header-debt retirement and a scoped non-regression preview.
No new real-link image, census gain, or runtime result is claimed.
