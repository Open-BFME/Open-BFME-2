// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?RenderMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z @0x000F200A 505B.
//
// W3DVolumetricShadow::RenderMeshVolume: draws one static shadow volume
// from its vertex/index buffer slots. Target evidence: retail
// 0x000F200A..0x000F2203 (plain frame, ret 0xC), called from RenderVolume
// (0x000F49D0). The stencil sub-mask ((this+0x34 >> 7) & 7) << 4 is
// replicated into D3DRS_STENCILMASK/STENCILREF through the out-of-line
// DX8Wrapper::Set_DX8_Render_State (0x0006615F) and restored afterwards
// from TheW3DShadowManager's mask; the volume's active counts sit at
// Geometry+0x10/+0x14, the slots at this+0x300/+0x580 with 160 meshes per
// light, the last bound buffer at 0x00DEBCF4, and the draw is gated on the
// triangle-draw flag 0x00DB5FCD and counted through
// Debug_Statistics::Record_DX8_Polys_And_Vertices (0x00129540) with
// ShaderClass::_PresetOpaqueShader. Device calls are the IDirect3DDevice9
// slots SetTransform (+0xB0), SetStreamSource (+0x190), SetIndices
// (+0x1A0) and DrawIndexedPrimitive (+0x148).
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp RenderMeshVolume (the ZH
// body plus the BFME stencil sub-mask). BFME 2 deltas read from retail:
// render states go through DX8Wrapper rather than the raw device. The last
// bound buffer stays the ZH file-static: retail keeps the slot chain live
// across its store, which only a non-escaping static allows.

typedef unsigned long DWORD;
typedef long HRESULT;
typedef unsigned int UINT;
typedef float Real;
typedef int Int;

#define D3DTS_WORLD				256
#define D3DPT_TRIANGLELIST		4
#define D3DRS_STENCILREF		57
#define D3DRS_STENCILMASK		58

struct D3DMATRIX;
struct IDirect3DDevice8;
struct IDirect3DVertexBuffer8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
	virtual HRESULT __stdcall GetDevice(IDirect3DDevice8 **ppDevice) = 0;
	virtual HRESULT __stdcall SetPrivateData(void) = 0;
	virtual HRESULT __stdcall GetPrivateData(void) = 0;
	virtual HRESULT __stdcall FreePrivateData(void) = 0;
	virtual DWORD __stdcall SetPriority(DWORD priorityNew) = 0;
	virtual DWORD __stdcall GetPriority(void) = 0;
	virtual void __stdcall PreLoad(void) = 0;
	virtual DWORD __stdcall GetType(void) = 0;
	virtual HRESULT __stdcall Lock(UINT offsetToLock, UINT sizeToLock, unsigned char **ppbData, DWORD flags) = 0;
	virtual HRESULT __stdcall Unlock(void) = 0;
};
struct IDirect3DIndexBuffer8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
	virtual HRESULT __stdcall GetDevice(IDirect3DDevice8 **ppDevice) = 0;
	virtual HRESULT __stdcall SetPrivateData(void) = 0;
	virtual HRESULT __stdcall GetPrivateData(void) = 0;
	virtual HRESULT __stdcall FreePrivateData(void) = 0;
	virtual DWORD __stdcall SetPriority(DWORD priorityNew) = 0;
	virtual DWORD __stdcall GetPriority(void) = 0;
	virtual void __stdcall PreLoad(void) = 0;
	virtual DWORD __stdcall GetType(void) = 0;
	virtual HRESULT __stdcall Lock(UINT offsetToLock, UINT sizeToLock, unsigned char **ppbData, DWORD flags) = 0;
	virtual HRESULT __stdcall Unlock(void) = 0;
};
struct IDirect3DDevice8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
	virtual HRESULT __stdcall TestCooperativeLevel(void) = 0;
	virtual UINT __stdcall GetAvailableTextureMem(void) = 0;
	virtual HRESULT __stdcall EvictManagedResources(void) = 0;
	virtual HRESULT __stdcall GetDirect3D(void **ppD3D9) = 0;
	virtual HRESULT __stdcall GetDeviceCaps(void *pCaps) = 0;
	virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, void *pMode) = 0;
	virtual HRESULT __stdcall GetCreationParameters(void *pParameters) = 0;
	virtual HRESULT __stdcall SetCursorProperties(UINT x, UINT y, void *pCursorBitmap) = 0;
	virtual void __stdcall SetCursorPosition(int x, int y, DWORD flags) = 0;
	virtual int __stdcall ShowCursor(int bShow) = 0;
	virtual HRESULT __stdcall CreateAdditionalSwapChain(void *pPresentationParameters, void **pSwapChain) = 0;
	virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, void **pSwapChain) = 0;
	virtual UINT __stdcall GetNumberOfSwapChains(void) = 0;
	virtual HRESULT __stdcall Reset(void *pPresentationParameters) = 0;
	virtual HRESULT __stdcall Present(const void *pSourceRect, const void *pDestRect, void *hDestWindowOverride, const void *pDirtyRegion) = 0;
	virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, DWORD type, void **ppBackBuffer) = 0;
	virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, void *pRasterStatus) = 0;
	virtual HRESULT __stdcall SetDialogBoxMode(int bEnableDialogs) = 0;
	virtual void __stdcall SetGammaRamp(UINT iSwapChain, DWORD flags, const void *pRamp) = 0;
	virtual void __stdcall GetGammaRamp(UINT iSwapChain, void *pRamp) = 0;
	virtual HRESULT __stdcall CreateTexture(void) = 0;
	virtual HRESULT __stdcall CreateVolumeTexture(void) = 0;
	virtual HRESULT __stdcall CreateCubeTexture(void) = 0;
	virtual HRESULT __stdcall CreateVertexBuffer(void) = 0;
	virtual HRESULT __stdcall CreateIndexBuffer(void) = 0;
	virtual HRESULT __stdcall CreateRenderTarget(void) = 0;
	virtual HRESULT __stdcall CreateDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall UpdateSurface(void) = 0;
	virtual HRESULT __stdcall UpdateTexture(void) = 0;
	virtual HRESULT __stdcall GetRenderTargetData(void) = 0;
	virtual HRESULT __stdcall GetFrontBufferData(void) = 0;
	virtual HRESULT __stdcall StretchRect(void) = 0;
	virtual HRESULT __stdcall ColorFill(void) = 0;
	virtual HRESULT __stdcall CreateOffscreenPlainSurface(void) = 0;
	virtual HRESULT __stdcall SetRenderTarget(void) = 0;
	virtual HRESULT __stdcall GetRenderTarget(void) = 0;
	virtual HRESULT __stdcall SetDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall GetDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall BeginScene(void) = 0;
	virtual HRESULT __stdcall EndScene(void) = 0;
	virtual HRESULT __stdcall Clear(void) = 0;
	virtual HRESULT __stdcall SetTransform(DWORD state, const D3DMATRIX *pMatrix) = 0;
	virtual HRESULT __stdcall GetTransform(void) = 0;
	virtual HRESULT __stdcall MultiplyTransform(void) = 0;
	virtual HRESULT __stdcall SetViewport(void) = 0;
	virtual HRESULT __stdcall GetViewport(void) = 0;
	virtual HRESULT __stdcall SetMaterial(void) = 0;
	virtual HRESULT __stdcall GetMaterial(void) = 0;
	virtual HRESULT __stdcall SetLight(void) = 0;
	virtual HRESULT __stdcall GetLight(void) = 0;
	virtual HRESULT __stdcall LightEnable(void) = 0;
	virtual HRESULT __stdcall GetLightEnable(void) = 0;
	virtual HRESULT __stdcall SetClipPlane(void) = 0;
	virtual HRESULT __stdcall GetClipPlane(void) = 0;
	virtual HRESULT __stdcall SetRenderState(DWORD state, DWORD value) = 0;
	virtual HRESULT __stdcall GetRenderState(DWORD state, DWORD *pValue) = 0;
	virtual HRESULT __stdcall CreateStateBlock(void) = 0;
	virtual HRESULT __stdcall BeginStateBlock(void) = 0;
	virtual HRESULT __stdcall EndStateBlock(void) = 0;
	virtual HRESULT __stdcall SetClipStatus(void) = 0;
	virtual HRESULT __stdcall GetClipStatus(void) = 0;
	virtual HRESULT __stdcall GetTexture(void) = 0;
	virtual HRESULT __stdcall SetTexture(void) = 0;
	virtual HRESULT __stdcall GetTextureStageState(void) = 0;
	virtual HRESULT __stdcall SetTextureStageState(void) = 0;
	virtual HRESULT __stdcall GetSamplerState(void) = 0;
	virtual HRESULT __stdcall SetSamplerState(void) = 0;
	virtual HRESULT __stdcall ValidateDevice(void) = 0;
	virtual HRESULT __stdcall SetPaletteEntries(void) = 0;
	virtual HRESULT __stdcall GetPaletteEntries(void) = 0;
	virtual HRESULT __stdcall SetCurrentTexturePalette(void) = 0;
	virtual HRESULT __stdcall GetCurrentTexturePalette(void) = 0;
	virtual HRESULT __stdcall SetScissorRect(void) = 0;
	virtual HRESULT __stdcall GetScissorRect(void) = 0;
	virtual HRESULT __stdcall SetSoftwareVertexProcessing(void) = 0;
	virtual int __stdcall GetSoftwareVertexProcessing(void) = 0;
	virtual HRESULT __stdcall SetNPatchMode(void) = 0;
	virtual float __stdcall GetNPatchMode(void) = 0;
	virtual HRESULT __stdcall DrawPrimitive(void) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitive(DWORD type, int baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount) = 0;
	virtual HRESULT __stdcall DrawPrimitiveUP(void) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitiveUP(void) = 0;
	virtual HRESULT __stdcall ProcessVertices(void) = 0;
	virtual HRESULT __stdcall CreateVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall SetVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall GetVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall SetFVF(DWORD fvf) = 0;
	virtual HRESULT __stdcall GetFVF(DWORD *pFVF) = 0;
	virtual HRESULT __stdcall CreateVertexShader(void) = 0;
	virtual HRESULT __stdcall SetVertexShader(void *pShader) = 0;
	virtual HRESULT __stdcall GetVertexShader(void) = 0;
	virtual HRESULT __stdcall SetVertexShaderConstantF(void) = 0;
	virtual HRESULT __stdcall GetVertexShaderConstantF(void) = 0;
	virtual HRESULT __stdcall SetVertexShaderConstantI(void) = 0;
	virtual HRESULT __stdcall GetVertexShaderConstantI(void) = 0;
	virtual HRESULT __stdcall SetVertexShaderConstantB(void) = 0;
	virtual HRESULT __stdcall GetVertexShaderConstantB(void) = 0;
	virtual HRESULT __stdcall SetStreamSource(UINT streamNumber, IDirect3DVertexBuffer8 *pStreamData, UINT offsetInBytes, UINT stride) = 0;
	virtual HRESULT __stdcall GetStreamSource(void) = 0;
	virtual HRESULT __stdcall SetStreamSourceFreq(void) = 0;
	virtual HRESULT __stdcall GetStreamSourceFreq(void) = 0;
	virtual HRESULT __stdcall SetIndices(IDirect3DIndexBuffer8 *pIndexData) = 0;
};
typedef IDirect3DDevice8 *LPDIRECT3DDEVICE8;
class Vector4
{
public:
	Vector4(void) {}
	__forceinline Vector4(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Vector4(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	Real &operator[](int i) { return (&X)[i]; }
	const Real &operator[](int i) const { return (&X)[i]; }
	Real X, Y, Z, W;
};

class Matrix3D
{
public:
	const Vector4 &operator[](int i) const { return Row[i]; }
protected:
	Vector4 Row[3];
};

class Matrix4
{
public:
	__forceinline explicit Matrix4(const Matrix3D &m) { Init(m); }
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3) { Init(r0, r1, r2, r3); }
	__forceinline void Init(const Matrix3D &m)
	{
		Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0,0.0,0.0,1.0);
	}
	__forceinline void Init(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}
	__forceinline Matrix4 Transpose(void) const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3])
		);
	}
protected:
	Vector4 Row[4];
};
typedef Matrix4 Matrix4x4;

class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
private:
	unsigned ShaderBits;
};

namespace Debug_Statistics
{
	void Record_DX8_Polys_And_Vertices(int polys, int vertices, const ShaderClass &shader);
}

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
	static bool _Is_Triangle_Draw_Enabled(void) { return _EnableTriangleDraw; }
	static void Set_DX8_Render_State(DWORD state, unsigned value);
private:
	static IDirect3DDevice8 *D3DDevice;
	static bool _EnableTriangleDraw;
};

class W3DShadowManager
{
public:
	unsigned getStencilShadowMask(void) { return m_stencilShadowMask; }
private:
	void *m_vtable;
	unsigned m_shadowColor;
	unsigned m_stencilShadowMask;
};
extern W3DShadowManager *TheW3DShadowManager;

class FVFInfoClass
{
public:
	unsigned Get_FVF_Size(void) const { return fvf_size; }
private:
	char m_pad[0xc];
	unsigned fvf_size;
};

class DX8VertexBufferClass
{
public:
	const FVFInfoClass &FVF_Info(void) const { return *fvf_info; }
	IDirect3DVertexBuffer8 *Get_DX8_Vertex_Buffer(void) { return VertexBuffer; }
private:
	char m_pad[0x14];
	FVFInfoClass *fvf_info;
	char m_pad18[4];
	IDirect3DVertexBuffer8 *VertexBuffer;
};

class DX8IndexBufferClass
{
public:
	IDirect3DIndexBuffer8 *Get_DX8_Index_Buffer(void) { return index_buffer; }
private:
	char m_pad[0x14];
	IDirect3DIndexBuffer8 *index_buffer;
};

class W3DBufferManager
{
public:
	struct W3DVertexBuffer
	{
		char m_pad[0x14];
		DX8VertexBufferClass *m_DX8VertexBuffer;
	};
	struct W3DIndexBuffer
	{
		char m_pad[0x10];
		DX8IndexBufferClass *m_DX8IndexBuffer;
	};
	struct W3DVertexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DVertexBuffer *m_VB;
	};
	struct W3DIndexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DIndexBuffer *m_IB;
	};
};

class Geometry
{
public:
	Int GetNumActivePolygon(void) const { return m_numActivePolygon; }
	Int GetNumActiveVertex(void) const { return m_numActiveVertex; }
private:
	char m_pad[0x10];
	Int m_numActivePolygon;
	Int m_numActiveVertex;
};

#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

class W3DVolumetricShadow
{
protected:
	void RenderMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform);
	void *m_vtable;
	char m_pad4[0x30];
	Int m_stencilFlags;
	char m_pad38[0x48];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
};

static IDirect3DVertexBuffer8 *lastActiveVertexBuffer = 0;

void W3DVolumetricShadow::RenderMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform)
{
	LPDIRECT3DDEVICE8 m_pDev = DX8Wrapper::_Get_D3D_Device8();
	if (!m_pDev)
		return;

	Int stencilIndex = (m_stencilFlags >> 7) & 7;
	if (stencilIndex)
	{
		unsigned stencilRef = stencilIndex << 4;
		unsigned stencilMask = stencilRef;
		stencilMask = (stencilMask << 8) | stencilRef;
		stencilMask = (stencilMask << 8) | stencilRef;
		stencilMask = (stencilMask << 8) | TheW3DShadowManager->getStencilShadowMask();
		stencilMask |= stencilRef;
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, stencilMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, stencilRef);
	}

	Geometry *geometry = m_shadowVolume[lightIndex][meshIndex];
	Int numVerts = geometry->GetNumActiveVertex();
	Int numPolys = geometry->GetNumActivePolygon();
	if (!numVerts || !numPolys)
		return;

	Matrix4x4 mWorld(*meshXform);
	m_pDev->SetTransform(D3DTS_WORLD, (D3DMATRIX *)&mWorld.Transpose());

	W3DBufferManager::W3DVertexBufferSlot *vbSlot = m_shadowVolumeVB[lightIndex][meshIndex];
	if (!vbSlot)
		return;
	if (vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer() != lastActiveVertexBuffer)
	{
		lastActiveVertexBuffer = vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer();
		m_pDev->SetStreamSource(0, lastActiveVertexBuffer, 0,
			vbSlot->m_VB->m_DX8VertexBuffer->FVF_Info().Get_FVF_Size());
	}

	W3DBufferManager::W3DIndexBufferSlot *ibSlot = m_shadowVolumeIB[lightIndex][meshIndex];
	if (!ibSlot)
		return;
	m_pDev->SetIndices(ibSlot->m_IB->m_DX8IndexBuffer->Get_DX8_Index_Buffer());

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
	{
		Debug_Statistics::Record_DX8_Polys_And_Vertices(numPolys, numVerts, ShaderClass::_PresetOpaqueShader);
		m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vbSlot->m_start, 0, numVerts, ibSlot->m_start, numPolys);
	}

	if (stencilIndex)
	{
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, TheW3DShadowManager->getStencilShadowMask());
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
	}
}
