# FXShaderSetup TU merge (2026-11-04, claudeb)

Target TU: `Code/Libraries/Source/WWVegas/WW3D2/FXShaderSetup.cpp` (tu_map path;
the file is the case variant `fxshadersetup.cpp`).

## Landed

- `2ad621d0c4`: `tu_skeleton --merge` absorbed 10 donors (FamilyDeletingDtors_muse-b4f6,
  Rva00152DC6Adapter, Rva001524CAEmptyHelp, Rva00151ECDLen, Rva00151FA8RamSize,
  Rva00152BDBValueVectorResize, StlSweepW5Rva00151FE7, stlport_vector_rva00151dab_clear,
  _destroy, _dtor). `./build.sh`: 69/69 rows matched.
- `9ebc31c72f`: one `Rva00151DAB` view (D3DXHANDLE m_parameter, RefCountPtr<TextureClass>
  m_texture, declared operator=) across the TU, Rva00151E30Assign.cpp and Rva00152004Copy.cpp;
  71/71 matched.
- Second merge: those two donors absorbed; 71/71 matched, find_declared_unmatched clean.

## Still rejected (tu_skeleton --merge --dry-run, after 9ebc31c72f)

| donor | refusal | cause |
| --- | --- | --- |
| FXShaderSetup_UpdateDynamicParameterSet.cpp | C2065 `m_chain` | private FXShaderSetup view; header_queue row FXShaderSetup (m_chain +0x8, 24 bytes) |
| Rva00152D1C.cpp | C2065 `m_ShaderAsset` | includes canonical FXShaderSetup.h, seed still has its private FXShaderSetup (header_queue: seed compile fails C2143/C2433) |
| StlSweepW5Rva00151E4D.cpp | C2953 StringBase redefined | private StringBase<char> template; also /O1 /D_STLP_NO_EXCEPTIONS flags |
| Rva0015229CEraseRange.cpp, stlport_vector_rva0007bb16_assign.cpp | C2036/C2011 | hand-rolled `_STL` vector/__false_type declarations clash with real <vector> |
| StlSweepW4Rva001524F9.cpp | compile (no message) | not investigated |

Next step: adopt canonical FXShaderSetup.h in the seed (header lane: its fields are void* opaque,
the seed's methods use typed vectors and the asset holder, so the header needs typed members first),
then rewrite the hand-rolled STL donors against the real STLport headers.
