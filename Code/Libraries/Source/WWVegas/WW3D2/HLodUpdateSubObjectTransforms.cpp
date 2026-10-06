// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Update_Sub_Object_Transforms: target19D640..19DB43,1283 bytes.
// EA/BFME1 hlod.cpp supplies the two model loops and method identity.
// Matched HLod constructors install table7D6780; slotA8 holds this body.
// Its base call19D649 targets1A5900: matched Animatable3DObj constructors
// install table7D6D10 with that callee at slotA8. The callee updates the
// hierarchy through the parent/motion-mode paths; no thunk is involved.
//
// Target-specific work: quaternion/translation pivots at30/40, stride58;
// pivot visibility50; float54 forwarded through RenderObj slot5C with index0;
// additional-model offsets applied to their matrix when nonzero. The float
// name below describes its use; its original source name is not established.
// Pivot offsets are independently backed by HTreePivotClass.cpp. The matrix
// expansion is shared in shape with the verified HLodAddLodModel recovery.
// Taking the additional offset reference before constructing the matrix
// reproduces retail register allocation. Shared donor headers are unchanged.
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
    unsigned char pad[3];
    float IndexedFactor;
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
void HLodClass::Update_Sub_Object_Transforms(void)
{
	/*
	** Update the animation transforms, recurse up to the
	** top of the tree...
	*/
	Animatable3DObjClass::Update_Sub_Object_Transforms();

	/*
	** Put the computed transforms into our sub objects.
	*/
	int lod,model;

	for (lod = 0; lod < LodCount; lod++) {
		for (model = 0; model < Lod[lod].Count(); model++) {

			RenderObjClass * robj = Lod[lod][model].Model;
			int bone = Lod[lod][model].BoneIndex;

			Matrix3D transform;
			treeMatrix(HTree,bone,transform);
			robj->Set_Transform(transform);
			robj->Set_Animation_Hidden(!reinterpret_cast<const HlodTreeView *>(HTree)->Pivot[bone].IsVisible);
			robj->_bfme_set_indexed_factor(0,reinterpret_cast<const HlodTreeView *>(HTree)->Pivot[bone].IndexedFactor);
			robj->Update_Sub_Object_Transforms();
		}
	}

	for (model = 0; model < AdditionalModels.Count(); model++) {

		RenderObjClass * robj = AdditionalModels[model].Model;
		int bone = AdditionalModels[model].BoneIndex;
        const Vector3 &offset = AdditionalModels[model].Offset;

		Matrix3D transform;
			treeMatrix(HTree,bone,transform);
			if (offset != Vector3(0.0f,0.0f,0.0f)) transform.Translate(offset);
        robj->Set_Transform(transform);
        robj->_bfme_set_indexed_factor(0,reinterpret_cast<const HlodTreeView *>(HTree)->Pivot[bone].IndexedFactor);
		robj->Set_Animation_Hidden(!reinterpret_cast<const HlodTreeView *>(HTree)->Pivot[bone].IsVisible);
		robj->Update_Sub_Object_Transforms();
	}

	Set_Sub_Object_Transforms_Dirty(false);
}
