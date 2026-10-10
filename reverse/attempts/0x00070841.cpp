// ?flushOccludedObjectsIntoStencil@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.9968 date=2026-10-10
// ?flushOccludedObjectsIntoStencil@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?flushOccludedObjectsIntoStencil@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z  Native 0x00070841..0x00070F80 (1855 bytes)
// NEAR (helper draft): same 1855-byte instruction stream as retail; the only
// differences are two swapped 12-byte stack slots (retail keeps the HSV_To_RGB
// output at ebp-0x3C and hsv at ebp-0x54; this source gets them reversed) and
// the two calls to renderStenciledPlayerColor 0x0006EB6D which resolve once
// that row lands. ZH W3DScene.cpp flushOccludedObjectsIntoStencil with BFME2
// deltas: early return without TheW3DShadowManager; no occluder/occludee
// guard; template word +0x5E2 bits 0x380 OR into DrawableInfo flags and
// select per-object stencil refs; renderOneObject is the pinned 4-argument
// rva0006FB59 and the mesh flush is rva001173F0(rinfo); player colour pass
// gated on TheGlobalData +0x68 TheGameLogic +0x99 and
// WW3D::IsCurrentlyRenderingShadowMap; ends by setting D3DRS_AMBIENT from
// the scene ambient light (vslot 7) through the inline Convert_Color.
// TheGameLogic +0x99 is read raw because the canonical GameLogic view keeps
// that byte as padding.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X, Y, Z;
};

void RGB_To_HSV(Vector3 &hsv, const Vector3 &rgb);
void HSV_To_RGB(Vector3 &rgb, const Vector3 &hsv);

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static unsigned int Convert_Color(const Vector3 &color, float alpha);
};

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

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
	Int getPlayerColor() const { return m_color; }
	char m_pad000[0x54];
	Int m_playerIndex;
	char m_pad058[0x280 - 0x58];
	Int m_color;
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
	char m_pad00[0x10];
	Player *m_local;
};
extern PlayerList *ThePlayerList;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class ThingTemplate
{
public:
	char m_pad000[0x5E2];
	UnsignedShort m_occlusionBits;
};

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() { return m_object; }
	void *m_vtbl;
	const ThingTemplate *m_template;
	char m_pad008[0xFC - 8];
	Object *m_object;
};

struct DrawableInfo
{
	Int m_pad00;
	Drawable *m_drawable;
	Int m_pad08;
	Int m_flags;
};

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

class W3DShadowManager
{
public:
	void setStencilShadowMask(Int mask) { m_stencilShadowMask = mask; }
	char m_pad00[8];
	Int m_stencilShadowMask;
};
extern W3DShadowManager *TheW3DShadowManager;

class GlobalData
{
public:
	char m_pad000[0x60];
	Bool m_useShadowVolumes;
	char m_pad061[0x68 - 0x61];
	Bool m_68;
	char m_pad069[0x984 - 0x69];
	Real m_occludedLuminanceScale;
};
extern GlobalData *TheWritableGlobalData;

class GameLogic;
extern GameLogic *TheGameLogic;

class WW3D
{
	friend class RTS3DScene;
	static bool IsCurrentlyRenderingShadowMap;
};

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
	void rva0006FB59(RenderInfoClass &rinfo, RenderObjClass *robj, Int localPlayerIndex, Bool flag);
	static __forceinline Bool drawOccludedColors()
	{
		return TheWritableGlobalData->m_68 && ((const char *)TheGameLogic)[0x99] && !WW3D::IsCurrentlyRenderingShadowMap;
	}
protected:
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
		((DrawableInfo *)robj->Get_User_Data())->m_flags |= draw->getTemplate()->m_occlusionBits & 0x380;
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
				Vector3 hsv, rgb;
				Int color = object->getControllingPlayer()->getPlayerColor();
				RGB_To_HSV(hsv, Vector3(((color >> 16) & 0xff) / 255.0f, ((color >> 8) & 0xff) / 255.0f, (color & 0xff) / 255.0f));
				hsv.Z *= TheWritableGlobalData->m_occludedLuminanceScale;
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
					rva0006FB59(rinfo, *renderList, localPlayerIndex, false);
					rva001173f0((UnsignedInt)&rinfo);
					DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, thisPlayerColorIndex);
				}
				else
					rva0006FB59(rinfo, *renderList, localPlayerIndex, false);
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
		Int bits = (((DrawableInfo *)robj->Get_User_Data())->m_drawable->getTemplate()->m_occlusionBits >> 3) & 0x70;
		if (bits)
		{
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, bits);
			rva0006FB59(rinfo, robj, localPlayerIndex, false);
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0);
		}
		else
			rva0006FB59(rinfo, *occluderList, localPlayerIndex, false);
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
		Int bits = (((DrawableInfo *)robj->Get_User_Data())->m_drawable->getTemplate()->m_occlusionBits >> 3) & 0x70;
		if (bits)
		{
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, bits | 0x80808080);
			rva0006FB59(rinfo, robj, localPlayerIndex, false);
			rva001173f0((UnsignedInt)&rinfo);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
		}
		else
			rva0006FB59(rinfo, *nonOccluderOrOccludeeList, localPlayerIndex, false);
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
