// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// platformsdk
// dxsdk
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"

// BFME1 34f59164 BfmeVolumetricShadowBufferEntryUpdate.cpp semantic lead.
// Target107961..107A50 full239 RET0; existing matched107E76 calls this
// on a24-byte Submesh entry. Native independently proves mesh modelC4,
// transform18, flags18/bit400, count28, vertex-holder30/data0C, vslot20,
// and the matched MeshClass::Get_Deformed_Vertices149A10.
// WB UpdateWorldSpaceVertices is a callgraph lead, so retain the neutral
// method identity already pinned by the matched caller.
#include "matrix4.h"
#include <d3dx9math.h>

struct BfmeShadowShareBuffer
{
	unsigned char m_pad[0xc];
	Vector3 *m_data;
};

struct MeshClassModel
{
	unsigned char m_beforeFlags[0x18];
	unsigned int m_flags;
	unsigned char m_betweenFlagsAndVertexCount[0xc];
	int m_vertexCount;
	unsigned char m_betweenVertexCountAndVertex[4];
	BfmeShadowShareBuffer *m_vertex;

	Vector3 *Get_Vertex_Array()
	{
		return m_vertex->m_data;
	}

	int Get_Vertex_Count() const
	{
		return m_vertexCount;
	}
};

class MeshClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void Validate_Transform() const;

	unsigned char m_beforeTransform[0x14];
	Matrix3D m_transform;
	unsigned char m_betweenTransformAndField84[0x3c];
	unsigned int m_field84;
	unsigned char m_betweenField84AndModel[0x3c];
	MeshClassModel *m_model;

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}

	MeshClassModel *Peek_Model() const
	{
		return m_model;
	}

	// Already matched target149A10, 64B. Declaration only.
	__declspec(noinline) void Get_Deformed_Vertices(Vector3 *dst);
};

// Native import thunk62AF6E names D3DXVec3TransformCoordArray (@24);
// <d3dx9math.h> declares it.

struct Rva00107E76Elem
{
	MeshClass *m_mesh;
	void *m_allocation0;
	void *m_allocation1;
	void *m_allocation2;
	unsigned int m_reserved10;
	unsigned char m_reserved14;

	void rva00107961();
};

void Rva00107E76Elem::rva00107961()
{
	if ((m_mesh->m_model->m_flags & 0x400) != 0)
	{
		m_mesh->Get_Deformed_Vertices((Vector3 *)m_allocation0);
		return;
	}

	Matrix4 matrix(m_mesh->Get_Transform());
	D3DXVec3TransformCoordArray(
		(D3DXVECTOR3 *)m_allocation0, 0xc,
		(const D3DXVECTOR3 *)m_mesh->Peek_Model()->Get_Vertex_Array(), 0xc,
		(D3DXMATRIX *)&matrix.Transpose(),
		m_mesh->Peek_Model()->Get_Vertex_Count());
}

