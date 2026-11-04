# MeshGeometryClass header adoption, 2026-11-04

Inspected base: `31ecf72513`. Scope: the eight-file cohort selected by
`next_work.py --claim`; class claim `MeshGeometryClass`, with explicit file
claims for the four edited units. No source paths or function identities move.

## Target evidence and change

`MeshGeometryClass.h` documents retail's 0x8C extent, the +0x18 flag word,
primary-table slot +0x0C `Compute_Plane_Equations`, and the secondary list
base at +8. The constructor/destructor private views already used this extent
and these bases. The plane-wrapper private view called slot +0x0C after testing
bit 2 at +0x18. Replacing these views therefore uses established target facts;
no donor layout or new function name is inferred.

- `MeshModelClassDefaultCtor.cpp`: include the canonical geometry header while
  retaining the existing canonical list headers. Suppress the reference
  `multilist.h` declarations via its include guard, since the required list
  declarations are already present. Select the header's inline integer
  `Set_Flag` overload explicitly; the enum overload is an out-of-line declaration
  and changes retail's inline flag store into a call.
- `MeshModelClassDtor.cpp`: same include reconciliation. Cast `Flags` to unsigned
  for the existing skin-bit shift, preserving the old unsigned private field's
  expression semantics while using the header's signed field.
- `MeshModelClassCopyCtor.cpp`: retain the existing list declarations and their
  optimization settings, and suppress the reference duplicate before including
  the canonical geometry header. The separate GenericMultiListClass header debt
  is retained; this change makes no claim to resolve it.
- `Rva00925030GetPlanesChecked.cpp`: use the canonical Flags/DIRTY_PLANES and
  Compute_Plane_Equations declarations. Add the reference include directories
  needed by the geometry header. Preserve the provisional owner/method identity.

## Verification

- Initial automatic `header_adopt_lane.py adopt --apply` attempted all eight
  selected units and applied none. The constructor group hit duplicate list
  declarations; the plane wrapper lacked reference include paths.
- `./build.sh` on the final default-constructor/destructor pair: **15/15 rows**,
  including EH funclets and the data row, exact. Parent EH data uniquely verifies
  compiler-renumbered funclet labels; no ledger object-symbol edits are needed.
- `./build.sh` on the final copy constructor: **7/7 rows**, including its four
  funclets, exact.
- `./build.sh` on the final plane wrapper: **1/1 row (41 bytes)** exact.
- `find_declared_unmatched.py` on all four final files: all definitions matched.
- `header_adopt_lane.py accept --class MeshGeometryClass` PASS for all four
  final units: structural/include checks, byte gates, and link previews preserve
  census-linked bytes. The tool itself retired four rows from header_queue.tsv.

## Remaining cohort work

The other four files are unchanged and retain their header-queue entries:
MeshMatDescFXShaderConversion.cpp, mesh_get_shade_indices.cpp,
mesh_get_vert_normals.cpp, and meshmdl.cpp. Their automatic trials still report
header-layout compile conflicts (C2084/C2011). Reconcile their existing reference
RefCountClass/Vector3/W3DMPO declarations before retrying adoption; the small
constructor-specific list include treatment alone does not address those inputs.

No census measurement or linked-byte increase is claimed.
