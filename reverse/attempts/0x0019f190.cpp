// ?Add_Sub_Object_To_Bone@HLodClass@@UAEHPAVRenderObjClass@@HPBVVector3@@@Z
// partial score=0.2618181818 date=2026-09-23
// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Target candidate 0x0019F190/275 is vtable slot 38 of the HLodClass table
// installed by the target ctor. Donor semantic source:
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp
// Target/donor distinction: this body preserves the donor visibility call,
// but target bytes index a compact pivot view (stride 0x58, visible byte +0x50)
// while this donor-header build uses a different PivotClass representation.
// Current scratch build is a semantic near miss, not a verified conversion.
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

int HLodClass::Add_Sub_Object_To_Bone(RenderObjClass *subobj, int boneindex, const Vector3 *offset)
{
	WWASSERT(subobj);
	if ((boneindex < 0) || (boneindex >= HTree->Num_Pivots())) return 0;

	subobj->Set_LOD_Bias(LODBias);
	ModelNodeClass newnode;
	newnode.Model = subobj;
	newnode.Model->Add_Ref();
	newnode.Model->Set_Container(this);
	newnode.Model->Set_Animation_Hidden(HTree->Get_Visibility(boneindex) == false);
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
