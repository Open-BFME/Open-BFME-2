# Adopt canonical Matrix3D in W3DVolumetricShadowRenderMeshVolume: bounded unsuccessful adoption trial

Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderMeshVolume.cpp`, existing parent `?RenderMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z` at
0x000F200A/505B. Native1/1, all retained external bodies, named-static check and data bindings match. Stricter whole-runtime-section comparison fails because unchanged Matrix4::Init and compiler array iterator COMDATs exchange object-section order. No checker relaxed or source reordered to force admission; original restored and native gate passes; object-order proof prerequisite retained.

The private candidate does not replace the committed source. No new native
row, completed adoption or runtime improvement is claimed. The existing
source remains byte-verified. Diagnostic sources and comparisons are retained
in ignored build/up-to-eighteen-each-20261102-2256/b2-10-*. The adjacent patch preserves the latest
private trial. Other trial variants, if performed, remain in the diagnostic controls.
No shared header, compiler flag, pin, alias or gate change is attempted.
