# MeshMatDescClass accessor header adoption, 2026-11-05

Base: `8d3de262eb`. Scope: the three WW3D2 consumers
`MeshMatDescClassGetColorArray.cpp`, `MeshMatDescGetUVArrayByIndex.cpp` and
`MeshMatDescHasColorArray.cpp`.

Replaced each private descriptor declaration with `MeshMatDescClass.h` and
used its existing member names. The per-pass setter retains its address-derived
name; its store now explicitly converts to the canonical `ColorSourceType`.
The existing local buffer templates and emitted inline providers remain.
No shared header, alias, data definition or function row changed.

The include roots are TU-scoped. Including the existing BFME2 debug declarations
before the descriptor prevents the donor WWLib include closure from introducing
`debug.lib` and a forced debug symbol. A byte match alone did not detect these
extra linker directives; whole-object comparison did, and the final objects
preserve them exactly.

Verification:

- `./build.sh` on the three final sources: 6/6 function rows byte-match,
  including the allocator funclet and handler; string and import checks pass.
- `find_declared_unmatched.py` passes for all three final sources.
- `class_cleanup.runtime_graph` / `same_runtime`, comparing objects built before
  the edits with the final objects: all three identical across all non-debug
  sections, relocations, external definitions, weak bindings and COMDAT policies.
  This also preserves link-wide providers and linker directives.
- One cohort `header_adopt_lane.py accept --class MeshMatDescClass` invocation
  examined the 25 served consumers and retired these three queue rows. The
  other 22 served consumers remain unchanged. Acceptance was rerun together on
  the three final sources after fixing the debug include: all PASS.
- Current-object `link_check.py` against census `f44cbcf5b0`
  (2026-11-05 15:19): all three LINKS; own linked bytes remain 115, 125 and 31
  respectively, 271 total. This is a preview, not a new image or census.
- `git diff --check` passes.

Result: three private descriptor copies removed and three header debts retired.
LINK-420's reader and material-pass prerequisites are unchanged.
