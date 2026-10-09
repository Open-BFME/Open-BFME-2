// ?rva000E8365@W3DShrubBuffer@@QAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib 
// W3DShrubBuffer::rva000E8365, retail 0x000E8365 (753 bytes): Zero Hour's
// updateVertexBuffer shape for shrubs, per locked vertex buffer re-transforms the
// vertices of every pushed-aside visible record. Donor: Open-BFME-1
// W3DShrubBufferRva0071D5E0.cpp (BFME1 0x0071D5E0). BFME2 facts read from
// retail: the buffer lists are vectors at +0x04 (vertex) / +0x1C (index) /
// +0x28 (index counts), 2000 records of 0xA0 at +0x1958 (count +0x4FB58),
// types of 0x5C at +0x4FB70, tree index step +0x51278, mesh model at +0xC4;
// the BFME1 darkening store is absent.
#include "vector3.h"
#include "matrix3d.h"

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertexBuffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array(void) { return m_vertices; }
	private:
		VertexBufferClass *m_vertexBuffer;
		void *m_vertices;
		int m_flags;
	};
};

struct VertexFormatXYZNDUV1
{
	float x, y, z;
	float nx, ny, nz;
	unsigned int diffuse;
	float u1, v1;
	float u2, v2;
};

struct Rva000E8365VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
};

struct Rva000E8365Model
{
	unsigned char m_head[0x28];
	int m_vertexCount;
	unsigned char m_gap2c[4];
	Rva000E8365VertexBuffer *m_vertexBuffer;
	int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexBuffer->m_array; }
};

class MeshClass
{
public:
	Rva000E8365Model *Peek_Model(void) const { return m_model; }
private:
	unsigned char m_head[0xc4];
	Rva000E8365Model *m_model;
};

struct Rva000E8365Data
{
	unsigned char m_head[0x18];
	float m_maxOutwardMovement;
};

struct Rva000E8365TreeType
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	unsigned char m_unreconstructed_10[0x10];
	const Rva000E8365Data *m_data;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

struct Rva000E8365Tree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	unsigned char m_unreconstructed_45[0x5c - 0x45];
	float pushAside;
	float pushAsideDelta;
	float pushAsideSin;
	float pushAsideCos;
	unsigned char m_unreconstructed_6c[0x7c - 0x6c];
	int firstIndex;
	int bufferNdx;
	int m_toppleState;
	unsigned char m_unreconstructed_88[0x9c - 0x88];
	int m_field9c;
};

template <class T> struct PtrVector
{
	T *start, *finish, *eos;
	T &operator[](unsigned n) { return start[n]; }
	unsigned size() const { return finish - start; }
};

class W3DShrubBuffer
{
public:
	void rva000E8365(void);

private:
	void *m_vtable;
	PtrVector<VertexBufferClass *> m_vertexTree;
	unsigned char m_unreconstructed_10[0x1c - 0x10];
	PtrVector<void *> m_indexTree;
	PtrVector<int> m_curNumTreeIndices;
	unsigned char m_unreconstructed_34[0x1958 - 0x34];
	Rva000E8365Tree m_trees[2000];
	int m_numTrees;
	bool m_anythingChanged;
	bool m_anyPushChanged;
	unsigned char m_unreconstructed_4fb5e[0x4fb6c - 0x4fb5e];
	bool m_initialized;
	unsigned char m_unreconstructed_4fb6d[3];
	Rva000E8365TreeType m_treeTypes[64];
	unsigned char m_unreconstructed_51270[8];
	int m_treeIndexStep;
};

// ?rva000E8365@W3DShrubBuffer@@QAEXXZ
void W3DShrubBuffer::rva000E8365(void)
{
	if (!m_initialized || !m_indexTree[0] || !m_vertexTree[0])
		return;
	for (unsigned bNdx = 0; bNdx < m_vertexTree.size(); bNdx++) {
		if (m_curNumTreeIndices[bNdx] == 0)
			break;
		VertexFormatXYZNDUV1 *vb;
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();

		for (int curTree = 0; curTree < m_numTrees; curTree += m_treeIndexStep) {
			if (m_trees[curTree].bufferNdx != (int)bNdx)
				continue;
			int type = m_trees[curTree].treeType;
			if (type < 0)
				continue;
			if (m_trees[curTree].pushAsideDelta == 0.0f)
				continue;
			m_anyPushChanged = true;
			if (!m_trees[curTree].visible)
				continue;
			if (m_trees[curTree].m_toppleState)
				continue;
			if (m_trees[curTree].m_field9c >= 4 || m_trees[curTree].m_field9c <= 0)
				continue;
			float scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			if (m_treeTypes[type].m_mesh == 0)
				type = 0;

			VertexFormatXYZNDUV1 *curVb = vb + m_trees[curTree].firstIndex;
			int numVertex = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();

			for (int i = 0; i < numVertex; i++) {
				float x = pVert[i].X;
				float y = pVert[i].Y;
				float z = pVert[i].Z;
				Vector3 vert(x, y, z);
				vert += m_treeTypes[type].m_offset;
				Vector3 vLoc;
				Matrix3D::Transform_Vector(m_trees[curTree].transform, vert, &vLoc);
				vLoc *= scale;

				if (m_trees[curTree].pushAside > 0.0f) {
					vLoc.X += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideCos * m_treeTypes[type].m_data->m_maxOutwardMovement;
					vLoc.Y += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideSin * m_treeTypes[type].m_data->m_maxOutwardMovement;
				}
				vLoc.X += loc.X;
				vLoc.Y += loc.Y;
				vLoc.Z += loc.Z;

				curVb->x = vLoc.X;
				curVb->y = vLoc.Y;
				curVb->z = vLoc.Z;
				curVb++;
			}
		}
	}
}
