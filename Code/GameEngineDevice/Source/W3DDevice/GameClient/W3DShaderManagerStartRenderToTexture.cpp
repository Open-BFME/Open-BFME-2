// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /arch:SSE /G7 -Ireference/shims/wwmath
// BF1 donor 575ba2b04743f190f069805fbdc59936123c45da:
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp.
// Native caller ScreenCrossFadeFilter::preRender F63FB and debug name establish
// startRenderToTexture at 75BD8; full ret-delimited extent is 378 bytes.
// Target adds the cooperative-level guard and target wrapper ABI. The three
// branch-local temporaries share a 12-byte lifetime overlay; scale occupies its
// last eight bytes. Release the cached material directly, retaining the native
// repeated refcount read, then update the cache and release the local reference.
#include "Vector2.h"
#define m_newRenderSurface (*(IDirect3DSurface8 **)&g_Va009E1F6C)
struct IDirect3DSurface8;
struct IDirect3DDevice8;
struct Rva00077D0FVertexElement;
struct IDirect3DDevice8Vtbl
{
	void *m_queryInterface;
	void *m_addRef;
	void *m_release;
	long (__stdcall *m_testCooperativeLevel)(IDirect3DDevice8 *device);
	void *m_reserved[65];
	long (__stdcall *m_setSamplerState)(IDirect3DDevice8 *device, unsigned stage, unsigned type, unsigned value);
	void *m_reserved70[16];
	long (__stdcall *m_createVertexShader)(IDirect3DDevice8 *device, const Rva00077D0FVertexElement *declaration, unsigned long *shader);
	void *m_reserved87[4];
	long (__stdcall *m_createShaderA)(IDirect3DDevice8 *device, const unsigned long *shaderData, unsigned long *shader);
	void *m_reserved92[14];
	long (__stdcall *m_createShaderB)(IDirect3DDevice8 *device, const unsigned long *shaderData, unsigned long *shader);
};
struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *m_vtable;
};
class ShaderClass
{
public:
	enum DepthCompareType
	{
		PASS_NEVER = 0,
		PASS_LESS,
		PASS_EQUAL,
		PASS_LEQUAL,
		PASS_GREATER,
		PASS_NOTEQUAL,
		PASS_GEQUAL,
		PASS_ALWAYS
	};
	enum DepthMaskType
	{
		DEPTH_WRITE_DISABLE = 0,
		DEPTH_WRITE_ENABLE
	};
	void Set_Depth_Compare(DepthCompareType mode)
	{
		m_bits &= ~7u;
		m_bits |= (unsigned)mode;
	}
	// Suppress the unused standalone copy; the verified caller keeps this inline.
	__declspec(dllimport) __forceinline void Set_Depth_Mask(DepthMaskType mode)
	{
		m_bits &= ~8u;
		m_bits |= ((unsigned)mode << 3);
	}
	static ShaderClass _PresetOpaqueSolidShader;
	unsigned m_bits;
};
class RefCountClass
{
public:
	virtual void Delete_This() = 0;
	int m_refs;
 __declspec(dllimport) __forceinline void Release_Ref() { --m_refs; if (*(volatile int *)&m_refs == 0) Delete_This(); }
};
class VertexMaterialClass : public RefCountClass
{
public:
	enum PresetType
	{
		PRELIT_DIFFUSE = 0
	};
	static VertexMaterialClass *Get_Preset(PresetType preset);
};
class GlobalData
{
public:
	char m_pad[0x84];
	bool m_showSoftWaterEdge;
};
extern GlobalData *TheWritableGlobalData;
class Rva00072B3A;
class BaseHeightMapRenderObjClass
{
public:
	char m_pad00[0x37C0];
	void *map; // +0x37C0
	char m_pad37C4[0x24];
	float m_minWaterOpacity; // +0x37E8
	char m_pad37EC[0x8C];
	Rva00072B3A *shroud; // +0x3878
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class Vector3
{
public:
	float m_x;
	float m_y;
	float m_z;
};
enum FilterTypes
{
	FT_NULL_FILTER = 0,
	FT_VIEW_BW_FILTER,
	FT_VIEW_MOTION_BLUR_FILTER,
	FT_VIEW_CROSSFADE,
	FT_VIEW_DEFAULT
};
extern VertexMaterialClass *ScreenMaterial;

class VertexBufferClass;
struct IDirect3D8;
class DX8Wrapper
{
private:
	friend class W3DShaderManager;
	friend void rva00075E42(void);
	friend void Rva00075A23Draw(int width, int height);
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *target, bool useDefaultDepth);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void bfmeRva00120700(unsigned start, unsigned count);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_Shader(const ShaderClass &shader);
	static void Clear(bool clearColor, bool clearDepth, bool clearStencil, const Vector3 &color, float alpha, float z, unsigned stencil);
	static void Mark_Material_Changed() { render_state_changed |= 0x4000; }
protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_stage_state_changes;
	static IDirect3D8 *D3DInterface;
	static unsigned render_state_changed;
};
// These existing storage owners are shared with availability and shutdown.
// Only the first handle is passed to the typed render-target wrapper; the
// opaque depth resource is tested for availability without asserting a layout.
extern unsigned int g_Va009E1F6C;
struct ShaderComResourceRef;
extern ShaderComResourceRef *rva012F9D10;

enum ChipsetType { DC_UNKNOWN = 0 };
enum CpuType { XX, P3, P4, K7 };
struct IDirect3DTexture8;
struct GlowSampleVector;
struct BfmeGaussianParams;
class W3DShaderManager
{
private:
	friend class Rva00075655;
	friend void Rva00075695Notify(int index);
	friend bool __cdecl Rva000756BFSelect(int index, int a1, int a2);
	friend bool __cdecl Rva000756F1Dispatch(int index, int a1, int a2, int a3, int a4);
public:
	enum ShaderTypes { ST_INVALID };
protected:
	static int m_currentShader;
	static int m_currentFilter;
	static bool m_renderingToTexture;
	static unsigned long m_dwGlowPixelShader;
	static unsigned long m_dwGlowVertexShader;
public:
	static IDirect3DSurface8 *m_oldRenderSurface;
	static IDirect3DTexture8 *m_renderTexture;
	W3DShaderManager();
	static int getShaderPasses(ShaderTypes shader);
	static void startRenderToTexture();
	static IDirect3DTexture8 *endRenderToTexture();
	static IDirect3DTexture8 *getRenderTexture();
	static void drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions);
	static bool testMinimumRequirements(ChipsetType *, CpuType *, int *, unsigned __int64 *, float *, float *, float *);
	static int setShroudTex(int);
	static void performGlow(float weightScale, const GlowSampleVector *samples, int textureSize, IDirect3DTexture8 *sourceTexture, IDirect3DSurface8 *tempSurface, IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface);
	static void createGaussianVector(void *,BfmeGaussianParams *);
};

union RenderTargetTemp
{
	struct { int pad; float x; float y; } scaleHome;
	Vector3 vector3;
	struct
	{
		char m_pad[8];
		ShaderClass shader;
	} shaderHome;
};

// ?startRenderToTexture@W3DShaderManager@@SAXXZ
void W3DShaderManager::startRenderToTexture()
{
	RenderTargetTemp temp;
	if (m_renderingToTexture || m_newRenderSurface == 0 || rva012F9D10 == 0)
		return;
	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	if (device && device->m_vtable->m_testCooperativeLevel(device) != 0)
		return;
	DX8Wrapper::Set_Render_Target(m_newRenderSurface, true);
	m_renderingToTexture = true;
	if (TheWritableGlobalData->m_showSoftWaterEdge)
	{
		if (m_currentFilter == FT_VIEW_MOTION_BLUR_FILTER || m_currentFilter == FT_VIEW_CROSSFADE)
		{
			DX8Wrapper::Set_DX8_Render_State(168, 8);
			temp.shaderHome.shader = ShaderClass::_PresetOpaqueSolidShader;
			temp.shaderHome.shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
			temp.shaderHome.shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
			DX8Wrapper::Set_Shader(temp.shaderHome.shader);
			VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
			if (vmat)
				++vmat->m_refs;
			if (ScreenMaterial) ScreenMaterial->Release_Ref();
			DX8Wrapper::Mark_Material_Changed();
			ScreenMaterial = vmat;
			if (vmat)
			{
				--vmat->m_refs;
				if (vmat->m_refs == 0)
					vmat->Delete_This();
			}
			temp.scaleHome.x = 1.0f;
			temp.scaleHome.y = 1.0f;
			drawViewport(0x00ffffff | (((int)(TheTerrainRenderObject->m_minWaterOpacity * 255.0f)) << 24), false, (const Vector2 *)&temp.scaleHome.x);
			DX8Wrapper::Set_DX8_Render_State(168, 7);
		}
		else
		{
			float opacity1 = TheTerrainRenderObject->m_minWaterOpacity;
			temp.vector3.m_x = 0.0f;
			temp.vector3.m_y = 0.0f;
			temp.vector3.m_z = 0.0f;
			DX8Wrapper::Clear(true, false, false, temp.vector3, opacity1, 1.0f, 0);
		}
	}
	else if (m_currentFilter == FT_VIEW_DEFAULT)
	{
		float opacity2 = TheTerrainRenderObject->m_minWaterOpacity;
		temp.vector3.m_x = 0.0f;
		temp.vector3.m_y = 0.0f;
		temp.vector3.m_z = 0.0f;
		DX8Wrapper::Clear(true, false, false, temp.vector3, opacity2, 1.0f, 0);
	}
}
