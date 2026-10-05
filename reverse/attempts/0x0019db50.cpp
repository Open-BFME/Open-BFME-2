// ?Update_Obj_Space_Bounding_Volumes@HLodClass@@MAEXXZ
// partial score=0.988 date=2026-10-05
// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Update_Obj_Space_Bounding_Volumes, RVA19DB50, 2501B: near miss.
// Identity as the bank: HLod definition constructor 19FF2F and installed table
// 7D6780 slot114; OBBOX class1B / "BOUNDINGBOX" search then child sphere/box
// combine in base pose. Pivot transform is quaternion+translation at 30/40,
// stride 58; the rotation expansion is the Add_Lod_Model recovery.
// What is still wrong (19 instructions): the loop's inlined pivot expansion
// keeps the xy product in retail's operand order (retail movss [q+30] then
// mulss [q+34]) where ours loads [q+34] first, and the loop tmpsphere.Transform
// keeps retail's register allocation. Binding the pivot transform to a local
// reference before pivotMatrix at the FIRST call site only (treeMatrixB vs the
// unbound treeMatrixU in the loop) fixed the pre-loop expansion's commutative
// operand order; binding it at both sites moves the flip into the loop instead.
// Not byte-verified progress. The similarity score measures byte sequences.
#define Matrix4x4 Matrix4
#include <sweep/winbase_shim.h>
#include <string.h>
#define _CRTIMP
#include "rendobj.h"
#include "winbase_shim.h"
#include "hlod.h"
#include "assetmgr.h"
#include "hmdldef.h"
#include "w3derr.h"
#include "chunkio.h"
#include "predlod.h"
class CameraClass;
#include "rinfo.h"
#include "sphere.h"
#include "boxrobj.h"

struct HlodTransformView
{
    float X, Y, Z, W;
    Vector3 Position;
};
struct HlodPivotView
{
    unsigned char unaccessed[0x30];
    HlodTransformView Transform;
    int Index;
    bool IsVisible;
    unsigned char tail[7];
};
typedef char HlodPivotStride[(sizeof(HlodPivotView) == 0x58) ? 1 : -1];
struct HlodTreeView
{
    char Name[16];
    int NumPivots; // +0x10
    HlodPivotView *Pivot; // +0x14
};
static __forceinline Matrix3D &pivotMatrix(const HlodTransformView &q, Matrix3D &m)
{
    const float xx = q.X * q.X * 2.0f;
    const float xy = q.X * q.Y * 2.0f;
    const float xz = q.Z * q.X * 2.0f;
    const float wx = q.W * q.X * 2.0f;
    const float yy = q.Y * q.Y * 2.0f;
    const float yz = q.Z * q.Y * 2.0f;
    const float wy = q.W * q.Y * 2.0f;
    const float zz = q.Z * q.Z * 2.0f;
    const float wz = q.W * q.Z * 2.0f;

    m[0][0] = 1.0f - yy - zz;
    m[0][1] = xy - wz;
    m[0][2] = xz + wy;
    m[1][0] = xy + wz;
    m[1][1] = 1.0f - zz - xx;
    m[1][2] = yz - wx;
    m[2][0] = xz - wy;
    m[2][1] = yz + wx;
    m[2][2] = 1.0f - yy - xx;
    m[0][3] = q.Position.X;
    m[1][3] = q.Position.Y;
    m[2][3] = q.Position.Z;
    return m;
}

static __forceinline Matrix3D &treeMatrix(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrix(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
static __forceinline Matrix3D &treeMatrixB(const HTreeClass *tree, int index, Matrix3D &m) { const HlodTransformView &q = reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform; return pivotMatrix(q,m); }
static __forceinline Matrix3D &treeMatrixU(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrix(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
{
	//
	//	Do we still have a valid bounding box index?
	//
	ModelArrayClass &high_lod = Lod[LodCount - 1];
	const int count = high_lod.Count ();
	if (	BoundingBoxIndex < 0 ||
			BoundingBoxIndex >= count ||
			high_lod[BoundingBoxIndex].Model->Class_ID () != RenderObjClass::CLASSID_OBBOX)
	{
		BoundingBoxIndex = -1;
	}

	//
	//	Attempt to find an OBBox mesh inside the heirarchy
	//
	unsigned int index = high_lod.Count ();
	while (index -- && BoundingBoxIndex == -1) {
		RenderObjClass *model = high_lod[index].Model;

		//
		//	Is this an OBBox mesh?
		//
		if (model->Class_ID () == RenderObjClass::CLASSID_OBBOX)
		{
			const char *name = model->Get_Name ();
			const char *name_seg = ::strchr (name, '.');
			if (NULL != name_seg) {
				name = name_seg + 1;
			}

			//
			//	Does the name match the designator we are looking for?
			//
			if (::stricmp (name, "BOUNDINGBOX") == 0) {
				BoundingBoxIndex = index;
			}
		}
	}


	RenderObjClass * robj = NULL;
	int i;

	// if we don't have any sub objects, just set default bounds
	if (Get_Num_Sub_Objects() <= 0) {
		ObjSphere.Init(Vector3(0,0,0),0);
		ObjBox.Center.Set(0,0,0);
		ObjBox.Extent.Set(0,0,0);
		return;
	}

	// loop through all sub-objects, combining their object-space bounding spheres and boxes.
	// Put our HTree in its base pose at the origin.
	AABoxClass obj_aabox;
	MinMaxAABoxClass box;
	SphereClass sphere;

	HTree->Base_Update(Matrix3D(1));

	WWASSERT(robj);
	robj = Get_Sub_Object(0);

	Matrix3D bonetm;
	treeMatrixB(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	sphere.Transform(bonetm);
	robj->Get_Obj_Space_Bounding_Box(obj_aabox);

	box.Init(obj_aabox);
	box.Transform(bonetm);

	robj->Release_Ref();

	for (i=1; i<Get_Num_Sub_Objects(); i++) {
		WWASSERT(robj);
		robj = Get_Sub_Object(i);

		Matrix3D bonetm;
	treeMatrixU(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);

		SphereClass tmpsphere;
		robj->Get_Obj_Space_Bounding_Sphere(tmpsphere);
		tmpsphere.Transform(bonetm);
		sphere.Add_Sphere(tmpsphere);

		AABoxClass tmpbox;
		robj->Get_Obj_Space_Bounding_Box(tmpbox);
		tmpbox.Transform(bonetm);
		box.Add_Box(tmpbox);

		robj->Release_Ref();
	}

	ObjSphere = sphere;
	ObjBox = box;

   Invalidate_Cached_Bounding_Volumes();
	Set_Hierarchy_Valid(false);

   // Now update the object space bounding volumes of this object's container:
   RenderObjClass *container = Get_Container();
   if (container) container->Update_Obj_Space_Bounding_Volumes();
}
