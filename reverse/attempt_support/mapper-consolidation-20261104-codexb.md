# mapper.cpp consolidation prerequisite trial (2026-11-04)

Inspected revision: `14de04da9b`. Claim owner: `yasinschroeder-codexb`.
No source, header, ledger ownership or hatch change retained.

## Current-input checks

- `check_csv.py`: passes (99,450 function rows).
- `find_declared_unmatched.py` for mapper.cpp and the three candidate donors:
  passes; mapper.cpp reports 93 matched rows.
- `name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/`:
  planner completed; committed TU map was stale, so its placements are hints.
  `tu_skeleton.py` rebuilt the map in memory for the actual merge trial.
- `tu_views.py mapper.cpp --dry-run`: BfmeVciAnchorElem already shared;
  TextureMapperClass, GridTextureMapperClass, ScaleTextureMapperClass and
  LinearOffsetTextureMapperClass have conflicting base clauses.
- `tu_skeleton.py --merge mapper.cpp --dry-run`: 112 approved rows, no
  accepted donors. TextureMapperSlot8.cpp: C2039, missing `_bfme_mapper_v8`.
  TextureMapperFXShaderConvert.cpp: Debug and StringBase redefinitions.
  TextureMapperApply.cpp: bytes. The guard identified all four inputs as
  census-linked. No write was attempted.

## Bounded hypothesis and result

Target facts: the existing Slot8 row at 0x00182150 is a five-byte false
returner popping one argument; its ledger evidence identifies vtable +0x20.
The included `reference/shims/bfmemapper/mapper.h` lacks that member between
Needs_Normals and Calculate_Texture_Matrix. The later include of the
`bfme_grid_mapper_link` variant is suppressed by the same include guard.

Trial: include the existing grid-specific variant first and declare
`virtual bool _bfme_mapper_v8(int unk)` after Needs_Normals. Only mapper.cpp
uses that variant. This is an ABI hypothesis, not recovery of the unknown
argument type or original member name.

`./build.sh mapper.cpp` refused one of 92 function rows: the grid-specific
variant's dllimport/forceinline declaration suppresses the rowed external
calculate_uv_offset helper. The other function rows and the data row passed.
This helper declaration must retain its existing out-of-line ownership.

Joint `link_check.py mapper.cpp TextureMapperSlot8.cpp` also refused the TU:
TextureMapperClass and WSEnvMapperClass vtable COMDATs differ from the selected
copies (no resolved retail address in this preview). Slot8 alone still links.
Index: census 2026-11-04 17:56, revision `8c757ea0db`.
This proves the proposed local change cannot be landed independently; it does
not prove which competing vtable is correct or establish a census gain.

Both edits were reverted. `./build.sh mapper.cpp` then passed on the restored
source. No alternatename, pin, protected-register or header-queue key retired.

## Next useful work

Reconcile the selected TextureMapperClass and WSEnvMapperClass vtable providers
with the target's ten-slot tables, preserving calculate_uv_offset's external
definition, before retrying Slot8 or Apply composition. The shader-conversion
donor separately needs Debug/string include reconciliation and matching mapper
base/field views. Do not repeat the unchanged merge dry run as new evidence.
