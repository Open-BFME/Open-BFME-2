# W3D rendering: WW3D2, WWMath and the W3D device layer {#sub_w3d_rendering}

Everything the player sees in the 3D world is drawn by Westwood's W3D engine.
It loads meshes, skeletons, animations and level-of-detail models from
`.w3d` files, keeps them in scenes, and draws them through `DX8Wrapper`, a
thin layer over the Direct3D device. On top of it, the W3D device layer
implements the game's display, camera, terrain, water, shadows, radar and
the draw modules that give each `Drawable` its look. Almost all of it is
game client code: it reads game state and never changes it.

This page maps the subsystem; its API group is \ref grp_w3d_rendering. When
the client draws a frame is on \ref page_frame_loop, and the seams for
porting the renderer are under \ref sub_w3d_rendering_remastering.

## Where it lives {#sub_w3d_rendering_where}

| Path under `Code/` | What is there |
|---|---|
| `Libraries/Source/WWVegas/WW3D2/` | the engine: `WW3D`, `DX8Wrapper`, render objects, meshes, hierarchies and animations, shaders and materials, textures, particles, scenes, cameras, lights, the 2D renderer and fonts, and BFME 2's FX shaders and asset registry |
| `Libraries/Source/WWVegas/WWMath/` | vectors, matrices, quaternions, bounding volumes, collision tests and culling systems |
| `Libraries/Source/WWVegas/wwshade/` | one small unit so far, from the shader library Zero Hour keeps there |
| `GameEngineDevice/Source/W3DDevice/GameClient/` | `W3DDisplay`, `W3DView`, `W3DGameClient`, terrain and its buffers, `Water/`, `Shadow/`, `Drawable/Draw/` (draw modules), `GUI/` (W3D drawing of window gadgets) |
| `GameEngineDevice/Source/W3DDevice/Common/` | `W3DModuleFactory` (draw module registration) and conversion helpers |
| `GameEngineDevice/Source/W3DDevice/GameLogic/` | `W3DTerrainLogic` and `W3DGhostObject`: device-specific code on the logic side |

Many files are split units or carry placeholder names, so search
`reverse/functions.csv` by class name rather than browsing by file
(\ref page_reading_code).

## Layers and key classes {#sub_w3d_rendering_classes}

- **Device.** `DX8Wrapper` owns the Direct3D device: adapter enumeration
  (`DX8Wrapper::Enumerate_Devices`), device creation and reset
  (`Create_Device`, `Reset_Device`), a cache of render states, textures and
  buffers that it applies before each draw (`Apply_Render_State_Changes`),
  and ending and presenting the scene (`End_Scene`). `DX8Caps` records what the card
  supports. Vertex and index buffers, including dynamic and sorting buffers,
  sit beside it.
- **Facade.** `WW3D` is a static class the game talks to: `WW3D::Init`,
  `Set_Render_Device`, `Set_Device_Resolution`, `Sync` (the frame's time
  base), `Render` for a render object, static sort lists for ordered
  drawing, gamma, screen shots and movie capture.
- **Render objects.** `RenderObjClass` is the base of anything drawable:
  `MeshClass` (with `MeshModelClass`, `MeshGeometryClass` and
  `MeshMatDescClass` for shared geometry and materials), `HLodClass`
  (level-of-detail models built on a skeleton), `CompositeRenderObjClass`,
  particle buffers and line renderers (`SegLineRendererClass`,
  `StreakLineClass`).
- **Animation.** `HTreeClass` is a skeleton; `HRawAnimClass` and
  `HCompressedAnimClass` are its animations, and `HAnimComboClass` combines
  several.
- **Materials.** `ShaderClass` (fixed-function blend and depth state),
  `VertexMaterialClass` and `TextureClass`. BFME 2 adds Direct3D effect
  shaders: `FXShaderAsset` loads an effect file and `FXShaderSetup` binds a
  mesh to one of its techniques and parameters.
- **Assets.** Render objects are created by name through the free function
  `Create_Render_Obj`, which asks the `AssetRegistry` for a prototype and
  returns null when there is none. `InitializeAssetManager` loads the asset
  index at start-up (\ref sub_w3d_rendering_modding).
- **Scenes and 2D.** `SceneClass`, `SimpleSceneClass` and the game's
  `RTS3DScene` hold render objects and lights; `CameraClass` and
  `LightEnvironmentClass` frame and light them. `Render2DClass`,
  `Render2DSentenceClass` and `FontCharsClass` draw screen-space images and
  text, and `SortingRendererClass` defers transparent triangles.
- **Math.** WWMath's `Matrix3D`, `Matrix4D`, `Vector3`, `Quaternion`,
  `AABoxClass`, `OBBoxClass`, `CollisionMath` and `GridCullSystemClass`.
  These are not render-only: game logic uses `Matrix3D` too, for example in
  object creation lists and weapons.
- **Device layer.** `W3DDisplay` is the game's `Display` (`TheDisplay`) and
  `W3DView` its camera. `W3DGameClient` creates the display, the font
  library and the snow manager through its factory methods. Terrain is `BaseHeightMapRenderObjClass` over `WorldHeightMap`,
  with `W3DRoadBuffer`, `W3DBridgeBuffer`, `W3DTreeBuffer`,
  `W3DShrubBuffer`, `W3DPropBuffer`, `W3DBibBuffer` and
  `W3DTerrainBackground`; water is `WaterRenderObjClass`. Shadows are
  `W3DVolumetricShadow` and its manager plus `W3DProjectedShadowManager`;
  `W3DShaderManager` holds custom shaders (Zero Hour: for terrain and screen
  filters). `W3DRadar`, `W3DMouse`, `W3DDisplayString`, `W3DSnowManager`,
  `W3DSmudgeManager`, `W3DVideoBuffer` and `CameraShakeSystemClass` complete
  it.

## Start-up and per-frame entry points {#sub_w3d_rendering_entry}

`W3DDisplay::init` brings the renderer up, in this order:

1. creates the W3D file system, initialises WWMath and creates three scenes
   (3D interface, 2D and the main `RTS3DScene`), giving the interface and 2D
   scenes white ambient light;
2. creates pairs of directional global lights, as many as the global data
   asks for, and applies the current time of day;
3. calls `WW3D::Init` on the game window and sets its static render options;
4. creates the 2D renderer, picks a static detail level if none is set yet,
   and opens the device at the configured resolution with 32-bit colour,
   falling back to 800x600, and throwing if that fails too;
5. sets the 2D renderer's range to the screen in pixels, loads the asset
   index (`InitializeAssetManager`), applies gamma, initialises
   `W3DShaderManager` and the streak renderer, and sets up the debug
   display.

Device creation and the shader manager's set-up run under a DX8 thread lock.
`W3DView::init` creates the 3D camera and a 2D camera.
`W3DModuleFactory::init` registers the W3D draw modules after the base
module factory's (\ref sub_rts_model).

Each client frame, `GameClient::update` updates the display and asks it to
redraw (\ref sub_gameclient). Where Zero Hour's `GameClient::update` calls
`Display::draw`, BFME 2 calls a display method at a different slot. BFME 2's
`W3DDisplay::draw` is not yet reconstructed, so its order (Zero Hour: sync
the animation clock, begin rendering, draw each view, draw the 2D overlay,
end rendering) is not confirmed here.

## How it connects {#sub_w3d_rendering_connects}

- **Driven by the client.** `GameClient` owns the display and the drawables;
  each `Drawable` renders through its draw modules (\ref sub_gameclient,
  \ref sub_objects_modules).
- **Reads the map and the logic.** `W3DTerrainLogic` is the device's
  `TerrainLogic` (\ref sub_gamelogic_map). Its `loadMap` builds a
  `WorldHeightMap` from the map only to record the extents and height range
  that game logic uses, then releases it. When the terrain render object
  loads roads and bridges (`BaseHeightMapRenderObjClass::loadRoadsAndBridges`),
  it hands `W3DTerrainLogic` to the bridge buffer. Draw modules read object
  state such as position and model conditions.
- **Draws the UI.** The window manager's gadgets and the Apt UI draw images
  and text through `W3DDisplay` and `Render2DClass` (\ref sub_gui_apt).
- **Files.** Compiled shaders are read through the game's file system and
  its BIG archives (\ref sub_common_services). The asset index is not:
  `InitializeAssetManager` opens its files directly
  (\ref sub_w3d_rendering_modding). Detail presets are INI data
  (\ref sub_ini).
- **Foundation.** WWLib supplies containers, file classes and strings
  (\ref sub_wwlib_thirdparty).

## BFME 2 compared with Zero Hour {#sub_w3d_rendering_zh}

- **Direct3D 9.** Zero Hour's `DX8Wrapper` drives Direct3D 8. BFME 2 keeps the
  class and most of its API but `DX8Wrapper::Init` loads `D3D9.DLL` and
  creates the interface through `Direct3DCreate9`; effects and some math go
  through `d3dx9_27.dll`, among other uses.
- **Effect shaders.** Meshes can carry an FX shader chunk naming an effect
  and technique (`FXShaderSetup::Load_W3D`), loaded through D3DX effects. Zero
  Hour does not use D3DX effects.
- **Assets.** Zero Hour creates render objects through `W3DAssetManager`, a
  `WW3DAssetManager`. BFME 2 uses `AssetRegistry`, `Create_Render_Obj` and an
  `asset.dat` index. BFME 1 has the same registry, in its own
  `assetmanager` library.
- **Draw modules.** Zero Hour registers 19 W3D draw modules, among them
  `W3DModelDraw`, the Overlord, police car, science and tracer draws. BFME 2
  registers 20: `W3DDefaultDraw`, `W3DDebrisDraw`, `W3DScriptedModelDraw`,
  `W3DHordeModelDraw`, `W3DLaserDraw`, `W3DQuadrupedDraw`, `W3DRopeDraw`,
  `W3DSupplyDraw`, `W3DTruckDraw`, `W3DTankDraw`, `W3DTreeDraw`,
  `W3DFloorDraw`, `W3DPropDraw`, `W3DLightDraw`, `W3DBuffDraw`,
  `W3DStreakDraw`, `W3DSailModelDraw`, `W3DBoatWakeModelDraw`,
  `W3DProjectileStreamDraw` and `W3DTornadoDraw`. `W3DModelDraw` code is
  still present, but the name is not registered. BFME 1 registers 16; BFME 2
  adds the sail, boat wake and tornado draws and has Zero Hour's projectile
  stream draw again.
- **Terrain.** The shrub buffer and the taint visuals are not in Zero Hour;
  BFME 1 has both.

## Modding notes {#sub_w3d_rendering_modding}

- **Models are data.** Meshes, skeletons, animations and LOD models come
  from `.w3d` files and are created by name. `Create_Render_Obj` lower-cases
  the name before the registry lookup.
- **Effect files.** `FXShaderAsset` first looks for a precompiled effect at
  `Shaders/Compiled/<name>o` through the game's file system, so a BIG archive
  can supply it. Otherwise D3DX compiles `Shaders/<name>` itself, which reads
  the loose file from disk rather than through the game's file system. Effects
  are compiled with the macros `_WW3D_` and `_WW3D_VERSION_` (set to 1). A
  static flag adds a third macro, `_W3DVIEW_`, and skips the precompiled
  path; no retail code sets it, so its link to a W3D viewer is inferred from
  the macro name. The technique named `_CreateShadowMap` is also looked up by
  name and stored separately.
- **The asset index.** `InitializeAssetManager` reads every `asset.dat` it
  finds, in turn: the first entry named `asset.dat` in the BIG file (`BIGF`
  or `BIG4`) named in the global data, opened and parsed directly by path,
  not through the game's file system; then `<asset directory>\asset.dat`;
  then `asset.dat` in the working directory. It reports failure when the last
  is missing or does not parse, which `W3DDisplay::init` does not check. The
  format of the index is not yet documented here.
- **Detail presets.** `StaticGameLOD` INI blocks set per-level options such
  as `ModelLOD`, `EffectsLOD`, `ShaderLOD`, `ShadowLOD`, `WaterLOD`,
  `MaxParticleCount`, `UseShadowVolumes`, `UseShadowMapping`,
  `UseTerrainNormalMap`, `ShowProps` and `TextureReductionFactor`. These
  names come from the field table in the retail executable.
- **Hard-coded.** The list of draw module names (a new kind of draw module
  needs code), the 800x600 fallback mode, 32-bit colour and the 4:3 view
  plane of the 2D camera.
- **Lockstep.** Zero Hour: rendering is client-side and is not part of the
  logic CRC. In BFME 2, game logic does use WWMath (`Matrix3D`) and
  `W3DTerrainLogic`, so changing their arithmetic or terrain loading can
  desynchronise multiplayer games and change replays
  (\ref sub_save_load_crc).

## Remastering notes {#sub_w3d_rendering_remastering}

- **Backend seams.** A new renderer can replace Direct3D 9 below
  `DX8Wrapper`, but must also replace the D3DX effect interface that
  `FXShaderAsset` and `FXShaderSetup` use directly and the D3DX calls in
  WWMath (below). Alternatively it can replace W3D above it by implementing
  `Display`, `View` and the `W3DGameClient` factories, plus the draw modules
  `W3DModuleFactory` registers.
- **D3DX in the math library.** `Matrix3D::Get_Inverse` calls
  `D3DXMatrixInverse`, and `Fast_Slerp` can hand off to
  `D3DXQuaternionSlerp`. Both are W3D-side dependencies on `d3dx9_27.dll`
  (their known callers are camera, mesh and animation code), so a port
  without D3DX must replace them. Whether any game-logic result depends on
  them has not been traced.
- **Resolution and aspect.** The device size comes from the global data and
  `W3DDisplay::setDisplayMode` changes it at run time, resizing the 2D
  coordinate range to match. The 2D camera made by `W3DView::init` has a fixed
  4:3 view plane, as in Zero Hour.
- **Presentation.** In windowed mode `W3DDisplay::init` sets the swap
  interval to zero, which selects immediate presentation (no wait for
  vertical sync); in full screen it clips the cursor to the window.
- **Threads.** Zero Hour's WW3D locks only in its texture loading and
  texture file cache code. BFME 2 also guards the device: `DX8Wrapper::Init`
  creates a device mutex, and `DX8Wrapper::Init`, `W3DDisplay::init` (device
  creation and shader set-up), `W3DDisplay::setDisplayMode` and
  `FXShaderAsset::Impl::Load` all take the same device lock. Which threads
  contend for it is not yet traced.

## State of the reconstruction {#sub_w3d_rendering_state}

The subsystem is large, and much of it is already byte-matched. WWMath is
almost entirely named. WW3D2 is largely named:
the device wrapper, meshes, HLODs, animations, particles and the 2D renderer
are recognisable Zero Hour classes, while BFME 2's dynamic buffers, sorting
draws and effect binding still carry many placeholder or role names. The W3D device
layer is the least settled part: `W3DDisplay`, the terrain and shrub buffers
and the screen filters have many placeholder-named rows, and
`W3DDisplay::draw` is not reconstructed. Many WW3D2 and device-layer files
do not link yet (`tools/link_rank.py` shows what holds them back), and
`reverse/canonical_classes.csv` lists which classes have a shared header.
To refresh this picture, search `reverse/functions.csv` and
`reverse/link_status.csv` for the directories above.

## Reading list {#sub_w3d_rendering_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/`:
  `Libraries/Source/WWVegas/WW3D2/` (`ww3d.cpp`, `dx8wrapper.cpp`,
  `mesh.cpp`, `hlod.cpp`), `Libraries/Source/WWVegas/WWMath/` and
  `GameEngineDevice/Source/W3DDevice/GameClient/` (`W3DDisplay.cpp`,
  `W3DView.cpp`, `BaseHeightMap.cpp`).
- BFME 1, in Open-BFME-1's `game/` tree: the same directories, plus
  `Libraries/Source/assetmanager/` and
  `GameEngineDevice/Source/W3DDevice/Common/Thing/W3DModuleFactory_init.cpp`.
- Matching notes in `docs/reconstruction/`: the `dx8wrapper-*.md` files,
  `dynamic-vertex-buffer.md`, `hlod-base-layout.md` and
  `animation-frame-modes.md`.
