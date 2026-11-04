### DX8Wrapper header adoption: missing static-member declarations

Status: Blocked for the initialization and render-target consumers; updated 2026-11-04 at `3683dc6110`.
Next: reconcile `DisplayFormat` and render-target static members with their retail/provider contracts before retrying `DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp`, `DX8Wrapper_Set_Render_Target_Depth.cpp` and `DX8Wrapper_Set_Render_Target_Surface.cpp`; their queue rows remain.
The SDK typedef collision is cleared for `DX8Wrapper_Set_Pixel_Shader_Constant.cpp`: canonical-header adoption accepted, 1/1 exact, link preview 86 -> 86 bytes; no new census claimed. [Evidence and failed-trial scope](../../reverse/attempt_support/dx8wrapper-pixel-shader-header-20261104-codexb.md).
2026-11-04: shader setup and statistics adopt the header, retire two queue rows and preserve 4,141 preview-linked bytes; shader namespace trials expose missing light-environment/fog accessors, while line group and texture filter retain the SDK typedef prerequisite. [Scope and verification](../../reverse/attempt_support/dx8wrapper-shader-statistics-header-20261104-codexb.md).
