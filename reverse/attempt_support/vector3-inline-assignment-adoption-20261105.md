# Vector3 inline assignment and cohort adoption (2026-11-05, claudeb)

## Target facts (retail BFME 2 1.06 image, RVAs)

- `??4Vector3@@QAEAAV0@ABV0@@Z` 0x00169FB0 (25 B, owner
  `Code/Libraries/Source/WWVegas/WWMath/matrix3d_inverse.cpp`):
  `8bc18b4c24048b1189108b51048950048b4908894808c20400`.
- A scan of every executable section for E8/E9 rel32 targets finds no call
  or jump to 0x00169FB0. The same scan finds 260 callers of 0x000069B1, the
  sanity control. It also finds no caller of the rowed subscripts 0x004047D9
  (const) or 0x007173D0 (non-const).
- renderSubBox 0x00093507 copies `snowCenter` into the vertex as three
  inline dword moves, with no call.

## Structural inference

`Vector3Data.h` declared `operator=` out of line, so every canonical
consumer that assigns a Vector3 emitted `lea; push; call ??4Vector3`, which
retail never contains. That is why the queued private-view consumers could
not adopt the header. Retail's unreferenced 0x00169FB0 body is the COMDAT
that Zero Hour's inline assignment leaves behind.

## Change

`Vector3Data.h` now defines `operator=` inline (`__forceinline`, three
component stores). The rowed body stays with matrix3d_inverse.cpp, which uses
its own ZH vector3.h view and is not affected.

## Verification

- Every source whose deps list `Vector3Data.h` (236 sources) was rebuilt with
  `./build.sh`: 2625/2625 functions matched, plus all data, string, float and
  import checks. No existing adopter changed bytes.
- Nine of those objects now carry an unreferenced `??4Vector3` COMDAT:
  MeshClassLifetime, MeshClassRender, PointGroupClassRva0017A890,
  BaseHeightMapBoundingBox, RTS3DSceneRenderOneObject,
  W3DProjectedShadowRenderShadows, W3DShadowMapManagerUpdateShadowCamera,
  W3DFloorBuffer and W3DSnowManagerRenderAsQuads. Their only relocation
  against it comes from its own associated section. The bytes equal retail
  0x00169FB0 exactly, so they are identical any-selection duplicates of the
  owner's body.
- `header_adopt_lane.py adopt` over the 24 remaining queued units: 0 passed
  before the change and 6 pass after it (ConstructVolume,
  RenderDynamicMeshVolume, VolumetricShadowUpdate, W3DBridgeLoad,
  TerrainVisualAddFactionBibDrawable, TerrainVisualLoad).
- Hand adoptions (the lane finds no private view once the include is in
  place): W3DSnowManagerRenderSubBox (struct replaced by the include) and
  W3DDynamicLightSetFrameFade (include plus a TU-local
  `operator*(const Vector3 &, float)`). Both byte-match.

## Still blocked

- W3DSmudgeManagerRender: with the include, a TU-local
  `inline float Vector3::operator[] const` and TU-local `operator*`/`operator+`,
  it compiles, but render 0x000A6E08 diverges. The frame grows, and `vsVert`
  is spilled to and reloaded from the stack inside the vertex loop. The
  private view's non-forceinline constructors and reference-returning
  subscript give retail's shape. Restored.
- W3DCamTransform: inlines Lerp/Distance/Length, which the canonical header
  rows out of line. It also needs `operator=(const Coord3D &)` and a free
  `operator-`. Not attempted.
- W3DBridgeBuffer: needs free binary operators, as precedent TUs do. Not
  attempted.
- Byte FAILs after the change: ShadowGeometryInitFromMesh,
  ShadowGeometryMesh, RenderMeshVolumeBounds, Silhouette,
  UpdateOptimalExtrusionPadding, V2BuildBuffers, W3DMouseInitW3DAssets,
  PropBufferAddProp, PropBufferUpdatePropPosition.
- PropBufferRemovePropsForConstruction: Coord3D field rename ambiguity.
  W3DBuffBuffer: C1083. PropBufferRva000EE04A,
  SceneUpdateFixedLightEnvironments and TerrainBackground: no private view.
