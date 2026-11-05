### LINK-420: MeshMatDescClass header adoption needs reader and template reconciliation
Status: Open for two remaining packet members; six adopted units cleared. Updated: 2026-11-05; inspected revision: 7414ae32f5.
Evidence / affected units: [eight-unit packet, retail layout facts, exact checks and remaining prerequisites](../../reverse/attempt_support/meshmatdesc_header_adoption_20261105.md).
Completed: six private descriptor views replaced by the canonical header; header_adopt_lane.py accept retired six queue rows, with 57/57 rows matching and joint preview preserving 21,543 linked bytes.
Remaining / next check: MeshModelReadTextureIds.cpp needs owning-handle predicate codegen reconciliation; bfme2_mesh_material_pass.cpp needs local template/include and descriptor-helper reconciliation. Both sources and their queue rows are unchanged; other queued consumers are outside this scope.
Clearance: current-object preview LINKS for MeshMatDescOpaqueBuffer.cpp, MeshModelLegacyMaterials.cpp, MeshModelReadShaderIds.cpp, MeshModelReset.cpp, meshmdl.cpp and seglinerenderer.cpp against index c95fcfcfcd (2026-11-05 05:17). Remaining packet members are not cleared by this pass.
Census confirmation: awaiting; no linked-byte increase or new census claimed.
Additional scope cleared (2026-11-05): three accessor consumers adopted the canonical header, retiring three queue rows with 6/6 byte matches and identical non-debug objects; [verification and scope](../../reverse/attempt_support/meshmatdesc-accessor-headers-20261105-codexb2.md). Reader and material-pass prerequisites remain unchanged.
