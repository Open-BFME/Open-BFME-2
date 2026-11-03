# BfmeResetTextureRef consumer adoption, 2026-11-03

Inspected revision: da3da397f1 (after updating from origin/master 3a553802fe).
Scope: the nine queued consumers of the existing canonical header
`Code/Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h`.

Six consumers now include that header instead of private class definitions:
`BfmeResetTextureRefClear.cpp`, `bfme_reset_texture_ref_device.cpp`,
`bfme_reset_texture_ref_recreate_device.cpp`,
`MeshLoadContextAddLegacyMaterial.cpp`, `dx8wrapper.cpp`, and
`fxshadersetup.cpp`, all under `Code/Libraries/Source/WWVegas/WW3D2/`.

The header's four-byte `void *` storage is unchanged. Providers cast it to
their existing resource views. Mesh material loading retains the visible
noinline clear definition, and DX8 reset retains the visible destructor and
boolean conversion as definitions outside the shared class declaration.
This preserves the callers' code generation without another private class.
No aliases, pins, compiler flags, source paths or shared headers change.

`adopt.log` records the initial mechanical trial; `build.log` records the
final scoped build: 314/314 matched rows, 13 data rows, literals and imports
verified. The final frozen-file check passes for all six changed sources.
`accept.log` records the header lane's byte/link verdict and queue retirement.
These are local verification results, not a new census or real-link measure.

Three consumers remain queued and unchanged: `W3DTerrainBackground.cpp`
requires the private `TerrainInit` constructor tag, `Rva00136032Factory.cpp`
requires `BfmeNoInitFactory`, and `BfmeResetTextureRef.cpp` fails its converting
constructor after a mechanical swap. These failures already appear in the
existing queue; no new blocker or change to their next step is claimed.
The obstacle-register matches (LINK-012 and the post-85f6b7f40c LINK-150 entry)
concern other causes and remain unchanged.
