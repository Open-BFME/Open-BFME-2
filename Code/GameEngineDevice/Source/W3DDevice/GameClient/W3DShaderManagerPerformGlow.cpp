// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
//
// W3DShaderManager::performGlow, retail 0x00077392..0x00077BF8
// (2150 bytes, cdecl, 7 arguments). Callers: 0x000F71F5 / 0x000F897E /
// 0x000F89A7.
//
// Identity: WorldBuilder 0x007D3D20 performGlow (W3DShaderManager.cpp asserts
// 1544 / 1546 on the glow pixel and vertex shaders).
//
// What the body does:
// - It renders into the temp surface (rowed Set_Render_Target 0x0011E250)
//   after a Clear (0x0011D330).
// - It sets the stage states, render states (rowed Set_DX8_Render_State
//   0x0006615F) and source textures.
// - It then runs two blur passes. Each pass, in groups of 4 samples:
//   - fills 4 weights (sample.Z * scale) and 4 offsets
//     (sample.XY / size; the second pass swaps them);
//   - goes through the cached pixel / vertex shader constant helpers
//     (memcmp / memcpy imports, constants 0 / 7 / 10);
//   - draws through the rowed 0x00075A23.
// - It resets the textures and shader and restores the render target.
//
// The DX8Wrapper inline helpers follow the rowed Rva000FBA57PostRender.cpp.
// Each offset is built in a named D3DXVECTOR4 local and then copied into the
// array: that fixes the sample X multiply operand order in both passes
// (a temporary constructed straight into offsets[j] flips them).
#include <string.h>
#include <d3d9.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

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

// The device, surfaces and textures keep their D3D8 type names (performGlow's and
// DX8Wrapper's decorations) but are Direct3D 9 objects. Device slots used here:
// SetRenderTarget 37, SetTexture 65, SetSamplerState 69, SetVertexDeclaration 87
// (g_fvfShader is the declaration Rva00066A9ABody creates), SetVertexShader 92,
// SetVertexShaderConstantF 94, SetPixelShader 107, SetPixelShaderConstantF 109;
// texture AddRef / Release 1 / 2.
struct IDirect3DSurface8;
struct IDirect3DBaseTexture8 {};
struct IDirect3DTexture8 : IDirect3DBaseTexture8 {};
struct IDirect3DDevice8;
#define DEVICE9 (reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8()))
#define TEXTURE9(x) (reinterpret_cast<IDirect3DBaseTexture9 *>(x))

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Clear(bool clear_color, bool clear_z_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_x, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	// The D3D9 slot at +0x114 is SetSamplerState (SetTextureStageState is
	// +0x10C): states 1/2 and 5/6/7 are ADDRESSU/V and MAG/MIN/MIPFILTER. The
	// sibling filter units call this helper Set_DX8_Sampler_State; under the
	// Set_DX8_Texture_Stage_State name its copy was judged against retail's
	// cached 0x000661DD body.
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned long state, unsigned value)
	{
		DEVICE9->SetSamplerState(stage, (D3DSAMPLERSTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
	static __forceinline void Set_DX8_Texture(unsigned stage, IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 16) {
			DEVICE9->SetTexture(stage, TEXTURE9(texture));
			number_of_DX8_calls++;
			return;
		}
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			TEXTURE9(Textures[stage])->Release();
		Textures[stage] = texture;
		if (Textures[stage])
			TEXTURE9(Textures[stage])->AddRef();
		DEVICE9->SetTexture(stage, TEXTURE9(texture));
		number_of_DX8_calls++;
		texture_changes++;
	}
	static __forceinline void Set_Pixel_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Pixel_Shader_Constants[reg], data, memsize);
		DEVICE9->SetPixelShaderConstantF(reg, (const float *)data, count);
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Vertex_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Vertex_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Vertex_Shader_Constants[reg], data, memsize);
		DEVICE9->SetVertexShaderConstantF(reg, (const float *)data, count);
		number_of_DX8_calls++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned texture_stage_state_changes;
	static unsigned texture_changes;
	static Vector4 Pixel_Shader_Constants[8];
	static Vector4 Vertex_Shader_Constants[96];
};

void Rva00075A23Draw(Int width, Int height);
extern UnsignedInt g_fvfShader;

struct GlowSampleVector
{
	Vector3 *m_start;
	Vector3 *m_finish;
	Vector3 *m_endOfStorage;
	UnsignedInt size() const { return m_finish - m_start; }
	const Vector3 &operator[](UnsignedInt i) const { return m_start[i]; }
};

class W3DShaderManager
{
public:
	static void performGlow(Real weightScale, const GlowSampleVector *samples, Int textureSize, IDirect3DTexture8 *sourceTexture,
		IDirect3DSurface8 *tempSurface, IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface);
protected:
	static unsigned long m_dwGlowPixelShader;
	static unsigned long m_dwGlowVertexShader;
};

void W3DShaderManager::performGlow(Real weightScale, const GlowSampleVector *samples, Int textureSize, IDirect3DTexture8 *sourceTexture,
	IDirect3DSurface8 *direct3DSurface8, IDirect3DTexture8 *direct3DTexture8, IDirect3DSurface8 *destSurface)
{
	if (!m_dwGlowPixelShader || !m_dwGlowVertexShader)
		return;

	DX8Wrapper::Set_Render_Target(direct3DSurface8, false);
	DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.75f, 0.0f), 0.0f, 1.0f, 0);
	IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	Int i;
	for (i = 0; i < 4; ++i)
	{
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	DX8Wrapper::Set_DX8_Render_State(D3DRS_CULLMODE, D3DCULL_NONE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, D3DZB_FALSE);
	DX8Wrapper::Set_DX8_Texture(0, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(1, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(2, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(3, sourceTexture);
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(
		reinterpret_cast<IDirect3DPixelShader9 *>(m_dwGlowPixelShader));
	number_of_DX8_calls++;
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetVertexDeclaration(
		reinterpret_cast<IDirect3DVertexDeclaration9 *>(g_fvfShader));
	number_of_DX8_calls++;
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetVertexShader(
		reinterpret_cast<IDirect3DVertexShader9 *>(m_dwGlowVertexShader));
	number_of_DX8_calls++;
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	D3DXVECTOR4 offsets[4];
	D3DXVECTOR4 weights[4];
	UnsignedInt sample;
	for (sample = 0; sample < samples->size(); sample += 4)
	{
		if (sample == 4)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
		for (Int j = 0; j < 4; ++j)
		{
			const Vector3 &s = (*samples)[sample + j];
			weights[j].x = s.Z * weightScale;
			weights[j].y = s.Z * weightScale;
			weights[j].z = s.Z * weightScale;
			weights[j].w = s.Z * weightScale;
			D3DXVECTOR4 off(s.X * (1.0f / (Real)textureSize), s.Y * (1.0f / (Real)textureSize), 0.0f, 0.0f);
			offsets[j] = off;
		}
		DX8Wrapper::Set_Pixel_Shader_Constant(0, weights, 4);
		D3DXVECTOR4 half(0.5f, 0.0f, 0.0f, 0.0f);
		DX8Wrapper::Set_Pixel_Shader_Constant(7, &half, 1);
		DX8Wrapper::Set_Vertex_Shader_Constant(10, offsets, 4);
		Rva00075A23Draw(textureSize, textureSize);
	}

	DX8Wrapper::Set_DX8_Texture(0, 0);
	DX8Wrapper::Set_DX8_Texture(1, 0);
	DX8Wrapper::Set_DX8_Texture(2, 0);
	DX8Wrapper::Set_DX8_Texture(3, 0);
	device->SetRenderTarget(0, reinterpret_cast<IDirect3DSurface9 *>(destSurface));
	DX8Wrapper::Set_DX8_Texture(0, direct3DTexture8);
	DX8Wrapper::Set_DX8_Texture(1, direct3DTexture8);
	DX8Wrapper::Set_DX8_Texture(2, direct3DTexture8);
	DX8Wrapper::Set_DX8_Texture(3, direct3DTexture8);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);

	for (sample = 0; sample < samples->size(); sample += 4)
	{
		if (sample == 4)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
		for (Int j = 0; j < 4; ++j)
		{
			const Vector3 &s = (*samples)[sample + j];
			weights[j].x = s.Z * weightScale;
			weights[j].y = s.Z * weightScale;
			weights[j].z = s.Z * weightScale;
			weights[j].w = s.Z * weightScale;
			D3DXVECTOR4 off(s.Y * (1.0f / (Real)textureSize), s.X * (1.0f / (Real)textureSize), 0.0f, 0.0f);
			offsets[j] = off;
		}
		DX8Wrapper::Set_Pixel_Shader_Constant(0, weights, 4);
		DX8Wrapper::Set_Vertex_Shader_Constant(10, offsets, 4);
		Rva00075A23Draw(textureSize, textureSize);
	}

	for (i = 0; i < 4; ++i)
	{
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		DX8Wrapper::Set_DX8_Sampler_State(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(0);
	number_of_DX8_calls++;
	DX8Wrapper::Set_Render_Target(0, true);
}
