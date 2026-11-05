# MeshGeometry reader header adoption

Inspected source base: `2416821611`. Claim: `class:MeshGeometryClass`.

Seven existing private MeshGeometryClass views now include the canonical
`Code/Libraries/Source/WWVegas/WW3D2/MeshGeometryClass.h`:

- `MeshGeometryBoneLinkRuns.cpp`
- `MeshGeometryClass_read_user_text_Thunk.cpp`
- `MeshGeometryClass_read_vertex_shade_indices.cpp`
- `MeshGeometryReadAABTree.cpp`
- `MeshGeometryReadChunks.cpp`
- `MeshGeometryReadVertexNormalsBool.cpp`
- `MeshGeometryReadVerticesBool.cpp`

Target facts are documented in that header: VertexCount +0x28, Vertex +0x30,
secondary vertex buffer +0x34, UserText +0x14, bone-link-run buffer +0x54,
and CullTree +0x88. The readers' existing accesses use those offsets. Renames
use the canonical UserText, Vertex, slot34 and slot54 spellings; no donor layout
or new identity is asserted.

The ordinary adoption trial exposed duplicate RefCountClass declarations.
Keep the existing reference base (including its inline members and original
optimization state) and suppress RefCountData.h at the geometry include.
Six consumers use the canonical MultiListObjectClass and suppress the broad
reference multilist include, which otherwise adds unresolved header dependencies.
The AAB-tree reader already includes that reference list header; keep its existing
base unchanged. Shared headers, compiler flags, pins, aliases, ledger identities
and source paths are unchanged. Failed trials in the other eighteen selected
units were reverted; their queue rows remain.

Verification:

- Original and final scoped `./build.sh` runs: 11/11 ledger rows byte-match
  across seven sources; both renamed EH labels verified through parent EH data.
  String, float and import reference checks pass.
- `find_declared_unmatched.py` passes for all seven final sources.
- One cohort `header_adopt_lane.py accept --class MeshGeometryClass` passes
  for all seven sources, preserving census-linked bytes in its current-object
  preview and retiring exactly seven header-queue rows through the lane.
- Before/after external-definition comparison found only two removed private
  getter spellings: `?Get_Vertex_Count@MeshGeometryClass@@ABEHXZ` and
  `?Get_Vertex_Count@MeshGeometryClass@@IBEHXZ`. A scan of all 23,737 compiled
  objects under build/match found zero remaining definitions or references to
  either spelling, including undefined/weak externals and /INCLUDE directives;
  every object parsed successfully. No other external definition was removed.
- `git diff --check` passes. No real-link or game-run improvement is claimed.

Link preview index metadata: `2026-11-05 15:19` at `f44cbcf5b0`.
