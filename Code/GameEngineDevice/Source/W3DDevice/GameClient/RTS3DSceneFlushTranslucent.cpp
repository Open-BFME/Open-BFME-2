// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
//
// Two BFME 2 translucent-object flush passes of RTS3DScene.
//
// Target facts: native 0x00070F80..0x000710D6 (342B) and 0x000710D6..0x00071233
// (349B), both thiscall RET4 taking the RenderInfoClass. The scene render body
// calls the first right after the "RenderStaticSortLists" render event and the
// second right after "RenderParticles" (call sites 0x00071D7D / 0x00071DDC),
// each only when custom pass mode +0x7EC and polygon mode +0x18 are zero.
// Both walk the translucent buffer (count +0x7F0, array +0x7F4), read the
// drawable through render-object user data (vtable +0x15C, DrawableInfo +4),
// split on the render-object byte +0xBC (first pass: zero, second: non-zero),
// set RenderInfo +0x1C from the matched drawable opacity getter 0x00272C9E,
// draw with the pinned scene helper 0x0006FB59, then flush the mesh renderer
// (0x001173F0) and the static sort lists, restore +0x1C to 1.0f and finally set
// D3DRS_AMBIENT (139) from the scene's ambient (vtable +0x1C) packed with 0
// alpha. Only the second pass clears the count.
// Donor: ZH GeneralsMD W3DScene.cpp RTS3DScene::flushTranslucentObjects (BFME1
// pointer) is the semantic guide; BFME 2 split it in two passes. The original
// names of the two passes are unknown, so both keep address-derived names.
// The x87 colour packing is dx8wrapper.h DX8Wrapper::Convert_Color's own
// inline assembler, reused from the verified DX8SetAmbient.cpp.

class Vector3 { public: float X, Y, Z; };

class RenderInfoClass
{
public:
	char gap00[0x1C];
	float alphaOverride; // +0x1C
};

class RenderObjClass
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void Set_User_Data(void *, bool);
	virtual void *Get_User_Data() const; // +0x15C
	char gap04[0xBC - 4];
	bool flagBC; // +0xBC
};

class Drawable
{
public:
	float rva00272C9E(int key);
};

struct DrawableInfo
{
	unsigned shroudStatusObjectID;
	Drawable *drawable; // +4
};

class PlayerList;
extern PlayerList *ThePlayerList;
struct ScenePlayerView { char gap[0x54]; int index; };
struct ScenePlayerListView { char gap[0x10]; ScenePlayerView *local; };

void __cdecl rva001173f0(unsigned int renderArgument);

class WW3D
{
public:
	static void Render_And_Clear_Static_Sort_Lists(RenderInfoClass &rinfo);
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static unsigned Convert_Color(const Vector3 &color, float alpha);
};

__forceinline unsigned DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
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

class RTS3DScene
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual const Vector3 &Get_Ambient_Light(); // +0x1C

	void rva0006FB59(RenderInfoClass &, RenderObjClass *, int, bool);
	void rva00070F80(RenderInfoClass &rinfo);
	void rva000710D6(RenderInfoClass &rinfo);

	char gap004[0x7F0 - 4];
	int m_translucentObjectsCount;               // +0x7F0
	RenderObjClass **m_translucentObjectsBuffer; // +0x7F4
};

// First pass: translucent objects whose render-object byte +0xBC is clear.
void RTS3DScene::rva00070F80(RenderInfoClass &rinfo)
{
	if (m_translucentObjectsCount)
	{
		int localPlayerIndex = ThePlayerList ? ((ScenePlayerListView *)ThePlayerList)->local->index : 0;

		for (int i = 0; i < m_translucentObjectsCount; i++)
		{
			RenderObjClass *robj = m_translucentObjectsBuffer[i];
			Drawable *draw = ((DrawableInfo *)robj->Get_User_Data())->drawable;
			if (robj->flagBC)
				continue;
			rinfo.alphaOverride = draw->rva00272C9E((int)robj);
			rva0006FB59(rinfo, robj, localPlayerIndex, false);
		}

		rva001173f0((unsigned int)&rinfo);
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
		rinfo.alphaOverride = 1.0f;
	}

	DX8Wrapper::Set_DX8_Render_State(139, DX8Wrapper::Convert_Color(Get_Ambient_Light(), 0.0f));
}

// Second pass: the objects with byte +0xBC set; this pass clears the buffer.
void RTS3DScene::rva000710D6(RenderInfoClass &rinfo)
{
	if (m_translucentObjectsCount)
	{
		int localPlayerIndex = ThePlayerList ? ((ScenePlayerListView *)ThePlayerList)->local->index : 0;

		for (int i = 0; i < m_translucentObjectsCount; i++)
		{
			RenderObjClass *robj = m_translucentObjectsBuffer[i];
			Drawable *draw = ((DrawableInfo *)robj->Get_User_Data())->drawable;
			if (!robj->flagBC)
				continue;
			rinfo.alphaOverride = draw->rva00272C9E((int)robj);
			rva0006FB59(rinfo, robj, localPlayerIndex, false);
		}

		rva001173f0((unsigned int)&rinfo);
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
		rinfo.alphaOverride = 1.0f;
		m_translucentObjectsCount = 0;
	}

	DX8Wrapper::Set_DX8_Render_State(139, DX8Wrapper::Convert_Color(Get_Ambient_Light(), 0.0f));
}
