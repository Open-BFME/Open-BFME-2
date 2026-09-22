// ?startRenderToTexture@W3DShaderManager@@SAXXZ
// partial score=0.97 date=2026-09-22
// ?startRenderToTexture@W3DShaderManager@@SAXXZ
// partial score=0.97 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /arch:SSE /G7
// ?preRender@ScreenMotionBlurFilter@@UAE_NAA_NAAW4CustomScenePassModes@@@Z retail 0x000FD4CE (19B).
// Ported from Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// (BFME1 0x007D8790, donor-verbatim): copies m_skipRender into skipRender,
// calls startRenderToTexture and returns true. Only the placed body is defined
// here.

enum CustomScenePassModes
{
	CUSTOM_SCENE_PASS_DUMMY = 0
};

enum FilterTypes
{
	FT_NULL_FILTER = 0,
	FT_VIEW_BW_FILTER,
	FT_VIEW_MOTION_BLUR_FILTER,
	FT_VIEW_CROSSFADE,
	FT_VIEW_DEFAULT
};

struct Vector2
{
	float m_x;
	float m_y;
};

struct Vector3
{
	float m_x;
	float m_y;
	float m_z;
};

struct IDirect3DSurface8;

class W3DShaderManager
{
public:
	static void startRenderToTexture();
	static void drawViewport(int color, bool useScale, const Vector2 *scale);

	static bool m_renderingToTexture;
	static IDirect3DSurface8 *m_newRenderSurface;
	static IDirect3DSurface8 *m_oldDepthSurface;
	static FilterTypes m_currentFilter;
};

class ScreenMotionBlurFilter
{
public:
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);

	char m_pad[0x09];
	bool m_skipRender;
};

bool ScreenMotionBlurFilter::preRender(bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = m_skipRender;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// ?startRenderToTexture@W3DShaderManager@@SAXXZ retail 0x00075BD8 (378B).
// Ported from Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// (BFME1 0x007D8790 donor): BFME2 routes the target switch through
// DX8Wrapper::Set_Render_Target after a device-lost guard, splits Clear into a
// 7-arg form and extends drawViewport with a scale flag. Only the placed body
// is defined here.

struct IDirect3DSurface8;

struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *m_queryInterface;
	void *m_addRef;
	void *m_release;
	long (__stdcall *m_testCooperativeLevel)(IDirect3DDevice8 *device);
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

	void Set_Depth_Mask(DepthMaskType mode)
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

	void Add_Ref()
	{
		++m_refs;
	}

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}

	int m_refs;
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

struct GlobalData
{
	char m_pad[0x84];
	bool m_showSoftWaterEdge;
};

extern GlobalData *TheGlobalData;

struct WaterTransparency
{
	char m_pad[0x37E8];
	float m_minWaterOpacity;
};

extern WaterTransparency *TheWaterTransparency;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *target, bool useDefaultDepth);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_Shader(const ShaderClass &shader);
	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		if (material)
			const_cast<VertexMaterialClass *>(material)->Add_Ref();
		if (m_material)
			m_material->Release_Ref();
		m_material = const_cast<VertexMaterialClass *>(material);
		m_changed |= 0x40;
	}
	static void Clear(bool clearColor, bool clearDepth, bool clearStencil, const Vector3 &color, float alpha, float z, unsigned stencil);

private:
	static IDirect3DDevice8 *D3DDevice;
	static VertexMaterialClass *m_material;
	static unsigned char m_changed;
};

void W3DShaderManager::startRenderToTexture()
{
	if (m_renderingToTexture || m_newRenderSurface == 0 || m_oldDepthSurface == 0)
		return;
	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	if (device && device->m_vtable->m_testCooperativeLevel(device) != 0)
		return;
	DX8Wrapper::Set_Render_Target(m_newRenderSurface, true);
	m_renderingToTexture = true;
	if (TheGlobalData->m_showSoftWaterEdge)
	{
		if (m_currentFilter == FT_VIEW_MOTION_BLUR_FILTER || m_currentFilter == FT_VIEW_CROSSFADE)
		{
			DX8Wrapper::Set_DX8_Render_State(168, 8);
			ShaderClass shader = ShaderClass::_PresetOpaqueSolidShader;
			shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
			shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
			DX8Wrapper::Set_Shader(shader);
			VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
			DX8Wrapper::Set_Material(vmat);
			if (vmat)
				vmat->Release_Ref();
			Vector2 one = { 1.0f, 1.0f };
			drawViewport(0x00ffffff | (((int)(TheWaterTransparency->m_minWaterOpacity * 255.0f)) << 24), false, &one);
			DX8Wrapper::Set_DX8_Render_State(168, 7);
		}
		else
		{
			Vector3 zero = { 0.0f, 0.0f, 0.0f };
			DX8Wrapper::Clear(true, false, false, zero, TheWaterTransparency->m_minWaterOpacity, 1.0f, 0);
		}
	}
	else if (m_currentFilter == FT_VIEW_DEFAULT)
	{
		Vector3 zero = { 0.0f, 0.0f, 0.0f };
		DX8Wrapper::Clear(true, false, false, zero, TheWaterTransparency->m_minWaterOpacity, 1.0f, 0);
	}
}
