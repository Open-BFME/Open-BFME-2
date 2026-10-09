// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Clean BFME1 donor 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp.
// Target 0x000B3094 is 159B; full /O1 /G7 body and Get_Parent_Index call
// at 0x000B30E4 -> rowed 0x00160BD0 match. The donor establishes traversal
// semantics; native calls separately prove slots 30/36/48/101, refcount +4
// and virtual deletion slot 0. The referenced RenderObj header's five calls
// were all four bytes early, so its class layout is not copied into this TU.
// Static helper's compiler-selected ESI argument is preserved by the emission
// anchor below; that anchor is build scaffolding and claims no retail bytes.
// stlport
typedef bool Bool;
typedef int Int;
class RenderObjClass;
#include "htree.h"
// Target call sites prove BFME2 slots 30/36/48/101. The shared RenderObj
// header currently emits slots 29/35/47/100, so dispatch the four observed
// slots through a single-inheritance member-pointer view without changing it.
class BfmeBoneRenderDispatch {};
typedef RenderObjClass *(BfmeBoneRenderDispatch::*BoneGetSub)(int) const;
typedef int (BfmeBoneRenderDispatch::*BoneGetIndex)(RenderObjClass *) const;
typedef int (BfmeBoneRenderDispatch::*BoneGetCount)() const;
typedef void (BfmeBoneRenderDispatch::*BoneSetHidden)(int);
// ?nativeSubObject absent-from-retail
__forceinline RenderObjClass *nativeSubObject(RenderObjClass *o, int index) { return (((BfmeBoneRenderDispatch *)o)->*(*(BoneGetSub *)&(*(void ***)o)[30]))(index); }
// ?nativeSubBone absent-from-retail
__forceinline int nativeSubBone(RenderObjClass *o, RenderObjClass *child) { return (((BfmeBoneRenderDispatch *)o)->*(*(BoneGetIndex *)&(*(void ***)o)[36]))(child); }
// ?nativeBoneCount absent-from-retail
__forceinline int nativeBoneCount(RenderObjClass *o) { return (((BfmeBoneRenderDispatch *)o)->*(*(BoneGetCount *)&(*(void ***)o)[48]))(); }
// ?nativeSetHidden absent-from-retail
__forceinline void nativeSetHidden(RenderObjClass *o, int hidden) { (((BfmeBoneRenderDispatch *)o)->*(*(BoneSetHidden *)&(*(void ***)o)[101]))(hidden); }
struct BfmeBoneRefCount { void *vtable; mutable int refs; };
typedef void (BfmeBoneRenderDispatch::*BoneDestroy)();
// ?nativeRelease absent-from-retail
__forceinline void nativeRelease(RenderObjClass *o) { if (--((BfmeBoneRefCount *)o)->refs == 0) (((BfmeBoneRenderDispatch *)o)->*(*(BoneDestroy *)&(*(void ***)o)[0]))(); }
static void doHideShowBoneSubObjs(Bool state, Int numSubObjects, Int boneIdx, RenderObjClass *fullObject, const HTreeClass *htree)
{
	for (Int i=0; i < numSubObjects; i++) 
	{
		RenderObjClass *childObject = nativeSubObject(fullObject, i);
		if (childObject)
		{
			Int parentBoneIndex = nativeSubBone(fullObject, childObject);
			nativeRelease(childObject);
			while (parentBoneIndex > 0 && parentBoneIndex < nativeBoneCount(fullObject))
			{
				parentBoneIndex = htree->Get_Parent_Index(parentBoneIndex);
				if (parentBoneIndex == boneIdx)
				{
					childObject = nativeSubObject(fullObject, i);
					if (childObject)
					{
						nativeSetHidden(childObject, state);
						nativeRelease(childObject);
					}
					break;
				}
			}
		}
	}
}

// ?invokeBoneVisibility absent-from-retail
void invokeBoneVisibility(Bool state, Int count, Int bone, RenderObjClass *obj, const HTreeClass *tree) { doHideShowBoneSubObjs(state, count, bone, obj, tree); }

// Target body at 0x000B3885. Retail evidence shows a hide flag at +4 in the
// first argument, a RenderObjClass pointer in the second, a subobject index
// in the third, and a render-object pointer at this+0x50. It sets the chosen
// subobject's hidden state, checks the HTree and bone bounds through retail
// vtable slots, then calls the byte-matched doHideShowBoneSubObjs body at
// 0x000B3094. W3DModelDraw's updateSubObjects path in the donor has the same
// behavior; the exact target method name remains address-derived.
struct Rva000B3885HideShowInfo
{
	char m_name[4];
	Bool m_hide;
	char m_pad05[3];
	float m_fadeRate;	// +0x08, per-update alpha step; zero hides or shows at once
	float m_alpha;		// +0x0C
	float m_delayStep;	// +0x10
	float m_delay;		// +0x14
};

// Owner byte +0x442 of the object at this+0x08: tested before fading.
struct Rva000B38F9Owner
{
	char m_pad[0x442];
	Bool m_bfme442;
};

// Retail 0x000B3814: applies an alpha to a subobject (W3DModelDraw view).
class Rva000B3814Arg;
class Rva000B3814
{
public:
	void rva000B3814(Rva000B3814Arg *subObject, float alpha);
};

class Rva000B3885
{
public:
	char m_pad00[0x08];
	Rva000B38F9Owner *m_owner;	// +0x08
	char m_pad0C[0x50 - 0x0C];
	RenderObjClass *m_renderObject;
	char m_pad54[0x1C9 - 0x54];
	Bool m_bfme1C9;			// +0x1C9
	void rva000B3885(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex);
	void rva000B38F9(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex);
};

typedef const HTreeClass *(BfmeBoneRenderDispatch::*BoneGetTree)() const;
typedef Int (BfmeBoneRenderDispatch::*BoneGetObjectIndex)(Int, Int) const;
typedef Int (BfmeBoneRenderDispatch::*BoneGetSubObjectCount)() const;

void Rva000B3885::rva000B3885(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex)
{
	nativeSetHidden(subObject, info->m_hide);

	const HTreeClass *tree = (((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetTree *)&(*(void ***)m_renderObject)[58]))();
	if (tree == NULL)
		return;

	Int boneIndex = (((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetObjectIndex *)&(*(void ***)m_renderObject)[35]))(0, subObjectIndex);
	if (boneIndex <= 0 || boneIndex >= nativeBoneCount(m_renderObject))
		return;

	doHideShowBoneSubObjs(info->m_hide,
		(((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetSubObjectCount *)&(*(void ***)m_renderObject)[28]))(),
		boneIndex, m_renderObject, tree);
}

// Target body at 0x000B38F9 (308 bytes), the fading form of rva000B3885, called
// from 0x000BB367 and 0x000BB3B6. With no fade rate
// the subobject is hidden or shown at once (slot 101). Otherwise, while the
// owner byte +0x442 is clear, the alpha snaps to the fade direction (1 or
// 0) and the rate and delay clear; with a pending delay the delay counts
// down and +0x1C9 is set; else the alpha steps by the rate clamped to 0..1.
// Either alpha path applies it through rowed 0x000B3814. The bone walk tail
// is rva000B3885's. WorldBuilder twin 0x00942B10 (callsite evidence).
void Rva000B3885::rva000B38F9(Rva000B3885HideShowInfo *info, RenderObjClass *subObject, Int subObjectIndex)
{
	if (info->m_fadeRate != 0.0f)
	{
		if (!m_owner->m_bfme442)
		{
			info->m_delayStep = 0.0f;
			info->m_delay = 0.0f;
			info->m_alpha = info->m_fadeRate > 0.0f ? 1.0f : 0.0f;
			info->m_fadeRate = 0.0f;
			((Rva000B3814 *)this)->rva000B3814((Rva000B3814Arg *)subObject, info->m_alpha);
		}
		else if (info->m_delayStep > 0.0f && info->m_delay > 0.0f)
		{
			info->m_delay -= info->m_delayStep;
			if (info->m_delay <= 0.0f)
				info->m_delay = 0.0f;
			m_bfme1C9 = true;
		}
		else
		{
			info->m_alpha += info->m_fadeRate;
			if (info->m_alpha > 1.0f)
				info->m_alpha = 1.0f;
			else if (info->m_alpha < 0.0f)
				info->m_alpha = 0.0f;
			((Rva000B3814 *)this)->rva000B3814((Rva000B3814Arg *)subObject, info->m_alpha);
		}
	}
	else
	{
		nativeSetHidden(subObject, info->m_hide);
	}

	const HTreeClass *tree = (((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetTree *)&(*(void ***)m_renderObject)[58]))();
	if (tree == NULL)
		return;

	Int boneIndex = (((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetObjectIndex *)&(*(void ***)m_renderObject)[35]))(0, subObjectIndex);
	if (boneIndex <= 0 || boneIndex >= nativeBoneCount(m_renderObject))
		return;

	doHideShowBoneSubObjs(info->m_hide,
		(((BfmeBoneRenderDispatch *)m_renderObject)->*(*(BoneGetSubObjectCount *)&(*(void ***)m_renderObject)[28]))(),
		boneIndex, m_renderObject, tree);
}
