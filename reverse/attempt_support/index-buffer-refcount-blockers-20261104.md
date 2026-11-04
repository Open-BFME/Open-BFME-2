# IndexBufferClass header adoption: donor refcount.h blockers, 2026-11-04

Target facts (native builds, `./build.sh <file>`, model=claude-opus-5-5):

- Adopted with `header_adopt_lane.py accept` (byte match, census bytes kept):
  BaseHeightMapRenderObjClass_updateScorches.cpp, W3DBridgeBuffer.cpp,
  FXShaderGeometry.cpp, W3DTerrainBackgroundDoPartialUpdate.cpp,
  W3DFloorBuffer.cpp, DX8RendererAddMesh.cpp, W3DWaterTracks.cpp.
- Still queued (IndexBufferClass, and DX8IndexBufferClass where listed):
  W3DTerrainBackground.cpp, W3DTreeBuffer.cpp, Render2DClassRender.cpp,
  SimpleStreakRendererRenderStreak.cpp, StreakRendererRenderStreak.cpp,
  linegrp.cpp.

Blocker: these TUs see the donor Zero Hour `RefCountClass` from
`reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/refcount.h`
(through `WW3D2/rendobj.h:56`, `WW3D2/linegrp_headers.h:17`, or an inlined
ZH dx8indexbuffer.h/refcount.h copy). The canonical `IndexBufferClass.h`
derives from `WWLib/RefCountData.h`'s RefCountClass, so including it fails:

```text
RefCountData.h(9) : error C2011: 'RefCountClass' : 'class' type redefinition
reference\open-bfme-1\game\Libraries\Source\WWVegas\WWLib\refcount.h(109) : see declaration of 'RefCountClass'
```

W3DWaterTracks.cpp included refcount.h directly, so swapping that one include
for RefCountData.h was enough there. In linegrp.cpp the same swap still fails
because linegrp_headers.h pulls refcount.h first; W3DTerrainBackground.cpp
fails through rendobj.h.

Next step: give rendobj.h and linegrp_headers.h (shared headers; full-gate
hook) the canonical RefCountData.h, or a TU-scoped shim that does, plus the
NEW_REF/REF_PTR_* macros those consumers use from the donor header. Then
re-run accept for the six units.
