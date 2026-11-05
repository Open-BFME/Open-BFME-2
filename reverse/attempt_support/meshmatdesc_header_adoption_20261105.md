# MeshMatDescClass header adoption, 2026-11-05

Inspected source revision: `7414ae32f5`. Claim owner:
`yasinschroeder-codexb`. Scope is the eight-unit packet served by
`next_work.py --claim`, not all remaining MeshMatDescClass consumers.

Target facts come from the existing canonical header's retail-body evidence:
MeshMatDescClass has size 0x118, its state pointer is at +0x0C, its reference
slots start at +0xB8 and +0x108, and its texture handles occupy +0x78..+0x97.
This pass establishes no new donor names or original source paths.

## Adopted units

All paths below are under `Code/Libraries/Source/WWVegas/WW3D2/`.

| Unit | Integration | Matched rows | Link preview, bytes before -> after |
| --- | --- | ---: | ---: |
| MeshMatDescOpaqueBuffer.cpp | canonical reference-count declaration, local inline base teardown, field_108 | 11 | 670 -> 670 |
| MeshModelLegacyMaterials.cpp | shared ShaderClass/reference-count declarations; existing owning-handle view converts to canonical RefCountPtr parameter | 6 | 735 -> 735 |
| MeshModelReadShaderIds.cpp | preserve inline Has_Shader_Data definition outside the class | 2 | 349 -> 349 |
| MeshModelReset.cpp | canonical geometry include avoids competing reference-count declarations; field_0C replaces RendererState | 3 | 214 -> 214 |
| meshmdl.cpp | field_0C replaces the old view's UV[0] at +0x0C; index the first canonical field_B8/field_108 slots | 14 | 1,059 -> 1,059 |
| seglinerenderer.cpp | replace declaration-only private descriptor with canonical include | 21 | 18,516 -> 18,516 |

The UV[0] spelling in meshmdl.cpp did not prove a UV access: the removed view
placed it immediately after the three counts, at +0x0C. The canonical state
pointer preserves that target displacement. No function body was moved and
no header, pin, alias, data register or hatch baseline was changed.

## Verification

- Initial and final `find_declared_unmatched.py` checks passed. The existing
  opaque-buffer and segment-renderer emission aids remain unchanged in role.
- Final `./build.sh` on the six adopted sources: **57/57 matched**, one string
  literal, 27 compiler float literals and two named imports verified. Eleven
  existing funclet labels were renumbered; the verifier resolved the current
  bodies, including parent EH proofs. No funclet ledger hint was hand-added.
- `header_adopt_lane.py accept --class MeshMatDescClass` passed for every
  adopted source and retired exactly six rows through the owning tool.
- Joint `link_check.py` preview against fetched index **c95fcfcfcd**, census
  **2026-11-05 05:17**: all six units LINKS, **21,543 -> 21,543 bytes**.
  Diagnostics for unreferenced Add_Ref copies and the existing DX8Wrapper
  Get_Transform copy were explicitly non-blocking.
- This is header debt retirement and preservation of the existing link preview;
  no new census, linked-byte gain, real game link or runtime result is claimed.

## Remaining packet members, unchanged

`MeshModelReadTextureIds.cpp`: automatic adoption refuses its opaque prefix.
A manual canonical include plus out-of-class inline Has_Texture_Data compiles,
but read_texture_ids at 0x00189140 (293 bytes) no longer matches. Both the
handle comparison and a direct `.Peek()` comparison change the inlined test
from a memory compare to a load/test, then change register allocation and
stack slots in the reader. The original source was restored; its queue row
remains. Next check: isolate the owning-handle predicate's optimizer/alias
interaction before altering the reader or the shared header. The original
matched function is already present; this was a failed header integration,
not a missing-function reconstruction.

`bfme2_mesh_material_pass.cpp`: automatic adoption refuses duplicate local
templates (C2953/C2955). Its private descriptor also exposes convenience
methods absent from the canonical API. The source and queue row remain
unchanged. Next check: reconcile the local RefCountPtr template/include
boundary and those helpers in this TU before retrying the canonical include.
