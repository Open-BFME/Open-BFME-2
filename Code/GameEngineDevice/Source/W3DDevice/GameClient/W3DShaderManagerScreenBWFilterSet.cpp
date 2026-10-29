// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
//
// ?set@ScreenBWFilter@@MAEHW4FilterModes@@@Z, retail 0x000FBC67..0x000FC04C
// (997B), thiscall ret 4; slot 5 (set) of the ScreenBWFilter vtable at
// VA 0x007CF364, whose slot 0 is the rowed ScreenBWFilter::init 0x000FB9D4.
//
// Zero Hour's W3DShaderManager.cpp ScreenBWFilter::set: steps the shared fade
// (dropping the view filter once a fade-out completes), sets up the quad
// state -- PRELIT_DIFFUSE preset material, _PresetOpaqueShader, no texture on
// stage 0, ZFUNC ALWAYS and ZWRITEENABLE off -- binds the monochrome pixel
// shader (+0x04) and loads the luminance weights, the tint for black & white
// (1), red (2) or green (3) and the fade value into pixel shader constants 0,
// 1 and 2. BFME 2's DX8Wrapper inlines Set_Shader, Set_DX8_Render_State and
// Set_Pixel_Shader_Constant here (with the WW3D snapshot strings) and passes
// the stage-0 texture through a temporary reference (BFME2Set_Texture
// 0x0011F4B0). Statics and DX8Wrapper members carry their ledger or Zero Hour
// names; callees are rowed.
//
// Codegen: under /arch:SSE MSVC 7.1 refuses (C4714) to inline helpers that
// hold unwindable locals unless the caller owns one itself; here that is the
// NULL texture reference temporary built at the call (retail EH state 0), so
// it must be the argument conversion in this body, not a local in a helper.

#include <string.h>
#include <d3d9.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum FilterModes
{
	FM_NULL_MODE = 0,
	FM_VIEW_BW_BLACK_AND_WHITE,
	FM_VIEW_BW_RED_AND_WHITE,
	FM_VIEW_BW_GREEN_AND_WHITE
};

enum FilterTypes
{
	FT_NULL_FILTER = 0
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class View
{
public:
	PAD_VIRTUALS10(s0) PAD_VIRTUALS10(s1) PAD_VIRTUALS10(s2) PAD_VIRTUALS10(s3)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void setViewFilterMode(FilterModes mode);	// slot 45 (+0xB4)
	virtual void s46();
	virtual void setViewFilter(FilterTypes filter);	// slot 47 (+0xBC)
};
extern View *TheTacticalView;

// Imported inline helpers retain their native inline use while suppressing
// competing COMDAT definitions; 997B/391B/43B and both EH tables stay exact.
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
	__declspec(dllimport) __forceinline void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
	Int NumRefs;
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
	__declspec(dllimport) __forceinline BFME2TextureRef(BFME2TextureResource *texture) : Ptr(texture) {}
	~BFME2TextureRef()
	{
		if (Ptr)
			((TextureBaseClass *)Ptr)->Release_Ref();
	}
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

// The device keeps its D3D8 type name but is a Direct3D 9 device: SetRenderState
// slot 57, SetPixelShader 107, SetPixelShaderConstantF 109.
struct IDirect3DDevice8;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

struct D3DXVECTOR4
{
	D3DXVECTOR4() {}
	D3DXVECTOR4(float fx, float fy, float fz, float fw) : x(fx), y(fy), z(fz), w(fw) {}
	operator const float *() const { return &x; }
	float x, y, z, w;
};

extern unsigned number_of_DX8_calls;

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
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned int value);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __declspec(dllimport) __forceinline void Set_Material(VertexMaterialClass *material)
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

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value)
			return;
		if (WW3D::Is_Snapshot_Activated())
		{
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetRenderState((D3DRENDERSTATETYPE)state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

	static __forceinline void Set_Pixel_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetPixelShaderConstantF(reg, (const float *)data, count);
		number_of_DX8_calls++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static Vector4 Pixel_Shader_Constants[8];
	static unsigned int RenderStates[256];
	static unsigned int render_state_changed;
	static unsigned int render_state_changes;
	static RenderStateStruct render_state;
};

#define REF_PTR_RELEASE(x) { if (x) x->Release_Ref(); x = 0; }

class W3DFilterInterface
{
public:
	virtual Int init(void) = 0;
protected:
	virtual Int set(FilterModes mode) = 0;
};

class ScreenBWFilter : public W3DFilterInterface
{
public:
	virtual Int init(void);

	static Int m_fadeFrames;
	static Int m_fadeDirection;
	static Int m_curFadeFrame;
	static Real m_curFadeValue;

protected:
	virtual Int set(FilterModes mode);

	unsigned long m_dwBWPixelShader;	// +0x04
};

Int ScreenBWFilter::set(FilterModes mode)
{
	if (mode > FM_NULL_MODE)
	{	//rendering a quad with redirected rendering surface tinted by pixel shader

		if (m_fadeDirection > 0)
		{	//turning effect on
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;

			if (fade < m_fadeFrames)
			{
				m_curFadeValue = (Real)fade / (Real)m_fadeFrames;
			}
			else
			{
				m_curFadeFrame = 0;
				m_curFadeValue = 1.0f;
				m_fadeDirection = 0;
			}
		}
		else if (m_fadeDirection < 0)
		{	//turning effect off
			m_curFadeFrame++;
			Int fade = m_curFadeFrame;
			if (fade < m_fadeFrames)
			{
				m_curFadeValue = 1.0f - (Real)fade / (Real)m_fadeFrames;
			}
			else
			{
				m_curFadeValue = 0.0f;
				TheTacticalView->setViewFilterMode(FM_NULL_MODE);
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				m_curFadeFrame = 0;
				m_fadeDirection = 0;
			}
		}

		VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		BFME2Set_Texture(0, 0);
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, FALSE);
		DX8Wrapper::Apply_Render_State_Changes();

		reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(
			reinterpret_cast<IDirect3DPixelShader9 *>(m_dwBWPixelShader));
		number_of_DX8_calls++;
		DX8Wrapper::Set_Pixel_Shader_Constant(0, D3DXVECTOR4(0.3f, 0.59f, 0.11f, 1.0f), 1);

		D3DXVECTOR4 color(1.0f, 1.0f, 1.0f, 1.0f);	//multiply color

		if (mode == FM_VIEW_BW_BLACK_AND_WHITE)
		{	//back & white mode
			color.x = 1.0f;
			color.y = 1.0f;
			color.z = 1.0f;
		}
		if (mode == FM_VIEW_BW_RED_AND_WHITE)
		{	//red is on
			color.x = 1.0f;
			color.y = 0.0f;
			color.z = 0.0f;
		}
		if (mode == FM_VIEW_BW_GREEN_AND_WHITE)
		{	//green is on
			color.x = 0.0f;
			color.y = 1.0f;
			color.z = 0.0f;
		}

		DX8Wrapper::Set_Pixel_Shader_Constant(1, color, 1);
		DX8Wrapper::Set_Pixel_Shader_Constant(2, D3DXVECTOR4(m_curFadeValue, m_curFadeValue, m_curFadeValue, 1.0f), 1);
		return true;
	}
	return false;
}

// Retail 0x000FDDB8..0x000FDF3F is the complete 391B RET4 body;
// the next independent 12B method starts at 0x000FDF3F.
// Target table 0x007CF440 slot 5, called by rowed Rva000FDD1C::rva000FDD1C.
// Zero Hour W3DShaderManager.cpp at BF1 reference575ba2b supplies the
// ScreenDefaultFilter::set semantic guide only;
// this slot-9 registered BFME2 filter's original identity remains unresolved.
enum CustomScenePassModes {CUSTOM_SCENE_PASS_DEFAULT=0};
class Rva000FDD1C
{
public:
 virtual void f00(); virtual void f01();
 virtual bool preRender(Bool &skipRender, CustomScenePassModes &scenePassMode);
 virtual void f03(); virtual void f04();
 virtual int rva000FDD1CFirst(int mode);
 virtual void rva000FDD1CNext();
};
int Rva000FDD1C::rva000FDD1CFirst(int mode)
{
 VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::Set_Material(vmat);
 REF_PTR_RELEASE(vmat);
 DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
 BFME2Set_Texture(0,0);
 DX8Wrapper::Apply_Render_State_Changes();
 DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
 DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
 DX8Wrapper::Apply_Render_State_Changes();
 return true;
}

// Table 0x007CF440 slot 2, complete 43B RET8 body. Smudge count +0x20;
// global-data +0xC60 gate remains unnamed. Zero Hour default-filter preRender
// provides the rendering role; BFME2's extra global-data condition is native.
class BfmeB991;
extern BfmeB991 *g_bfmeB991;
struct Rva000FDCF1SmudgeView { unsigned char pad[0x20]; int count; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva000FDCF1GlobalView { unsigned char pad[0xC60]; int option; };
class W3DShaderManager { public: static void startRenderToTexture(); };
bool Rva000FDD1C::preRender(Bool &skipRender, CustomScenePassModes &scenePassMode)
{
 if (g_bfmeB991) {
  if (((Rva000FDCF1SmudgeView *)g_bfmeB991)->count == 0 ||
      ((Rva000FDCF1GlobalView *)TheWritableGlobalData)->option != -1)
   return false;
 }
 W3DShaderManager::startRenderToTexture();
 return true;
}
