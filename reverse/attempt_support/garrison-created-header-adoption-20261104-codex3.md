# GarrisonContain creation header adoption, 2026-11-04

Base: `97959ebc2c7c7bffee74780c0939385e85bc24ae`.
Source: `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnObjectCreated.cpp`.
Target: `?onObjectCreated@GarrisonContain@@UAEXXZ`, RVA `0x004787B0`, 160 bytes.

Replaced the private Player and GarrisonContainModuleData declarations with
canonical headers. The roster now uses the canonical nested InitialRoster type;
the default-team call uses Player's canonical const accessor. Removed the
TU-private bfme_default_team helper. Compiler flags and ledger ownership remain
unchanged; no alias pragma was removed.

Verification:

- `find_declared_unmatched.py` before and after: all defined bodies matched.
- `./build.sh` after each adoption: 1/1 body byte-exact, 160 bytes; string,
  float and import checks clear.
- `header_adopt_lane.py accept --class GarrisonContainModuleData SOURCE`: PASS,
  retired one header-queue row through the owning tool.
- `header_adopt_lane.py accept --class Player SOURCE`: PASS, retired one more
  header-queue row through the owning tool. Both acceptance checks include byte
  and per-unit link acceptance.
- Final `link_check.py SOURCE`: LINKS, LINKED 160 -> 160 credited bytes against
  census 2026-11-04 17:56 at `8c757ea0db`. This is a preview, not a new census or
  evidence of a measured linking gain.

Consolidation remains a separate prerequisite chain. The supported initial dry
merge accepted no donors. `tu_views.py` applied no reconciliation: GarrisonContain
bases, Object layouts and primary virtual slots conflict. The seed still owns a
private GarrisonContainModuleData declaration and calls its flat roster fields;
its canonical adoption must preserve the constructor and EH funclet bytes. Its
primary view also names the module-data slot m_pad4 rather than m_moduleData.
Other donor diagnostics include Object::m_conditionBits, a duplicate
GARRISON_POINT_PRISTINE enumerator, a duplicate STL list comparison template and
the missing exitObjectViaDoor declaration. No source files or rows were moved.

Final supported dry merge after both adoptions: accepted no donors (exit 2).
The creation donor now first exposes the seed constructor's undeclared m_filter40
when the canonical module-data definition is composed; the other four donor
first diagnostics above remain unchanged. The creation donor no longer appears
in adopt_first. Reconcile the seed constructor's canonical module-data fields
and preserve its EH bytes before retrying composition.
