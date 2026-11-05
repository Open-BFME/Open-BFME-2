# MeshModelClass deformation header adoption

Inspected revision: `3e204a566d8bde122a8cce45df6c96c68a5bf0c4`.
Worker: `yasinschroeder-codexb`. This is header-debt cleanup.

The existing canonical MeshModelClass/MeshGeometryClass headers document the
vertex count at +0x28, position-buffer pointers at +0x30/+0x34, normal-buffer
pointers at +0x38/+0x3C, bone links at +0x50 and bone/run buffer at +0x54.
Both deformation units used padded private model declarations spanning these
fields, which the automatic offset mapper could not replace (LINK-565).

The two units now include MeshModelClass.h, use its named fields and index
its adjacent position/normal pointer pairs in the existing stream loops.
The two-stream unit's existing minimal buffer template takes the canonical
ShareBufferClass spelling so those fields have their declared pointer types.
No shared header, function ledger identity, pin, alias or source path changes.
The remaining local buffer/HTree/transform views are outside this adoption.
This does not claim original source recovery for those views or their members.

Verification:

- `./build.sh MeshModelClass_get_deformed_vertices.cpp
  Rva0016BF40DeformedVertices.cpp`: 2/2 matched rows, 2,237 and 2,960 bytes;
  all 12 floating literals verified, string/import checks pass.
- Before and after declared-unmatched checks pass. Original sources were
  rebuilt through the normal builder for the provider comparison, then the
  final sources restored and rebuilt successfully; no direct cache compilation.
- Every common emitted code symbol has identical bytes and relocation targets
  before/after, including both rowed deformation bodies. Removed external code
  definitions: MeshModelClass::Get_Vertex_Count() const in both units, and the
  two BfmeSkinBuffer::Get_Array specializations in the two-stream unit.
  Added definitions are MeshGeometryClass::Get_Vertex_Count() and the equivalent
  ShareBufferClass::Get_Array specializations. Other external bindings agree.
- Scanned all 139,752 `.obj` files under build/ (including the imported store
  and historical builds; excluding the four explicit before/after evidence
  copies directly in build/). Exact COFF-symbol inspection finds **zero
  undefined references** to any of those three removed helper names.
  MeshModelClass::Get_Vertex_Count() const also remains defined in eight
  build/match objects and one historical scratch object. The old BfmeSkinBuffer
  helpers have neither remaining definitions nor undefined references.
- One `header_adopt_lane.py accept --class MeshModelClass` over the complete
  eleven-file selected cohort accepts these two files and retires exactly
  their two header_queue.tsv rows. Its exit is 1 because the other nine
  unchanged members still declare private bodies; their queue rows remain.
- Joint current-object `link_check.py` against index `112a456a2c`
  (2026-11-05 15:52): both LINKS, preserving 2,234 + 2,957 = 5,191 credited
  bytes. These exclude trailing alignment bytes counted in the row extents.
  The existing unreferenced BoneTransform::TransformPositionArray diagnostic
  in the two-stream object remains; its bytes/relocations are unchanged.

No census, real-link result, runtime result or linking gain is claimed.
Nine other members of the original cohort still need the list-specialization,
inline-forwarding, member-scoped mapping and include-context repairs in the
previous LINK-565 evidence. The opaque deformation-prefix blocker is resolved
for these two units. No source-path compatibility audit is needed: paths do
not move. No data/identity/hatch register keys are removed.
