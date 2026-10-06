// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.7233 date=2026-10-06
// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.4 date=2026-10-02
// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /G6
// BFME1 MeshGeometryClass::read_chunks donor, adapted to the BFME2 bool ABI.
// Retail dispatches vertices at +0x25, normals by get_vert_normals(false),
// triangles at +0x83, user text at +0x8c, influences at +0x9a, shade indices
// through get_shade_indices(true) at +0xa4, and AABTree at +0xce. The 251B
// Ghidra extent ends inside the failure epilogue: the in-body branch at
// +0xf9 reaches the second ret-4 at +0xfe, so the verified body is 257B.
#include "always.h"
#include "bittype.h"
#include "chunkio.h"
#include "vector3.h"
#include "w3d_file.h"

class MeshGeometryClass
{
protected:
    bool read_chunks(ChunkLoadClass &cload);
    bool read_vertices(ChunkLoadClass &cload, bool alternate);
    Vector3 *get_vert_normals(bool alternate_format);
    bool read_triangles(ChunkLoadClass &cload);
    bool read_user_text(ChunkLoadClass &cload);
    bool read_vertex_influences(ChunkLoadClass &cload);
    uint32 *get_shade_indices(bool create);
    bool read_aabtree(ChunkLoadClass &cload);

private:
    char BeforeVertexCount[0x28];
    int VertexCount;
};

// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
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
            unsigned int bytes = VertexCount * sizeof(Vector3);
            error = cload.Read(normals, bytes) == bytes;
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
            uint32 *shade_indices = get_shade_indices(true);
            unsigned int bytes = VertexCount * sizeof(uint32);
            error = cload.Read(shade_indices, bytes) == bytes;
            break;
        }

        case W3D_CHUNK_AABTREE:
            read_aabtree(cload);
            break;

        default:
            break;
        }

        cload.Close_Chunk();
        if (!error) {
            return false;
        }
    }

    return true;
}
