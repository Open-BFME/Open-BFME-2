// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?renderStenciledPlayerColor@@YAXII_NI@Z  Native 0x0006EB6D..0x0006ED29 (444 bytes)
// ZH W3DScene.cpp renderStenciledPlayerColor with the BFME2 deltas: an early
// return without TheW3DShadowManager; the clear pass uses the caller stencil
// reference and the shadow manager stencil mask (+8) for both stencil masks
// and always disables colour writes; the colour pass takes its stencil mask
// from a fourth argument; the full-screen quad is drawn with
// W3DShaderManager::drawViewport 0x00075746 (scale 1 1) and colour writes are
// restored to 0xF at the end. Set_Material is inlined (render_state.material
// at 0x009EE5DC and MATERIAL_CHANGED 0x4000 in render_state_changed). The
// player colour shader is the W3DScene.cpp file static at VA 0x00DB4248.
// Callers: RTS3DScene::flushOccludedObjectsIntoStencil 0x00070841 (two sites).

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class ShaderClass { public: unsigned int ShaderBits; };
extern ShaderClass g_00DB4248;

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int NumRefs;
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	void Add_Ref() { NumRefs++; }
	void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
};

extern VertexMaterialClass *ScreenMaterial;

struct IDirect3DDevice8;

class DX8Wrapper
{
public:
	enum { MATERIAL_CHANGED = 0x4000 };
	static void Set_Shader(const ShaderClass &shader);
	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		render_state_changed |= MATERIAL_CHANGED;
		ScreenMaterial = material;
	}
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static Bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
protected:
	static unsigned int render_state_changed;
	static IDirect3DDevice8 *D3DDevice;
	static Bool _EnableTriangleDraw;
};

struct Vector2 { float X; float Y; };

class W3DShaderManager
{
public:
	static void drawViewport(Int color, Bool flag, const Vector2 *scale);
};

class W3DShadowManager
{
public:
	UnsignedInt getStencilShadowMask() const { return m_stencilShadowMask; }
	char m_pad00[8];
	UnsignedInt m_stencilShadowMask;
};
extern W3DShadowManager *TheW3DShadowManager;

enum {
	D3DRS_ZENABLE = 7, D3DRS_SRCBLEND = 19, D3DRS_DESTBLEND = 20, D3DRS_ZFUNC = 23,
	D3DRS_ALPHABLENDENABLE = 27, D3DRS_STENCILENABLE = 52, D3DRS_STENCILFAIL = 53,
	D3DRS_STENCILZFAIL = 54, D3DRS_STENCILPASS = 55, D3DRS_STENCILFUNC = 56,
	D3DRS_STENCILREF = 57, D3DRS_STENCILMASK = 58, D3DRS_STENCILWRITEMASK = 59,
	D3DRS_COLORWRITEENABLE = 168
};
enum { D3DCMP_NEVER = 1, D3DCMP_LESS = 2, D3DCMP_EQUAL = 3, D3DCMP_ALWAYS = 8 };
enum { D3DSTENCILOP_KEEP = 1, D3DSTENCILOP_ZERO = 2, D3DSTENCILOP_REPLACE = 3 };
enum { D3DBLEND_ZERO = 1, D3DBLEND_ONE = 2, D3DBLEND_SRCALPHA = 5, D3DBLEND_INVSRCALPHA = 6 };

void renderStenciledPlayerColor(UnsignedInt color, UnsignedInt stencilRef, Bool clear, UnsignedInt stencilMask)
{
	if (!TheW3DShadowManager)
		return;

	DX8Wrapper::Set_Shader(g_00DB4248);
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	if (vmat)
		vmat->Release_Ref();
	DX8Wrapper::Apply_Render_State_Changes();

	if (!DX8Wrapper::_Get_D3D_Device8())
		return;

	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, true);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, true);
	if (clear)
	{
		Int occludedMask = TheW3DShadowManager->getStencilShadowMask();
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, stencilRef);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, occludedMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, occludedMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_LESS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_NEVER);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE, 0);
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, stencilRef);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, stencilMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, 0xffffffff);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, true);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
	{
		Vector2 scale;
		scale.X = 1.0f;
		scale.Y = 1.0f;
		W3DShaderManager::drawViewport(color, false, &scale);
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, false);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, false);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE, 0xf);
}
