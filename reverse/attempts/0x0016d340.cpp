// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.9 date=2026-10-06
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z, retail 0x0016D340, 251 bytes.
// Switch dispatcher over W3D chunk IDs with LINK BONUS 645B in MeshGeometryLoadW3D.
// Evidence: callers 0x0016DA41 Load_W3D; rowed Open_Chunk 0x00614F50 Cur_Chunk_ID 0x00615020 Close_Chunk 0x00614FC0 Read 0x006151A0 read_vertices 0x0016AE70 get_vert_normals 0x0016AAE0 read_triangles 0x0016B020 read_user_text 0x0016B0E0 get_shade_indices 0x0016A010 read_aabtree 0x001693A0; pin-only read_vertex_influences 0x0016B1A0; donor BFME1 MeshGeometryReadChunks.cpp case values.
class Vector3;
class ChunkLoadClass
{
public:
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
	bool Close_Chunk();
	unsigned long Read(void *dst, unsigned long size);
};
class MeshGeometryClass
{
protected:
	bool read_chunks(ChunkLoadClass &cload);
	bool read_vertices(ChunkLoadClass &cload, bool alternate);
	Vector3 *get_vert_normals(bool alternate);
	bool read_triangles(ChunkLoadClass &cload);
	bool read_user_text(ChunkLoadClass &cload);
	bool read_vertex_influences(ChunkLoadClass &cload);
	unsigned long *get_shade_indices(bool alternate);
	bool read_aabtree(ChunkLoadClass &cload);
	char m_pad00[0x28];
	int m_count28;
};
enum
{
	W3D_CHUNK_VERTICES = 0x02,
	W3D_CHUNK_VERTEX_NORMALS = 0x03,
	W3D_CHUNK_SURRENDER_NORMALS = 0x04,
	W3D_CHUNK_MESH_USER_TEXT = 0x0c,
	W3D_CHUNK_VERTEX_INFLUENCES = 0x0e,
	W3D_CHUNK_TRIANGLES = 0x20,
	W3D_CHUNK_VERTEX_SHADE_INDICES = 0x22,
	W3D_CHUNK_AABTREE = 0x90
};
bool MeshGeometryClass::read_chunks(ChunkLoadClass &cload)
{
	while (cload.Open_Chunk()) {
		bool error = true;
		switch (cload.Cur_Chunk_ID()) {
			case W3D_CHUNK_VERTICES:
				error = read_vertices(cload, false);
				break;
			case W3D_CHUNK_SURRENDER_NORMALS:
			case W3D_CHUNK_VERTEX_NORMALS: {
				Vector3 *normals = get_vert_normals(false);
				int count = m_count28;
				unsigned long bytes = (unsigned long)(count * 12);
				unsigned long got = cload.Read(normals, bytes);
				unsigned long want = (unsigned long)(count * 4 * 3);
				error = (got == want);
				break;
			}
			case W3D_CHUNK_TRIANGLES:
				error = read_triangles(cload);
				break;
			case W3D_CHUNK_MESH_USER_TEXT:
				error = read_user_text(cload);
				break;
			case W3D_CHUNK_VERTEX_INFLUENCES:
				error = read_vertex_influences(cload);
				break;
			case W3D_CHUNK_VERTEX_SHADE_INDICES: {
				unsigned long *indices = get_shade_indices(true);
				int count = m_count28;
				unsigned long bytes = (unsigned long)(count * 4);
				unsigned long got = cload.Read(indices, bytes);
				unsigned long want = (unsigned long)(count << 2);
				error = (got == want);
				break;
			}
			case W3D_CHUNK_AABTREE:
				read_aabtree(cload);
				break;
			default:
				break;
		}
		cload.Close_Chunk();
		if (error != true)
			return error;
	}
	return true;
}
