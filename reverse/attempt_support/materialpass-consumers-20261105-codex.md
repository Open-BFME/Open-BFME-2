# MaterialPassClass consumer layouts, 2026-11-05

Inspected revision: `1e2bcf3d94`. The header picker claimed MaterialPassClass,
its frozen header and the nine remaining queued consumers for
`yasinschroeder-codex`. No shared header or compiler flags change.

Five consumers now use the existing MaterialPassClass header:

- GapBodiesSeat1A: account for the full 0x38-byte embedded member at +0x330;
  padding starts at +0x368, retaining the vector at +0x578.
- Rva0073F96ACtor and GlowMaterial: remove 0x34 bytes of padding that stood
  in for the previously four-byte base. The canonical 0x38-byte base retains
  the derived fields at +0x38/+0x3C/+0x40/+0x44.
- OpaqueScalarDeletingDtorsB08: replace both private base declarations and
  their synthetic tag constructors; the existing non-retail derived emit
  constructor calls the canonical default constructor. All nine deleting
  destructor rows still match.
- bfme2_mesh_material_pass: replace the partial MaterialPassClass prefix and
  private ShaderClass. The bit update uses canonical ShaderBits with the
  same mask and value.

Verification evidence:

- The normal build passes 219 code rows across the five consumers: 188 in
  the three layout consumers, nine in the deleting-destructor unit and 22
  in bfme2_mesh_material_pass. The one data row in the layout cohort passes.
- find_declared_unmatched passes all five sources before and after edits.
- The combined link_check preview reports five LINKS, retaining 8,675 bytes
  (2,695 + 252 + 56 + 2,207 + 3,465) against the census at `f44cbcf5b0`,
  2026-11-05 15:19. This is a prediction, not a new real-link or runtime result.
- External-definition comparison of before/current COFF objects finds only
  two removals: the B08ShroudPassBaseTag constructors of MaterialPassClass
  and RefCountClass. A scan of all 39,185 build/**/*.obj files finds no
  undefined symbol or /alternatename use of either spelling. The only
  retained definitions are the pre-edit scratch snapshot. No other existing
  external definition is removed. Rva0073F96ACtor additionally emits the
  canonical empty const UnInstall_Materials body.

Remaining consumers: W3DGlowOutlineMaterialPassClass still has competing
reference-header bases; MaterialPassClassCtorThunk and MaterialPassClassDestructor
need typed owning stage lifetimes in place of the canonical opaque array.
MeshClassRender needs the canonical base destructor to replace its old slot-1
placeholder; doing that fixes virtual-call offsets, but Render still changes
floating-point instruction order (1,126 retail bytes vs 1,116 compiled bytes).
Moving the MaterialPassClass include after the camera declaration does not
repair that code generation. This trial was restored; its normal build passes
all 12 rows, and its queue entries remain. No nonmatching trial is kept in Code/.

The supported acceptance lane passes the full five-consumer MaterialPassClass
cohort and retires five queue rows together. With direct canonical includes,
it also passes and retires the RefCountClass row in
OpaqueScalarDeletingDtorsB08 and the ShaderClass row in
bfme2_mesh_material_pass: seven header-queue rows retired in total.
The final declared-unmatched checks, ledger check and diff whitespace check pass.
