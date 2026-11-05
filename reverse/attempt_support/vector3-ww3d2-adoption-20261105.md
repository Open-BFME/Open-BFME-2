# Vector3 adoption in two WW3D2 consumers, 2026-11-05

Inspected revision: `e36efe1879`; census index: `f44cbcf5b0`
(2026-11-05 15:19). This continues the inline-assignment repair documented
in `vector3-inline-assignment-adoption-20261105.md`.

`Code/Libraries/Source/WWVegas/WW3D2/LightClassCopyCtor.cpp` and
`Code/Libraries/Source/WWVegas/WW3D2/FXShaderGeometry.cpp` now include
`../WWMath/Vector3Data.h` instead of defining private Vector3 classes.
The canonical header and ledger names are unchanged.

Verification:

- Normal `./build.sh` passes all 39 function rows, five string literals,
  six float literals and the funclet checks across these two sources.
- Original and adopted sources were each built through the normal builder.
  `class_cleanup.runtime_graph` / `same_runtime` reports exact runtime
  equality, including non-debug bytes, relocations, external definitions,
  weak bindings and COMDAT policies. LightClassCopyCtor retains all 22
  external definitions; FXShaderGeometry retains all 138. Neither object
  adds or removes a provider, so there is no lost definition for other
  objects to reference.
- One cohort `header_adopt_lane.py accept --class Vector3` passes both
  sources, including its combined link preview, and retires both queue rows.
  This is header-debt retirement, not a new census or real-link measurement.

W3DViewIterateDrawablesInRegion still fails its byte trial with the current
header; its original source and queue row are retained. The other remaining
Vector3 obstacles are unchanged.
