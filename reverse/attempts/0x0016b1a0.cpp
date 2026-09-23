// ?read_vertex_influences@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.5501858736 date=2026-09-23
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/shims/sweep
#include "always.h"
#include "chunkio.h"

// BFME1 meshgeometry.cpp supplies the influence reader's purpose and read loop.
// BFME2 16B1A0 reads four words and builds consecutive equal-tuple runs.
class MeshGeometryClass {
    char BeforeFlags[0x18];
    int Flags;
    char BeforeVertexCount[0x28 - 0x1C];
    int VertexCount;
protected:
    unsigned short *get_bone_links(bool create);
    unsigned short *get_buffer54(int count);
    bool read_vertex_influences(ChunkLoadClass &cload);
};

bool MeshGeometryClass::read_vertex_influences(ChunkLoadClass &cload)
{
    unsigned short influence[4];
    unsigned short *links = get_bone_links(true);
    int count = VertexCount;
    for (int i = 0; i < count; ++i) {
        if (cload.Read(influence, sizeof(influence)) != sizeof(influence))
            return false;
        links[i] = influence[0];
        links[i + count] = influence[1];
        links[i + count * 2] = influence[2];
        links[i + count * 3] = influence[3];
    }
    int run_count = 0;
    for (int i = 0; i < count;) {
        unsigned short first = links[i];
        unsigned short second = links[i + count];
        unsigned short third = links[i + count * 2];
        unsigned short fourth = links[i + count * 3];
        while (i < count && first == links[i] && second == links[i + count]
               && third == links[i + count * 2] && fourth == links[i + count * 3])
            ++i;
        ++run_count;
    }
    unsigned short *runs = get_buffer54(run_count * 2);
    for (int i = 0; i < VertexCount;) {
        unsigned short tuple[3] = { links[i+count], links[i+count*2], links[i+count*3] };
        int end = i;
        while (end < VertexCount && links[i] == links[end]
               && tuple[0] == links[end + count] && tuple[1] == links[end + count * 2]
               && tuple[2] == links[end + count * 3])
            ++end;
        *runs++ = links[i];
        *runs++ = end - i;
        i = end;
    }
    Flags |= 0x400;
    return true;
}
