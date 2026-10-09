// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00115791,0011580A),121B, RET8. WorldBuilder places the body in
// W3DTerrainBackground.cpp (unnamed there). With the flag set it locks the
// vertex buffer at +0x24 and stores the float into each 0x20-byte vertex's
// z (+0x8) for the vertex count at +0x48; otherwise it rebuilds the whole
// tile through doTesselatedUpdate (0x001149EB, named by WorldBuilder) over
// {0, 0, +0x50 + +0x58, +0x54 + +0x58} with the map at +0x5C. Every offset
// is a target fact; the method name is address-derived.

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return m_vertices; }

	private:
		VertexBufferClass *m_buffer;
		void *m_vertices;
		int m_flags;
	};
};

class WorldHeightMap;

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct TerrainBackgroundVertex
{
	float x;
	float y;
	float z;
	unsigned char m_rest[0x14];
};

class W3DTerrainBackground
{
public:
	void doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures);
	void rva00115791(bool flat, float height);

private:
	unsigned char m_pad00[0x24];
	VertexBufferClass *m_vertexTerrain;
	unsigned char m_pad28[0x48 - 0x28];
	int m_curNumTerrainVertices;
	int m_curNumTerrainIndices;
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

void W3DTerrainBackground::rva00115791(bool flat, float height)
{
	if (flat) {
		if (m_curNumTerrainVertices > 0) {
			VertexBufferClass::WriteLockClass lock(m_vertexTerrain, 0);
			TerrainBackgroundVertex *vertices =
				(TerrainBackgroundVertex *)lock.Get_Vertex_Array();
			for (int i = 0; i < m_curNumTerrainVertices; i++) {
				vertices->z = height;
				vertices++;
			}
		}
	} else {
		IRegion2D range;
		range.lo.x = 0;
		range.lo.y = 0;
		range.hi.x = m_xOrigin + m_width;
		range.hi.y = m_yOrigin + m_width;
		doTesselatedUpdate(range, m_map, false);
	}
}
