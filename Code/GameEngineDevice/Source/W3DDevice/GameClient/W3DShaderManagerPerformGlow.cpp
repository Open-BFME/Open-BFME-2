// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};

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
struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};
struct IDirect3DTexture8 : IDirect3DBaseTexture8
{
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
#define GLOW_D3D_SLOT(n) virtual void __stdcall slot##n() = 0;
	GLOW_D3D_SLOT(03) GLOW_D3D_SLOT(04) GLOW_D3D_SLOT(05) GLOW_D3D_SLOT(06) GLOW_D3D_SLOT(07)
	GLOW_D3D_SLOT(08) GLOW_D3D_SLOT(09) GLOW_D3D_SLOT(10) GLOW_D3D_SLOT(11) GLOW_D3D_SLOT(12)
	GLOW_D3D_SLOT(13) GLOW_D3D_SLOT(14) GLOW_D3D_SLOT(15) GLOW_D3D_SLOT(16) GLOW_D3D_SLOT(17)
	GLOW_D3D_SLOT(18) GLOW_D3D_SLOT(19) GLOW_D3D_SLOT(20) GLOW_D3D_SLOT(21) GLOW_D3D_SLOT(22)
	GLOW_D3D_SLOT(23) GLOW_D3D_SLOT(24) GLOW_D3D_SLOT(25) GLOW_D3D_SLOT(26) GLOW_D3D_SLOT(27)
	GLOW_D3D_SLOT(28) GLOW_D3D_SLOT(29) GLOW_D3D_SLOT(30) GLOW_D3D_SLOT(31) GLOW_D3D_SLOT(32)
	GLOW_D3D_SLOT(33) GLOW_D3D_SLOT(34) GLOW_D3D_SLOT(35) GLOW_D3D_SLOT(36)
	virtual long __stdcall slot37(unsigned long a, IDirect3DSurface8 *b) = 0;		// +0x94
	GLOW_D3D_SLOT(38) GLOW_D3D_SLOT(39) GLOW_D3D_SLOT(40) GLOW_D3D_SLOT(41) GLOW_D3D_SLOT(42)
	GLOW_D3D_SLOT(43) GLOW_D3D_SLOT(44) GLOW_D3D_SLOT(45) GLOW_D3D_SLOT(46) GLOW_D3D_SLOT(47)
	GLOW_D3D_SLOT(48) GLOW_D3D_SLOT(49) GLOW_D3D_SLOT(50) GLOW_D3D_SLOT(51) GLOW_D3D_SLOT(52)
	GLOW_D3D_SLOT(53) GLOW_D3D_SLOT(54) GLOW_D3D_SLOT(55) GLOW_D3D_SLOT(56) GLOW_D3D_SLOT(57)
	GLOW_D3D_SLOT(58) GLOW_D3D_SLOT(59) GLOW_D3D_SLOT(60) GLOW_D3D_SLOT(61) GLOW_D3D_SLOT(62)
	GLOW_D3D_SLOT(63) GLOW_D3D_SLOT(64)
	virtual long __stdcall SetTexture(unsigned long stage, IDirect3DBaseTexture8 *texture) = 0;	// +0x104
	GLOW_D3D_SLOT(66) GLOW_D3D_SLOT(67) GLOW_D3D_SLOT(68)
	virtual long __stdcall SetTextureStageState(unsigned long stage, unsigned long type, unsigned long value) = 0;	// +0x114
	GLOW_D3D_SLOT(70) GLOW_D3D_SLOT(71) GLOW_D3D_SLOT(72) GLOW_D3D_SLOT(73) GLOW_D3D_SLOT(74)
	GLOW_D3D_SLOT(75) GLOW_D3D_SLOT(76) GLOW_D3D_SLOT(77) GLOW_D3D_SLOT(78) GLOW_D3D_SLOT(79)
	GLOW_D3D_SLOT(80) GLOW_D3D_SLOT(81) GLOW_D3D_SLOT(82) GLOW_D3D_SLOT(83) GLOW_D3D_SLOT(84)
	GLOW_D3D_SLOT(85) GLOW_D3D_SLOT(86)
	virtual long __stdcall SetVertexShader(unsigned long handle) = 0;					// +0x15C
	GLOW_D3D_SLOT(88) GLOW_D3D_SLOT(89) GLOW_D3D_SLOT(90) GLOW_D3D_SLOT(91)
	virtual long __stdcall slot92(unsigned long handle) = 0;							// +0x170
	GLOW_D3D_SLOT(93)
	virtual long __stdcall SetVertexShaderConstant(unsigned long reg, const void *data, unsigned long count) = 0;	// +0x178
	GLOW_D3D_SLOT(95) GLOW_D3D_SLOT(96) GLOW_D3D_SLOT(97) GLOW_D3D_SLOT(98) GLOW_D3D_SLOT(99)
	GLOW_D3D_SLOT(100) GLOW_D3D_SLOT(101) GLOW_D3D_SLOT(102) GLOW_D3D_SLOT(103) GLOW_D3D_SLOT(104)
	GLOW_D3D_SLOT(105) GLOW_D3D_SLOT(106)
	virtual long __stdcall SetPixelShader(unsigned long handle) = 0;					// +0x1AC
	GLOW_D3D_SLOT(108)
	virtual long __stdcall SetPixelShaderConstant(unsigned long reg, const void *data, unsigned long count) = 0;	// +0x1B4
#undef GLOW_D3D_SLOT
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Clear(bool clear_color, bool clear_z_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_x, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
	{
		_Get_D3D_Device8()->SetTextureStageState(stage, state, value);
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
		_Get_D3D_Device8()->SetPixelShaderConstant(reg, data, count);
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Vertex_Shader_Constant(int reg, const void *data, int count)
	{
		int memsize = sizeof(Vector4) * count;
		if (memcmp(data, &Vertex_Shader_Constants[reg], memsize) == 0)
			return;
		memcpy(&Vertex_Shader_Constants[reg], data, memsize);
		_Get_D3D_Device8()->SetVertexShaderConstant(reg, data, count);
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
	IDirect3DSurface8 *tempSurface, IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface)
{
	if (!m_dwGlowPixelShader || !m_dwGlowVertexShader)
		return;

	DX8Wrapper::Set_Render_Target(tempSurface, false);
	DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.75f, 0.0f), 0.0f, 1.0f, 0);
	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	Int i;
	for (i = 0; i < 4; ++i)
	{
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 1, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 2, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 6, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 7, 2);
	}
	DX8Wrapper::Set_DX8_Render_State(0x16, 1);
	DX8Wrapper::Set_DX8_Render_State(0x0E, 0);
	DX8Wrapper::Set_DX8_Render_State(0x07, 0);
	DX8Wrapper::Set_DX8_Texture(0, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(1, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(2, sourceTexture);
	DX8Wrapper::Set_DX8_Texture(3, sourceTexture);
	DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(m_dwGlowPixelShader);
	number_of_DX8_calls++;
	DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(g_fvfShader);
	number_of_DX8_calls++;
	DX8Wrapper::_Get_D3D_Device8()->slot92(m_dwGlowVertexShader);
	number_of_DX8_calls++;
	DX8Wrapper::Set_DX8_Render_State(0x1B, 0);
	DX8Wrapper::Set_DX8_Render_State(0x13, 2);
	DX8Wrapper::Set_DX8_Render_State(0x14, 4);

	D3DXVECTOR4 offsets[4];
	D3DXVECTOR4 weights[4];
	UnsignedInt sample;
	for (sample = 0; sample < samples->size(); sample += 4)
	{
		if (sample == 4)
			DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
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
	device->slot37(0, destSurface);
	DX8Wrapper::Set_DX8_Texture(0, tempTexture);
	DX8Wrapper::Set_DX8_Texture(1, tempTexture);
	DX8Wrapper::Set_DX8_Texture(2, tempTexture);
	DX8Wrapper::Set_DX8_Texture(3, tempTexture);
	DX8Wrapper::Set_DX8_Render_State(0x1B, 0);

	for (sample = 0; sample < samples->size(); sample += 4)
	{
		if (sample == 4)
			DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
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
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 5, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 6, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(i, 7, 2);
	}
	DX8Wrapper::_Get_D3D_Device8()->SetPixelShader(0);
	number_of_DX8_calls++;
	DX8Wrapper::Set_Render_Target(0, true);
}
