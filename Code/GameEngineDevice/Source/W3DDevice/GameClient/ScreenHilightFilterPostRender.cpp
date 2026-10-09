// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ScreenHilightFilter::set, retail 0x000FB10B..0x000FB2C1 (438B), is slot 5
// of the same vftable. The clean BFME 1 donor at revision
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d (game/GameEngineDevice/Source/
// W3DDevice/GameClient/ScreenHilightFilterSet.cpp) establishes the material,
// opaque shader, two empty textures and depth-state setup. BFME 2 uses the
// matched ScreenBWFilter helpers and texture-reference ABI; every body byte
// and relocation agrees. This partial class view retains the donor's spelling.
// Set_Hilight_Render_State keeps this inlined setup separate from postRender's
// existing out-of-line Set_DX8_Render_State calls.
//
// ScreenHilightFilter::postRender, slot 3 of its vftable (0x007CF31C, after
// the rowed preRender 0x000FAAC5). Zero Hour's postRender contract with
// BFME 2's hilight pass: a deferred frame (+0x14 set by preRender) only
// restores the default target and resets; otherwise, after set(mode), when
// GlobalData +0xD34 asks for it the stretched back buffer (+0x28 texture of
// the current pair) is redrawn into the +0x2C target through the filter's
// pixel/vertex shaders (+0x04/+0x08) with a colour constant from 0x000ABBEF,
// then the gaussian blur 0x00077392 runs over the pair and the result
// (+0x24) is blended additively over the viewport (drawViewport). Device
// calls use the D3D9 slot numbers; the sampler, texture and pixel-shader
// constant helpers are DX8Wrapper's inline forms (counters as the matched
// Rva000FBA57PostRender.cpp and W3DShaderManagerScreenBWFilterSet.cpp).
#include <string.h>

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	Vector4(void) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	float X, Y, Z, W;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct Vector2;

struct IDirect3DSurface8;
struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define S(n) virtual void __stdcall slot##n() = 0;
	S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17)
	S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32)
	S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47)
	S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56)
	virtual long __stdcall SetRenderState(unsigned long state, unsigned long value) = 0; // 57
	S(58) S(59) S(60) S(61) S(62)
	S(63) S(64)
	virtual long __stdcall SetTexture(unsigned stage, IDirect3DBaseTexture8 *texture) = 0;	// 65
	S(66) S(67) S(68)
	virtual long __stdcall SetSamplerState(unsigned sampler, unsigned type, unsigned value) = 0;	// 69
	S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77) S(78) S(79) S(80) S(81) S(82) S(83) S(84)
	S(85) S(86)
	virtual long __stdcall SetVertexDeclaration(unsigned decl) = 0;	// 87
	S(88) S(89) S(90) S(91)
	virtual long __stdcall SetVertexShader(unsigned shader) = 0;	// 92
	S(93) S(94) S(95) S(96) S(97) S(98) S(99) S(100) S(101) S(102) S(103) S(104) S(105) S(106)
	virtual long __stdcall SetPixelShader(unsigned shader) = 0;	// 107
	S(108)
	virtual long __stdcall SetPixelShaderConstantF(unsigned reg, const void *data, unsigned count) = 0;	// 109
#undef S
};

extern unsigned number_of_DX8_calls;
extern unsigned g_fvfShader;

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	__forceinline ~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};

class VertexMaterialClass
{
public:
	enum PresetType
	{
		PRELIT_DIFFUSE = 0
	};
	virtual void Delete_This();
	static VertexMaterialClass *Get_Preset(PresetType type);
	void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};
extern VertexMaterialClass *ScreenMaterial;

class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
	unsigned int ShaderBits;
protected:
	friend class DX8Wrapper;
	static bool ShaderDirty;
private:
	unsigned int m_bits[2];
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

struct BFME2TextureResource;
struct BFME2TextureRef
{
	BFME2TextureRef(BFME2TextureResource *texture) : Ptr(texture) {}
	~BFME2TextureRef()
	{
		if (Ptr)
			((TextureBaseClass *)Ptr)->Release_Ref();
	}
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

class WW3D
{
public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
};

struct RenderStateStruct
{
	ShaderClass shader;
};
class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Apply_Render_State_Changes();

	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned int value);
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = material;
		render_state_changed |= 0x4000;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader.ShaderBits = shader.ShaderBits;
		render_state_changed |= 0x8000;
		StringClass str;
	}

	static __forceinline void Set_Hilight_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value)
			return;
		if (WW3D::Is_Snapshot_Activated())
		{
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		_Get_D3D_Device8()->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned type, unsigned value)
	{
		_Get_D3D_Device8()->SetSamplerState(stage, type, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			_Get_D3D_Device8()->SetTexture(stage, texture);
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			Textures[stage]->AddRef();
		_Get_D3D_Device8()->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void Set_Pixel_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		_Get_D3D_Device8()->SetPixelShaderConstantF(reg, data, count);
		number_of_DX8_calls++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
	static unsigned texture_stage_state_changes;
	static Vector4 Pixel_Shader_Constants[8];
	static unsigned RenderStates[256];
	static unsigned render_state_changed;
	static unsigned render_state_changes;
	static RenderStateStruct render_state;
};

class W3DShaderManager
{
public:
	static void drawViewport(int color, bool shaded, const Vector2 *viewportSize);
};

// The settings block behind Rva00309E4BGet (+0x08 is the blur strength).
struct BfmeHilightSettings
{
	char m_pad00[8];
	float m_08;
};
int Rva00309E4BGet();

// Rowless helpers called only from here: the colour read (0x000ABBEF), the
// square quad draw (rowed 0x00075A23) and the gaussian blur pass
// (0x00077392).
void Rva000ABBEF(float *r, float *g, float *b, int index);
void Rva00075A23Draw(int width, int height);
void Rva00077392(float strength, void *kernel, int size, IDirect3DBaseTexture8 *result,
	void *surface, IDirect3DBaseTexture8 *source, IDirect3DSurface8 *target);

extern bool bfmeOnlyEmissiveDraws;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct BfmeHilightGlobalDataView
{
	char m_pad[0xD34];
	bool m_D34;
};

enum FilterModes { FM_NULL_MODE = 0 };

class ScreenHilightFilter
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual bool preRender(bool &skipRender, int &scenePassMode);
	virtual bool postRender(int mode, Coord2D &scrollDelta, bool &doExtraRender, Coord2D *viewportSize);
	virtual void slot10();
protected:
	virtual int set(FilterModes mode);
public:
	virtual void reset();
private:
	unsigned m_pixelShader;	// +0x04
	unsigned m_vertexShader;	// +0x08
	int m_size;	// +0x0C
	int m_current;	// +0x10
	bool m_14;	// +0x14
	int m_kernel[3];	// +0x18
	IDirect3DBaseTexture8 *m_result;	// +0x24
	IDirect3DBaseTexture8 *m_textures[1];	// +0x28, indexed by m_current
	IDirect3DSurface8 *m_renderTarget;	// +0x2C
	void *m_surfaces[2];	// +0x30
};

// ?postRender@ScreenHilightFilter@@UAE_NHAAVCoord2D@@AA_NPAV2@@Z @0x000FAC37
bool ScreenHilightFilter::postRender(int mode, Coord2D &scrollDelta, bool &doExtraRender, Coord2D *viewportSize)
{
	bfmeOnlyEmissiveDraws = false;
	if (m_14) {
		DX8Wrapper::Set_Render_Target(0, true);
		reset();
		doExtraRender = true;
		m_14 = false;
		return true;
	}
	if (!set((FilterModes)mode))
		return false;
	if (TheWritableGlobalData && ((BfmeHilightGlobalDataView *)TheWritableGlobalData)->m_D34) {
		DX8Wrapper::Set_Render_Target(m_renderTarget, false);
		{
			Vector3 color(0.0f, 0.0f, 0.0f);
			DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
		}
		DX8Wrapper::Set_DX8_Sampler_State(0, 1, 3);
		DX8Wrapper::Set_DX8_Sampler_State(0, 2, 3);
		DX8Wrapper::Set_DX8_Sampler_State(0, 5, 2);
		DX8Wrapper::Set_DX8_Sampler_State(0, 6, 2);
		DX8Wrapper::Set_DX8_Sampler_State(0, 7, 2);
		DX8Wrapper::Set_DX8_Render_State(0x16, 1);
		DX8Wrapper::Set_DX8_Render_State(0x0E, 0);
		DX8Wrapper::Set_DX8_Render_State(0x07, 0);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0x18, 0);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0x18, 0);
		DX8Wrapper::Set_DX8_Texture(0, m_textures[m_current]);
		DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_pixelShader);
		number_of_DX8_calls++;
		DX8Wrapper::_Get_D3D_Device8()->SetVertexDeclaration(g_fvfShader);
		number_of_DX8_calls++;
		DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(m_vertexShader);
		number_of_DX8_calls++;
		{
			float r, g, b;
			Rva000ABBEF(&r, &g, &b, -1);
			Vector4 constant(r - 1.0f, g - 1.0f, b - 1.0f, 0.0f);
			DX8Wrapper::Set_Pixel_Shader_Constant(0, &constant, 1);
		}
		DX8Wrapper::Set_DX8_Render_State(0x1B, 0);
		DX8Wrapper::Set_DX8_Render_State(0x13, 2);
		DX8Wrapper::Set_DX8_Render_State(0x14, 1);
		Rva00075A23Draw(m_size, m_size);
		DX8Wrapper::Set_Render_Target(0, true);
	}
	Rva00077392(((BfmeHilightSettings *)Rva00309E4BGet())->m_08, m_kernel, m_size, m_result,
		m_surfaces[m_current], m_textures[m_current], m_renderTarget);
	DX8Wrapper::Set_DX8_Texture(0, m_result);
	DX8Wrapper::Set_DX8_Render_State(0x13, 2);
	DX8Wrapper::Set_DX8_Render_State(0x14, 4);
	DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0x18, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0x18, 0);
	DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(0);
	number_of_DX8_calls++;
	W3DShaderManager::drawViewport(-1, true, (const Vector2 *)viewportSize);
	reset();
	return true;
}

// ?set@ScreenHilightFilter@@MAEHW4FilterModes@@@Z @0x000FB10B
int ScreenHilightFilter::set(FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{
		VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		if (vmat) vmat->Release_Ref();
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		BFME2Set_Texture(0, 0);
		BFME2Set_Texture(1, 0);
		DX8Wrapper::Apply_Render_State_Changes();
		DX8Wrapper::Set_Hilight_Render_State(23, 8);
		DX8Wrapper::Set_Hilight_Render_State(14, 0);
		DX8Wrapper::Apply_Render_State_Changes();
	}
	return true;
}
