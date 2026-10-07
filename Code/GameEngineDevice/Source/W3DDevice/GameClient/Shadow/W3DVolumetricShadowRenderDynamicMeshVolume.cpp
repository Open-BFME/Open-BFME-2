// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?RenderDynamicMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z @0x000F42FF 1745B.
//
// W3DVolumetricShadow::RenderDynamicMeshVolume: streams a dynamic shadow
// volume into the shared shadow vertex/index rings and draws it. Target
// evidence: retail 0x000F42FF..0x000F49D0 (EH frame, ret 0xC), called from
// RenderVolume (0x000F49D0). Stencil sub-mask as in RenderMeshVolume, but
// here through the inline DX8Wrapper::Set_DX8_Render_State (RenderStates
// 0x00DED5F8, snapshot flag 0x00DEC3FD, StringClass 0x00065F34/0x00610A40,
// value names 0x00121A10). Over-limit volumes (8192 vertices, 16384
// indices) are reported once per render object name: two function-local
// STLport set<AsciiString> statics (0x00DEBFE4/0x00DEBFD8, guard 0x00DEBFF0,
// atexit cleanups 0x007B6E7C/0x007B6E72) searched with the const char*
// find (0x000F2F5A) and filled through insert (0x0005897D); the report
// goes through theDebug (0x00DE0880) slots 0x60/0x6C/0x38/0x34/0x4C after
// _bfme_debugReportingEnabled (0x000387C0) and Debug::SkipNext
// (0x00038790). Rings: shadowVertexBufferD3D/shadowIndexBufferD3D
// 0x00DEBCDC/0x00DEBCE0 and counters 0x00DEBCE4..0x00DEBCF0; the index copy
// goes through Geometry::GetPolygonIndex (0x000EFC7A).
// Donor: Open-BFME-1 W3DVolumetricShadowRenderDynamicMeshVolume.cpp (ZH
// body plus BFME stencil bits and release diagnostics). BFME 2 deltas read
// from retail: render states through DX8Wrapper, the once-per-name sets.

#include "ascii_string.h"
#include <set>

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
typedef unsigned short UnsignedShort;
typedef bool Bool;

#define D3DTS_WORLD				256
#define D3DPT_TRIANGLELIST		4
#define D3DRS_STENCILREF		57
#define D3DRS_STENCILMASK		58
#define D3DLOCK_NOOVERWRITE		0x1000
#define D3DLOCK_DISCARD			0x2000
typedef DWORD D3DRENDERSTATETYPE;

#define SHADOW_VERTEX_SIZE	8192
#define SHADOW_INDEX_SIZE	16384


class Vector3 { public: Real X, Y, Z; };

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

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
private:
	void Free_String();
};

extern unsigned number_of_DX8_calls;

class WW3D
{
public:
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
	static bool _Is_Triangle_Draw_Enabled(void) { return _EnableTriangleDraw; }
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);

	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static bool _EnableTriangleDraw;
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
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

class Debug
{
public:
	static bool SkipNext(bool skip);
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30();
	virtual Debug &slot34(int value);
	virtual Debug &slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};
extern Debug *theDebug;
bool _bfme_debugReportingEnabled(void);

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual const char *Get_Name(void) const;
};

class Geometry
{
public:
	Int GetNumActivePolygon(void) { return m_numActivePolygon; }
	Int GetNumActiveVertex(void) { return m_numActiveVertex; }
	UnsignedShort *GetPolygonIndex(long dwPolyId, short *psIndexList) const
	{
		*psIndexList++ = m_indices[dwPolyId*3];
		*psIndexList++ = m_indices[dwPolyId*3+1];
		*psIndexList++ = m_indices[dwPolyId*3+2];
		return &m_indices[dwPolyId];
	}
	Vector3 *GetVertex(int dwVertId) { return &m_verts[dwVertId]; }
private:
	Vector3 *m_verts;
	UnsignedShort *m_indices;
	Int m_numPolygon;
	Int m_numVertex;
	Int m_numActivePolygon;
	Int m_numActiveVertex;
};

#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

class W3DVolumetricShadow
{
protected:
	void RenderDynamicMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform);
	void *m_vtable;
	char m_pad4[0x30];
	Int m_stencilFlags;
	char m_pad38[0x38];
	RenderObjClass *m_robj;
	char m_pad74[0xc];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
};

extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;
extern Int nShadowVertsInBuf;
extern Int nShadowStartBatchVertex;
extern Int nShadowIndicesInBuf;
extern Int nShadowStartBatchIndex;
static IDirect3DVertexBuffer8 *lastActiveVertexBuffer = 0;

void W3DVolumetricShadow::RenderDynamicMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform)
{
	Geometry *geometry;
	Int numVerts, numPolys, numIndex;
	Vector3 *pvVertices;
	UnsignedShort *pvIndices;
	LPDIRECT3DDEVICE8 m_pDev = DX8Wrapper::_Get_D3D_Device8();
	if (!m_pDev)
		return;

	Int stencilIndex = (m_stencilFlags >> 7) & 7;
	if (stencilIndex)
	{
		unsigned stencilMask = stencilIndex << 4;
		unsigned stencilRef = stencilIndex << 4;
		stencilMask |= (((stencilMask << 8) | stencilMask) << 8 | stencilMask) << 8 | TheW3DShadowManager->getStencilShadowMask();
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, stencilMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, stencilRef);
	}

	geometry = m_shadowVolume[lightIndex][meshIndex];
	numVerts = geometry->GetNumActiveVertex();
	numPolys = geometry->GetNumActivePolygon();
	numIndex = numPolys*3;
	if (numVerts == 0 || numPolys == 0)
		return;

	if (numVerts > SHADOW_VERTEX_SIZE)
	{
		static _STL::set<AsciiString> vertexWarned;
		if (vertexWarned.find(m_robj->Get_Name()) == vertexWarned.end())
		{
			if (_bfme_debugReportingEnabled())
			{
				Debug::SkipNext(true);
				theDebug->slot60();
				theDebug->slot6C(0, 0, 0).slot38("Shadow geometry for ").slot38(m_robj->Get_Name()).slot38(" has too many vertices (").slot34(numVerts).slot38(" with a limit of ").slot34(SHADOW_VERTEX_SIZE).slot38("). Either reduce the geometric complexity or have engineering increase SHADOW_VERTEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]").slot4C(2);
			}
			vertexWarned.insert(m_robj->Get_Name());
		}
		return;
	}
	if (numIndex > SHADOW_INDEX_SIZE)
	{
		static _STL::set<AsciiString> indexWarned;
		if (indexWarned.find(m_robj->Get_Name()) == indexWarned.end())
		{
			if (_bfme_debugReportingEnabled())
			{
				Debug::SkipNext(true);
				theDebug->slot60();
				theDebug->slot6C(0, 0, 0).slot38("Shadow geometry for ").slot38(m_robj->Get_Name()).slot38(" has too many indices (").slot34(numIndex).slot38(" with a limit of ").slot34(SHADOW_INDEX_SIZE).slot38("). Either reduce the geometric complexity or have engineering increase SHADOW_INDEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]").slot4C(2);
			}
			indexWarned.insert(m_robj->Get_Name());
		}
		return;
	}

	if (nShadowVertsInBuf > SHADOW_VERTEX_SIZE-numVerts)
	{
		if (shadowVertexBufferD3D->Lock(0, numVerts*sizeof(Vector3), (unsigned char**)&pvVertices, D3DLOCK_DISCARD) != 0)
			return;
		nShadowVertsInBuf = 0;
		nShadowStartBatchVertex = 0;
	}
	else
	{
		if (shadowVertexBufferD3D->Lock(nShadowVertsInBuf*sizeof(Vector3), numVerts*sizeof(Vector3), (unsigned char**)&pvVertices, D3DLOCK_NOOVERWRITE) != 0)
			return;
	}
	if (pvVertices)
		memcpy(pvVertices, geometry->GetVertex(0), numVerts*sizeof(Vector3));
	shadowVertexBufferD3D->Unlock();

	if (nShadowIndicesInBuf > SHADOW_INDEX_SIZE-numIndex)
	{
		if (shadowIndexBufferD3D->Lock(0, numIndex*sizeof(short), (unsigned char**)&pvIndices, D3DLOCK_DISCARD) != 0)
			return;
		nShadowIndicesInBuf = 0;
		nShadowStartBatchIndex = 0;
	}
	else
	{
		if (shadowIndexBufferD3D->Lock(nShadowIndicesInBuf*sizeof(short), numIndex*sizeof(short), (unsigned char**)&pvIndices, D3DLOCK_NOOVERWRITE) != 0)
			return;
	}
	if (pvIndices)
		memcpy(pvIndices, geometry->GetPolygonIndex(0, (short *)pvIndices), numPolys*3*sizeof(short));
	shadowIndexBufferD3D->Unlock();

	m_pDev->SetIndices(shadowIndexBufferD3D);
	Matrix4x4 mWorld(*meshXform);
	m_pDev->SetTransform(D3DTS_WORLD, (D3DMATRIX *)&mWorld.Transpose());

	if (shadowVertexBufferD3D != lastActiveVertexBuffer)
	{
		m_pDev->SetStreamSource(0, shadowVertexBufferD3D, 0, sizeof(Vector3));
		lastActiveVertexBuffer = shadowVertexBufferD3D;
	}

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
	{
		Debug_Statistics::Record_DX8_Polys_And_Vertices(numPolys, numVerts, ShaderClass::_PresetOpaqueShader);
		m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nShadowStartBatchVertex, 0, numVerts, nShadowStartBatchIndex, numPolys);
	}

	if (stencilIndex)
	{
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, TheW3DShadowManager->getStencilShadowMask());
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
	}

	nShadowVertsInBuf += numVerts;
	nShadowStartBatchVertex = nShadowVertsInBuf;
	nShadowIndicesInBuf += numIndex;
	nShadowStartBatchIndex = nShadowIndicesInBuf;
}

// ??$find@PBD@?$set@VAsciiString@@U?$less@VAsciiString@@@_STL@@V?$allocator@VAsciiString@@@3@@_STL@@QBE?AU?$_Rb_tree_iterator@VAsciiString@@U?$_Const_traits@VAsciiString@@@_STL@@@1@ABQBD@Z @0x000F4003 20B.
// The out-of-line const char* find of the warning sets (forwards to
// _M_find 0x000F2F5A); retail keeps this unit's copy at 0x000F4003.
template _STL::set<AsciiString>::iterator _STL::set<AsciiString>::find<const char *>(const char * const &) const;
