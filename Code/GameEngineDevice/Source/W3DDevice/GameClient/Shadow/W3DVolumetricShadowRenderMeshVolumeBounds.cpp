// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
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
#include <d3d9.h>

typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;


struct IDirect3DDevice8;
struct IDirect3DVertexBuffer8;
struct IDirect3DIndexBuffer8;
// The device and buffers keep their D3D8 type names (the decorations of
// DX8Wrapper::D3DDevice, the shadow buffers and the WW3D buffer classes) but
// are Direct3D 9 objects: SetTransform 44, DrawIndexedPrimitive 82,
// SetStreamSource 100, SetIndices 104; buffer Lock / Unlock 11 / 12.
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

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

class Matrix4
{
public:
	__declspec(dllimport) __forceinline Matrix4(bool identity) { if (identity) Make_Identity(); }
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
	static __declspec(dllimport) __forceinline IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
protected:
	static IDirect3DDevice8 *D3DDevice;
};

#define DX8CALL(x) reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->x; number_of_DX8_calls++;

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
// Owned here: the dynamic shadow-volume index buffer and its fill count;
// retail .data starts them at 0 (VA 0x009EBCE0/0x009EBCEC).
IDirect3DIndexBuffer8 *shadowIndexBufferD3D = 0;
extern Int nShadowVertsInBuf;
// Owned here: written below; retail .data starts it at 0 (VA 0x009EBCE4).
Int nShadowVertsInBuf = 0;
extern Int nShadowStartBatchVertex;
extern Int nShadowIndicesInBuf;
Int nShadowIndicesInBuf = 0;
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
	IDirect3DDevice9 *m_pDev=reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());

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
		if (reinterpret_cast<IDirect3DVertexBuffer9 *>(shadowVertexBufferD3D)->Lock(0,numVerts*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX),(void **)&pvVertices,D3DLOCK_DISCARD) != D3D_OK)
			return;
		nShadowVertsInBuf=0;
		nShadowStartBatchVertex=0;
	}
	else
	{	if (reinterpret_cast<IDirect3DVertexBuffer9 *>(shadowVertexBufferD3D)->Lock(nShadowVertsInBuf*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX),numVerts*sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX), (void **)&pvVertices,D3DLOCK_NOOVERWRITE) != D3D_OK)
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

	reinterpret_cast<IDirect3DVertexBuffer9 *>(shadowVertexBufferD3D)->Unlock();

	if (nShadowIndicesInBuf > (SHADOW_INDEX_SIZE-numIndex))	//check if room for model verts
	{	//flush the buffer by drawing the contents and re-locking again
		if (reinterpret_cast<IDirect3DIndexBuffer9 *>(shadowIndexBufferD3D)->Lock(0,numIndex*sizeof(short),(void **)&pvIndices,D3DLOCK_DISCARD) != D3D_OK)
			return;;
		nShadowIndicesInBuf=0;
		nShadowStartBatchIndex=0;
	}
	else
	{	if (reinterpret_cast<IDirect3DIndexBuffer9 *>(shadowIndexBufferD3D)->Lock(nShadowIndicesInBuf*sizeof(short),numIndex*sizeof(short), (void **)&pvIndices,D3DLOCK_NOOVERWRITE) != D3D_OK)
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

	reinterpret_cast<IDirect3DIndexBuffer9 *>(shadowIndexBufferD3D)->Unlock();

	m_pDev->SetIndices(reinterpret_cast<IDirect3DIndexBuffer9 *>(shadowIndexBufferD3D));

	//todo: replace this with mesh transform
	//identity since boxes are pre-transformed to world space.
	m_pDev->SetTransform(D3DTS_WORLD, (D3DMATRIX *)&Matrix4x4(1));

	m_pDev->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9 *>(shadowVertexBufferD3D), 0, sizeof(SHADOW_DYNAMIC_VOLUME_VERTEX));
	DX8CALL(SetFVF(SHADOW_DYNAMIC_VOLUME_FVF));

	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nShadowStartBatchVertex, 0, numVerts, nShadowStartBatchIndex, numPolys);

	nShadowVertsInBuf += numVerts;
	nShadowStartBatchVertex=nShadowVertsInBuf;

	nShadowIndicesInBuf += numIndex;
	nShadowStartBatchIndex=nShadowIndicesInBuf;
}
