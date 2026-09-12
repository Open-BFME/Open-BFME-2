// ?Scale@MeshGeometryClass@@QAEXABVVector3@@@Z
// partial score=0.94 date=2026-09-11
// Standalone attempt body for ?Scale@MeshGeometryClass@@QAEXABVVector3@@@Z
// @ 0x0016B3F0 (652 bytes). Belongs in
// Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.cpp, which already
// carries ZH's verbatim Scale under a present-unmatched marker, PLUS this
// TU-level prerequisite (retail news AABTreeClass through scalar new):
//
//   #include "always.h"
//   #pragma push_macro("W3DMPO_GLUE")
//   #undef W3DMPO_GLUE
//   #define W3DMPO_GLUE(ARGCLASS)
//   #include "aabtree.h"
//   #pragma pop_macro("W3DMPO_GLUE")
//
// (same technique as BFME1's meshmatdesc.cpp; layout-safe, the macro adds no
// data members or vtable slots; all landed rows in the TU stay green).
//
// Proven deltas from ZH, all verified in the diff except the last item:
//  - BFME2 scales a second per-vertex array (the +0x34 ShareBuffer, Vector3
//    stride, null-checked) right after the Vertex loop.
//  - BoundSphereRadius max-select is if/else-shaped, not ZH's ternaries
//    (ternaries emit ucomiss+lahf; retail is comiss+jcc).
//  - NEW_REF(AABTreeClass,()) resolves to scalar new + AABTree ctor;
//    op=, Set_Mesh, Generate_Culling_Tree, REF_PTR Add_Ref/Release_Ref
//    (inlined counters, virtual Delete_This) and the EH states all match.
// Remaining diff: both vertex loops emit vert-first mulss order
// (movss xmm0,[eax-8]; mulss xmm0,[edi]) where retail loads sc first
// (movss xmm0,[edi]; mulss xmm0,[eax-8]); `*=` and `= sc * vert` spellings
// compile identically, and the max if/else normalizes unpredictably, so no
// source lever for the order was found.
void MeshGeometryClass::Scale(const Vector3 &sc)
{
	Vector3 * vert = Vertex->Get_Array();

	for (int i=0;i<VertexCount; i++) {
		vert[i].X = sc.X * vert[i].X;
		vert[i].Y = sc.Y * vert[i].Y;
		vert[i].Z = sc.Z * vert[i].Z;
	}

	// BFME2 drift from Zero Hour: a second per-vertex array rides along.
	if (VertexNorm != NULL) {
		Vector3 *normals = VertexNorm->Get_Array();
		for (int i=0;i<VertexCount; i++) {
			normals[i].X = sc.X * normals[i].X;
			normals[i].Y = sc.Y * normals[i].Y;
			normals[i].Z = sc.Z * normals[i].Z;
		}
	}

	BoundBoxMin.Scale(sc);
	BoundBoxMax.Scale(sc);
	BoundSphereCenter.Scale(sc);

	float max;
	if (sc.X > sc.Y)
		max = sc.X;
	else
		max = sc.Y;
	if (max <= sc.Z)
		max = sc.Z;
	BoundSphereRadius *= max;

	// If scaling uniformly normals are OK:
	if (sc.X != sc.Y || sc.Y != sc.Z) {
		Set_Flag(DIRTY_VNORMALS,true);
	}
	// pnormals are plane equations...
	Set_Flag(DIRTY_PLANES,true);

	// the cull tree is invalid, release it and make a new one
	if (CullTree) {
		// If the scale is uniform, we can scale the cull tree, which is a lot faster than creating a new one
		if (fabs(sc[0]-sc[1])<WWMATH_EPSILON && fabs(sc[0]-sc[2])<WWMATH_EPSILON) {
			// create a copy of the old culltree
			AABTreeClass *temp = NEW_REF(AABTreeClass, ());
			*temp = *CullTree;
			temp->Set_Mesh(this);
			REF_PTR_SET(CullTree, temp);
			REF_PTR_RELEASE(temp);
			CullTree->Scale(sc[0]);
		}
		else {
			REF_PTR_RELEASE(CullTree);
			Generate_Culling_Tree();
		}
	}
}
