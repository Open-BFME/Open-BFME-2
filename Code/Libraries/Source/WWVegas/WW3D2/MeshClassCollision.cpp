// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// BFME2 MeshClass overrides built against the BFME2 RenderObjClass view
// (reference/shims/bfme2renderobj), whose slots follow retail's vtable
// (Get_Collision_Type at +0x1E0, Get_Num_Polys at slot 10). mesh.cpp's
// shared header places them differently, so these Zero Hour bodies cannot
// match there. Collision and bounding-volume overrides plus the small
// Model-forwarding getters.
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

class MeshGeometryClass : public RefCountClass
{
public:
	// BFME2 bit values (MeshGeometryClass +0x18).
	enum FlagsType {
		ALIGNED =	0x00000200,
		ORIENTED =	0x00000800,
	};

	int Get_Flag(FlagsType flag) { return Flags & flag; }
	int Get_Polygon_Count(void) const { return PolyCount; }
	int Get_Vertex_Count(void) const { return VertexCount; }
	int Get_Sort_Level(void) const { return SortLevel; }
	bool Intersect_OBBox(OBBoxIntersectionTestClass & boxtest);

protected:
	char _bfme_unk_08[0x10];
	int Flags;                              // +0x18
	signed char SortLevel;                  // +0x1C
	char _bfme_unk_1d[7];
	int PolyCount;                          // +0x24
	int VertexCount;                        // +0x28
};

class MeshMatDescClass
{
public:
	int Get_Pass_Count(void) const { return PassCount; }

private:
	int PassCount;                          // +0x00
};

class MaterialInfoClass : public RefCountClass
{
};

class MeshModelClass : public MeshGeometryClass
{
public:
	int Get_Pass_Count(void) const { return CurMatDesc->Get_Pass_Count(); }

	char _bfme_unk_2c[0x94 - 0x2C];
	MeshMatDescClass *CurMatDesc;           // +0x94
	MaterialInfoClass *MatInfo;             // +0x98
};

// upstream identity and virtual interface:
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
// Layout as in MeshClassLifetime.cpp; only Model (+0xC4) is touched here.
class MeshClass : public RenderObjClass
{
public:
	virtual int Get_Num_Polys(void) const;
	virtual int _bfme_ro_v9(void) const;
	virtual bool Intersect_AABox(AABoxIntersectionTestClass & boxtest);
	virtual int Get_Sort_Level(void) const;
	virtual MaterialInfoClass *Get_Material_Info(void);

protected:
	virtual void Update_Cached_Bounding_Volumes(void) const;

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

// MeshClass vtable 0xBD35A8 slot 127, 0x0014B650. BFME2 scales the cached
// sphere radius by ObjectScale (+0x48) before the box is derived from it.
void MeshClass::Update_Cached_Bounding_Volumes(void) const
{
	Get_Obj_Space_Bounding_Sphere(CachedBoundingSphere);
	Get_Transform().mulVector3(CachedBoundingSphere.Center);
	CachedBoundingSphere.Radius *= ObjectScale;

	// If we are camera-aligned or -oriented, we don't know which way we are facing at this point,
	// so the box we return needs to contain the sphere. Otherewise do the normal computation.
	if (Model->Get_Flag(MeshGeometryClass::ALIGNED) || Model->Get_Flag(MeshGeometryClass::ORIENTED)) {
		CachedBoundingBox.Center = CachedBoundingSphere.Center;
		CachedBoundingBox.Extent.Set(CachedBoundingSphere.Radius, CachedBoundingSphere.Radius, CachedBoundingSphere.Radius);
	} else {
		Get_Obj_Space_Bounding_Box(CachedBoundingBox);
		CachedBoundingBox.Transform(Get_Transform());
	}

	Validate_Cached_Bounding_Volumes();
}

// MeshClass vtable 0xBD35A8 slot 10, 0x00149A50.
int MeshClass::Get_Num_Polys(void) const
{
	if (Model) {
		int num_passes=Model->Get_Pass_Count();
		int poly_count=Model->Get_Polygon_Count();
		return num_passes*poly_count;
	} else {
		return 0;
	}
}

// MeshClass vtable 0xBD35A8 slot 11, 0x00149A70: the vertex-count twin of
// Get_Num_Polys. The base slot is the shim's unnamed _bfme_ro_v9.
int MeshClass::_bfme_ro_v9(void) const
{
	if (Model) {
		int num_passes=Model->Get_Pass_Count();
		int vertex_count=Model->Get_Vertex_Count();
		return num_passes*vertex_count;
	} else {
		return 0;
	}
}

// MeshClass vtable 0xBD35A8 slot 94, 0x0014A070.
int MeshClass::Get_Sort_Level(void) const
{
	if (Model) {
		return (Model->Get_Sort_Level());
	}
	return(0);	// SORT_LEVEL_NONE
}

// MeshClass vtable 0xBD35A8 slot 85, 0x00149980.
MaterialInfoClass * MeshClass::Get_Material_Info(void)
{
	if (Model) {
		if (Model->MatInfo) {
			Model->MatInfo->Add_Ref();
			return Model->MatInfo;
		}
	}
	return NULL;
}
