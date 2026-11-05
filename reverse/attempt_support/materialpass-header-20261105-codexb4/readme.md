# MaterialPassClass header adoption, 2026-11-05

Inspected source revision: `5f6ed5eb3e`. Class scope was acquired through
`next_work.py --tier header --claim` as `yasinschroeder-codexb4`.

Four consumers replace their private MaterialPassClass declaration with the
existing canonical header:

- `RTS3DSceneCtor.cpp`: constructor and shader setter declarations, eight-byte
  RefCountClass base, and the established 0x38 allocation size are retained.
- `rinfo.cpp`: the empty derived reference-count view uses the shared class.
- `DX8RigidDelayedMaterialPass.cpp`: the direct count increment uses the
  canonical inherited NumRefs at +4. The unused synthetic vtable field is gone.
- `DX8RigidMaterialPassAppend.cpp`: Add_Ref now resolves to its canonical base
  declaration and retains its existing inline count increment.

`header_adopt_lane.py adopt --apply` accepted the first two. The two DX8 units
needed manual removal of their unused synthetic vptr/vtable fields, which the
automatic field mapper correctly refuses to treat as ordinary data members.
`header_adopt_lane.py accept --class MaterialPassClass` passed both pairs and
retired exactly four queue rows. No baseline, hatch, source path, ledger name,
shared header or unrelated source was changed.

Verification:

- `./build.sh` passes all 55 rows across the four sources (51 automatic-cohort
  rows and four DX8 rows), including the scene constructor's renamed EH labels.
- `find_declared_unmatched.py` passes every edited source before and after.
- `check_csv.py` and `git diff --check` pass.
- The owning acceptance checks predict no loss of census-linked bytes.
  The explicit combined preview reports all four LINKS, retaining 2,962 bytes
  against the index updated to `c95fcfcfcd` (2026-11-05 05:17). This is a scoped
  prediction, not a new census or a headline gain.
- All three external COMDAT digests in the delayed-pass object are unchanged.
  The append object's five shared definitions have unchanged digests; its
  sixth moves from MaterialPassClass::Add_Ref to RefCountClass::Add_Ref with
  the identical bytes/relocation digest `7f46b2a25328` and five-byte extent.
  The index reference graph contains no incoming edge to the old spelling and
  does not mark it reachable. The final push audit still checks affected
  consumers; this comparison does not claim complete object equivalence.

The other nine automatic trials were restored without source or queue changes.
Their diagnostics are in `adopt.log`: GapBodiesSeat1A and GlowMaterial fail
unrelated row bytes; Rva0073F96ACtor loses its constructor bytes;
OpaqueScalarDeletingDtorsB08 needs a constructor signature absent from the
canonical class; W3DGlowOutlineMaterialPassClass has a competing RefCountClass;
the matpass constructor/destructor use owning MaterialPassStage arrays rather
than the canonical opaque pointer storage; MeshClassRender and
bfme2_mesh_material_pass require reconciliation of partial prefix views.
Those are prerequisites for later work, not permission to change the shared
header or retire their queue entries. Existing matpass flag/merge obstacles
remain outside this repair.

The earlier SimpleObjectIterator consolidation dry run accepted its cleanup
donor, but application stopped before writing because another worker held
shared RVA 0x0014F3C4. Its file scopes were released; no merge was applied.
