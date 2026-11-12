// cl: /Ireference/shims/bfme_lineseg_math_link /Ireference/shims/bfme2ray /O1 /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?Cast_Ray@MeshClass@@UAE_NAAVRayCollisionTestClass@@@Z @0x0014B240 928B (MeshClass vtable 0xBD35A8). Zero Hour mesh.cpp body
// built against the BFME2 RenderObjClass view (reference/shims/bfme2renderobj), whose Get_Collision_Type sits at retail's
// vtable +0x1E0 (mesh.cpp's shared header places it one slot lower, so the Zero Hour bodies cannot match there).
// Intersect_AABox 0x0014B5E0 lives in MeshClassCollision.cpp; its declaration is kept for the vtable order only.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
// Preserve the inline transform algorithms while suppressing unused external copies.
// An inline function's out-of-line copy takes the optimization state of its definition:
// under /O1 settings Matrix3D() and Matrix3D(const Matrix3D &) build Row through ??_H,
// as retail's owners (0x000423C5, 0x0006645C) do. Bodies that inline them are unchanged.
#pragma optimize("gsy", on)
#include "matrix3d.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "inttest.h"
#include "coltest.h"

// matrix3d.h's Matrix3D::Get_Translation(Vector3*) under a unit-local name: called as the
// Matrix3D member, this unit also emitted an external integer-move COMDAT copy that differs
// from retail's one x87 body (0x0009314A) and from the other units' copies. Body unchanged.
class CastRayTranslationView : public Matrix3D
{
public:
	WWINLINE void Get_Translation(Vector3 * set) const { set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3]; }
};

#include "MeshModelClass.h"

// Retail inlines MeshGeometryClass::Get_Flag here; the header keeps it out of line.
static inline int CastRay_Get_Flag(MeshModelClass *model, MeshGeometryClass::FlagsType flag) { return model->Flags & flag; }

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
	if (CastRay_Get_Flag(Model, MeshGeometryClass::ALIGNED)) {
			Vector3 mesh_position;
			((const CastRayTranslationView &)world).Get_Translation(&mesh_position);
			world.Obj_Look_At(mesh_position,mesh_position - raytest.Ray.Get_Dir(),0.0f);
	} else if (CastRay_Get_Flag(Model, MeshGeometryClass::ORIENTED)) {
			Vector3 mesh_position;
			((const CastRayTranslationView &)world).Get_Translation(&mesh_position);
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
