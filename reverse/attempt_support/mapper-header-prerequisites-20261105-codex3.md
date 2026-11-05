# Mapper header prerequisites, 2026-11-05

Inspected revision: `7cbd36821e`. Scope: `mapper.cpp` and
`TextureMapperFXShaderConvert.cpp` under `Code/Libraries/Source/WWVegas/WW3D2/`.
This advances LINK-289's prerequisites; no TU merge is retained.

## Retained changes

- Load the target `Debug` declaration before the reference debug macros and
  suppress the reference `debug_debug.h` declaration. This removes the Debug
  redefinition encountered when the FX donor joins the mapper TU.
- Replace mapper's private `MaterialInfoClass` view with its canonical header.
  The TU already has the reference `RefCountClass`; suppressing the duplicate
  base header preserves that existing base. Both bases have an eight-byte
  release layout, count at +4 and `Delete_This` at slot zero, as documented by
  `RefCountData.h`'s target facts. Call inherited `Release_Ref` rather than the
  private `bfme_release` helper.
- Select the FX donor's existing BFME2 ASCII shim explicitly. With merged
  include directories, the bare include selected the WWLib string definitions
  and then collided with the BFME2 ASCII header included by the callsite shim.
  No compiler flags, shared headers, aliases or pins change.

## Verification

`./build.sh mapper.cpp TextureMapperFXShaderConvert.cpp` (full source paths):
98/98 function rows and one data row pass; string, float and import checks pass.
`find_declared_unmatched.py` passes for both changed sources.

`header_adopt_lane.py accept --class MaterialInfoClass` on mapper passes and
retires its single `reverse/header_queue.tsv` row through the owning tool.

Paired `link_check.py` previews pass using the fetched census index at
`c95fcfcfcd`, 2026-11-05 05:17 UTC: mapper 12,573 -> 12,573 bytes; FX donor
1,552 -> 1,552 bytes. The mapper's existing unreferenced Get_Transform and
Matrix4 constructor copy diagnostics remain. These are unit previews, not a
real link or a census gain. An attempted precommit batch audit was inconclusive
because the working tree differed from its supplied HEAD tip; publication's
batch audit must assess the actual outgoing commit and affected consumers.

## Remaining consolidation work

The current-input `tu_skeleton.py --merge .../mapper.cpp --dry-run` still
accepts zero of three donors. Header conflicts are cleared, exposing:

- Slot8: `_bfme_mapper_v8` is absent from `TextureMapperClass`.
- FX donor: `ScaleTextureMapperClass::rva00187690` and `Mapper_ID` do not agree
  with the mapper TU's declarations.
- Apply donor: byte mismatch.

The dry run began before header acceptance, so its `adopt_first` output still
lists the now-retired MaterialInfo row. No failing merged source is retained.
Next reconcile the mapper class declarations, inheritance and selected vtable
providers in a separately byte-verified prerequisite, retaining the external
`calculate_uv_offset` row described in the earlier LINK-289 evidence. No new
claim about donor names, source provenance or census coverage is made.
