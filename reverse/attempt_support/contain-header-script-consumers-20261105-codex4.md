# Containment header adoption in script consumers

2026-11-05; inspected `f3397f1e18`; worker `yasinschroeder-codex4`.

Replaced private `ContainModuleInterface` declarations with the existing
`Code/GameEngine/Include/GameLogic/Module/ContainModule.h` in:

- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding.cpp`
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_garrison.cpp`
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerUnitCounts.cpp`

The nearest-building action's former slot-1 getter now uses `asOpenContain`,
casting its result to the existing local +0xDE field view. The garrison actions'
former slot-31 getter now uses `slot31`, casting its result to their existing
`ContainedObjectSource` view. The player-unit condition's former slot-70
aggregate getter now uses `slot70`; the existing list view reads the result's
second word. These are mappings of the old call slots to the canonical surface,
not new donor-derived identities or layouts. The shared header is unchanged.

## Checks and debt retirement

`find_declared_unmatched.py` passes before and after the edits. The normal
`./build.sh` invocation for all four attempted units verifies 271/271 function
rows and six data rows. The restored GameLogicInit unit separately verifies
207/207 function rows and the same six data rows; the retained three units
therefore account for 64 verified function rows.

`header_adopt_lane.py accept --class ContainModuleInterface` passes the three
script units and retires exactly their three queue rows. A subsequent ordinary
`link_check.py` preview against census `c95fcfcfcd` (2026-11-05 05:17) preserves:

| Unit | Before | After |
| --- | ---: | ---: |
| ScriptActions_doUnitGarrisonNearestBuilding.cpp | 309 B | 309 B |
| ScriptActions_garrison.cpp | 3,921 B | 3,921 B |
| ScriptConditionsPlayerUnitCounts.cpp | 2,946 B | 2,946 B |
| Total | 7,176 B | 7,176 B |

No new census or real-link result is claimed.

## GameLogicInit attempt restored

The same header replacement and existing-slot adaptations also byte-verify in
`Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`. Acceptance refuses
it because the ordinary preview reports 28,401 -> 0 census-linked bytes with
unresolved `?rva0023C8DA@GameLogic@@QAEXE@Z`. Restoring the original source,
rebuilding it through `./build.sh`, and repeating the preview reproduces the
identical missing name. No GameLogicInit source edit or queue retirement is
retained.

The missing provider is already rowed at RVA `0x0023C8DA` in
`Code/GameEngine/Source/GameLogic/Rva0023C8DA.cpp`. Verify its current object and
provider-index receipt, then repeat acceptance before retrying this consumer;
the preview alone does not establish a missing retail body. The tool-recorded
blocked verdict is keyed `header-ContainModuleInterface-GameLogicInit` at the
attempted containment worker `0x0024877A`. No provider edit was attempted.
