// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?flushOccludedObjectsIntoStencil@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
// retail 0x00070841..0x00070F80 (1855 bytes), thiscall RET 4.
//
// BFME 2's RTS3DScene::flushOccludedObjectsIntoStencil. Donor: Zero Hour
// W3DScene.cpp flushOccludedObjectsIntoStencil. BFME 2 differences, read from retail:
// - early return without TheW3DShadowManager; no occluder/occludee count guard;
// - the template word +0x5E2 bits 0x380 are ORed into the DrawableInfo flags
//   while bucketing, and select per-object stencil references ((flags >> 3) & 0x70);
// - objects render through the four-argument renderOneObject 0x0006FB59 and the
//   mesh flush rva001173f0(rinfo);
// - player colours are drawn only when GlobalData +0x68 and GameLogic +0x99 are set
//   outside shadow-map rendering (WW3D::IsCurrentlyRenderingShadowMap), through the
//   four-argument renderStenciledPlayerColor 0x0006EB6D;
// - it ends by setting D3DRS_AMBIENT from the scene ambient light (vslot 7)
//   through the inline asm Convert_Color.
// TheGameLogic +0x99 is read raw because the canonical GameLogic view keeps that
// byte as padding.
//
// Same-TU context (retail W3DScene.obj): the colorspace.h inlines RGB_To_HSV and
// HSV_To_RGB are visible here, as they were to retail (both copies sit inside
// W3DScene.obj's range); retail still calls them out of line, but knowing they
// keep no pointer to hsv/rgb is what gives retail's frame, with hsv/rgb at function
// scope as in Zero Hour. Either change alone leaves the 12-byte homes swapped.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"

inline float WWMath::Min(float a, float b)
{
	if (a<b) return a;
	return b;
}

inline float WWMath::Max(float a, float b)
{
	if (a>b) return a;
	return b;
}

// colorspace.h (ZH/BFME 1 WW3D2): the inline bodies retail compiled out of line in
// W3DScene.obj (RGB_To_HSV 0x0006E2C2, HSV_To_RGB 0x0006E3D7, rowed in ColorSpaceO1Inlines.cpp).
inline void RGB_To_HSV(Vector3 &hsv,const Vector3 &rgb)
{
	float max=WWMath::Max(rgb.X,rgb.Y);
	max=WWMath::Max(max,rgb.Z);
	float min=WWMath::Min(rgb.X,rgb.Y);
	min=WWMath::Min(min,rgb.Z);
	hsv.Z=max;
	hsv.Y=(max!=0.0f)?((max-min)/max):0.0f;
	if (hsv.Y==0.0f) hsv.X=-1.0f;
	else
	{
		float delta=max-min;
		if (rgb.X==max)
			hsv.X=(rgb.Y-rgb.Z)/delta;
		else if (rgb.Y==max)
			hsv.X=2.0f+ (rgb.Z-rgb.X)/delta;
		else if (rgb.Z==max)
			hsv.X=4.0f+ (rgb.X-rgb.Y)/delta;
		hsv.X*=60.0f;
		if (hsv.X<0.0f) hsv.X+=360.0f;
	}
}
inline void HSV_To_RGB(Vector3 &rgb, const Vector3 &hsv)
{
	float h=hsv.X;
	float s=hsv.Y;
	float v=hsv.Z;
	if (hsv.Y==0.0f)	{
		rgb.Set(v,v,v);
	} else	{
		float f,p,q,t;
		int i;
		if (h==360.0f) h=0.0f;
		h/=60.0f;
		i=floorf(h);
		f=h-i;
		p=v*(1.0f-s);
		q=v*(1.0f-(s*f));
		t=v*(1.0f-(s*(1.0f-f)));
		switch (i)	{
		case 0: rgb.Set(v,t,p); break;
		case 1: rgb.Set(q,v,p); break;
		case 2: rgb.Set(p,v,t); break;
		case 3: rgb.Set(p,q,v); break;
		case 4: rgb.Set(t,p,v); break;
		case 5: rgb.Set(v,p,q); break;
		}
	}
}

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

__forceinline unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;
	__asm
	{
		sub	esp,20
		fwait
		fstcw		[esp+16]
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)
		or			eax,(1024|2048)
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or		eax,ecx
		or		eax,ebx
		or		eax,edx
		fstp	st(0)
		cmp	edi,0
		je		not_changed
		fwait
		fldcw	[esp+16];
not_changed:
		add	esp,20
		mov	col,eax
	}
	return col;
}

#include "../../../../GameEngine/Include/Common/Player.h"

#include "../../../../GameEngine/Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../../GameEngine/Source/GameLogic/Object/object.h"

#include "../../../../GameEngine/Include/Common/ThingTemplate.h"

#include "../../../../GameEngine/Include/GameClient/Drawable.h"

#include "../../../../GameEngine/Include/GameClient/DrawableInfoClass.h"

class RenderObjClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86();
	virtual void *Get_User_Data();
};

class RenderInfoClass;

#include "../../../Include/W3DDevice/GameClient/W3DShadowManager.h"
extern W3DShadowManager *TheW3DShadowManager;

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

class GameLogic;
extern GameLogic *TheGameLogic;

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

Int Rva0006EB3BReverse(Int index);
void rva001173f0(UnsignedInt rinfo);
void renderStenciledPlayerColor(UnsignedInt color, UnsignedInt stencilRef, Bool clear, UnsignedInt stencilMask);

enum {
	D3DRS_ZENABLE = 7, D3DRS_STENCILENABLE = 52, D3DRS_STENCILFAIL = 53,
	D3DRS_STENCILZFAIL = 54, D3DRS_STENCILPASS = 55, D3DRS_STENCILFUNC = 56,
	D3DRS_STENCILREF = 57, D3DRS_STENCILMASK = 58, D3DRS_STENCILWRITEMASK = 59,
	D3DRS_AMBIENT = 139
};
enum { D3DCMP_ALWAYS = 8 };
enum { D3DSTENCILOP_KEEP = 1, D3DSTENCILOP_REPLACE = 3 };

#define MAX_PLAYER_COUNT 20
#define MAX_VISIBLE_OCCLUDED_PLAYER_OBJECTS 512

class RTS3DScene
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual const Vector3 &Get_Ambient_Light() const;
	static __forceinline Bool drawOccludedColors()
	{
		return TheWritableGlobalData->m_useBehindBuildingMarker && ((const char *)TheGameLogic)[0x99] && !WW3D::IsCurrentlyRenderingShadowMap;
	}
protected:
	void renderOneObject(RenderInfoClass &rinfo, RenderObjClass *robj, Int localPlayerIndex, Int flag);
	void flushOccludedObjectsIntoStencil(RenderInfoClass &rinfo);
	char m_pad004[0x7FC - 4];
	RenderObjClass **m_nonOccludersOrOccludees;
	RenderObjClass **m_potentialOccludees;
	RenderObjClass **m_potentialOccluders;
	Int m_numNonOccluderOrOccludee;
	Int m_numPotentialOccludees;
	Int m_numPotentialOccluders;
};

void RTS3DScene::flushOccludedObjectsIntoStencil(RenderInfoClass &rinfo)
{
	RenderObjClass *robj;
	Drawable *draw;
	RenderObjClass *playerObjects[MAX_PLAYER_COUNT][MAX_VISIBLE_OCCLUDED_PLAYER_OBJECTS];
	RenderObjClass **lastPlayerObject[MAX_PLAYER_COUNT];
	Int playerColorIndex[MAX_PLAYER_COUNT];
	Int visiblePlayerColors[MAX_PLAYER_COUNT];
	Int numObjects;
	Vector3 hsv, rgb;
	Int i;

	if (!TheW3DShadowManager)
		return;

	Int numVisiblePlayerColors = 0;

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		lastPlayerObject[i] = &playerObjects[i][0];
		playerColorIndex[i] = -1;
	}

	TheW3DShadowManager->setStencilShadowMask(0);

	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

	for (Int k = 0; k < m_numPotentialOccludees; k++)
	{
		robj = m_potentialOccludees[k];
		draw = ((DrawableInfo *)robj->Get_User_Data())->m_drawable;
		Object *object = draw->getObject();
		Int index = object->getControllingPlayer()->getPlayerIndex();
		if ((lastPlayerObject[index] - &playerObjects[index][0]) >= MAX_VISIBLE_OCCLUDED_PLAYER_OBJECTS)
			continue;
		*lastPlayerObject[index] = robj;
		lastPlayerObject[index]++;
		((DrawableInfo *)robj->Get_User_Data())->m_flags |= draw->getTemplate()->m_shadowType & 0x380;
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, 0xffffffff);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, 0xffffffff);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		if ((numObjects = lastPlayerObject[i] - &playerObjects[i][0]) != 0)
		{
			if (playerColorIndex[i] == -1)
			{
				playerColorIndex[i] = Rva0006EB3BReverse(numVisiblePlayerColors + 1);
				draw = ((DrawableInfo *)playerObjects[i][0]->Get_User_Data())->m_drawable;
				Object *object = draw->getObject();
				Int color = object->getControllingPlayer()->getPlayerColor();
				RGB_To_HSV(hsv, Vector3(((color >> 16) & 0xff) / 255.0f, ((color >> 8) & 0xff) / 255.0f, (color & 0xff) / 255.0f));
				hsv.Z *= TheWritableGlobalData->m_occludedColorLuminanceScale;
				HSV_To_RGB(rgb, hsv);
				visiblePlayerColors[numVisiblePlayerColors++] = DX8Wrapper::Convert_Color(rgb, 0.5f);
			}

			Int thisPlayerColorIndex = playerColorIndex[i];
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, thisPlayerColorIndex);

			RenderObjClass **renderList = &playerObjects[i][0];
			for (Int j = 0; j < numObjects; j++)
			{
				DrawableInfo *drawInfo = (DrawableInfo *)(*renderList)->Get_User_Data();
				if (drawInfo->m_flags & 0x380)
				{
					rva001173f0((UnsignedInt)&rinfo);
					DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, ((((DrawableInfo *)(*renderList)->Get_User_Data())->m_flags >> 3) & 0x70) | thisPlayerColorIndex);
					renderOneObject(rinfo, *renderList, localPlayerIndex, 0);
					rva001173f0((UnsignedInt)&rinfo);
					DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, thisPlayerColorIndex);
				}
				else
					renderOneObject(rinfo, *renderList, localPlayerIndex, 0);
				renderList++;
			}
			rva001173f0((UnsignedInt)&rinfo);
		}
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, 0xffffffff);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, 0x70);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	RenderObjClass **occluderList = m_potentialOccluders;
	for (i = 0; i < m_numPotentialOccluders; i++)
	{
		RenderObjClass *robj = *occluderList;
		Int bits = (((DrawableInfo *)robj->Get_User_Data())->m_drawable->getTemplate()->m_shadowType >> 3) & 0x70;
		if (bits)
		{
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, bits);
			renderOneObject(rinfo, robj, localPlayerIndex, 0);
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0);
		}
		else
			renderOneObject(rinfo, *occluderList, localPlayerIndex, 0);
		occluderList++;
	}
	rva001173f0((UnsignedInt)&rinfo);

	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, 0xffffffff);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, 0x808080f0);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	RenderObjClass **nonOccluderOrOccludeeList = m_nonOccludersOrOccludees;
	for (i = 0; i < m_numNonOccluderOrOccludee; i++)
	{
		robj = *nonOccluderOrOccludeeList;
		Int bits = (((DrawableInfo *)robj->Get_User_Data())->m_drawable->getTemplate()->m_shadowType >> 3) & 0x70;
		if (bits)
		{
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, bits | 0x80808080);
			renderOneObject(rinfo, robj, localPlayerIndex, 0);
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
		}
		else
			renderOneObject(rinfo, *nonOccluderOrOccludeeList, localPlayerIndex, 0);
		nonOccluderOrOccludeeList++;
	}
	rva001173f0((UnsignedInt)&rinfo);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, true);

	Int usedPlayerColorBits = 0;
	for (i = 0; i < numVisiblePlayerColors; i++)
	{
		Int stencilRef = Rva0006EB3BReverse(i + 1) | 0x80;
		if (drawOccludedColors())
			renderStenciledPlayerColor(visiblePlayerColors[i], stencilRef, false, 0x8f);
		usedPlayerColorBits |= stencilRef;
	}

	TheW3DShadowManager->setStencilShadowMask(usedPlayerColorBits);
	if (TheWritableGlobalData->m_useShadowVolumes)
	{
		if (usedPlayerColorBits == 0)
			TheW3DShadowManager->setStencilShadowMask(0x80808080);
		if (drawOccludedColors())
			renderStenciledPlayerColor(0, 0x80808080, true, 0xffffffff);
		else
			renderStenciledPlayerColor(0, 0, true, 0xffffffff);
		TheW3DShadowManager->setStencilShadowMask(0x80808080);
	}
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, false);

	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENT, DX8Wrapper::Convert_Color(Get_Ambient_Light(), 0.0f));
}
