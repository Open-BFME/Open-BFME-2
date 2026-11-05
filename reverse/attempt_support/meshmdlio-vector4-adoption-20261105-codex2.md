# Mesh material I/O Vector4 queue retirement

Base: `830ecebb80`. Scope: `Code/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp`.

The two Vector4 queue rows came from MeshModelReadDig.cpp and
MeshModelReadVertexColors.cpp before their consolidation. The current TU
already includes the full WWMath vector4.h. Include Vector4Data.h explicitly
after that header; its shared VECTOR4_H guard preserves the full definition.
No member body, alias, data definition or compiler flag is removed or changed.

Verification:

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp`: 42/42 matched;
  seven funclet pins verified, two string literals and 27 float literals pass.
- `find_declared_unmatched.py` before and after: all defined functions already
  matched (the tool notes four unclaimed definitions).
- One `header_adopt_lane.py accept --class Vector4` over the selected two-file
  cohort: meshmdlio PASS; tool retired both meshmdlio rows. Quadruped remains
  queued, with its original matched source preserved. Its previously recorded
  POD-to-constructor/SSE scheduling blocker is not resolved here.
- `link_check.py meshmdlio.cpp`: LINKS, census-linked 5,663 -> 6,452 bytes,
  against census 2026-11-05 15:19 at `f44cbcf5b0`. This is a bounded prediction,
  not a new census gain.

The remaining meshmdlio DX8Wrapper queue row requires a different header
reconciliation: its current shim owns inline Convert_Color bodies, whereas
DX8WrapperClass.h declares them out of line. No DX8Wrapper replacement was
attempted and that row is retained. LINK-012's wider shatter/material findings
remain open.
