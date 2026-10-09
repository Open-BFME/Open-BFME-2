// ?rva000E7DF3@W3DShrubBuffer@@QAEXXZ
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib 
// W3DShrubBuffer::rva000E7DF3, retail 0x000E7DF3 (1394 bytes): Zero Hour's
// loadTreesInVertexAndIndexBuffers shape for shrubs (WorldBuilder name
// loadShrubsInVertexAndIndexBuffers). Per buffer it locks the index and vertex
// buffers (12-byte locks, no flags) and appends the vertices and triangles of
// every upright visible record whose mesh is loaded, stopping at 30000
// vertices / 60000 indices. BFME2 layout read from retail: buffer lists are
// vectors at +0x04 (vertex buffers), +0x10 (vertex counts), +0x1C (index
// buffers), +0x28 (index counts); 2000 records of 0xA0 at +0x1958 (count
// +0x4FB58, changed +0x4FB5C, initialized +0x4FB6C), types of 0x5C at +0x4FB70,
// tree index step +0x51278. Vertex is 0x2C bytes: position, normal, diffuse,
// one UV set, sway and the tree's pivot height.
#include "vector3.h"
#include "matrix3d.h"


struct TriIndex { unsigned short I, J, K; };

extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		BFMEDX8DeviceLock device_lock;
		unsigned short *indices;
		IndexBufferClass *index_buffer;
	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags = 0);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return indices; }
	};
};

class VertexBufferClass
{
public:
	class WriteLockClass
	{
		BFMEDX8DeviceLock device_lock;
		void *Vertices;
		VertexBufferClass *VertexBuffer;
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags = 0);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }
	};
};

// Retail 0x0016AB90 (ledger name BfmeC998::bfmeGo998C): the model's vertex normal getter.


struct Rva000E7DF3Vertex
{
	float x, y, z;
	float nx, ny, nz;
	unsigned int diffuse;
	float u1, v1;
	float sway;
	float pivotZ;
};

struct Rva000E7DF3ArrayHolder
{
	unsigned char m_head[0x0c];
	void *m_array;
};

class BfmeC998 { public: int bfmeGo998C(int); };

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array(int pass, int stage);
	unsigned char m_head[0x0c];
	int m_uvSourceCount;
	Rva000E7DF3ArrayHolder *m_uv0;
	unsigned char m_gap14[0x50 - 0x14];
	Rva000E7DF3ArrayHolder *m_color0;
};

struct Rva000E7DF3Model
{
	unsigned char m_head[0x24];
	int m_polyCount;
	int m_vertexCount;
	Rva000E7DF3ArrayHolder *m_polys;
	Rva000E7DF3ArrayHolder *m_vertices;
	unsigned char m_gap34[0x94 - 0x34];
	MeshMatDescClass *m_matDesc;

	int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return (Vector3 *)m_vertices->m_array; }
	int Get_Polygon_Count(void) const { return m_polyCount; }
	const TriIndex *Get_Polygon_Array(void) const { return (const TriIndex *)m_polys->m_array; }
	__forceinline const Vector2 *Get_UV_Array_By_Index(int)
	{
		if (m_matDesc->m_uvSourceCount != 0)
			return m_matDesc->Get_UV_Array(0, 0);
		return m_matDesc->m_uv0 ? (const Vector2 *)m_matDesc->m_uv0->m_array : 0;
	}
	__forceinline const Vector3 *Get_Vertex_Normal_Array(void) { return (const Vector3 *)((BfmeC998 *)this)->bfmeGo998C(0); }
	__forceinline const unsigned *Get_Color_Array0(void) const { return m_matDesc->m_color0 ? (const unsigned *)m_matDesc->m_color0->m_array : 0; }
};

class MeshClass
{
public:
	Rva000E7DF3Model *Peek_Model(void) const { return m_model; }
private:
	unsigned char m_head[0xc4];
	Rva000E7DF3Model *m_model;
};

struct Rva000E7DF3Data
{
	unsigned char m_head[0x18];
	float m_maxOutwardMovement;
	unsigned char m_gap1c[0x54 - 0x1c];
	bool m_noSway;
};

struct Rva000E7DF3Type
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	unsigned char m_gap10[0x10];
	const Rva000E7DF3Data *m_data;
	Vector2 m_scale;
	unsigned char m_gap2c[0x34 - 0x2c];
	Vector2 m_origin;
	unsigned char m_gap3c[0x5c - 0x3c];
};

struct Rva000E7DF3Tree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	unsigned char m_gap45[0x5c - 0x45];
	float pushAside;
	float pushAsideDelta;
	float pushAsideSin;
	float pushAsideCos;
	unsigned char m_gap6c[0x78 - 0x6c];
	int swayType;
	int firstIndex;
	int bufferNdx;
	int m_toppleState;
	unsigned char m_gap88[0x9c - 0x88];
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
	void rva000E7DF3(void);

private:
	void *m_vtable;
	PtrVector<VertexBufferClass *> m_vertexTree;
	PtrVector<int> m_curNumTreeVertices;
	PtrVector<IndexBufferClass *> m_indexTree;
	PtrVector<int> m_curNumTreeIndices;
	unsigned char m_gap34[0x1958 - 0x34];
	Rva000E7DF3Tree m_trees[2000];
	int m_numTrees;
	
	bool m_anythingChanged;
	unsigned char m_gap4fb5d[0x4fb6c - 0x4fb5d];
	bool m_initialized;
	unsigned char m_gap4fb6d[3];
	Rva000E7DF3Type m_treeTypes[64];
	unsigned char m_gap51270[8];
	int m_treeIndexStep;
};

// ?rva000E7DF3@W3DShrubBuffer@@QAEXXZ
void W3DShrubBuffer::rva000E7DF3(void)
{
	if (!m_initialized || !m_indexTree[0] || !m_vertexTree[0] || !m_anythingChanged)
		return;

	int curTree;
	for (curTree = 0; curTree < m_numTrees; curTree++)
		m_trees[curTree].bufferNdx = -1;

	curTree = 0;
	for (unsigned bNdx = 0; bNdx < m_vertexTree.size(); bNdx++) {
		m_curNumTreeVertices[bNdx] = 0;
		m_curNumTreeIndices[bNdx] = 0;
		if (curTree >= m_numTrees)
			break;
		IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx], 0);
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		Rva000E7DF3Vertex *vb = (Rva000E7DF3Vertex *)lockVtxBuffer.Get_Vertex_Array();
		unsigned short *ib = lockIdxBuffer.Get_Index_Array();
		unsigned short *curIb = ib;
		Rva000E7DF3Vertex *curVb = vb;

		for (; curTree < m_numTrees; curTree += m_treeIndexStep) {
			int type = m_trees[curTree].treeType;
			if (type < 0)
				continue;
			if (!m_trees[curTree].visible)
				continue;
			if (m_trees[curTree].m_toppleState != 0)
				continue;
			if (m_trees[curTree].m_field9c >= 4 || m_trees[curTree].m_field9c <= 0)
				continue;
			float scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			if (m_treeTypes[type].m_mesh == 0)
				continue;

			int startVertex = m_curNumTreeVertices[bNdx];
			m_trees[curTree].firstIndex = startVertex;
			m_trees[curTree].bufferNdx = bNdx;
			int numVertex = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Array();
			if (m_curNumTreeVertices[bNdx] + numVertex >= 30000)
				break;
			int numIndex = m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Count();
			const TriIndex *pPoly = m_treeTypes[type].m_mesh->Peek_Model()->Get_Polygon_Array();
			if (m_curNumTreeIndices[bNdx] + 3 * numIndex >= 60000)
				break;

			const Vector2 *uvs = m_treeTypes[type].m_mesh->Peek_Model()->Get_UV_Array_By_Index(0);
			const Vector3 *normals = m_treeTypes[type].m_mesh->Peek_Model()->Get_Vertex_Normal_Array();
			const unsigned *vecDiffuse = m_treeTypes[type].m_mesh->Peek_Model()->Get_Color_Array0();

			for (int i = 0; i < numVertex; i++) {
				float U = uvs[i].U;
				float V = uvs[i].V;
				if (U > 1.0f) U = 1.0f;
				if (U < 0.0f) U = 0.0f;
				if (V > 1.0f) V = 1.0f;
				if (V < 0.0f) V = 0.0f;

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
				if (normals) {
					curVb->nx = normals[i].X;
					curVb->ny = normals[i].Y;
					curVb->nz = normals[i].Z;
				} else {
					curVb->nx = 0.0f;
					curVb->ny = 0.0f;
					curVb->nz = 1.0f;
				}
				if (vecDiffuse)
					curVb->diffuse = vecDiffuse[i] | 0xff000000;
				else
					curVb->diffuse = 0xffffffff;
				curVb->u1 = U * m_treeTypes[type].m_scale.X + m_treeTypes[type].m_origin.X;
				curVb->v1 = V * m_treeTypes[type].m_scale.Y + m_treeTypes[type].m_origin.Y;
				curVb->sway = (float)(m_treeTypes[type].m_data->m_noSway ? 0 : m_trees[curTree].swayType);
				curVb->pivotZ = loc.Z;
				curVb++;
			}
			m_curNumTreeVertices[bNdx] += numVertex;

			for (int i = 0; i < numIndex; i++) {
				*curIb++ = startVertex + pPoly[i].I;
				*curIb++ = startVertex + pPoly[i].J;
				*curIb++ = startVertex + pPoly[i].K;
			}
			m_curNumTreeIndices[bNdx] += 3 * numIndex;
		}
	}
}
