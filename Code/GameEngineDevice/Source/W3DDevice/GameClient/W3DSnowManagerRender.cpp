// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?render@W3DSnowManager@@QAEXAAVRenderInfoClass@@@Z
// Retail 0x0009470F..0x000949D9 (714 bytes), __thiscall, ret 4.
//
// W3DSnowManager::render. Transferred from the matched Open-BFME-1
// W3DSnowManagerRender.cpp (BFME 1 retail 0x00725710 745 bytes; reviewed
// at open-bfme-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f) with the BFME 2
// deltas witnessed in retail: weather snowEnabled/usePointSprites at
// +0x45/+0x44; manager layout shifted by 4 (amplitude +0x24 through the
// visible/3D gates at +0x40/+0x41); an added WW3D shadow-map pass gate;
// no heightTraveled update; caps point-sprite flag at +0x2A9; terrain map
// at +0x37C0 with origin at +0x120E0; per-mode resource reacquire as two
// nested tests; D3D9 SetStreamSource/SetFVF with one DX8 call count; and
// dwBase stored before cullOverscan. Called from 0x0004D468 through
// TheSnowManager. Callees renderAsQuads 0x00093CC3 and renderSubBox
// 0x00093507 (both RET 0x14 with rinfo and four ints) are unrowed.
// The shader at VA 0x00DB4720 (bits 0x000198B3) has no ledger name.
#include "Coord3D.h"
class RenderInfoClass;
class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	virtual void Delete_This();
	void Add_Ref() { ++NumRefs; }
	void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
	int NumRefs;
};

extern VertexMaterialClass *ScreenMaterial;

class DX8Caps
{
public:
	char m_pad[0x2A9];
	bool m_supportPointSprites;
};

struct IDirect3DVertexBuffer8;
struct IDirect3DDevice8
{
#define S(n) virtual void __stdcall slot##n() = 0;
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
	S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77) S(78) S(79)
	S(80) S(81) S(82) S(83) S(84) S(85) S(86) S(87) S(88)
	virtual long __stdcall SetFVF(unsigned long fvf) = 0;	// 89
	S(90) S(91) S(92) S(93) S(94) S(95) S(96) S(97) S(98) S(99)
	virtual long __stdcall SetStreamSource(unsigned int stream, IDirect3DVertexBuffer8 *data, unsigned int offset, unsigned int stride) = 0;	// 100
#undef S
};

extern unsigned int number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = material;
		render_state_changed |= 0x4000;
	}
protected:
	static DX8Caps *CurrentCaps;
	static unsigned int render_state_changed;
	static IDirect3DDevice8 *D3DDevice;
};

class WW3D
{
	friend class W3DSnowManager;
	static bool IsCurrentlyRenderingShadowMap;
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
	void *m_vtbl;
	Overridable *m_nextOverride;
};

class WeatherSetting : public Overridable
{
public:
	char m_pad08[0x3C];
	bool m_usePointSprites;	// +0x44
	bool m_snowEnabled;		// +0x45
};

template <class T> class OVERRIDE
{
public:
	T *m_overridable;
	int m_pad04;
	int m_pad08;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;


class View
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
	S(70)
#undef S
	virtual const Coord3D &get3DCameraPosition() const;	// 71
};
extern View *TheTacticalView;

class WorldHeightMap
{
public:
	char m_pad00[8];
	int m_width;
	int m_height;
	int m_borderSize;
	char m_pad14[0x120E0 - 0x14];
	int m_originX;
	int m_originY;
};

class BaseHeightMapRenderObjClass
{
public:
	char m_pad00[0x37C0];
	WorldHeightMap *m_map;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

struct BFME2TextureRef
{
	void *m_texture;
};
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);

extern ShaderClass g_00DB4720;

class W3DSnowManager
{
public:
	void render(RenderInfoClass &rinfo);
	bool ReAcquireResources();
	void renderAsQuads(RenderInfoClass &rinfo, int originX, int originY, int dimX, int dimY);
	void renderSubBox(RenderInfoClass &rinfo, int originX, int originY, int dimX, int dimY);
	static __forceinline const WeatherSetting *weather(const WeatherSetting *p)
	{
		if (!p)
			return 0;
		if (p->m_nextOverride)
			return (const WeatherSetting *)p->m_nextOverride->friend_getFinalOverride();
		return p;
	}
	static unsigned long FtoDW(float f) { return *((unsigned long *)&f); }

	char m_pad00[0x24];
	float m_amplitude;		// +0x24
	float m_pointSize;		// +0x28
	float m_maxPointSize;	// +0x2C
	float m_minPointSize;	// +0x30
	float m_quadSize;		// +0x34
	float m_boxDimensions;	// +0x38
	float m_emitterSpacing;	// +0x3C
	bool m_isVisible;		// +0x40
	bool m_enabled3D;		// +0x41
	char m_pad42[0x74 - 0x42];
	void *m_indexBuffer;	// +0x74
	BFME2TextureRef m_snowTexture;	// +0x78
	IDirect3DVertexBuffer8 *m_vertexBuffer;	// +0x7C
	int m_dwBase;			// +0x80
	int m_dwFlush;			// +0x84
	int m_dwDiscard;		// +0x88
	int m_leafDim;			// +0x8C
	float m_snowCeiling;	// +0x90
	float m_94;
	float m_98;
	float m_9C;
	int m_totalRendered;	// +0xA0
	float m_cullOverscan;	// +0xA4
};
void W3DSnowManager::render(RenderInfoClass &rinfo)
{
	const WeatherSetting *settings = TheWeatherSetting.m_overridable;
	if (!weather(settings)->m_snowEnabled || !m_enabled3D || !m_isVisible || WW3D::IsCurrentlyRenderingShadowMap)
		return;
	int usePointSprites = DX8Wrapper::Get_Current_Caps()->m_supportPointSprites && weather(settings)->m_usePointSprites;
	TheTacticalView->get3DCameraPosition();
	WorldHeightMap *map = TheTerrainRenderObject->m_map;
	int border = map->m_borderSize * 2;
	int originX = (int)((float)map->m_originX * 10.0f);
	int originY = (int)((float)map->m_originY * 10.0f);
	int dimX = (int)((float)(map->m_width - border) * 10.0f);
	int dimY = (int)((float)(map->m_height - border) * 10.0f);
	m_snowCeiling = m_boxDimensions;
	DX8Wrapper::Set_Shader(g_00DB4720);
	VertexMaterialClass *material = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(material);
	if (material)
		material->Release_Ref();
	if (usePointSprites) {
		if (m_vertexBuffer == 0)
			ReAcquireResources();
	} else if (m_indexBuffer == 0)
		ReAcquireResources();
	BFME2Set_Texture(0, m_snowTexture);
	m_totalRendered = 0;
	if (!usePointSprites) {
		renderAsQuads(rinfo, originX, originY, dimX, dimY);
		return;
	}
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(156, 1);
	DX8Wrapper::Set_DX8_Render_State(157, 1);
	DX8Wrapper::Set_DX8_Render_State(154, FtoDW(m_pointSize));
	DX8Wrapper::Set_DX8_Render_State(155, FtoDW(m_minPointSize));
	DX8Wrapper::Set_DX8_Render_State(166, FtoDW(m_maxPointSize));
	DX8Wrapper::Set_DX8_Render_State(158, FtoDW(0.0f));
	DX8Wrapper::Set_DX8_Render_State(159, FtoDW(0.0f));
	DX8Wrapper::Set_DX8_Render_State(160, FtoDW(1.0f));
	DX8Wrapper::_Get_D3D_Device8()->SetStreamSource(0, m_vertexBuffer, 0, 16);
	DX8Wrapper::_Get_D3D_Device8()->SetFVF(0x42);
	number_of_DX8_calls++;
	m_dwBase = 4096;
	m_cullOverscan = m_quadSize + m_amplitude;
	renderSubBox(rinfo, originX, originY, dimX, dimY);
	DX8Wrapper::Set_DX8_Render_State(156, 0);
	DX8Wrapper::Set_DX8_Render_State(157, 0);
}
