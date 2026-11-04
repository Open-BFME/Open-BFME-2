### LINK-357: MeshGeometry header adoption collides with existing list declarations
Status: Cleared for the four-unit scope below. Updated: 2026-11-04; inspected revision: 31ecf72513.
Evidence / affected units: MeshModelClassDefaultCtor.cpp, MeshModelClassCopyCtor.cpp, MeshModelClassDtor.cpp and Rva00925030GetPlanesChecked.cpp; [target facts, include reconciliation, byte checks and remaining cohort](../../reverse/attempt_support/meshgeometry_header_adoption_20261104.md).
Completed: replaced the four private MeshGeometryClass views with its canonical header, retaining existing list declarations and inline/unsigned flag behavior; header acceptance retired four debt rows.
Remaining / next check: other cohort files retain their queue rows; reconcile reference base/type declarations before retrying them, as detailed in the evidence. GenericMultiListClass debt in the copy constructor is unchanged.
Clearance: all 23 rows byte-match; header_adopt_lane.py accept passes for all four units, including link previews preserving census-linked bytes. Scope excludes the other queued geometry consumers.
Census confirmation: awaiting; no new census or linked-byte increase claimed.
