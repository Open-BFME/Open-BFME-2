// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Add_Lod_Model: retail 0x0019F2B0..0x0019F4AF, 511 bytes.
// EA/BFME1 hlod.cpp supplies the method identity and attachment semantics.
// Target evidence: matched definition constructor calls this at 0x0019FE42;
// its installed table 0x007D6780 holds this body at slot +0x234. The body
// validates the bone index, retains/attaches the model, sets its transform,
// clears its offset, optionally notifies the scene, and appends the node.
//
// BFME2 pivots store quaternion/translation at +0x30/+0x40, stride 0x58,
// corroborated by HTreePivotClass.cpp's matched constructor and assignment.
// The target expands that block into a temporary Matrix3D. Its arithmetic
// establishes the formulas below; Transform is a descriptive field name.
// A local view avoids changing the donor HTree header's matrix-based layout.
// The product declaration order preserves retail MSVC 7.1 SSE scheduling.
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
// Retail links the size-form RefCountClass inlines (Release_Ref 0x005D1A7D) and the /O1
// Matrix3D default constructor (0x000423C5): compile those headers in that state,
// matrix3d.h's dependencies first, unchanged.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include <assert.h>
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#pragma optimize("gsy", on)
#include "matrix3d.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "winbase_shim.h"
// Retail links the size-optimized WeightInfoStruct vector deleting destructor (??_E,
// the copy htree.cpp emits); it takes the optimization state of the first function
// that needs it, so this unemitted anchor needs it first. The private struct is reached
// by befriending the anchor while hanim.h is first read; layout and names are unchanged.
struct BfmeWeightInfoVddAnchor;
#define private private: friend struct BfmeWeightInfoVddAnchor; private
#include "hanim.h"
#undef private
struct BfmeWeightInfoVddAnchor { typedef NamedPivotMapClass::WeightInfoStruct Info; };
#pragma optimize("gsy", on)
static void bfmeWeightInfoVddAnchor(BfmeWeightInfoVddAnchor::Info *p) { delete [] p; }
#pragma optimize("", on)
// Retail's Get_Bone_Transform returns by value; the shim's guard keeps the reference animobj.h out.
#include "../../../../../reference/shims/bfmeanimobj/animobj.h"
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
static __forceinline Matrix3D &pivotMatrix(const HlodTransformView &hlodTransformView, Matrix3D &matrix3D)
{
    const float xx = hlodTransformView.X * hlodTransformView.X * 2.0f;
    const float xy = hlodTransformView.X * hlodTransformView.Y * 2.0f;
    const float xz = hlodTransformView.Z * hlodTransformView.X * 2.0f;
    const float wx = hlodTransformView.W * hlodTransformView.X * 2.0f;
    const float yy = hlodTransformView.Y * hlodTransformView.Y * 2.0f;
    const float yz = hlodTransformView.Z * hlodTransformView.Y * 2.0f;
    const float wy = hlodTransformView.W * hlodTransformView.Y * 2.0f;
    const float zz = hlodTransformView.Z * hlodTransformView.Z * 2.0f;
    const float wz = hlodTransformView.W * hlodTransformView.Z * 2.0f;

    matrix3D[0][0] = 1.0f - yy - zz;
    matrix3D[0][1] = xy - wz;
    matrix3D[0][2] = xz + wy;
    matrix3D[1][0] = xy + wz;
    matrix3D[1][1] = 1.0f - zz - xx;
    matrix3D[1][2] = yz - wx;
    matrix3D[2][0] = xz - wy;
    matrix3D[2][1] = yz + wx;
    matrix3D[2][2] = 1.0f - yy - xx;
    matrix3D[0][3] = hlodTransformView.Position.X;
    matrix3D[1][3] = hlodTransformView.Position.Y;
    matrix3D[2][3] = hlodTransformView.Position.Z;
    return matrix3D;
}

void HLodClass::Add_Lod_Model(int lod, RenderObjClass * robj, int boneindex)
{
	WWASSERT(robj != NULL);

	// (gth) survive the case where the skeleton for this object no longer has
	// the bone that we're trying to use.  This happens when a skeleton is re-exported
	// but the models that depend on it aren't re-exported...
	if (boneindex >= HTree->Num_Pivots()) {
		WWDEBUG_SAY(("ERROR: Model %s tried to use bone %d in skeleton %s.  Please re-export!\n",Get_Name(),boneindex,HTree->Get_Name()));
		boneindex = 0;
	}

	ModelNodeClass newnode;
	newnode.Model = robj;
	newnode.Model->Add_Ref();
	newnode.BoneIndex = boneindex;
	newnode.Model->Set_Container(this);
	Matrix3D transform;
	newnode.Model->Set_Transform(pivotMatrix(reinterpret_cast<const HlodTreeView *>(HTree)->Pivot[boneindex].Transform,transform));
	newnode.Offset.X = newnode.Offset.Y = newnode.Offset.Z = 0.0f;

	if (Is_In_Scene() && lod == CurLod) {
		newnode.Model->Notify_Added(Scene);
	}
	Lod[lod].Add(newnode);
}
