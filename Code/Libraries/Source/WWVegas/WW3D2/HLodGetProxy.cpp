// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Get_Proxy: retail0x0019C750..0x0019C881,305 bytes.
// EA/BFME1 hlod.cpp supplies the donor method and ProxyRecord/ProxyArray
// declarations. Matched HLod constructors install table7D6780, whose slot244
// holds this body next to the matched Get_Proxy_Count at slot240. Target
// behavior agrees: base-update the tree, resolve the indexed proxy bone,
// copy its transform/name, and return identity plus an empty name on failure.
//
// The target writes name at proxy+0 and a 28-byte rotation/position block
// at proxy+4, replacing the donor's Matrix3D. Pivot stride58 and block30
// independently agree with HTreePivotClass.cpp and the recovered HLod methods.
// BfmeProxyTransform is a descriptive local type, not a recovered retail name.
// This TU models only this method's output layout; it does not establish the
// identity of other methods or template rows named ProxyClass elsewhere.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4
#include <sweep/winbase_shim.h>
#include <string.h>
#define _CRTIMP
#include "rendobj.h"
#include "winbase_shim.h"
#include "quat.h"
#include "wwstring.h"
#define __PROXY_H
struct BfmeProxyTransform {
 Quaternion Rotation;
 Vector3 Position;
 BfmeProxyTransform() {}
 explicit BfmeProxyTransform(bool) { Rotation.Make_Identity(); Position.Set(0.0f,0.0f,0.0f); }
};
class ProxyClass {
 StringClass Name;
 BfmeProxyTransform Transform;
public:
 void Set_Name(const char *name) { Name=name; }
 void Set_Transform(const BfmeProxyTransform &transform) { Transform=transform; }
};

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

class ProxyRecordClass
{
public:
	ProxyRecordClass(void) : BoneIndex(0)
	{
		memset(Name,0,sizeof(Name));
	}

	bool					operator == (const ProxyRecordClass & that) { return false; }
	bool					operator != (const ProxyRecordClass & that) { return !(*this == that); }

	void					Init(const W3dHLodSubObjectStruct & w3d_data)
	{
		BoneIndex = w3d_data.BoneIndex;
		strncpy(Name,w3d_data.Name,sizeof(Name));
	}

	int					Get_Bone_Index(void)		{ return BoneIndex; }
	const char *		Get_Name(void)				{ return Name; }

protected:

	int		BoneIndex;
	char		Name[2*W3D_NAME_LEN];

};

/**
** ProxyArrayClass
** This is a ref-counted list of proxy objects.  It is generated whenever an HLODdef contains
** proxies.  Each instantiated HLOD simply add-refs a pointer to the single list.
*/
class ProxyArrayClass : public W3DMPO, public VectorClass<ProxyRecordClass>, public RefCountClass
{
	// BFME2 dropped the W3D pool for this class: retail ??_GProxyArrayClass
	// calls global operator delete, so no W3DMPO_GLUE here.
public:
	ProxyArrayClass(int size) : VectorClass<ProxyRecordClass>(size)
	{
	}
};



struct HlodProxyPivot { unsigned char prefix[0x30]; BfmeProxyTransform Transform; unsigned char tail[12]; };
struct HlodProxyTree { char Name[16]; int NumPivots; HlodProxyPivot *Pivot; };
typedef char HlodProxyPivotStride[(sizeof(HlodProxyPivot) == 0x58) ? 1 : -1];
typedef char HlodProxyOutputSize[(sizeof(ProxyClass) == 32) ? 1 : -1];
bool HLodClass::Get_Proxy (int index, ProxyClass &proxy) const
{
	bool retval = false;

	if (ProxyArray != NULL) {

		//
		//	Lookup the proxy's transform
		//
		HTree->Base_Update(Get_Transform());
		BfmeProxyTransform transform = reinterpret_cast<const HlodProxyTree *>(HTree)->Pivot[(*ProxyArray)[index].Get_Bone_Index()].Transform;
		Set_Hierarchy_Valid(false);

		//
		//	Pass the data onto the proxy object
		//
		proxy.Set_Transform(transform);
		proxy.Set_Name((*ProxyArray)[index].Get_Name());
		retval = true;

	} else {
		proxy.Set_Name ("");
		proxy.Set_Transform (BfmeProxyTransform (true));
	}

	return retval;
}
