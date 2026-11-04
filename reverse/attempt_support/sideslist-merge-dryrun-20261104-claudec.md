# SidesList.cpp TU merge dry run, 2026-11-04 (claudec)

Base: `17aee47abe`. Tools: `tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Map/SidesList.cpp --dry-run`,
then `tu_views.py` on the same TU (dry run, then write mode). No source changed.

## Result

- 454 approved rows; 45 candidate donors; `refused` empty.
- Accepted with the seed: `Code/GameEngine/Source/Common/Rva0032AF56Destroy.cpp` and
  `Code/GameEngine/Source/GameLogic/Map/Rva0019B780Lookup_Rva0032d0b5.cpp` (58 rows verify).
- The real `--merge` wrote nothing: it needs RVA `0x0007FAB3` (the ICF-folded 14-byte vector
  destructor), which another worker's `AIGameTeam.cpp` merge held. Rerun the merge once that claim is gone;
  the saved plan under `build/tu_skeleton/plans/` is valid only while inputs are unchanged.
- `tu_views.py` write mode changed nothing: every planned class is "already shared" or conflicts
  (`TeamsInfoRec` 17 files: `m_index` under the bases in SidesListTeamsInfoRecMoveTeams.cpp;
  `BfmeE8` field overlap; `BfmeThingUBB` +0x8 iterator vs int; `Rva0032989F` base clause;
  `BfmeParserBindingBaseVE` dllimport dtor; `Rva00196D90Element` inline vs out-of-line ctor;
  `TeamsInfoEntry` class vs struct). `BfmePod128` reverted (SidesListCopyCtor.cpp no longer compiles).

## Rejection classes of the other 43 donors

- Seed uses the GameLogic-side `SidesList`/`TeamsInfoRec` views; donors call members only the
  canonical `Common/SidesList.h` or their private views declare (`swap`, `exchangeFlag`,
  `rva0032B7A7`, `rva0032B871`, `rva0032F0AA`, `TeamsInfoRec::swap/m_entries/addToIndex/rva0032C2C4`).
  This is the open SidesList header-queue backlog (20 rows, `field renames` against the canonical
  header's opaque padding), not merge mechanics.
- Canonical-header redefinitions against private copies: `Coord3D` (BuildListInfo*, stlport_copy_buildlistinfo),
  `Dict`, `SubsystemInterface`, `DataChunkTableOfContents`, `Xfer`, `FieldParse`.
- Private STLport template copies (`allocator`, `vector`, `list`, `_Rb_tree`, `__false_type`,
  `_STL::free` using-declaration clash).
- `#error` guards: ScriptList and BuildListInfo need the named Snapshot surface before Snapshot.
- `Rva0032B610Compare.cpp`: bytes; `stlport_map_int_vector_pod128.cpp`: link guard
  (census-linked pair<const int, vector<BfmePod128>> dtor COMDAT would be lost).

Next step for the bulk: adopt canonical `Common/SidesList.h` (header lane) in the seed and donors,
starting from the constructor prerequisite in `sideslist-notifier-adoption-20261104.md`.
