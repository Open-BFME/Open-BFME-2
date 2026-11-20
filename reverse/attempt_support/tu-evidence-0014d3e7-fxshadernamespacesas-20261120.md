# TU evidence handoff: `0x0014D3E7..0x0014D9F3` (`fxshadernamespacesas.cpp`)

- Date: 2026-11-20
- Served item: `tu-evidence` no-signal run `0x0014D3E7..0x0014D9F3` (10 rows in 10 sources under `Code/GameEngine/Source/Common/Rva0014D*.cpp`).
- Outcome: `blocked` (no re-checkable anchor reachable without tooling/lead updates; no files modified).

## Target facts

1. Every row in the run belongs to the retail `fxshadernamespacesas.cpp` object (`0x0014D1E3..0x0015115B`), whose surrounding functions are already matched in `Code/Libraries/Source/WWVegas/WW3D2/fxshadernamespacesas.cpp`:
   - `0x0014D3E7` (`Rva0014D3E7Set.cpp`) and `0x0014D405` (`Rva0014D405Clear.cpp`): called on `g_00DF36B4` (`FXShaderParameterSourceNamespaceSAS *`) in `MeshClassRenderWithFXMaterial.cpp`; set/clear `m_SourceNamespace_Skeleton` (`+0xB8`) fields `+0x10/+0x14/+0x18`.
   - `0x0014D417` (`Rva0014D417Set.cpp`) and `0x0014D431` (`Rva0014D431Clear.cpp`): called on `g_00DF36B4` (`FXShaderParameterSourceNamespaceSAS *`) in `FXShaderRenderer.cpp`; set/clear `+0xD0/+0xD4` (`m_SourceNamespace_Skeleton` `+0x18/+0x1C`).
   - `0x0014D522` (`Rva0014D522Init.cpp`), `0x0014D722` (`Rva0014D722Init.cpp`), `0x0014D7D4` (`Rva0014D7D4Init.cpp`), `0x0014D887` (`Rva0014D887Init.cpp`), `0x0014D982` (`Rva0014D982Init.cpp`), `0x0014D9F3` (`Rva0014D9F3Init.cpp`): callbacks bound directly in `fxshadernamespacesas.cpp` by `SourceNamespace_Camera::ResolveBindings`, `SourceNamespace_DirectionalLight::ResolveBindings`, `SourceNamespace_PointLight::ResolveBindings`, and `SourceNamespace_Shadow::ResolveBindings`.
   - `.text$x` confirms ordering: `0x00766905..0x00766959` (`AnimationAsset.cpp`) is immediately followed by `0x00766963..0x0076696B` (`0x0014D1E3` `SourceNamespace_Shadow::~SourceNamespace_Shadow`), `0x00766975..0x0076697D` (`0x0014D982`), `0x00766987..0x007669BD` (`fxshadernamespacesas.cpp`), and `0x007669DF..0x00766A20` (`FXShaderParameterSourceNamespaceSAS.cpp` provisional).

2. Why `tools/tu_map.py` and `tools/tu_evidence.py` leave all 10 rows without a TU:
   - **No `F`**: `reverse/string_xrefs.tsv` contains no `__FILE__` string anywhere in `0x0014D100..0x00151200` (only parameter path strings like `"NearFarClipping"`, `"ShadowMap"`, etc.).
   - **No `Z`/`S`/`L`**: `FXShaderParameterSourceNamespaceSAS` is BFME 2-only (absent from Zero Hour) and not vendored.
   - **No `W`**: `reverse/wb_name_leads.csv` has no `wb_file` entry anywhere in `0x0014D100..0x0015115B` (only `0x0014D9F3` with empty `wb_name` and `wb_file`).
   - **No `N`/`C`/`T`/`E` bracket**: `FXShaderParameterSourceNamespaceSAS.cpp` is only provisionally approved (`by=N`) from `0x0014F778..0x001510C2`. Earlier rows in `fxshadernamespacesas.cpp` (`0x0014D1E3..0x0014F00A`) belong to nested classes (`SourceNamespace_*@FXShaderParameterSourceNamespaceSAS@@`), which `tu_map.py`'s single-level `CTOR`/`METHOD` regexes do not extract for `N`, and `0x0014DB78` (`??0FXShaderParameterSourceNamespace@@QAE@ABV0@@Z`, implicit copy ctor emitted in `fxshadernamespacesas.cpp`) emits a proposed N-only `FXShaderParameterSourceNamespace.cpp` row in the middle of the span, blocking contiguity `C` (`T` only brackets on `F/Z/L`).
   - Renaming `Rva0014D3E7..Rva0014D431` alone cannot pass `tu_map.py`: no canonical rename basis exists (`caller` spelling is a hint only), their `Code/GameEngine/Source/Common/` directory would yield the wrong `N` path, and `0x0014DB78` plus `UNION_SPAN` (`0x2000` vs `0x3CDB` span) still block contiguity.

## Unblocking prerequisites

- Either `reverse/wb_name_leads.csv` needs WorldBuilder file-path leads for `FXShaderParameterSourceNamespaceSAS` (providing `W` anchors on `fxshadernamespacesas.cpp`), or a tooling seat (`Verifier-Change:`) needs to evaluate outer-class extraction for nested classes (`Inner@Outer@@`) and non-ZH implicit copy constructors in `tools/tu_map.py` against the 99% held-out gate.
