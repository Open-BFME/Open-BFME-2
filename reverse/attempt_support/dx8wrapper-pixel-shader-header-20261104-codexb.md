# DX8Wrapper pixel-shader header adoption

Inspected base: `3683dc6110`; date: 2026-11-04; seat: codexb.

## Applied and verified

`DX8Wrapper_Set_Pixel_Shader_Constant.cpp` now includes
`DX8WrapperClass.h` instead of defining its own DX8Wrapper class.
The SDK typedef `D3DTRANSFORMSTATETYPE` is locally preprocessed as
`D3D9TransformStateType` while including d3d9.h; its enum tag stays
`_D3DTRANSFORMSTATETYPE`. This preserves the canonical header's two native
enum identities. Existing local precedent:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilterPreRender.cpp`.
No game symbols, flags, function bodies, pins or aliases change.

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/DX8Wrapper_Set_Pixel_Shader_Constant.cpp`:
  1/1 functions exact (RVA 0x00075399, 86 bytes); reference checks pass.
- `find_declared_unmatched.py` before/after: all defined functions matched.
- `header_adopt_lane.py accept --class DX8Wrapper` on that source:
  PASS; the tool retired exactly its one header-queue row.
- `link_check.py` on that source: LINKS, 86 -> 86 census-linked bytes;
  census 2026-11-04 11:27 at `3a8028f34e`. This is a prediction, not a new census.

## Unchanged trials and next prerequisites

The four-source adoption trial first reproduced C2371 on the SDK typedef
in the pixel setter and both Set_Render_Target overload units. After the
local SDK typedef fix, the pixel setter passed; both render-target units
instead failed C2065 for `DefaultRenderTarget`, which the shared header
does not declare. Their temporary edits were reverted completely.
`DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp` failed C2065 for
`DisplayFormat` and was left unchanged. No rows for these three units
were retired. No nonmatching reconstruction remains in Code/.

Before retrying these consumers, recover their missing static-member
contracts from retail and existing providers, then reconcile the canonical
header under its broader dependent scope. The local typedef fix alone is
insufficient. No new byte coverage or linked-byte gain is claimed.
