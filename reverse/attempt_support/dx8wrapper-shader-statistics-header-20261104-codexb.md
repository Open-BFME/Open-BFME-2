# DX8Wrapper shader and statistics header adoption

Date: 2026-11-04. Seat: codexb. Inspected base: `066da33373`.

## Applied scope

`fxshadersetup.cpp` and `statistics.cpp` now include `DX8WrapperClass.h`
instead of private DX8Wrapper declarations. Statistics reads the existing
`Get_Current_Caps()` accessor into a const pointer instead of its private
`Read_CurrentCaps()` helper. Both inline accessors read the same protected
`CurrentCaps` pointer; this change does not alter the caps layout or allocation.
The shared header, row identities, source paths, pins and aliases are unchanged.

Verification:

- `./build.sh` on both sources: 91/91 functions and one data row exact;
  string, float and import reference checks pass.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class DX8Wrapper` passes for both sources
  and retires exactly their two rows from `reverse/header_queue.tsv`.
- Combined `link_check.py`: both LINKS; shader setup preserves 2,881 bytes,
  statistics preserves 1,260 bytes, total 4,141 -> 4,141 census-linked bytes.
  Index: 2026-11-04 13:15 at `f6d845ecd4`. This is a preview, not a census.
- Other queued classes in statistics (WW3D and ShaderClass) are peer-held;
  the dry-run claim check refused both. Their private views and queue rows remain.

## Reverted trial scope and next checks

The six-source automatic DX8Wrapper adoption trial kept only shader setup.
Statistics initially failed on `Read_CurrentCaps`; the accessor change above
resolved that failure. The other four sources were restored by the lane:

- `fxshadernamespacesas.cpp`: C2039, `Get_Light_Environment` missing from the
  shared header. Reconcile its static accessor/provider contract before retrying.
- `fxshadernamespaceww3d.cpp`: C3861, `Get_Fog_Color` missing. Its existing
  accessor returns a local vector view, so confirm the shared return identity
  and conversion contract before retrying.
- `linegrp.cpp` and `texturefilter.cpp`: C2371 on the SDK
  `D3DTRANSFORMSTATETYPE` typedef versus the header's enum declaration. A local
  SDK typedef reconciliation has precedent in the pixel-shader setter adoption;
  it alone does not prove the remaining APIs or inlined bodies compatible.

No queue row for these four trials was retired, and no failed source edit remains.
The separate initialization/render-target prerequisites recorded in the obstacle
entry are unchanged.
