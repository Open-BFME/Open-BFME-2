// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
//
// ?postRender@Rva007DCA80@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z,
// retail 0x000F9F82..0x000FA632 (1712 bytes, thiscall ret 0x10): slot 3 of
// vftable 0x007CF2F8 whose slot 0 is the rowed init 0x000F9D94 and slot 1
// the rowed shutdown 0x000FA8AE (slot 5 set 0x000FA632 and slot 6 reset
// 0x000FB0BC are rowed under Rva007D85C0). WorldBuilder twin 0x008F79E0
// (unnamed; W3DScreenSmokeGlowFilter) has the same calls constants and order.
//
// It mirrors the filter's active flag (+0x1C) into TheGlobalData +0xD34 and
// clears bfmeOnlyEmissiveDraws. A pending target restore (+0x30) resets the
// render target and the filter and asks for an extra render. Otherwise it
// sets the mode (slot 5) then picks the glow width from a 13-step table by
// the pulse phase (float 0x00DEC0DC advanced by 0.6 and wrapped at 13; floor
// then WWMath::Float_To_Long) scaled by 80 / the float at 0x00DB457C (at
// least 3 samples at +0x18) and runs W3DShaderManager::performGlow on the two
// render targets. It drifts the vapor offsets (+0x20/+0x24/+0x28) binds the
// glow texture (stage 0 inline Set_DX8_Texture) and the two ExVapor
// textures (stages 1 and 2 through BFME2Set_Texture with wrap sampler states)
// builds a four-vertex XYZRHW|DIFFUSE|TEX3 quad over the tactical view (UVs
// scaled by the viewport size argument) picks additive or modulating blend
// by the flag at 0x00DB5B08 and draws it as a triangle strip then resets.
// Globals without a ledger name keep address-derived names.
#include "Lib/Coord2D.h"
#include <math.h>

struct D3DXVECTOR4
{
	float x;
	float y;
	float z;
	float w;

	D3DXVECTOR4() {}
	D3DXVECTOR4(float xValue, float yValue, float zValue, float wValue)
		: x(xValue), y(yValue), z(zValue), w(wValue) {}
};

struct IDirect3DSurface8;
struct IDirect3DTexture8;
struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DDevice8
{
#define SLOT(n) virtual void __stdcall slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
	SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64)
	virtual long __stdcall SetTexture(unsigned long stage, IDirect3DBaseTexture8 *texture) = 0;
	SLOT(66) SLOT(67) SLOT(68)
	virtual long __stdcall SetSamplerState(unsigned long sampler, unsigned long type, unsigned long value) = 0;
	SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82)
	virtual long __stdcall DrawPrimitiveUP(unsigned long type, unsigned count, const void *data, unsigned stride) = 0;
	SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88)
	virtual long __stdcall SetFVF(unsigned long fvf) = 0;
	SLOT(90) SLOT(91)
	virtual long __stdcall SetVertexShader(void *shader) = 0;
#undef SLOT
};

extern unsigned number_of_DX8_calls;
extern bool bfmeOnlyEmissiveDraws;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *surface, bool additional);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Apply_Render_State_Changes();

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

	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned long state, unsigned value)
	{
		_Get_D3D_Device8()->SetSamplerState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}

protected:
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
	static unsigned texture_stage_state_changes;
	static IDirect3DDevice8 *D3DDevice;
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

struct BFME2TextureRef;
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

struct GlowSampleVector;
class W3DShaderManager
{
public:
	static void performGlow(float strength, const GlowSampleVector *samples, int size,
		IDirect3DTexture8 *source, IDirect3DSurface8 *sourceSurface,
		IDirect3DTexture8 *target, IDirect3DSurface8 *targetSurface);
};

int Rva00309E4BGet();
struct Rva000F9F82Settings
{
	char m_pad00[0x08];
	float m_glowStrength; // +0x08
};

class View
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C) SLOT(20) SLOT(24)
	SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38)
	virtual int getWidth() = 0;
	SLOT(40)
	virtual int getHeight() = 0;
	SLOT(48)
#undef SLOT
	virtual void getOrigin(int *x, int *y) = 0;
};
extern View *TheTacticalView;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva000F9F82GlobalData
{
	char m_pad000[0xD34];
	bool m_glowActive; // +0xD34
};

// Frame-rate divisor and the glow pulse phase of this filter.
extern float g_Va00DB457C;
extern float g_Va00DEC0DC;
extern bool g_Va00DB5B08;

class WWMath
{
public:
	static __forceinline float Floor(float val) { return (float)floor(val); }
	static __forceinline long Float_To_Long(float f)
	{
		long retval;
		__asm fld dword ptr [f]
		__asm fistp dword ptr [retval]
		return retval;
	}
};

enum FilterModes { FM_NULL_MODE = 0 };

class Rva007DCA80
{
public:
	virtual int init(void);
	virtual int shutdown(void);
	virtual bool preRender(bool &skipRender, int &scenePassMode);
	virtual bool postRender(FilterModes mode, Coord2D &scrollDelta, bool &doExtraRender, Coord2D *viewportSize);
	virtual int setup(FilterModes mode);
	virtual int set(FilterModes mode);
	virtual void reset(void);

private:
	unsigned long m_pixelShader;      // +0x04
	unsigned m_vertexShader;          // +0x08
	char m_pad0C[0x18 - 0x0C];
	int m_glowSamples;                // +0x18
	bool m_glowActive;                // +0x1C
	float m_uOffset;                  // +0x20
	float m_vOffset;                  // +0x24
	float m_uSpread;                  // +0x28
	int m_size;                       // +0x2C
	bool m_restoreTarget;             // +0x30
	char m_pad31[3];
	char m_kernel[0x0C];              // +0x34
	IDirect3DTexture8 *m_texture[3];  // +0x40
	IDirect3DSurface8 *m_surface[3];  // +0x4C
	TextureBaseClass *m_vapor1;       // +0x58
	TextureBaseClass *m_vapor2;       // +0x5C
};

bool Rva007DCA80::postRender(FilterModes mode, Coord2D &scrollDelta, bool &doExtraRender, Coord2D *viewportSize)
{
	((Rva000F9F82GlobalData *)TheWritableGlobalData)->m_glowActive = m_glowActive;
	bfmeOnlyEmissiveDraws = false;

	if (m_restoreTarget)
	{
		DX8Wrapper::Set_Render_Target((IDirect3DSurface8 *)0, true);
		reset();
		doExtraRender = true;
		m_restoreTarget = false;
		return true;
	}

	if (!set(mode))
		return false;

	int steps[13] = { 15, 16, 15, 17, 18, 17, 20, 21, 19, 20, 17, 18, 16 };
	float frameScale = 80.0f / g_Va00DB457C;

	g_Va00DEC0DC += 0.6f;
	if (g_Va00DEC0DC >= 13.0f)
		g_Va00DEC0DC = 0;

	int step = WWMath::Float_To_Long(WWMath::Floor(g_Va00DEC0DC));
	m_glowSamples = (int)(steps[step] * frameScale);
	if (m_glowSamples < 3)
		m_glowSamples = 3;

	W3DShaderManager::performGlow(((Rva000F9F82Settings *)Rva00309E4BGet())->m_glowStrength,
		(const GlowSampleVector *)m_kernel, m_size, m_texture[0], m_surface[1], m_texture[1], m_surface[0]);

	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();

	struct Vertex
	{
		D3DXVECTOR4 position;
		unsigned long color;
		float u1;
		float v1;
		float u2;
		float v2;
		float u3;
		float v3;
	} vertices[4];

	if (m_vOffset > 1.0f)
		m_vOffset -= 1.0f;
	if (m_uOffset < -1.0f)
		m_uOffset += 1.0f;
	if (m_uSpread > 1.0f)
		m_uSpread -= 1.0f;
	m_vOffset += 0.03f;
	m_uOffset -= 0.0225f;
	m_uSpread += 0.02f;

	DX8Wrapper::Set_DX8_Texture(0, (IDirect3DBaseTexture8 *)m_texture[0]);

	{
	// The quad setup is its own scope: retail packs the view origin into
	// the dead mode argument slot.
	int x;
	int y;
	int width;
	int height;
	TheTacticalView->getOrigin(&x, &y);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	BFME2Set_Texture(1, *(const BFME2TextureRef *)&m_vapor2);
	DX8Wrapper::Set_DX8_Sampler_State(1, 1, 1);
	DX8Wrapper::Set_DX8_Sampler_State(1, 2, 1);
	DX8Wrapper::Set_DX8_Sampler_State(2, 1, 1);
	DX8Wrapper::Set_DX8_Sampler_State(2, 2, 1);
	BFME2Set_Texture(2, *(const BFME2TextureRef *)&m_vapor1);
	DX8Wrapper::Set_DX8_Texture(2, ((TextureBaseClass *)&m_vapor1)->Peek_D3D_Base_Texture());

	float spread = 3.0f / frameScale;

	vertices[0].position = D3DXVECTOR4(x + width - 0.5f, y + height - 0.5f, 0.0f, 1.0f);
	vertices[0].u1 = (float)(x + width) / viewportSize->x;
	vertices[0].v1 = (float)(y + height) / viewportSize->y;
	vertices[0].u2 = spread;
	vertices[0].v2 = spread;
	vertices[1].position = D3DXVECTOR4(x + width - 0.5f, y - 0.5f, 0.0f, 1.0f);
	vertices[1].u1 = (float)(x + width) / viewportSize->x;
	vertices[1].v1 = (float)y / viewportSize->y;
	vertices[1].u2 = spread;
	vertices[1].v2 = 0;
	vertices[2].position = D3DXVECTOR4(x - 0.5f, y + height - 0.5f, 0.0f, 1.0f);
	vertices[2].u1 = (float)x / viewportSize->x;
	vertices[2].v1 = (float)(y + height) / viewportSize->y;
	vertices[2].u2 = 0;
	vertices[2].v2 = spread;
	vertices[3].position = D3DXVECTOR4(x - 0.5f, y - 0.5f, 0.0f, 1.0f);
	vertices[3].u1 = (float)x / viewportSize->x;
	vertices[3].v1 = (float)y / viewportSize->y;
	vertices[3].u2 = 0;
	vertices[3].v2 = 0;

	float uScale = 2.0f;
	float vScale = 1.0f;
	for (int i = 0; i < 4; i++)
	{
		vertices[i].u2 = uScale * vertices[i].u2 + m_uOffset;
		vertices[i].v2 = vScale * vertices[i].v2 + m_vOffset;
		vertices[i].v3 = vertices[i].v2;
		vertices[i].u3 = vertices[i].u2 - m_uSpread;
		vertices[i].u2 = vertices[i].u2 + m_uSpread;
	}
	vertices[0].color = 0xffffffff;
	vertices[1].color = 0xffffffff;
	vertices[2].color = 0xffffffff;
	vertices[3].color = 0xffffffff;

	if (g_Va00DB5B08)
	{
		DX8Wrapper::Set_DX8_Render_State(0x13, 2);
		DX8Wrapper::Set_DX8_Render_State(0x14, 4);
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(0x13, 5);
		DX8Wrapper::Set_DX8_Render_State(0x14, 6);
	}
	DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(0x1B, 1);

	DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(0);
	number_of_DX8_calls++;
	DX8Wrapper::_Get_D3D_Device8()->SetFVF(0x344);
	number_of_DX8_calls++;

	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 3);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0xB, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 4);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0xB, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 5);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 6, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 1, 5);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 0x18, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 0xB, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 2, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 3, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 4, 5);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 6, 2);

	device->DrawPrimitiveUP(5, 2, vertices, sizeof(Vertex));
	}
	reset();
	return true;
}
