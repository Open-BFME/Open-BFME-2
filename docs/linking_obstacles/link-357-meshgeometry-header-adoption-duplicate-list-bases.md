### LINK-357: MeshGeometry header adoption collides with existing list declarations
Status: Cleared for the eight-unit scope below. Updated: 2026-11-05; inspected revision: f23f469a4f.
Evidence / affected units: MeshModelClassDefaultCtor.cpp, MeshModelClassCopyCtor.cpp, MeshModelClassDtor.cpp and Rva00925030GetPlanesChecked.cpp; [target facts, include reconciliation, byte checks and remaining cohort](../../reverse/attempt_support/meshgeometry_header_adoption_20261104.md).
Completed: replaced the four private MeshGeometryClass views with its canonical header, retaining existing list declarations and inline/unsigned flag behavior; header acceptance retired four debt rows.
Remaining / next check: other queued geometry consumers remain outside the cleared eight-unit scope; preserve the accessors' reference-base inline destructor when reconciling their includes. GenericMultiListClass debt in the copy constructor is unchanged.
Clearance: all 23 rows byte-match; header_adopt_lane.py accept passes for all four units, including link previews preserving census-linked bytes. Scope excludes the other queued geometry consumers.
Census confirmation: awaiting; no new census or linked-byte increase claimed.

2026-11-05 scope extension: MeshMatDescFXShaderConversion.cpp, meshmdl.cpp, mesh_get_shade_indices.cpp and mesh_get_vert_normals.cpp adopt the geometry header; all 27 rows byte-match and final header acceptance preserves census-linked bytes, retiring four queue rows. [Local include reconciliation and deleting-destructor constraint](../../reverse/attempt_support/meshgeometry_remaining_cohort_20261104.md).
