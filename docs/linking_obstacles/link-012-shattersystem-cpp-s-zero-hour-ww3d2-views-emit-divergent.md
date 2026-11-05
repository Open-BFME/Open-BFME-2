### LINK-012: shattersystem.cpp's Zero Hour WW3D2 views emit divergent shared COMDATs

2026-11-05: meshmdlio's two obsolete Vector4 queue rows are retired by owning acceptance; 42/42 rows match and the bounded preview links. DX8Wrapper and the wider material/shatter prerequisites remain open. [Evidence](../../reverse/attempt_support/meshmdlio-vector4-adoption-20261105-codex2.md).

**2026-10-30 bounded getter probe:** the native MeshMatDesc getter at
0x002C8ECF reads +0xA4; shatter's current copy reads +0xA8. The copy's incoming
relocations are debug-only, but its body is also inlined into two other methods.
Force-inline (definition only or declaration plus definition) keeps the wrong
copy. A declaration-only private shim probe removes it while changing both
MeshModelClass::Peek_Single_Material and ShatterSystem::Process_Clip_Pools,
so the proposed narrow suppression is not accepted. Scale's 133 bytes remain
exact in all probes; no production edit, retirement or link gain is retained.
Next reconcile the native layout and caller bodies with their existing owners;
the Add_Vertex_Material provider and broader dependencies remain open.
[Rejected hypotheses and native facts](../../reverse/attempt_support/shatter-material-getter-prerequisites-20261030/README.md).

**Status: Open (partial repair landed). Updated: 2026-10-25; inspected revision: 70d32d864.**

- **Evidence / scope:** `Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp` compiles
  against Zero Hour's `WWLib/Vector.H`, `WW3D2/matinfo.h` and the `meshmatdesclayout`
  shim, and emitted a 75-byte `DynamicVectorClass<VertexMaterialClass*>::Add` while
  retail's folded owner (0x001A3A60, 77 B) is what the six BFME 1-header units emit.
  The census (ef9c691284) kept shattersystem's copy, so every user of that `Add` failed
  `wrong_selected`: MeshLoadContextAddLegacyMaterial.cpp (2,714 B),
  MaterialCollectorDestructor.cpp (1,588 B), MaterialCollectorCollectMaterials.cpp
  (1,489 B), MeshModelReadVertexMaterials.cpp (270 B) and meshmdlio.cpp (352 B).
- **Completed:** shattersystem.cpp declares the `Add` specialization decl-only (before
  matinfo.h, whose inline `Add_Vertex_Material` instantiates it), so it emits no copy.
  `./build.sh` 1/1; `tools/link_check.py` with shattersystem.cpp and each consumer:
  all five consumers LINK (0 -> 6,413 B predicted).
- **Remaining / next check:** shattersystem.cpp still emits non-retail
  `MaterialInfoClass::Add_Vertex_Material` (out-of-line `Add` call where retail 0x00189670
  inlines BFME's `Add`) and `MeshMatDescClass::Peek_Single_Material` (material array at
  +0xA8 in the `meshmatdesclayout` view; retail 0x002C8ECF reads +0xA4). Those keep
  dynamesh.cpp (owner of both rows) and shattersystem.cpp itself from linking. The two
  `Add` bodies are textually identical, so the difference is the views' class layouts:
  reconcile shattersystem.cpp onto the BFME 1 WWLib/WW3D2 headers dynamesh.cpp uses,
  checking its 0x00074643 `Matrix3D::Scale` row.
- **Clearance:** preview scope only (current objects for the listed units).
- **Census confirmation:** awaiting the next census.

- **Mesh material I/O follow-up (2026-10-25, inspected `d7fa8a31bf3`):**
  [the bounded cleanup and provider control](../../reverse/attempt_support/meshmdlio-hatch-cleanup-20261025-bce2/readme.md)
  confirms meshmdlio's eleven rows remain exact (352 bytes). Against the
  `f995f30157` index, checking the current shattersystem object alongside it
  clears the historical Add blocker before and after the cleanup. This is
  inherited repair, not new linking credit. The file's obsolete construction
  anchor and stale matched-destructor annotation are removed, retiring three
  hatch occurrences through the register tool. The RefCount optimization is
  retained after an independent removal trial changed Add_Ref's emission.
  Shattersystem's seven current unresolved/COMDAT/selected findings are
  unchanged and recorded in the evidence. Only this consumer's ordinary
  preview scope is cleared; family closure and census confirmation remain open.

- **Material collector follow-up (2026-10-26, inspected `a91e877b4d`):**
  [Whole-file cleanup and paired provider checks](../../reverse/attempt_support/material-collector-anchor-cleanup-20261026.md)
  preserve all eight rows (1,506 bytes) and one EXACT EH graph. With the
  current shattersystem object, the consumer previews clean for 1,489 authored
  bytes before and after removing its unused construction anchor. Its three
  unreferenced diagnostics and the provider's seven blockers are unchanged.
  The owning hatch tool retires two optimization occurrences. This is new
  hatch retirement plus confirmation of inherited repair, not new linking
  credit or broader closure; census confirmation remains pending.
  A separately verified follow-up replaces its local array-delete declaration
  with the toolchain `<new>` header, using the donor's existing allocation
  guard to avoid duplicate placement bodies. All eight rows, the EH graph
  and the paired preview stay exact/unchanged; the Microsoft-header scan
  reports zero local definitions or declarations.

**Assigned current-provider recheck (2026-10-27, inspected `97c23353111e60304b56434c02d20bee3465d83f`, index `5ce093a71a`, retail-truth-4):** `shattersystem.cpp` retains U3/L2/S2 with current named providers and its 133-byte Matrix3D::Scale row remains exact. `Add_Vertex_Material` at 0x00189670 (85 B) and `Peek_Single_Material` at 0x002C8ECF (14 B) are still owned by `dynamesh.cpp`; `Get_Z_Vector` at 0x00143260 (32 B) is owned by `lightenvironment.cpp`. The unresolved texture/normal operations occur in emitted unrowed shatter code rather than the matched Scale row. The existing WWLib/WW3D2 and mesh-material shim reconciliation remains the prerequisite; no shared header was edited and no earlier failed trial was repeated. No source change or further clearance is claimed. Census confirmation remains pending.

- **Mesh material I/O seed cleanup (2026-10-28, base `5ab8984c4c`, index `41c28839bf`):**
  [The cleanup and provider comparison](../../reverse/attempt_support/meshmdlio-seed-cleanup-20261028-codex.md)
  remove disabled donor save code (22 obsolete hatch entries) and the unused
  getter-emission anchor. The four removed getter COMDATs are byte-and-symbolic-
  relocation twins of their existing owners in MeshModelLegacyMaterials.cpp and
  MeshLoadContextAddLegacyMaterial.cpp; all retained seed COMDATs are unchanged.
  All 38 rows across those three units verify, and ordinary preview keeps their
  3,801 authored bytes linking. No new linking credit or TU merge is claimed.
  Fresh view planning still requires material-class layout/inheritance and
  shared-header reconciliation before composition. The outgoing batch audit is
  inconclusive: its index predates the base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Broader provider-selection clearance and census confirmation remain
  open; include the removed duplicate providers in the next scheduled census.
