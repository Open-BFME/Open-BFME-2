// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?RenderMeshVolumeBounds@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z @0x000F2203 1241B.
//
// W3DVolumetricShadow::RenderMeshVolumeBounds: debug draw of a shadow
// volume's bounding box. Target evidence: retail 0x000F2203..0x000F26DC
// (plain frame, ret 0xC): three guarded function statics (the +-1 box
// corners at 0x00DEBF30, the twelve faces at 0x00DEBEA0 and the world-space
// corners at 0x00DEBE40), the shadow volume read from this+0x80 with 160
// meshes per light, the shared dynamic vertex/index buffers
// (0x00DEBCDC/0x00DEBCE0) and their fill counters 0x00DEBCE4..0x00DEBCF0
// locked through slot 11 and unlocked through slot 12, srand through the
// CRT import, then IDirect3DDevice9 SetIndices (+0x1A0), SetTransform
// (+0xB0), SetStreamSource (+0x190), SetFVF through DX8Wrapper's device
// (+0x164, counted in number_of_DX8_calls) and DrawIndexedPrimitive
// (+0x148).
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp RenderMeshVolumeBounds
// (0x007BC8B0), itself the ZH body. BFME 2 deltas read from retail: the
// identity world matrix is a temporary built in the SetTransform argument
// and passed untransposed, and SetFVF goes through DX8CALL.

#include <stdlib.h>

typedef unsigned long DWORD;
typedef long HRESULT;
typedef unsigned int UINT;
typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

#define D3D_OK					0
#define D3DLOCK_NOOVERWRITE		0x00001000L
#define D3DLOCK_DISCARD			0x00002000L
#define D3DTS_WORLD				256
#define D3DPT_TRIANGLELIST		4
#define D3DFVF_XYZ				0x002

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
class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real &operator[](int i) { return (&X)[i]; }
	const Real &operator[](int i) const { return (&X)[i]; }
	Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	Real X, Y, Z;
};

class Vector3i
{
public:
	Vector3i(void) {}
	Vector3i(int i, int j, int k) { I = i; J = j; K = k; }
	int &operator[](int n) { return (&I)[n]; }
	const int &operator[](int n) const { return (&I)[n]; }
	int I, J, K;
};

class Vector4
{
public:
	void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	Real X, Y, Z, W;
};

class Matrix4
{
public:
	__forceinline Matrix4(bool identity) { if (identity) Make_Identity(); }
	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f,0.0f,0.0f,0.0f);
		Row[1].Set(0.0f,1.0f,0.0f,0.0f);
		Row[2].Set(0.0f,0.0f,1.0f,0.0f);
		Row[3].Set(0.0f,0.0f,0.0f,1.0f);
	}
protected:
	Vector4 Row[4];
};
typedef Matrix4 Matrix4x4;

class Matrix3D
{
public:
	void Get_Translation(Vector3 *set) const { set->X = Row[0].W; set->Y = Row[1].W; set->Z = Row[2].W; }
protected:
	Vector4 Row[3];
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class Geometry
{
public:
	AABoxClass &getBoundingBox(void) { return m_boundingBox; }
private:
	char m_pad[0x1c];
	AABoxClass m_boundingBox;
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
private:
	static IDirect3DDevice8 *D3DDevice;
};

#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;

#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

class W3DVolumetricShadow
{
protected:
	void RenderMeshVolumeBounds(Int meshIndex, Int lightIndex, const Matrix3D *meshXform);
	void *m_vtable;
	char m_pad4[0x7c];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
};

struct SHADOW_DYNAMIC_VOLUME_VERTEX
{
	float x, y, z;
};
#define SHADOW_DYNAMIC_VOLUME_FVF	D3DFVF_XYZ

#define SHADOW_VERTEX_SIZE	8192
#define SHADOW_INDEX_SIZE	16384

extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
// Owned here: the dynamic shadow-volume vertex buffer; retail .data starts
// it at 0 (VA 0x009EBCDC).
IDirect3DVertexBuffer8 *shadowVertexBufferD3D = 0;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;
extern Int nShadowVertsInBuf;
extern Int nShadowStartBatchVertex;
extern Int nShadowIndicesInBuf;
extern Int nShadowStartBatchIndex;

/** Debug function to draw bounding boxes around shadow volumes */
void W3DVolumetricShadow::RenderMeshVolumeBounds(Int meshIndex, Int lightIndex, const Matrix3D *meshXform)
{
	Geometry *geometry;
	Int numVerts, numPolys, numIndex;
	SHADOW_DYNAMIC_VOLUME_VERTEX* pvVertices;
	UnsignedShort *pvIndices;
	// Vertex Positions as a function of the box extents
	static Vector3						_BoxVerts[8] = 
	{
		Vector3(  1.0f, 1.0f, 1.0f ),		// +z ring of 4 verts
		Vector3( -1.0f, 1.0f, 1.0f ),
		Vector3( -1.0f,-1.0f, 1.0f ),
		Vector3(  1.0f,-1.0f, 1.0f ),

		Vector3(  1.0f, 1.0f,-1.0f ),		// -z ring of 4 verts;
		Vector3( -1.0f, 1.0f,-1.0f ),
		Vector3( -1.0f,-1.0f,-1.0f ),
		Vector3(  1.0f,-1.0f,-1.0f ),
	};
	// Face Connectivity
	static Vector3i					_BoxFaces[12] = 
	{
		Vector3i( 0,1,2 ),		// +z faces
		Vector3i( 0,2,3 ),		
		Vector3i( 4,7,6 ),		// -z faces
		Vector3i( 4,6,5 ),
		Vector3i( 0,3,7 ),		// +x faces
		Vector3i( 0,7,4 ),
		Vector3i( 1,5,6 ),		// -x faces
		Vector3i( 1,6,2 ),
		Vector3i( 4,5,1 ),		// +y faces
		Vector3i( 4,1,0 ),
		Vector3i( 3,2,6 ),		// -y faces
		Vector3i( 3,6,7 )
	};

	static Vector3 verts[8];

	//Get D3D Device used by W3D for quicker access.
	LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();

	if (!m_pDev)
		return;

	Vector3 meshPosition;
	meshXform->Get_Translation(&meshPosition);	//current mesh position

	geometry = m_shadowVolume[lightIndex][ meshIndex ];
	AABoxClass &aab=geometry->getBoundingBox();

	// compute the vertex positions
	meshPosition += aab.Center;	//get world space position of bounding box

	for (int ivert=0; ivert<8; ivert++)
	{
		verts[ivert].X = meshPosition.X + _BoxVerts[ivert][0] * aab.Extent.X;
		verts[ivert].Y = meshPosition.Y + _BoxVerts[ivert][1] * aab.Extent.Y;
		verts[ivert].Z = meshPosition.Z + _BoxVerts[ivert][2] * aab.Extent.Z;
	}

	// get geometry requirements
	numVerts = 8;
	numPolys = 12;
	numIndex = numPolys * 3;

	// reject shadows with no data
	if( numVerts == 0 || numPolys == 0 )
		return;


	if (nShadowVertsInBuf > (SHADOW_VERTEX_SIZE-numVerts))	//check if room for model verts
	{	//flush the buffer by drawing the contents and re-locking again
		if (shadowVertexBufferD3D->Lock(0,numVerts*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX),(unsigned char**)&pvVertices,D3DLOCK_DISCARD) != D3D_OK)
			return;
		nShadowVertsInBuf=0;
		nShadowStartBatchVertex=0;
	}
	else
	{	if (shadowVertexBufferD3D->Lock(nShadowVertsInBuf*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX),numVerts*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX), (unsigned char**)&pvVertices,D3DLOCK_NOOVERWRITE) != D3D_OK)
			return;
	}
	srand(0x1345465);
	if(pvVertices)
	{	for (Int i=0; i<8; i++)
		{
			pvVertices->x=verts[i][0];
			pvVertices->y=verts[i][1];
			pvVertices->z=verts[i][2];
			pvVertices++;
		}
	}

	shadowVertexBufferD3D->Unlock();

	if (nShadowIndicesInBuf > (SHADOW_INDEX_SIZE-numIndex))	//check if room for model verts
	{	//flush the buffer by drawing the contents and re-locking again
		if (shadowIndexBufferD3D->Lock(0,numIndex*sizeof(short),(unsigned char**)&pvIndices,D3DLOCK_DISCARD) != D3D_OK)
			return;;
		nShadowIndicesInBuf=0;
		nShadowStartBatchIndex=0;
	}
	else
	{	if (shadowIndexBufferD3D->Lock(nShadowIndicesInBuf*sizeof(short),numIndex*sizeof(short), (unsigned char**)&pvIndices,D3DLOCK_NOOVERWRITE) != D3D_OK)
			return;
	}


	if(pvIndices)
	{
		for (Int i=0; i<numPolys; i++,pvIndices+=3)
		{
			pvIndices[0] = _BoxFaces[i][0];
			pvIndices[1] = _BoxFaces[i][1];
			pvIndices[2] = _BoxFaces[i][2];
		}
	}

	shadowIndexBufferD3D->Unlock();

	m_pDev->SetIndices(shadowIndexBufferD3D);

	//todo: replace this with mesh transform
	//identity since boxes are pre-transformed to world space.
	m_pDev->SetTransform(D3DTS_WORLD, (D3DMATRIX *)&Matrix4x4(1));

	m_pDev->SetStreamSource(0, shadowVertexBufferD3D, 0, sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX));
	DX8CALL(SetFVF(SHADOW_DYNAMIC_VOLUME_FVF));

	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nShadowStartBatchVertex, 0, numVerts, nShadowStartBatchIndex, numPolys);

	nShadowVertsInBuf += numVerts;
	nShadowStartBatchVertex=nShadowVertsInBuf;

	nShadowIndicesInBuf += numIndex;
	nShadowStartBatchIndex=nShadowIndicesInBuf;
}
