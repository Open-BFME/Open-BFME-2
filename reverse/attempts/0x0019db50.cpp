// ?Update_Obj_Space_Bounding_Volumes@HLodClass@@MAEXXZ
// partial score=0.976 date=2026-09-29
// ?Update_Obj_Space_Bounding_Volumes@HLodClass@@MAEXXZ
// partial score=0.9760095962 date=2026-09-27
// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Banked HLodClass::Update_Obj_Space_Bounding_Volumes: RVA19DB50,2501B.
// Identity: recovered HLod definition constructor call19FF2F and its installed
// table7D6780 slot114. Target searches OBBOX class1B with BOUNDINGBOX name,
// combines child sphere/box bounds in base pose, then invalidates cached bounds.
// EA/BFME1 hlod.cpp supplies the semantic source. BFME2 pivot transform uses
// rotation+translation at30/40 with stride58, corroborated by HTreePivotClass.
// The exact Add_Lod_Model recovery supplies the inline rotation expansion.
// This bank emits2501 bytes, no unresolved calls, but differs in 98 byte
// positions (first+1D9); commutative SSE operands and sphere transform registers
// remain. Matrix-return temporaries and separate rotation helper did not fix it.
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
void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
{
	//
	//	Do we still have a valid bounding box index?
	//
	ModelArrayClass &high_lod = Lod[LodCount - 1];
	int count = high_lod.Count ();
	if (	BoundingBoxIndex < 0 ||
			BoundingBoxIndex >= count ||
			high_lod[BoundingBoxIndex].Model->Class_ID () != RenderObjClass::CLASSID_OBBOX)
	{
		BoundingBoxIndex = -1;
	}

	//
	//	Attempt to find an OBBox mesh inside the heirarchy
	//
	int index = high_lod.Count ();
	while (index -- && BoundingBoxIndex == -1) {
		RenderObjClass *model = high_lod[index].Model;

		//
		//	Is this an OBBox mesh?
		//
		if (model->Class_ID () == RenderObjClass::CLASSID_OBBOX)
		{
			const char *name = model->Get_Name ();
			const char *name_seg = ::strchr (name, '.');
			if (name_seg != NULL) {
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


	int i;
	RenderObjClass * robj = NULL;

	// if we don't have any sub objects, just set default bounds
	if (Get_Num_Sub_Objects() <= 0) {
		ObjSphere.Init(Vector3(0,0,0),0);
		ObjBox.Center.Set(0,0,0);
		ObjBox.Extent.Set(0,0,0);
		return;
	}

	// loop through all sub-objects, combining their object-space bounding spheres and boxes.
	// Put our HTree in its base pose at the origin.
	SphereClass sphere;
	AABoxClass obj_aabox;
	MinMaxAABoxClass box;

	HTree->Base_Update(Matrix3D(1));

	robj = Get_Sub_Object(0);
	WWASSERT(robj);

	Matrix3D bonetm;
	treeMatrix(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	sphere.Transform(bonetm);
	robj->Get_Obj_Space_Bounding_Box(obj_aabox);

	box.Init(obj_aabox);
	box.Transform(bonetm);

	robj->Release_Ref();

	for (i=1; i<Get_Num_Sub_Objects(); i++) {
		robj = Get_Sub_Object(i);
		WWASSERT(robj);

		Matrix3D bonetm;
	treeMatrix(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);

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
