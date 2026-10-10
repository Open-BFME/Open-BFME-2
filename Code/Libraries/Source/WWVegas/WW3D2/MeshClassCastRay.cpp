// cl: /O1 /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?Cast_Ray@MeshClass@@UAE_NAAVRayCollisionTestClass@@@Z @0x0014B240 928B (MeshClass vtable 0xBD35A8). Zero Hour mesh.cpp body
// built against the BFME2 RenderObjClass view (reference/shims/bfme2renderobj), whose Get_Collision_Type sits at retail's
// vtable +0x1E0 (mesh.cpp's shared header places it one slot lower, so the Zero Hour bodies cannot match there).
// Intersect_AABox 0x0014B5E0 lives in MeshClassCollision.cpp; its declaration is kept for the vtable order only.

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

bool MeshClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	//Modified for 'Generals' so we could select trees but filter out headlight beams, etc. -MW
	if (raytest.CheckTranslucent && Is_Additive()!=0)
		return false;
	if (Is_Hidden() && !raytest.CheckHidden) return false;
	// Codegen: the hidden-animation test goes through a named int local (native compare-against-zero form).
	int _z = (int)(Is_Animation_Hidden());
	if (_z) return false;
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

	// Codegen: same-valued PHI receiver on Model closes the native register roles.
	bool hit = (Model?Model:Model)->Cast_Ray(objray);

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
