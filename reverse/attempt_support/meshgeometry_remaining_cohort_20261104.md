# MeshGeometryClass: remaining four consumers

Inspected base: `f23f469a4f`. Scope: the four consumers selected by
`next_work.py --claim`, under the `class:MeshGeometryClass` claim. This extends
the earlier four-file repair recorded in `meshgeometry_header_adoption_20261104.md`.
No source paths, function identities, aliases or ledger extents change.

## Target facts and local changes

The existing canonical header documents geometry's 0x8C extent, its primary
RefCountClass base, secondary MultiListObjectClass base at +8, Flags at +0x18,
VertexCount at +0x28, normals at +0x38/+0x3C and shade indices at +0x4C.
These agree with the private views and accesses in the four consumers.

- `MeshMatDescFXShaderConversion.cpp`: use the canonical list base and geometry
  header. The native culling parameter still tests bit 0x100 directly at +0x18.
  Suppress the reference multilist declarations, whose mempool include otherwise
  introduces a second Debug class; `<new>` already owns placement operators.
- `meshmdl.cpp`: use always.h's empty W3DMPO and the existing canonical list
  base with the geometry header. Preserve the two unsigned byte accesses at
  +0x19 by indexing the canonical Flags word's byte representation. The model's
  existing byte-mask helper and constants retain their semantics.
- `mesh_get_shade_indices.cpp` and `mesh_get_vert_normals.cpp`: use the canonical
  geometry header instead of the broad rendobj.h include. Retain the existing
  reference RefCountClass declaration under its original size optimization;
  suppress the competing RefCountData.h declaration at the geometry include.
  This preserves the inline base destructor and its generated deleting wrapper.
  Keep the
  existing pointer-to-member emission anchors in fieldless derived accessors,
  preserving protected access without another geometry layout. The alternate
  normals buffer uses the header's neutral slot3C spelling.

The automatic four-file adoption initially applied none (C2011/C2084 header
conflicts). The first manual converter trial additionally exposed the reference
Debug collision; using the canonical list base resolved it locally. The shared
headers are unchanged. No new donor identity or member name is inferred.

The first byte-exact accessor trial also adopted RefCountData.h. Header
acceptance refused both files: the preview lost their 344 and 170 census-linked
bytes because `??_GRefCountClass@@MAEPAXI@Z` was not retail's body. That header
declares the base destructor out of line, unlike the reference inline body.
Retaining the existing reference base is therefore necessary for this geometry
adoption; this work does not claim RefCountClass header adoption.

## Verification

- Accessor build: **4/4 rows** byte-match across the two files, including the
  unsigned-long shared-buffer constructor and deleting destructor. String,
  float and import reference checks pass.
- Converter/model build: **23/23 rows** byte-match, including EH funclets verified
  through parent EH data after compiler label renumbering. The 57 literals,
  two empty-string references, four compiler float literals and import checks pass.
- All four files pass `find_declared_unmatched.py`; the shade accessor's existing
  admitted emission marker is unchanged.

- Final four-file `header_adopt_lane.py accept --class MeshGeometryClass`:
  **PASS for all four** on 2026-11-05. Its structural checks, byte gates and
  link previews preserve census-linked bytes. The lane retired four queue rows
  in total (two in the initial converter/model acceptance, two in the final pass).
- Published index: 2026-11-04 22:40, census commit `3a95b274a2`;
  SHA-256 `794a70c21bcb5471b1e2a811d380f9e4029f5c06432f7bec2dfe1c240d126256`.
- `git diff --check` passes. No new census or linked-byte increase is claimed.
