# Snow.cpp consolidation prerequisite

Inspected revision: `0cf7c10a0b`. Claims: the approved Snow.cpp scope and five donors.

## Canonical Overridable

The seed carried a private 12-byte Overridable followed by a placeholder dword at +0x0C. The canonical base owns that dword, so remove the placeholder when adopting its header. Retail 0x00201153 (18 bytes) loads TheWeatherSetting, checks its next override and tail-calls friend_getFinalOverride on that next node, or returns the original node. Calling the canonical helper on the original node directly does not reproduce that inline first step; spelling it through friend_getNextOverride does. No class/header/global/row identity changed.

`./build.sh Code/GameEngine/Source/GameClient/Snow.cpp`: all five code rows and one data row pass, including strings, floats and imports. `find_declared_unmatched.py --fail` passes. `header_adopt_lane.py accept --class Overridable Code/GameEngine/Source/GameClient/Snow.cpp` passes and retires exactly its one header-queue row. No data/code-identity/MS-header debt keys name this source.

## Remaining composition work

The initial current-input tu_skeleton dry run accepts zero donors. Snow_Unresolved.cpp includes the older subsystem shim, which redefines the seed canonical SubsystemInterface. The other WeatherSetting donors require incompatible base/layout or special-member declarations; INIParseWeatherDefinition also remains queued for Overridable. The generic tu_views planner refuses the differing SnowManager and WeatherSetting base clauses. This prerequisite retires header debt; it does not itself remove a source or change census figures.

## Shared subsystem prerequisite

Both SnowManager views now inherit the canonical header with BFME_SUBSYSTEM_SLOTS. The seed drops its redundant placeholder virtual declarations, including an unsupported tail beyond the actual subsystem/updateIniSettings surface; the lifetime donor no longer imports the old reference shim. The existing donor was already using the same fourteen base slots; no shared header or row changes are needed.

The normal builder passes all ten rows plus the data row across both sources; the destructor EH graph is EXACT. Both frozen-file checks pass. Ordinary previews retain Snow.cpp 783/783 and Snow_Unresolved.cpp 335/335 bytes. A fresh tu_skeleton dry run now accepts the seed and Snow_Unresolved.cpp (ten rows), versus zero accepted donors initially. Other four donors remain rejected with their existing special-member/base or canonical Overridable prerequisites. Apply only the accepted lifetime donor through tu_skeleton after committing this repair.

## Applied lifetime merge and outgoing path audit

`tu_skeleton.py --merge Code/GameEngine/Source/GameClient/Snow.cpp` absorbs only Snow_Unresolved.cpp, repoints its five rows in functions.csv and the existing map's source column, and deletes that donor. No map regeneration is committed. Source files decrease by one; matched coverage is unchanged. The other four donors and the mixed ConstIntGetters satellite stay untouched. A fresh tu_views dry run still refuses their differing base clauses; those prerequisites remain open.

`./build.sh Snow.cpp` verifies ten code rows and the one data row, including the renumbered destructor funclet via its parent's exact EH graph. The frozen-file check and check_csv pass. `eh_verify.py` reports one EXACT parent, no baseline cases. The ordinary link preview reports LINKS, 1,118 combined bytes (783 seed plus 335 donor), against the 2026-11-05 05:17 census index at c95fcfcfcd; this is a preview, not a census increase.

Before/after object inspection preserves the union of all 23 external code definitions and three external data definitions, with no added definitions and no REL32 callee changes. No new undefined external appears. TheWeatherSetting, init, reset and updateIniSettings become internal to the composed object. The merge's LinkGuard passes with the removed donor excluded, checking selected COMDATs, provider/consumer routes and outside new-variant losses. No alternatename is removed.

The full outgoing batch from origin/master through c534412a8a plus this merge has one deleted source: Snow_Unresolved.cpp -> Snow.cpp. Searching active tools, hooks, workflows, source/includes, build configurations and source registries finds no active old-path consumer. Remaining mentions are the preserved source provenance comment, historical attempt evidence and reverse/link_status.csv (the immutable census measurement). No code-identity, data-identity, header, Microsoft-header or hatch key names either the removed donor or destination after the earlier owning-lane header acceptance. The merge refreshes the header/MS-header reports through its owning tools; neither changes. TheWeatherSetting data row remains owned by Snow.cpp. Ledger and fold-proof searches resolve to the surviving source; no debt retirement or transfer is needed for the deleted donor.
