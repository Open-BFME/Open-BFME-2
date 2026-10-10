// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?read_vertex_influences@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// retail 0x0016B1A0..0x0016B3BA (538 bytes ret 4).  Chunk 0x0E reader
// dispatched from read_chunks 0x0016D340.
//
// Structure from the WorldBuilder twin (meshgeometry.cpp wb 0xA0E010):
// read one four-word influence record per vertex into the bone-link buffer
// (get_bone_links 0x0016A0C0) as four planes of VertexCount words; count
// the runs of consecutive equal four-word tuples; size the span buffer
// (get_buffer54 0x0016A170) to two words per run; then write each run's
// first word and length; finally Set_Flag(0x400).  Get_Vertex_Count and
// Set_Flag are the inline accessors the twin calls (+0x28 and +0x18).
//
// Layout evidence from the twin's frame: the record is one 8-byte local
// outside the read loop, and each run loop keeps its four tuple words as two
// 4-byte two-word locals -- retail's spill slots pack them in pairs (and
// reuse the dead ChunkLoadClass argument slot), which only an aggregate
// reproduces.  Member and type names beyond the twin's are descriptive.
#include "always.h"
#include "chunkio.h"

struct VertInfRecord {
    unsigned short Value[4];
};

struct VertInfPair {
    unsigned short First;
    unsigned short Second;
};

class MeshGeometryClass {
    char BeforeFlags[0x18];
    int Flags;
    char BeforeVertexCount[0x28 - 0x1C];
    int VertexCount;
public:
    int Get_Vertex_Count() const { return VertexCount; }
    void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
protected:
    unsigned short *get_bone_links(bool create);
    unsigned short *get_buffer54(int count);
    bool read_vertex_influences(ChunkLoadClass &cload);
};

bool MeshGeometryClass::read_vertex_influences(ChunkLoadClass &cload)
{
    unsigned short *links = get_bone_links(true);
    int vcount = Get_Vertex_Count();
    VertInfRecord inf;
    for (int i = 0; i < vcount; i++) {
        if (cload.Read(&inf, sizeof(inf)) != sizeof(inf))
            return false;
        links[i] = inf.Value[0];
        links[vcount + i] = inf.Value[1];
        links[i + vcount * 2] = inf.Value[2];
        links[vcount * 3 + i] = inf.Value[3];
    }

    int span_count = 0;
    int v = 0;
    while (v < vcount) {
        VertInfPair pa = { links[v], links[vcount + v] };
        VertInfPair pb = { links[v + vcount * 2], links[vcount * 3 + v] };
        int j;
        for (j = v; j < vcount; j++) {
            if (pa.First != links[j] || pa.Second != links[vcount + j]
                || pb.First != links[j + vcount * 2] || pb.Second != links[vcount * 3 + j])
                break;
        }
        span_count++;
        v = j;
    }

    unsigned short *spans = get_buffer54(span_count * 2);
    span_count = 0;
    v = 0;
    while (v < Get_Vertex_Count()) {
        VertInfPair pa = { links[v], links[vcount + v] };
        VertInfPair pb = { links[v + vcount * 2], links[vcount * 3 + v] };
        int j;
        for (j = v; j < Get_Vertex_Count(); j++) {
            if (pa.First != links[j] || pa.Second != links[vcount + j]
                || pb.First != links[j + vcount * 2] || pb.Second != links[vcount * 3 + j])
                break;
        }
        int len = j - v;
        spans[span_count++] = pa.First;
        spans[span_count++] = len;
        v = j;
    }
    Set_Flag(0x400, true);
    return true;
}
