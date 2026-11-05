# Snow.cpp consolidation prerequisite

Inspected revision: `0cf7c10a0b`. Claims: the approved Snow.cpp scope and five donors.

## Canonical Overridable

The seed carried a private 12-byte Overridable followed by a placeholder dword at +0x0C. The canonical base owns that dword, so remove the placeholder when adopting its header. Retail 0x00201153 (18 bytes) loads TheWeatherSetting, checks its next override and tail-calls friend_getFinalOverride on that next node, or returns the original node. Calling the canonical helper on the original node directly does not reproduce that inline first step; spelling it through friend_getNextOverride does. No class/header/global/row identity changed.

`./build.sh Code/GameEngine/Source/GameClient/Snow.cpp`: all five code rows and one data row pass, including strings, floats and imports. `find_declared_unmatched.py --fail` passes. `header_adopt_lane.py accept --class Overridable Code/GameEngine/Source/GameClient/Snow.cpp` passes and retires exactly its one header-queue row. No data/code-identity/MS-header debt keys name this source.

## Remaining composition work

The initial current-input tu_skeleton dry run accepts zero donors. Snow_Unresolved.cpp includes the older subsystem shim, which redefines the seed canonical SubsystemInterface. The other WeatherSetting donors require incompatible base/layout or special-member declarations; INIParseWeatherDefinition also remains queued for Overridable. The generic tu_views planner refuses the differing SnowManager and WeatherSetting base clauses. This prerequisite retires header debt; it does not itself remove a source or change census figures.
