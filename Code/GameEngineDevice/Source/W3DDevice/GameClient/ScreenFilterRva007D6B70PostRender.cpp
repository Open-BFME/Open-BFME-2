// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// dxsdk
// platformsdk
//
// ?postRender@Rva007D6B70@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z,
// retail 0x000F7187..0x000F816E (4071 bytes, thiscall ret 0x10): slot 3 of
// the Rva007D6B70 filter vtable, whose shutdown 0x000F70EB, set 0x000F816E
// and reset 0x000F8735 are rowed. Twin of the Rva007DB820 postRender
// 0x000F88E8 (ScreenFilterRva007DB820PostRender.cpp).
//
// It sets the mode, runs the glow pass when enabled, drifts the scroll and
// spread offsets, draws a first-pass quad over the tactical view, then has the
// grid helper 0x000F6DB0 (pinned; its body is banked) fill a 10x10 dynamic
// grid and draws that with the second-pass shader while the draw strength is
// positive.
//
// Levers: the 1/viewport divisions are written as plain divisions (cl emits
// one reciprocal), the two function-scope D3DXVECTOR4 constants come from a
// by-value RGBColor helper (their temps share the vertex-temp slot),
// Set_Pixel_Shader is an inline wrapper, and u = m_scrollX + (u*2 + m_spread).
#include <math.h>
// <math.h>'s sin(float) under its own name: this /O1 unit's copy of
// ?sin@@YAMM@Z calls _sin and would compete with retail's intrinsic body at
// 0x0002FBB0. Keep it extern: a static copy reschedules the grid helper's pops.
inline float __cdecl waveSin(float _X)
        {return (sinf(_X)); }
#include <string.h>
#include <d3d9.h>
#include "Lib/Coord2D.h"
#include "Lib/RGBColor.h"

typedef bool Bool;
class DynamicIBAccessClass;
class DynamicVBAccessClass;
struct D3DXVECTOR4
{
	float x, y, z, w;
	D3DXVECTOR4() {}
	D3DXVECTOR4(float xValue, float yValue, float zValue, float wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

struct IDirect3DSurface8;
struct IDirect3DTexture8;
struct IDirect3DBaseTexture8;

// The device, surfaces and textures keep their D3D8 type names (DX8Wrapper's
// static decorations) but are Direct3D 9 objects from the vendored SDK.
struct IDirect3DDevice8;

extern unsigned number_of_DX8_calls;

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	__forceinline ~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};

class WW3D { public: static bool Is_Snapshot_Activated() { return SnapshotActivated; } private: static bool SnapshotActivated; };

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Apply_Render_State_Changes();
	static void Set_Index_Buffer(const DynamicIBAccessClass &ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const DynamicVBAccessClass &vb);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value)
			return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetRenderState((D3DRENDERSTATETYPE)state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
	{
		if (stage >= 16) {
			reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
			number_of_DX8_calls++;
			return;
		}
		if (TextureStageStates[stage][state] == value)
			return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned long state, unsigned value)
	{
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetSamplerState(stage, (D3DSAMPLERSTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->AddRef();
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void Set_Pixel_Shader(void *shader)
	{
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetPixelShader(static_cast<IDirect3DPixelShader9 *>(shader));
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Pixel_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(D3DXVECTOR4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8())->SetPixelShaderConstantF(reg, (const float *)data, count);
		number_of_DX8_calls++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static unsigned TextureStageStates[16][32];
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned render_state_changes;
	static unsigned texture_stage_state_changes;
	static unsigned texture_changes;
	// dx8wrapper.cpp's Vector4 array at 0x009EDF10
	static Vector4 Pixel_Shader_Constants[8];
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

struct GlowSampleVector;
class W3DShaderManager
{
public:
	static void performGlow(float strength, const GlowSampleVector *samples, int size,
		IDirect3DTexture8 *source, IDirect3DSurface8 *sourceSurface,
		IDirect3DTexture8 *target, IDirect3DSurface8 *targetSurface);
};

class View
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C) SLOT(20) SLOT(24)
	SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38)
	virtual int getWidth() = 0;	// +0x3C
	SLOT(40)
	virtual int getHeight() = 0;	// +0x44
	SLOT(48)
	virtual void getOrigin(int *x, int *y) = 0;	// +0x4C
#undef SLOT
};
extern View *TheTacticalView;

enum FilterModes { FM_NULL_MODE = 0 };
class DynamicIBAccessClass
{
public:
	DynamicIBAccessClass(unsigned short type, unsigned short index_count);
	~DynamicIBAccessClass();
	class WriteLockClass
	{
	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return Indices; }
	private:
		DynamicIBAccessClass *DynamicIBAccess;
		unsigned short *Indices;
		int m_08;
	};
private:
	char m_storage[0x0C];
};

struct VertexFormatXYZRHWDUV4
{
	float x, y, z, rhw;
	unsigned diffuse;
	float u0, v0, u1, v1, u2, v2, u3, v3;
};

class DynamicVBAccessClass
{
public:
	DynamicVBAccessClass(unsigned type, unsigned fvf, unsigned short vertex_count, unsigned declaration);
	~DynamicVBAccessClass();
	class WriteLock
	{
	public:
		WriteLock(DynamicVBAccessClass *vb_access);
		~WriteLock();
		VertexFormatXYZRHWDUV4 *Get_Formatted_Vertex_Array() { return Vertices; }
	private:
		DynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZRHWDUV4 *Vertices;
		int m_08;
	};
private:
	char m_storage[0x18];
};

int Rva00309E7FGet(void);

extern float g_Va00DB457C;

// The filter settings record returned by 0x309E7F (VA 0x00DBD918).
struct Rva007D6B70Settings
{
	float m_00;	// +0x00 pixel constant 4 numerator
	float m_04;	// +0x04 draw strength (draws while > 0)
	RGBColor m_08;	// +0x08 pixel constant 2
	RGBColor m_14;	// +0x14 pixel constant 1
	float m_20;	// +0x20 pixel constant 3
	float m_24;	// +0x24 pixel constant 6
	char m_pad28[0x4C - 0x28];
	float m_4C;	// +0x4C drift rate
	float m_50;	// +0x50 spread drift rate
	float m_54;	// +0x54 grid scale
};
static __forceinline Rva007D6B70Settings *filterSettings() { return (Rva007D6B70Settings *)Rva00309E7FGet(); }
static __forceinline D3DXVECTOR4 colorConstant(RGBColor color) { return D3DXVECTOR4(color.red, color.green, color.blue, 1.0f); }
static Bool s_glowEnabled;	// 0x00DEC061, read only here
static Bool s_drawGrid;		// 0x00DEC060, read only here

class Rva007D6B70
{
public:
	virtual int init();
	virtual int shutdown();
	virtual Bool preRender(Bool &skipRender, int &scenePassMode);
	virtual Bool postRender(FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender, Coord2D *displaySize);
	virtual Bool setup(FilterModes mode);
protected:
	virtual int set(FilterModes mode);
	virtual void reset();
public:
	void rva000F6DB0(DynamicIBAccessClass *ib, int a, DynamicVBAccessClass *vb, int b, int columns, int rows,
		float left, float top, float width, float height, Coord2D *dims);
private:
	void *m_pixelShader;	// +0x04
	void *m_08;
	void *m_0C;
	TextureBaseClass m_texture1;	// +0x10
	char m_pad11[3];
	TextureBaseClass m_texture2;	// +0x14
	char m_pad15[3];
	IDirect3DTexture8 *m_renderTexture;	// +0x18
	void *m_1C;
	float m_scrollX, m_scrollY, m_spread;	// +0x20
	char m_glowSamples[0x0C];	// +0x2C
	IDirect3DTexture8 *m_glowTexture;	// +0x38
	IDirect3DTexture8 *m_3C;	// +0x3C
	IDirect3DSurface8 *m_glowSurface;	// +0x40
	IDirect3DSurface8 *m_44;	// +0x44
};

// Retail 0x000F7187..0x000F816E (4071 B, thiscall RET 0x10): slot 3 of the
// Rva007D6B70 filter vtable.
Bool Rva007D6B70::postRender(FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender, Coord2D *displaySize)
{
	DX8Wrapper::Set_Render_Target(0, true);
	if (!set(mode))
		return false;
	doExtraRender = true;
	IDirect3DDevice9 *pDev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	if (s_glowEnabled)
		W3DShaderManager::performGlow(0.8f, (const GlowSampleVector *)m_glowSamples, 0x100, m_renderTexture, m_glowSurface, m_glowTexture, m_44);

	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		float u, v;
		float u1, v1;
		float u2, v2;
	} v[4];
	int xpos, ypos, width, height;
	TheTacticalView->getOrigin(&xpos, &ypos);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	if (m_scrollY > 1.0f)
		m_scrollY -= 1.0f;
	if (m_scrollX < -1.0f)
		m_scrollX += 1.0f;
	if (m_spread > 1.0f)
		m_spread -= 1.0f;
	m_scrollY += filterSettings()->m_4C * 0.03f;
	m_scrollX -= filterSettings()->m_4C * 0.0225f;
	m_spread += filterSettings()->m_50 * 0.005;

	float scale = g_Va00DB457C * 0.0125f;
	if (scale > 6.0f) scale = 6.0f;
	if (scale < 0.6f) scale = 0.6f;
	float amplitude = filterSettings()->m_54 * scale;

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (float)(xpos + width) / displaySize->x;
	v[0].v = (float)(ypos + height) / displaySize->y;
	v[0].u1 = amplitude;
	v[0].v1 = amplitude;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (float)(xpos + width) / displaySize->x;
	v[1].v = (float)ypos / displaySize->y;
	v[1].u1 = amplitude;
	v[1].v1 = 0.0f;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (float)xpos / displaySize->x;
	v[2].v = (float)(ypos + height) / displaySize->y;
	v[2].u1 = 0.0f;
	v[2].v1 = amplitude;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (float)xpos / displaySize->x;
	v[3].v = (float)ypos / displaySize->y;
	v[3].u1 = 0.0f;
	v[3].v1 = 0.0f;
	for (int i = 0; i < 4; ++i) {
		v[i].color = 0x64ffffff;
		v[i].u1 = m_scrollX + (v[i].u1 * 2 + m_spread);
		v[i].v1 += m_scrollY;
		v[i].v2 = v[i].v1 + m_spread;
		v[i].u2 = v[i].u1 - m_spread;
		v[i].u1 += m_spread;
	}

	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX3);
	number_of_DX8_calls++;
	DX8Wrapper::Set_Pixel_Shader_Constant(0, &D3DXVECTOR4(0.3f, 0.59f, 0.11f, 1.0f), 1);
	D3DXVECTOR4 color1 = colorConstant(filterSettings()->m_14);
	DX8Wrapper::Set_Pixel_Shader_Constant(1, &color1, 1);
	D3DXVECTOR4 color2 = colorConstant(filterSettings()->m_08);
	DX8Wrapper::Set_Pixel_Shader_Constant(2, &color2, 1);
	{
		float f = filterSettings()->m_20;
		DX8Wrapper::Set_Pixel_Shader_Constant(3, &D3DXVECTOR4(f, f, f, f), 1);
	}
	{
		float f = filterSettings()->m_00 / (scale * 80.0f);
		DX8Wrapper::Set_Pixel_Shader_Constant(4, &D3DXVECTOR4(f, f, f, 1.0f), 1);
	}
	float strength = filterSettings()->m_04;
	DX8Wrapper::Set_Pixel_Shader_Constant(5, &D3DXVECTOR4(strength, strength, strength, strength), 1);
	{
		float f = filterSettings()->m_24;
		DX8Wrapper::Set_Pixel_Shader_Constant(6, &D3DXVECTOR4(f, f, f, f), 1);
	}
	DX8Wrapper::Set_Pixel_Shader_Constant(7, &D3DXVECTOR4(0.55f, 0.45f, 0.5f, 0.5f), 1);

	DX8Wrapper::Set_DX8_Render_State(27, 1);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture(0, (IDirect3DBaseTexture8 *)m_renderTexture);
	DX8Wrapper::Set_DX8_Texture(1, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 5, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 6, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0);

	DynamicIBAccessClass ib(2, 606);
	DynamicVBAccessClass vb(2, 14, 202, 0);
	rva000F6DB0(&ib, 606, &vb, 202, 10, 10, (float)xpos, (float)ypos, (float)width, (float)height, displaySize);
	DX8Wrapper::Set_Index_Buffer(ib, 0);
	DX8Wrapper::Set_Vertex_Buffer(vb);
	DX8Wrapper::Apply_Render_State_Changes();
	if (s_glowEnabled) {
		DX8Wrapper::Set_DX8_Texture(3, (IDirect3DBaseTexture8 *)m_3C);
		DX8Wrapper::Set_DX8_Texture(4, (IDirect3DBaseTexture8 *)m_3C);
	} else {
		DX8Wrapper::Set_DX8_Texture(3, (IDirect3DBaseTexture8 *)m_renderTexture);
		DX8Wrapper::Set_DX8_Texture(4, (IDirect3DBaseTexture8 *)m_renderTexture);
	}
	DX8Wrapper::Set_DX8_Texture(1, m_texture1.Peek_D3D_Base_Texture());
	DX8Wrapper::Set_DX8_Texture(2, m_texture2.Peek_D3D_Base_Texture());
	DX8Wrapper::Set_DX8_Sampler_State(0, 1, 3);
	DX8Wrapper::Set_DX8_Sampler_State(0, 2, 3);
	DX8Wrapper::Set_DX8_Sampler_State(1, 1, 1);
	DX8Wrapper::Set_DX8_Sampler_State(1, 2, 1);
	DX8Wrapper::Set_DX8_Sampler_State(2, 1, 1);
	DX8Wrapper::Set_DX8_Sampler_State(2, 2, 1);
	DX8Wrapper::Set_DX8_Sampler_State(3, 1, 3);
	DX8Wrapper::Set_DX8_Sampler_State(3, 2, 3);
	DX8Wrapper::Set_DX8_Sampler_State(4, 1, 3);
	DX8Wrapper::Set_DX8_Sampler_State(4, 2, 3);
	DX8Wrapper::Set_DX8_Render_State(27, 1);
	DX8Wrapper::Set_DX8_Render_State(19, 2);
	DX8Wrapper::Set_DX8_Render_State(20, 2);
	DX8Wrapper::Set_Pixel_Shader(m_pixelShader);
	DX8Wrapper::Set_Render_Target(0, true);
	if (strength > 0.0f) {
		if (s_drawGrid) {
			DX8Wrapper::Draw_Triangles(0, 200, 0, 202);
		} else {
			reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX3);
			number_of_DX8_calls++;
			pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
		}
	}
	reset();
	return true;
}

// The grid wave state for the update below (file statics in the original).
static float GridPhase0, GridPhase1;
static float GridWave0Amplitude = 0.2f, GridWave0Frequency = 12.566370964f, GridWave0Phase = 2.0f;
static float GridWave1Amplitude = 0.5f, GridWave1Frequency = 12.566370964f, GridWave1Phase = 2.0f;


// Grid update called by postRender: rebuilds the strip indices and the
// wave-displaced vertices. The (float) rounding of each 0.5f*sin(...) term
// and the trailing ++p give retail's loop-tail schedule.
void Rva007D6B70::rva000F6DB0(DynamicIBAccessClass *ib, int a, DynamicVBAccessClass *vb, int b, int columns, int rows,
	float left, float top, float width, float height, Coord2D *dims)
{
	++columns; ++rows;
	float scale = g_Va00DB457C * 0.0125f;
	if (scale > 6.0f) scale = 6.0f;
	if (scale < 0.6f) scale = 0.6f;
	float amplitude = scale * filterSettings()->m_54;
	{
		DynamicIBAccessClass::WriteLockClass lock(ib);
		unsigned short *vertexFormatXYZRHWDUV4 = lock.Get_Index_Array();
		for (int y = 0; y < rows - 1; ++y) {
			for (int x = 0; x < columns - 1; ++x) {
				vertexFormatXYZRHWDUV4[0] = y * columns + x; vertexFormatXYZRHWDUV4[1] = (y + 1) * columns + x + 1; vertexFormatXYZRHWDUV4[2] = (y + 1) * columns + x;
				vertexFormatXYZRHWDUV4[3] = y * columns + x; vertexFormatXYZRHWDUV4[4] = y * columns + x + 1; vertexFormatXYZRHWDUV4[5] = (y + 1) * columns + x + 1;
				vertexFormatXYZRHWDUV4 += 6;
			}
		}
	}
	GridPhase0 += 0.05f; GridPhase1 += 0.05f;
	{
		DynamicVBAccessClass::WriteLock lock(vb);
		VertexFormatXYZRHWDUV4 *vertexFormatXYZRHWDUV4 = lock.Get_Formatted_Vertex_Array();
		float invRows = 1.0f / (rows - 1);
		float invColumns = 1.0f / (columns - 1);
		for (int y = 0; y < rows; ++y) {
			float fy = y * invRows;
			float screenY = (fy * height + top) - 0.5f;
			for (int x = 0; x < columns; ++x) {
				float fx = x * invColumns;
				vertexFormatXYZRHWDUV4->x = fx * width + left - 0.5f; vertexFormatXYZRHWDUV4->y = screenY; vertexFormatXYZRHWDUV4->z = 0; vertexFormatXYZRHWDUV4->rhw = 1; vertexFormatXYZRHWDUV4->diffuse = 0x64ffffff;
				vertexFormatXYZRHWDUV4->u0 = (fx * width + left) / dims->x; vertexFormatXYZRHWDUV4->v0 = (fy * height + top) / dims->y;
				vertexFormatXYZRHWDUV4->u1 = fx * amplitude * 2 + m_scrollX; vertexFormatXYZRHWDUV4->v1 = fy * amplitude + m_scrollY;
				float u1 = vertexFormatXYZRHWDUV4->u1; float v1 = vertexFormatXYZRHWDUV4->v1;
				vertexFormatXYZRHWDUV4->v2 = v1 + m_spread; vertexFormatXYZRHWDUV4->u2 = u1 - m_spread; vertexFormatXYZRHWDUV4->u1 += m_spread;
				vertexFormatXYZRHWDUV4->u3 = (0.5f - (float)(0.5f * waveSin((fx + fy) * GridWave0Frequency + GridPhase0 * GridWave0Phase))) * GridWave0Amplitude;
				float wave = (0.5f - (float)(0.5f * waveSin((fx + fy) * GridWave1Frequency + GridPhase1 * GridWave1Phase))) * GridWave1Amplitude;
				vertexFormatXYZRHWDUV4->v3 = 0;
				vertexFormatXYZRHWDUV4->u1 += wave; vertexFormatXYZRHWDUV4->u2 += wave;
				++vertexFormatXYZRHWDUV4;
			}
		}
	}
}
