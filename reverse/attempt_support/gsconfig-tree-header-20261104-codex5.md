# GSConfig donor tree-header adoption

Inspected revision: `81d2d1f584` (2026-11-04). Scope:
`Code/Libraries/Source/WWVegas/WWLib/Rva0054F434Dtor.cpp` and
`Code/Libraries/Source/WWVegas/WWLib/Rva0054F434Vslot1.cpp`.

Both donors duplicated an 8-byte `Rva00072FE6` view followed by four bytes of
padding. The registered header defines the complete 12-byte member. Including
that header and removing the now-zero-sized padding preserves the member at
`+0x58` and the following string at `+0x64`. No class or function was renamed.

Verification:

- `./build.sh` on both donors: 10/10 rows byte-exact, including parent-verified
  EH funclets; string, floating-point and import checks pass.
- `find_declared_unmatched.py` passes before and after the edit.
- `header_adopt_lane.py accept --class Rva00072FE6` passes both donors and
  retires their two header-queue rows through the owning tool.
- Comparing pre-edit and post-edit objects through `link_census.object_symbols`
  shows identical external definitions, references, weak aliases and linker
  directives. `_comdat_sections` gives identical byte/relocation digests for
  all 53 and 22 external COMDAT sections, respectively.
- `link_check.py` with current cached inputs predicts both units link:
  215 -> 215 and 27 -> 27 bytes. Its census reference is 2026-11-04 07:28,
  `a62ac1c10b`. Existing unreferenced STL codegen diagnostics remain. This is
  a preview, not a new census or real-link measurement.

## Remaining consolidation prerequisites

The required GameSpy consolidation planner and `tu_skeleton.py --merge
Code/GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp --dry-run` were run
before this adoption. The skeleton rebuilt the stale TU map in memory; no map
or source move was committed. It accepted no donors:

- `Rva0054E7C3Find.cpp` uses STLport 4.6 while the seed uses 4.5; the combined
  trial reports C2244 for allocator `deallocate`.
- The destructor donor's private `set<int>` specialization hides `insert`
  needed by the seed (C2039).
- The vslot donor trial differs in bytes. `tu_views.py --dry-run` also identifies
  incompatible slot-1 declarations: `rva0054F3FD` versus `rva0054F3E2`.
- `GapBodiesGE30.cpp` and `stlport_vector_word_o1.cpp` contain mixed TU rows.

This commit clears only the two canonical-header adoption prerequisites.
Reconcile the STL interface and private class views in separately verified
commits, then repeat the supported merge dry-run. It does not establish the
merged class layout, slot identity or a new retail source name.
