# Four Rva00045411BitSet header consumers

Inspected revision: `ac664c88aa`, 2026-11-05. Worker: `yasinschroeder-codex`.

Replace the private mask declarations in Common/BfmeT1035.cpp,
Common/Rva0039BF0BFinish.cpp, Common/StatsReporter.cpp and
Common/StatsReporterStrategicResults.cpp with the existing canonical
GameLogic/Module/Rva00045411BitSet.h include. All paths above are relative to
Code/GameEngine/Source/. These consumers do not access the private storage
member, so no field rename is needed. Their struct class-key is preserved;
the constructor callers also adopt the canonical nonthrowing declaration.
No shared header, symbol name, ledger row, alias or pin changes.

Verification:

- `find_declared_unmatched.py` passes before and after each source edit.
- `./build.sh`: 6/6 rows in Rva0039BF0BFinish and 33/33 rows in the other
  three units match. Existing unwind labels are verified through parent EH
  data despite compiler label renumbering. String, float and import checks pass.
- `header_adopt_lane.py accept --class Rva00045411BitSet` passes for all
  four units and retires exactly their four header-queue rows.
- Combined ordinary `link_check.py` preview: all four units LINKS, with
  7,450 -> 7,450 linked bytes (130 + 443 + 4,640 + 2,237), against the
  published index at `c95fcfcfcd` (2026-11-05 05:17). This is preservation
  within the preview scope, not a new census or full-game link result.

The initially selected ObjectFilter.cpp adoption remains unchanged. The lane
refuses the isolated provider rename because CastleBehavior.cpp,
GarrisonContain.cpp, TunnelContainModuleDataCtor.cpp and
QueueProductionExitUpdateQueryRallyOverride.cpp must adopt together.
Tunnel's additional copy-constructor/exception-contract prerequisite is
already documented in horde-garrison-header-adoption-20261105-codexb.md;
this session did not retry that reconstruction or retire its queue row.
