// ?Cast_Ray@MeshClass@@UAE_NAAVRayCollisionTestClass@@@Z
// partial score=0.9701216 date=2026-10-05
// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// BFME2 MeshClass collision overrides, built against the BFME2 RenderObjClass
// view (reference/shims/bfme2renderobj), whose Get_Collision_Type sits at
// retail's vtable +0x1E0. mesh.cpp's shared header places it one slot
// lower, so these Zero Hour bodies cannot match there.
//
// Intersect_AABox 0x0014B5E0: MeshClass vtable 0xBD35A8 slot 61. It builds the
// OBBox test through the out-of-line ctor 0x0014A3F0 and hands it to the
// model's Intersect_OBBox at 0x0016D7E0, whose callees are the AABTree
// Intersect_OBBox_Recursive 0x00198730 and intersect_obbox_brute_force
// 0x0016CD30.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "rendobj.h"
#include "inttest.h"
#include "coltest.h"

class MeshGeometryClass : public RefCountClass
{
public:
	// BFME2 bit values, read by Cast_Ray from +0x18.
	enum FlagsType {
		ALIGNED =	0x00000200,
		ORIENTED =	0x00000800,
	};

	int Get_Flag(FlagsType flag) { return Flags & flag; }
	void Get_Bounding_Box(AABoxClass * set_box);
	bool Cast_Ray(RayCollisionTestClass & raytest);
	bool Intersect_OBBox(OBBoxIntersectionTestClass & boxtest);

protected:
	char _bfme_unk_08[0x10];
	int Flags;                              // +0x18
};

class MeshModelClass : public MeshGeometryClass
{
};

// upstream identity and virtual interface:
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
// Layout as in MeshClassLifetime.cpp; only Model (+0xC4) is touched here.
class MeshClass : public RenderObjClass
{
public:
	virtual bool Cast_Ray(RayCollisionTestClass & raytest);
	virtual bool Intersect_AABox(AABoxIntersectionTestClass & boxtest);

private:
	MeshModelClass *Model;                  // +0x0C4
};

bool MeshClass::Intersect_AABox(AABoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;

	Matrix3D inv_tm;
	Get_Transform().Get_Orthogonal_Inverse(inv_tm);
	OBBoxIntersectionTestClass local_test(boxtest,inv_tm);
	return Model->Intersect_OBBox(local_test);
}

bool MeshClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	//Modified for 'Generals' so we could select trees but filter out headlight beams, etc. -MW
	if (raytest.CheckTranslucent && Is_Additive()!=0)
		return false;
	if (Is_Hidden() && !raytest.CheckHidden) return false;
	if (Is_Animation_Hidden()) return false;
	if (raytest.Result->StartBad) return false;

	Matrix3D world_to_obj;
	Matrix3D world=Get_Transform();

	// if aligned or oriented rotate the mesh so that it's aligned to the ray
	if (Model->Get_Flag(MeshGeometryClass::ALIGNED)) {
			Vector3 mesh_position;
			world.Get_Translation(&mesh_position);
			world.Obj_Look_At(mesh_position,mesh_position - raytest.Ray.Get_Dir(),0.0f);
	} else if (Model->Get_Flag(MeshGeometryClass::ORIENTED)) {
			Vector3 mesh_position;
			world.Get_Translation(&mesh_position);
			world.Obj_Look_At(mesh_position,raytest.Ray.Get_P0(),0.0f);
	}

	world.Get_Inverse(world_to_obj);
	RayCollisionTestClass objray(raytest,world_to_obj);

	// BFME2: a model whose bounding box is (nearly) flat is never hit.
	AABoxClass box;
	Model->Get_Bounding_Box(&box);
	if (box.Extent.Length2() < 58.782887f) return false;

	bool hit = Model->Cast_Ray(objray);

	// transform result back into original coordinate system
	if (hit) {
		raytest.CollidedRenderObj = this;
		Matrix3D::Rotate_Vector(world,raytest.Result->Normal, &(raytest.Result->Normal));
		if (raytest.Result->ComputeContactPoint) {
			Matrix3D::Transform_Vector(world,raytest.Result->ContactPoint, &(raytest.Result->ContactPoint));
		}
	}

	return hit;
}
