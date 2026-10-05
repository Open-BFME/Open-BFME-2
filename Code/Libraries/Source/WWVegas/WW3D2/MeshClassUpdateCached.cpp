// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?Update_Cached_Bounding_Volumes@MeshClass@@MBEXXZ 0x0014B650 366B
// vslot 127 (offset 0x1FC) of MeshClass vtable 0x007D35A8.
// Evidence: slot mapping from packet; donor Zero Hour mesh.cpp Update_Cached_Bounding_Volumes
// plus BFME2 RenderObj bounds (sphere@4C box@5C scale@48) from RenderObjBounds.cpp;
// Model flag byte at +0x19 mask 0x0A matches ALIGNED|ORIENTED.
//
#include "rendobj.h"
#include "aabox.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

class MeshModelClass
{
public:
	enum FlagsType
	{
		ALIGNED = 0x00000200,
		ORIENTED = 0x00000800
	};
	int Get_Flag(FlagsType flag) { return Flags & flag; }

private:
	char _pad[0x18];
	int Flags;
};

class MeshClass : public RenderObjClass
{
public:
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;

protected:
	virtual void Update_Cached_Bounding_Volumes(void) const;

private:
	MeshModelClass *Model; // +0xC4
};

void MeshClass::Update_Cached_Bounding_Volumes(void) const
{
	Get_Obj_Space_Bounding_Sphere(CachedBoundingSphere);
	Get_Transform().mulVector3(CachedBoundingSphere.Center);
	CachedBoundingSphere.Radius = ObjectScale * CachedBoundingSphere.Radius;
	if (Model->Get_Flag(MeshModelClass::ALIGNED) || Model->Get_Flag(MeshModelClass::ORIENTED)) {
		CachedBoundingBox.Center = CachedBoundingSphere.Center;
		CachedBoundingBox.Extent.Set(CachedBoundingSphere.Radius, CachedBoundingSphere.Radius, CachedBoundingSphere.Radius);
	} else {
		Get_Obj_Space_Bounding_Box(CachedBoundingBox);
		CachedBoundingBox.Transform(Get_Transform());
	}
	Validate_Cached_Bounding_Volumes();
}
