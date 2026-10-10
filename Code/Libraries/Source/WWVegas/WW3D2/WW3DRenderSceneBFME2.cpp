// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 001182A0..0011842F, 399B, cdecl bool-return ABI, called by
// verified Rva00118660Call. Semantic lead: BFME1 6583b3c1 WW3DRenderScene.cpp
// and ZH ww3d.cpp scene Render; retail supplies an existing RenderInfo.
// Target facts: scene polygon mode +14, ambient vcall +1C, Render +58;
// camera On_Frame_Update +34, camera pointer at RenderInfo+0; renderer+4.
// The original entry name remains unknown. Existing named globals/callees
// are reused from matched WW3DRenderObjRender and DX8SetAmbient.
// The reference Convert_Color x87 rounding helper is retained for its
// proven control-word/codegen requirements, as in matched DX8SetAmbient.
class Vector3 {
public:
    float X,Y,Z;
    Vector3 &operator=(const Vector3 &other) {
        X=other.X; Y=other.Y; Z=other.Z;
        return *this;
    }
};
class CameraClass;
class RenderInfoClass;
class LightEnvironmentClass;

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void Render(RenderInfoClass &rinfo);
};

class CameraClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void On_Frame_Update(void);
	void Apply(void);
};

class RenderInfoClass
{
public:
	CameraClass *Camera;
	char m_padding04[0x24];
	void *light_environment;
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static unsigned Convert_Color(const Vector3 &color, float alpha);
};

class DX8MeshRendererClass
{
public:
	void Set_Camera(CameraClass *camera) { m_camera = camera; }
	void Flush(void);
	void Clear_Pending_Delete_Lists(void);

private:
	char m_padding00[4];
	CameraClass *m_camera;
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class Rva00DF6F94GapFillerContext { public: void rva174ba6(); };
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

// The +0x87 static flush: the callee reads only the global 0x00DEC4F4 and an
// SSE constant, so it takes no this and is __cdecl. Pinned address name.
extern void __cdecl rva0012F190(void);

class StaticSortListClass
{
public:
	virtual ~StaticSortListClass(void);
	virtual void Add_To_List(RenderObjClass *obj, unsigned sort_level);
	virtual void Render_And_Clear(RenderInfoClass &rinfo);
};

class WW3D
{
	friend bool Rva001182A0(void *owner, RenderInfoClass &rinfo);
	// ww3d.cpp defines these private (?IsInitted@WW3D@@0_NA, ...).
	static bool IsInitted;
	static bool AreStaticSortListsEnabled;
	static StaticSortListClass *CurrentStaticSortLists;
};

class SceneClass {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual const Vector3 &Get_Ambient_Light();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void Render(RenderInfoClass &);
    int Get_Polygon_Mode() const { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this)+0x14); }
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


extern Vector3 g_Va00DEDC70;
bool Rva001182A0(void *owner, RenderInfoClass &rinfo)
{
    if (!WW3D::IsInitted) return true;
    SceneClass *scene=static_cast<SceneClass *>(owner);
    rinfo.Camera->On_Frame_Update();
    rinfo.Camera->Apply();
    switch (scene->Get_Polygon_Mode()) {
    case 0: DX8Wrapper::Set_DX8_Render_State(8,1); break;
    case 1: DX8Wrapper::Set_DX8_Render_State(8,2); break;
    case 2: DX8Wrapper::Set_DX8_Render_State(8,3); break;
    }
    const Vector3 &color=scene->Get_Ambient_Light();
    g_Va00DEDC70=color;
    DX8Wrapper::Set_DX8_Render_State(139,DX8Wrapper::Convert_Color(color,0.0f));
    TheDX8MeshRenderer->Set_Camera(rinfo.Camera);
    scene->Render(rinfo);
    TheDX8MeshRenderer->Flush();
    TheMeshGapFillerContext->rva174ba6();
    bool old_enable=WW3D::AreStaticSortListsEnabled;
    WW3D::AreStaticSortListsEnabled=false;
    WW3D::CurrentStaticSortLists->Render_And_Clear(rinfo);
    WW3D::AreStaticSortListsEnabled=old_enable;
    rva0012F190();
    TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
    return true;
}
