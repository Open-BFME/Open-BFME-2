// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?loadShrubsInVertexAndIndexBuffers@W3DShrubBuffer@@QAEXXZ
// W3DShrubBuffer::loadShrubsInVertexAndIndexBuffers, retail 0x000E7DF3 (1394 bytes): Zero Hour's
// loadTreesInVertexAndIndexBuffers shape for shrubs (WorldBuilder name
// loadShrubsInVertexAndIndexBuffers). Per buffer it locks the index and vertex
// buffers and appends the vertices and triangles of every upright visible
// record whose mesh is loaded, stopping at 30000 vertices / 60000 indices.
// Layout read from retail: buffer lists are STLport vectors at +0x04/+0x10/
// +0x1C/+0x28, 2000 records of 0xA0 at +0x1958, types of 0x5C at +0x4FB70,
// tree index step +0x51278; vertex is 0x2C bytes (position, normal, diffuse,
// one UV set, sway, pivot height). Codegen depends on the real std::vector
// (operator[] through begin()), the sibling 0xE8365's x/y/z vertex form and
// the W3D MeshMatDescClass::Get_UV_Array_By_Index(index, create) nesting.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
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

// Retail 0x0016AB90: MeshGeometryClass::Get_Vertex_Normal_Array(bool).


struct ShrubVertex
{
	float x, y, z;
	Vector3 normal;
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


class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array(int pass, int stage);
	unsigned char m_head[0x0c];
	int m_uvSourceCount;
	Rva000E7DF3ArrayHolder *m_uv0;
	// Only the existing-buffer path used by this unit. The full create-gated
	// MeshMatDescClass accessor is supplied by its verified 0xD1F40 owner.
	__forceinline Vector2 *Get_Existing_UV_Array_By_Index(int index)
	{
		if (m_uvSourceCount != 0)
			return Get_UV_Array(0, index);
		if ((&m_uv0)[index])
			return (Vector2 *)(&m_uv0)[index]->m_array;
		return 0;
	}
	unsigned char m_gap14[0x50 - 0x14];
	Rva000E7DF3ArrayHolder *m_color0;
};

template <class T> class Rva000E7DF3ShareBuffer
{
public:
	T *Get_Array(void) { return m_array; }
private:
	unsigned char m_head[0x0c];
	T *m_array;
};

class MeshGeometryClass
{
public:
	const Vector3 *Get_Vertex_Normal_Array(bool create);
	int Get_Polygon_Count(void) const { return m_polyCount; }
	int Get_Vertex_Count(void) const { return m_vertexCount; }
	const TriIndex *Get_Polygon_Array(void) { return get_polys(); }
	Vector3 *Get_Vertex_Array(void) { return m_vertices->Get_Array(); }
protected:
	TriIndex *get_polys(void) { return m_polys->Get_Array(); }
	unsigned char m_head[0x24];
	int m_polyCount;
	int m_vertexCount;
	Rva000E7DF3ShareBuffer<TriIndex> *m_polys;
	Rva000E7DF3ShareBuffer<Vector3> *m_vertices;
};

struct Rva000E7DF3Model : public MeshGeometryClass
{
	unsigned char m_gap34[0x94 - 0x34];
	MeshMatDescClass *m_matDesc;

	__forceinline const Vector2 *Get_UV_Array_By_Index(int index) { return m_matDesc->Get_Existing_UV_Array_By_Index(index); }
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

struct ShrubInstance
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


// The vertex and index loops each open with a WorldBuilder assert
// (W3DShrubBuffer.cpp:297 and :360). In retail they compile to no code but keep
// one action-less unwind state each under the two locks (FuncInfo 0x00D07298,
// states 2 -> 1 and 3 -> 1): the release macro's dead branch holds a temporary
// with a destructor. Its type is unknown; this sink reproduces the EH shape.
struct ShrubAssertSink { ShrubAssertSink(); ~ShrubAssertSink(); void Crash(); };
#define SHRUB_ASSERT(c) do { if (0) { ShrubAssertSink().Crash(); } } while (0)

class W3DShrubBuffer
{
public:
	void loadShrubsInVertexAndIndexBuffers(void);

private:
	void *m_vtable;
	std::vector<VertexBufferClass *> m_vertexTree;
	std::vector<int> m_curNumTreeVertices;
	std::vector<IndexBufferClass *> m_indexTree;
	std::vector<int> m_curNumTreeIndices;
	unsigned char m_gap34[0x1958 - 0x34];
	ShrubInstance m_trees[2000];
	int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_gap4fb5d[0x4fb6c - 0x4fb5d];
	bool m_initialized;
	unsigned char m_gap4fb6d[3];
	Rva000E7DF3Type m_treeTypes[64];
	unsigned char m_gap51270[8];
	int m_treeIndexStep;
};

// ?loadShrubsInVertexAndIndexBuffers@W3DShrubBuffer@@QAEXXZ
void W3DShrubBuffer::loadShrubsInVertexAndIndexBuffers(void)
{
	if (!m_initialized || !m_indexTree[0] || !m_vertexTree[0])
		return;
	if (!m_anythingChanged)
		return;

	int curTree;
	int bNdx;
	for (curTree = 0; curTree < m_numTrees; curTree++)
		m_trees[curTree].bufferNdx = -1;

	curTree = 0;
	for (bNdx = 0; bNdx < m_vertexTree.size(); bNdx++) {
		m_curNumTreeVertices[bNdx] = 0;
		m_curNumTreeIndices[bNdx] = 0;
		if (curTree >= m_numTrees)
			break;
		ShrubVertex *vb;
		unsigned short *ib;
		IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx], 0);
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		vb = (ShrubVertex *)lockVtxBuffer.Get_Vertex_Array();
		ib = lockIdxBuffer.Get_Index_Array();
		unsigned short *curIb = ib;
		ShrubVertex *curVb = vb;

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
			const Matrix3D *mtx = &m_trees[curTree].transform;
			if (type < 0 || m_treeTypes[type].m_mesh == 0)
				continue;

			int startVertex = m_curNumTreeVertices[bNdx];
			m_trees[curTree].firstIndex = startVertex;
			m_trees[curTree].bufferNdx = bNdx;
			int i;
			Rva000E7DF3Model *model = m_treeTypes[type].m_mesh->Peek_Model();
			Vector3 *pVert = model->Get_Vertex_Array();
			int numVertex = model->Get_Vertex_Count();
			if (m_curNumTreeVertices[bNdx] + numVertex >= 30000)
				break;
			int numIndex = model->Get_Polygon_Count();
			const TriIndex *pPoly = model->Get_Polygon_Array();
			if (m_curNumTreeIndices[bNdx] + 3 * numIndex >= 60000)
				break;

			const Vector2 *uvs = model->Get_UV_Array_By_Index(0);
			const Vector3 *normals = model->Get_Vertex_Normal_Array(false);
			const unsigned *vecDiffuse = m_treeTypes[type].m_mesh->Peek_Model()->Get_Color_Array0();
			float uScale = m_treeTypes[type].m_scale.X;
			float vScale = m_treeTypes[type].m_scale.Y;
			float uOrigin = m_treeTypes[type].m_origin.X;
			float vOrigin = m_treeTypes[type].m_origin.Y;

			for (i = 0; i < numVertex; i++) {
				SHRUB_ASSERT(m_curNumTreeVertices[bNdx] + i < 30000);
				float x = pVert[i].X;
				float y = pVert[i].Y;
				float z = pVert[i].Z;
				Vector3 vert(x, y, z);
				vert += m_treeTypes[type].m_offset;
				Vector3 vLoc;
				Matrix3D::Transform_Vector(*mtx, vert, &vLoc);
				vLoc *= scale;
				if (m_trees[curTree].pushAside > 0.0f) {
					vLoc.X += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideCos * m_treeTypes[type].m_data->m_maxOutwardMovement;
					vLoc.Y += pVert[i].Z * m_trees[curTree].pushAside * m_trees[curTree].pushAsideSin * m_treeTypes[type].m_data->m_maxOutwardMovement;
				}
				vLoc.X += loc.X;
				vLoc.Y += loc.Y;
				vLoc.Z += loc.Z;
				curVb->z = vLoc.Z;
				curVb->x = vLoc.X;
				curVb->y = vLoc.Y;
				if (normals) {
					curVb->normal = normals[i];
				} else {
					curVb->normal.X = 0.0f;
					curVb->normal.Y = 0.0f;
					curVb->normal.Z = 1.0f;
				}
				if (vecDiffuse)
					curVb->diffuse = vecDiffuse[i] | 0xff000000;
				else
					curVb->diffuse = 0xffffffff;
				float U = uvs[i].U;
				float V = uvs[i].V;
				if (U > 1.0f) U = 1.0f;
				if (U < 0.0f) U = 0.0f;
				if (V > 1.0f) V = 1.0f;
				if (V < 0.0f) V = 0.0f;
				curVb->u1 = U * uScale + uOrigin;
				curVb->v1 = V * vScale + vOrigin;
				curVb->sway = (float)(m_treeTypes[m_trees[curTree].treeType].m_data->m_noSway ? 0 : m_trees[curTree].swayType);
				curVb->pivotZ = loc.Z;
				curVb++;
			}
			m_curNumTreeVertices[bNdx] += numVertex;

			for (i = 0; i < numIndex; i++) {
				SHRUB_ASSERT(m_curNumTreeIndices[bNdx] + 3 * i + 2 < 60000);
				*curIb++ = startVertex + pPoly[i].I;
				*curIb++ = startVertex + pPoly[i].J;
				*curIb++ = startVertex + pPoly[i].K;
			}
			m_curNumTreeIndices[bNdx] += 3 * numIndex;
		}
	}
}
