// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
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
#include <d3d9.h>
#include "Coord3D.h"
class RenderInfoClass;
#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

extern VertexMaterialClass *ScreenMaterial;

class DX8Caps
{
public:
	char m_pad[0x2A9];
	bool m_supportPointSprites;
};

struct IDirect3DVertexBuffer8;
// The device and vertex buffer keep their D3D8 type names but are Direct3D 9
// objects (SetFVF slot 89, SetStreamSource slot 100).
struct IDirect3DDevice8;

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

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

#include "../../../../GameEngine/Include/Common/Overridable.h"

class WeatherSetting : public Overridable
{
public:
	char m_pad10[0x34];
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


#include "../../../../GameEngine/Include/GameClient/View.h"
extern View *TheTacticalView;

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// VertexMaterialClass already includes the retail RefCountClass definition.
#define REFCOUNT_H
class PersistFactoryClass;
class ChunkSaveClass;
class ChunkLoadClass;

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

struct BFME2TextureRef
{
	void *m_texture;
};
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);

// Native snow point-sprite shader, initialized bits verified at VA DB4720.
ShaderClass BfmeSnowPointSpriteShader(0x000198B3);

class W3DSnowManager
{
public:
	void render(RenderInfoClass &rinfo);
	bool ReAcquireResources();
	void renderAsQuads(RenderInfoClass &rinfo, int originX, int originY, int dimX, int dimY);
	void renderSubBox(RenderInfoClass &rinfo, int originX, int originY, int dimX, int dimY);
	static __forceinline const WeatherSetting *weather(const WeatherSetting *weatherSetting)
	{
		if (!weatherSetting)
			return 0;
		if (weatherSetting->getNextOverride())
			return (const WeatherSetting *)((WeatherSetting *)weatherSetting)->friend_getNextOverride()->friend_getFinalOverride();
		return weatherSetting;
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
	int originX = (int)((float)map->m_drawOriginX * 10.0f);
	int originY = (int)((float)map->m_drawOriginY * 10.0f);
	int dimX = (int)((float)(map->m_width - border) * 10.0f);
	int dimY = (int)((float)(map->m_height - border) * 10.0f);
	m_snowCeiling = m_boxDimensions;
	DX8Wrapper::Set_Shader(BfmeSnowPointSpriteShader);
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
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSPRITEENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALEENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE, FtoDW(m_pointSize));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE_MIN, FtoDW(m_minPointSize));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSIZE_MAX, FtoDW(m_maxPointSize));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALE_C, FtoDW(1.0f));
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetStreamSource(0,
		reinterpret_cast<IDirect3DVertexBuffer9 *>(m_vertexBuffer), 0, 16);
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	number_of_DX8_calls++;
	m_dwBase = 4096;
	m_cullOverscan = m_quadSize + m_amplitude;
	renderSubBox(rinfo, originX, originY, dimX, dimY);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSPRITEENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_POINTSCALEENABLE, FALSE);
}
