// cl: /DNDEBUG /MD /EHsc /arch:SSE /G7
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/SceneClass_Render.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7). BFME2 deltas from
// the donor: a float ZBias call, Set_Fog latching start/end, Convert_Color's
// result zeroed before the asm block (retail stores 0 to it first).
// readable body of ?Render@SceneClass@@MAEXAAVRenderInfoClass@@@Z: game/Libraries/Source/WWVegas/WW3D2/scene.cpp
// BFME SceneClass::Render: ZH body with Set_DX8_ZBias out of line (not
// Set_DX8_Render_State D3DRS_ZBIAS) and Clear split into color/z/stencil.

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class RenderInfoClass;
class SceneIterator;
class RenderObjClass;
class ChunkSaveClass;
class ChunkLoadClass;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);
	virtual ~RefCountClass(void);
	int NumRefs;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	static bool ShaderDirty;
	static void Invalidate() { ShaderDirty = true; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static bool FogEnable;
	static unsigned FogColor;
	static void Set_DX8_Render_State(unsigned long state, unsigned value);

	static void Clear(bool clear_color, bool clear_z, bool clear_stencil,
		const Vector3 &color, float dest_alpha = 0.0f, float z = 1.0f,
		unsigned stencil = 0);
	static unsigned Convert_Color(const Vector3 &color, float alpha);
};

// BFME2 keeps Set_DX8_ZBias out of line with a float bias (0x0011F1C0, rowed
// under this name), and its Set_Fog also latches start/end into the two
// globals after FogColor (VA 0x00DEDA28/0x00DEDA2C; only this store pins them).
void bfmeSetProjectionDepthBias(float bias);
extern float g_Va00DEDA28;
extern float g_Va00DEDA2C;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool IsTexturingEnabled;
	static bool Is_Texturing_Enabled() { return IsTexturingEnabled; }
	static void Enable_Texturing(bool b);
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

__forceinline void Set_Fog(bool enable, const Vector3 &color, float start, float end)
{
	DX8Wrapper::FogEnable = enable;
	DX8Wrapper::FogColor = DX8Wrapper::Convert_Color(color, 0.0f);
	g_Va00DEDA28 = start;
	g_Va00DEDA2C = end;
	ShaderClass::Invalidate();
	DX8Wrapper::Set_DX8_Render_State(36, *(unsigned *)(&start));
	DX8Wrapper::Set_DX8_Render_State(37, *(unsigned *)(&end));
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SceneClass : public RefCountClass
{
public:
	virtual ~SceneClass(void);
	virtual void Add_Render_Object(RenderObjClass * obj);
	virtual void Remove_Render_Object(RenderObjClass * obj);
	virtual SceneIterator * Create_Iterator(bool onlyvisible = false) = 0;
	virtual void Destroy_Iterator(SceneIterator * it) = 0;
	virtual void Set_Ambient_Light(const Vector3 & color);
	virtual const Vector3 & Get_Ambient_Light(void);
	virtual void Set_Fog_Enable(bool set);
	virtual bool Get_Fog_Enable(void);
	virtual void Set_Fog_Color(const Vector3 & color);
	virtual const Vector3 & Get_Fog_Color(void);
	virtual void Set_Fog_Range(float start, float end);
	virtual void Get_Fog_Range(float * start, float * end);
	virtual void Register(RenderObjClass * obj, int for_what) = 0;
	virtual void Unregister(RenderObjClass * obj, int for_what) = 0;
	virtual float Compute_Point_Visibility(RenderInfoClass & rinfo, const Vector3 & point);
	virtual void Slot17(void) = 0;
	virtual void Slot18(void) = 0;
	virtual void Slot19(void) = 0;
	virtual void Save(ChunkSaveClass & csave);
	virtual void Load(ChunkLoadClass & cload);

	enum ExtraPassPolyRenderType
	{
		EXTRA_PASS_DISABLE,
		EXTRA_PASS_LINE,
		EXTRA_PASS_CLEAR_LINE
	};
	ExtraPassPolyRenderType Get_Extra_Pass_Polygon_Mode(void) { return ExtraPassPolyRenderMode; }

protected:
	virtual void Render(RenderInfoClass & rinfo);

	Vector3 AmbientLight;
	int PolyRenderMode;
	ExtraPassPolyRenderType ExtraPassPolyRenderMode;
	bool FogEnabled;
	Vector3 FogColor;
	float FogStart;
	float FogEnd;

private:
	virtual void Customized_Render(RenderInfoClass & rinfo) = 0;
	virtual void Pre_Render_Processing(RenderInfoClass & rinfo) {}
	virtual void Post_Render_Processing(RenderInfoClass & rinfo) {}
};

void SceneClass::Render(RenderInfoClass & rinfo)
{
	Pre_Render_Processing(rinfo);

	Set_Fog(FogEnabled, FogColor, FogStart, FogEnd);

	if (Get_Extra_Pass_Polygon_Mode() == EXTRA_PASS_DISABLE) {
		Customized_Render(rinfo);
	}
	else {
		bool old_enable = WW3D::Is_Texturing_Enabled();

		bfmeSetProjectionDepthBias(0.0f);
		Customized_Render(rinfo);
		switch (Get_Extra_Pass_Polygon_Mode()) {
		case EXTRA_PASS_LINE:
			WW3D::Enable_Texturing(false);
			DX8Wrapper::Set_DX8_Render_State(8, 2);
			bfmeSetProjectionDepthBias(7.0f);
			Customized_Render(rinfo);
			break;
		case EXTRA_PASS_CLEAR_LINE:
			DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.0f, 0.0f));
			WW3D::Enable_Texturing(false);
			DX8Wrapper::Set_DX8_Render_State(8, 2);
			bfmeSetProjectionDepthBias(7.0f);
			Customized_Render(rinfo);
			break;
		}

		WW3D::Enable_Texturing(old_enable);
	}

	Post_Render_Processing(rinfo);
}
