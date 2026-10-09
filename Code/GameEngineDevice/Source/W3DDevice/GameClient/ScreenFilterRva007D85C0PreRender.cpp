// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// postRender is slot 3 of the same vftable, base 0x007CF330, entry
// 0x007CF33C -> 0x000FB2C1. Native 0x000FB2C1..0x000FB85D is the
// complete 1436B RET16 body; the inventory's longer extent includes the
// neighboring destructors and constructors. Clean BFME 1 revision
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d supplies the donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// ScreenFilterRva007D85C0PostRender.cpp. BFME 2 uses the matched texture
// cache and TSS helpers, D3D9 SetVertexShader/SetFVF slots and counters,
// and compiler float literals. Its Vector4 assignments replace the donor's
// explicit empty-constructor iterator. All postRender bytes/relocations
// and the existing 196B preRender agree; original owner remains unknown.
//
// preRender (vftable 0x007CF338) of the screen filter the ledger calls
// Rva007D85C0 (its shutdown 0x000FB964 sits one slot earlier). Zero Hour's
// preRender contract: clear skipRender, redirect rendering to the filter's
// render target and clear it. BFME 2 first rebuilds the filter's gaussian
// kernel at +0x10 from the settings block returned by Rva00309E4BGet whenever
// g_bfmeDirtyCU is set (WorldBuilder names the builder
// W3DShaderManager::createGaussianVector).

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct IDirect3DSurface8;

typedef int Int;
typedef float Real;
typedef bool Bool;
#include "../../../../Libraries/Include/Lib/Coord2D.h"
enum FilterModes { FM_NULL_MODE = 0 };
extern unsigned number_of_DX8_calls;
extern bool bfmeOnlyEmissiveDraws;
class View;
extern View *TheTacticalView;
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

struct Vec4Base
{
	Real x;
	Real y;
	Real z;
	Real w;
};

struct Vec4 : Vec4Base
{
	// ??0Vec4@@QAE@MMMM@Z absent-from-retail
	Vec4(Real a, Real b, Real c, Real d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

struct Rva007D85C0Device;

struct Rva007D85C0DeviceVtable
{
	char pad000[0x104];
	long (__stdcall *SetTexture)(Rva007D85C0Device *, unsigned int, void *);
	char pad108[4];
	long (__stdcall *SetTextureStageState)(Rva007D85C0Device *, unsigned int,
		unsigned int, unsigned int);
	char pad110[0x3c];
	long (__stdcall *DrawPrimitiveUP)(Rva007D85C0Device *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	// D3D9 slot 89 (FVF), retaining the legacy device type spelling.
	long (__stdcall *SetFVF)(Rva007D85C0Device *, unsigned int);
	char pad168[8];
	// D3D9 slot 92 (programmable vertex shader).
	long (__stdcall *SetVertexShader)(Rva007D85C0Device *, unsigned int);
};

struct Rva007D85C0Device
{
	Rva007D85C0DeviceVtable *v;
};

#define Rva007D85C0DeviceGlobal ((Rva007D85C0Device *)DX8Wrapper::_Get_D3D_Device8())
#define Rva007D85C0TacticalViewGlobal ((Rva007D85C0TacticalView *)TheTacticalView)

class Rva007D85C0TacticalView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual Int getWidth() = 0;
	virtual void slot16() = 0;
	virtual Int getHeight() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(Int *, Int *) = 0;
};



class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Set_DX8_Render_State(unsigned long, unsigned);
	static void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
	static void Apply_Render_State_Changes();
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
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
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
protected:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_changes;
};

// The settings block behind Rva00309E4BGet.
struct BfmeGaussianSettings
{
	char m_pad00[4];
	int m_taps; // +0x04
	char m_pad08[0x10 - 0x08];
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};
int Rva00309E4BGet();

struct BfmeGaussianParams
{
	int m_mode;
	int m_taps;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};

class W3DShaderManager
{
public:
	static void createGaussianVector(void *kernel, BfmeGaussianParams *params);
};

extern bool g_bfmeDirtyCU;

enum CustomScenePassModes
{
	SCENE_PASS_DEFAULT
};

class Rva007D85C0
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset();
private:
	Int m_04, m_08;
	bool m_0C; // +0x0C
	int m_kernel[(0x20 - 0x10) / 4]; // +0x10
	IDirect3DBaseTexture8 *m_20;
	char m_pad24[4];
	IDirect3DSurface8 *m_renderTarget; // +0x28
};

// ?preRender@Rva007D85C0@@UAE_NAA_NAAW4CustomScenePassModes@@@Z @0x000FAFF8
bool Rva007D85C0::preRender(bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = false;
	if (g_bfmeDirtyCU) {
		BfmeGaussianParams params;
		params.m_mode = 2;
		params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
		params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
		params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
		params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
		params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
		W3DShaderManager::createGaussianVector(m_kernel, &params);
		g_bfmeDirtyCU = false;
	}
	DX8Wrapper::Set_Render_Target(m_renderTarget, true);
	{
		Vector3 color(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	}
	m_0C = true;
	return true;
}

Bool Rva007D85C0::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	bfmeOnlyEmissiveDraws = 0;
	if (m_0C)
	{
		DX8Wrapper::Set_Render_Target(0, true);
		reset();
		doExtraRender = true;
		m_0C = 0;
		return true;
	}
	if (!set(mode))
		return false;

	Rva007D85C0Device *pDev = Rva007D85C0DeviceGlobal;
	struct Vertex
	{
		Vec4Base p;
		Real u;
		Real v;
		Real u1;
		Real v1;
	} vertex[4];

	Real inverse = 1.0f / (Real)m_08;
	Real halfTexel = inverse * 0.5f;
	vertex[0].p = Vec4(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[0].u = 1.0f + halfTexel;
	vertex[0].v = halfTexel;
	vertex[1].p = Vec4(1.0f, -1.0f, 0.0f, 1.0f);
	vertex[1].u = 1.0f + halfTexel;
	vertex[1].v = 1.0f + halfTexel;
	vertex[2].p = Vec4(-1.0f, 1.0f, 0.0f, 1.0f);
	vertex[2].u = halfTexel;
	vertex[2].v = halfTexel;
	vertex[3].p = Vec4(-1.0f, -1.0f, 0.0f, 1.0f);
	vertex[3].u = halfTexel;
	vertex[3].v = 1.0f + halfTexel;

	DX8Wrapper::Set_Render_Target(0, true);
	DX8Wrapper::Set_DX8_Render_State(0x13, 5);
	DX8Wrapper::Set_DX8_Render_State(0x14, 2);
	DX8Wrapper::Set_DX8_Render_State(0x1b, 1);
	DX8Wrapper::Set_DX8_Render_State(0x3c, 0x2f000000);
	DX8Wrapper::Set_DX8_Render_State(0x8d, 1);
	DX8Wrapper::Set_DX8_Render_State(0x91, 1);
	DX8Wrapper::Apply_Render_State_Changes();

	DX8Wrapper::Set_DX8_Texture(0, m_20);
	DX8Wrapper::Set_DX8_Texture(1, m_20);
	Rva007D85C0DeviceGlobal->v->SetVertexShader(Rva007D85C0DeviceGlobal, 0);
	++number_of_DX8_calls;
	Rva007D85C0DeviceGlobal->v->SetFVF(Rva007D85C0DeviceGlobal, 0x204);
	++number_of_DX8_calls;
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 3);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 3);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 5, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 6, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 0);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 7);
	DX8Wrapper::Set_DX8_Texture_Stage_State(2, 1, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0x18, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0x18, 0);

	Int xpos, ypos, width, height;
	Rva007D85C0TacticalViewGlobal->getOrigin(&xpos, &ypos);
	width = Rva007D85C0TacticalViewGlobal->getWidth();
	height = Rva007D85C0TacticalViewGlobal->getHeight();
	Real finalHalfTexel = (1.0f / (Real)m_08) *
		0.5f;

	vertex[0].p = Vec4((Real)(xpos + width) - 0.5f, (Real)(ypos + height) - 0.5f, 0.0f, 1.0f);
	vertex[0].u = (1.0f / displaySize->x) * (Real)(xpos + width) - finalHalfTexel;
	vertex[0].v = (Real)(ypos + height) / displaySize->y - finalHalfTexel;
	vertex[0].u1 = (1.0f / displaySize->x) * (Real)(xpos + width) + finalHalfTexel;
	vertex[0].v1 = (Real)(ypos + height) / displaySize->y - finalHalfTexel;
	vertex[1].p = Vec4((Real)(xpos + width) - 0.5f, (Real)ypos - 0.5f, 0.0f, 1.0f);
	vertex[1].u = (1.0f / displaySize->x) * (Real)(xpos + width) - finalHalfTexel;
	vertex[1].v = (Real)ypos / displaySize->y - finalHalfTexel;
	vertex[1].u1 = (1.0f / displaySize->x) * (Real)(xpos + width) + finalHalfTexel;
	vertex[1].v1 = (Real)ypos / displaySize->y - finalHalfTexel;
	vertex[2].p = Vec4((Real)xpos - 0.5f, (Real)(ypos + height) - 0.5f, 0.0f, 1.0f);
	vertex[2].u = (1.0f / displaySize->x) * (Real)xpos - finalHalfTexel;
	vertex[2].v = (Real)(ypos + height) / displaySize->y - finalHalfTexel;
	vertex[2].u1 = (1.0f / displaySize->x) * (Real)xpos + finalHalfTexel;
	vertex[2].v1 = (Real)(ypos + height) / displaySize->y - finalHalfTexel;
	vertex[3].p = Vec4((Real)xpos - 0.5f, (Real)ypos - 0.5f, 0.0f, 1.0f);
	vertex[3].u = (1.0f / displaySize->x) * (Real)xpos - finalHalfTexel;
	vertex[3].v = (Real)ypos / displaySize->y - finalHalfTexel;
	vertex[3].u1 = (1.0f / displaySize->x) * (Real)xpos + finalHalfTexel;
	vertex[3].v1 = (Real)ypos / displaySize->y - finalHalfTexel;
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, vertex, sizeof(Vertex));

	vertex[0].u = (1.0f / displaySize->x) * (Real)(xpos + width) - finalHalfTexel;
	vertex[0].v = (1.0f / displaySize->y) * (Real)(ypos + height) + finalHalfTexel;
	vertex[0].u1 = (1.0f / displaySize->x) * (Real)(xpos + width) + finalHalfTexel;
	vertex[0].v1 = (1.0f / displaySize->y) * (Real)(ypos + height) + finalHalfTexel;
	vertex[1].u = (1.0f / displaySize->x) * (Real)(xpos + width) - finalHalfTexel;
	vertex[1].v = (1.0f / displaySize->y) * (Real)ypos + finalHalfTexel;
	vertex[1].u1 = (1.0f / displaySize->x) * (Real)(xpos + width) + finalHalfTexel;
	vertex[1].v1 = (1.0f / displaySize->y) * (Real)ypos + finalHalfTexel;
	vertex[2].u = (1.0f / displaySize->x) * (Real)xpos - finalHalfTexel;
	vertex[2].v = (1.0f / displaySize->y) * (Real)(ypos + height) + finalHalfTexel;
	vertex[2].u1 = (1.0f / displaySize->x) * (Real)xpos + finalHalfTexel;
	vertex[2].v1 = (1.0f / displaySize->y) * (Real)(ypos + height) + finalHalfTexel;
	vertex[3].u = (1.0f / displaySize->x) * (Real)xpos - finalHalfTexel;
	vertex[3].v = (1.0f / displaySize->y) * (Real)ypos + finalHalfTexel;
	vertex[3].u1 = (1.0f / displaySize->x) * (Real)xpos + finalHalfTexel;
	vertex[3].v1 = (1.0f / displaySize->y) * (Real)ypos + finalHalfTexel;
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, vertex, sizeof(Vertex));

	reset();
	return true;
}
