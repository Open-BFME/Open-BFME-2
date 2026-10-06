// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// EA/BFME1 hlod.cpp semantic donor; reconstructed from the saved partial at
// reverse/attempts/0x0019f190.cpp. Target RVA 0x0019F190, 275 bytes through
// ret 12 at 0x0019F2A0; HLod constructors install table RVA 0x007D6780,
// where slot +0x98 (not +0x38) holds this body. The recovered definition
// constructor also calls it directly at 0x0019FEB4.
//
// The donor method supplies the identity and model-attachment semantics.
// Target accesses establish the bone validation, Vector3 offset copy, and
// visibility lookup. The latter uses BFME2 pivots: stride 0x58, flag +0x50,
// independently established by HTreePivotClass.cpp's constructor/assignment.
// The existing donor HTree header still models matrix-based pivots, so use
// a TU-local view of only the accessed fields. No shared layout is changed.
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

struct HlodPivotView
{
    unsigned char unaccessed[0x50];
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
static __forceinline bool pivotVisible(const HTreeClass *tree, int index)
{
    return reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].IsVisible;
}

int HLodClass::Add_Sub_Object_To_Bone(RenderObjClass *subobj, int boneindex, const Vector3 *offset)
{
	WWASSERT(subobj);
	if ((boneindex < 0) || (boneindex >= HTree->Num_Pivots())) return 0;

	subobj->Set_LOD_Bias(LODBias);
	ModelNodeClass newnode;
	newnode.Model = subobj;
	newnode.Model->Add_Ref();
	newnode.Model->Set_Container(this);
	newnode.Model->Set_Animation_Hidden(pivotVisible(HTree,boneindex) == false);
	newnode.BoneIndex = boneindex;
	if (offset) {
		newnode.Offset = *offset;
	} else {
		newnode.Offset.X = newnode.Offset.Y = newnode.Offset.Z = 0.0f;
	}
	int result = AdditionalModels.Add(newnode);
	Update_Sub_Object_Bits();
	Update_Obj_Space_Bounding_Volumes();
	Set_Hierarchy_Valid(false);
	Set_Sub_Object_Transforms_Dirty(true);
	if (Is_In_Scene()) subobj->Notify_Added(Scene);
	return result;
}
