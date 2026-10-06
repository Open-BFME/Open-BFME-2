// ?rva000F1018@W3DShadowGeometry@@QAEHPAVMeshModelClass@@HPAV1@@Z
// partial score=0.7789 date=2026-10-06
// ?rva000F1018@W3DShadowGeometry@@QAEHPAVMeshModelClass@@HPAV1@@Z
// partial score=0.45 date=2026-10-05
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /G7
// Target method identity comes from the Zero Hour W3DVolumetricShadow donor and
// the retail HLOD vtable calls.  BFME2 splits per-mesh population into the
// adjacent address-derived helper; its object offsets are read from retail.
#include <string.h>

#define MAX_SHADOW_CASTER_MESHES 160
#define MAX_SHADOW_VOLUME_VERTS 16384

typedef unsigned short UnsignedShort;
typedef int Int;

#include "vector3.h"

class MeshModelClass;
class RenderObjClass
{
public:
    virtual void __renderObjSlot0();
    virtual void __renderObjSlot1();
    virtual void __renderObjSlot2();
    virtual int Class_ID();
    virtual void __renderObjSlot4();
    virtual MeshModelClass *Get_Model();
};

class HLodClass : public RenderObjClass
{
public:
    virtual void __hlodSlot6();
    virtual void __hlodSlot7();
    virtual void __hlodSlot8();
    virtual void __hlodSlot9();
    virtual void __hlodSlot10();
    virtual void __hlodSlot11();
    virtual void __hlodSlot12();
    virtual void __hlodSlot13();
    virtual void __hlodSlot14();
    virtual void __hlodSlot15();
    virtual void __hlodSlot16();
    virtual void __hlodSlot17();
    virtual void __hlodSlot18();
    virtual void __hlodSlot19();
    virtual void __hlodSlot20();
    virtual void __hlodSlot21();
    virtual void __hlodSlot22();
    virtual void __hlodSlot23();
    virtual void __hlodSlot24();
    virtual void __hlodSlot25();
    virtual void __hlodSlot26();
    virtual void __hlodSlot27();
    virtual void __hlodSlot28();
    virtual void __hlodSlot29();
    virtual void __hlodSlot30();
    virtual void __hlodSlot31();
    virtual void __hlodSlot32();
    virtual void __hlodSlot33();
    virtual void __hlodSlot34();
    virtual void __hlodSlot35();
    virtual void __hlodSlot36();
    virtual void __hlodSlot37();
    virtual void __hlodSlot38();
    virtual void __hlodSlot39();
    virtual void __hlodSlot40();
    virtual void __hlodSlot41();
    virtual void __hlodSlot42();
    virtual void __hlodSlot43();
    virtual void __hlodSlot44();
    virtual void __hlodSlot45();
    virtual void __hlodSlot46();
    virtual void __hlodSlot47();
    virtual void __hlodSlot48();
    virtual void __hlodSlot49();
    virtual void __hlodSlot50();
    virtual void __hlodSlot51();
    virtual void __hlodSlot52();
    virtual void __hlodSlot53();
    virtual void __hlodSlot54();
    virtual void __hlodSlot55();
    virtual void __hlodSlot56();
    virtual void __hlodSlot57();
    virtual void __hlodSlot58();
    virtual void __hlodSlot59();
    virtual void __hlodSlot60();
    virtual void __hlodSlot61();
    virtual void __hlodSlot62();
    virtual void __hlodSlot63();
    virtual void __hlodSlot64();
    virtual void __hlodSlot65();
    virtual void __hlodSlot66();
    virtual void __hlodSlot67();
    virtual void __hlodSlot68();
    virtual void __hlodSlot69();
    virtual void __hlodSlot70();
    virtual void __hlodSlot71();
    virtual void __hlodSlot72();
    virtual void __hlodSlot73();
    virtual void __hlodSlot74();
    virtual void __hlodSlot75();
    virtual void __hlodSlot76();
    virtual void __hlodSlot77();
    virtual void __hlodSlot78();
    virtual void __hlodSlot79();
    virtual void __hlodSlot80();
    virtual int Get_LOD_Count();
    virtual void __hlodSlot82();
    virtual void __hlodSlot83();
    virtual void __hlodSlot84();
    virtual void __hlodSlot85();
    virtual void __hlodSlot86();
    virtual void __hlodSlot87();
    virtual void __hlodSlot88();
    virtual void __hlodSlot89();
    virtual void __hlodSlot90();
    virtual void __hlodSlot91();
    virtual void __hlodSlot92();
    virtual void __hlodSlot93();
    virtual void __hlodSlot94();
    virtual void __hlodSlot95();
    virtual void __hlodSlot96();
    virtual void __hlodSlot97();
    virtual void __hlodSlot98();
    virtual void __hlodSlot99();
    virtual void __hlodSlot100();
    virtual void __hlodSlot101();
    virtual void __hlodSlot102();
    virtual void __hlodSlot103();
    virtual void __hlodSlot104();
    virtual void __hlodSlot105();
    virtual void __hlodSlot106();
    virtual void __hlodSlot107();
    virtual void __hlodSlot108();
    virtual void __hlodSlot109();
    virtual void __hlodSlot110();
    virtual void __hlodSlot111();
    virtual void __hlodSlot112();
    virtual void __hlodSlot113();
    virtual void __hlodSlot114();
    virtual void __hlodSlot115();
    virtual void __hlodSlot116();
    virtual void __hlodSlot117();
    virtual void __hlodSlot118();
    virtual void __hlodSlot119();
    virtual void __hlodSlot120();
    virtual void __hlodSlot121();
    virtual void __hlodSlot122();
    virtual void __hlodSlot123();
    virtual void __hlodSlot124();
    virtual void __hlodSlot125();
    virtual void __hlodSlot126();
    virtual void __hlodSlot127();
    virtual void __hlodSlot128();
    virtual void __hlodSlot129();
    virtual void __hlodSlot130();
    virtual void __hlodSlot131();
    virtual void __hlodSlot132();
    virtual void __hlodSlot133();
    virtual void __hlodSlot134();
    virtual void __hlodSlot135();
    virtual void __hlodSlot136();
    virtual int Get_Lod_Model_Count(int lod);
    virtual RenderObjClass *Peek_Lod_Model(int lod, int model);
};

struct RetailMeshBuffer
{
    void *vtable;
    int references;
    int opaque;
    Vector3 *vertices;
};

// View established by the target accesses at MeshModelClass+0xC4.
struct RetailMeshGeometry
{
    unsigned char prefix[0x18];
    unsigned int flags;
    unsigned char middle[8];
    int polygonCount;
    int vertexCount;
    RetailMeshBuffer *polygonBuffer;
    RetailMeshBuffer *vertexBuffer;
};

class MeshModelClass
{
public:
    unsigned char prefix[0xC4];
    RetailMeshGeometry * volatile geometry;
};

class RefCountClass
{
public:
    virtual void Delete_This();
protected:
    virtual ~RefCountClass();
private:
    int references;
};

class HashableClass
{
public:
    virtual ~HashableClass();
    virtual const char *Get_Key() = 0;
private:
    HashableClass *next;
};

class W3DShadowGeometry;
struct W3DShadowGeometryMesh
{
    RetailMeshBuffer *polygonBuffer;       // +0x00
    RetailMeshBuffer *vertexBuffer;        // +0x04
    const Vector3 *vertices;               // +0x08
    Int meshRobjIndex;                     // +0x0C
    Int opaque10;                          // +0x10
    Int numUniqueVertices;                 // +0x14
    Int sourceVertexCount;                 // +0x18
    Int numPolygons;                       // +0x1C
    UnsignedShort *parentVertices;         // +0x20
    Int opaque24;                          // +0x24
    Int opaque28;                          // +0x28
    W3DShadowGeometry *parentGeometry;     // +0x2C
    unsigned char flags;                   // +0x30
    unsigned char pad[3];
};

typedef char W3DShadowGeometryMesh_must_be_0x34[(sizeof(W3DShadowGeometryMesh) == 0x34) ? 1 : -1];

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
    virtual const char *Get_Key();
    int initFromHLOD(RenderObjClass *robj);
    int rva000F1018(MeshModelClass *model, int index, W3DShadowGeometry *parent);
private:
    Int nameStorage;                       // BFME2 AsciiString is four bytes
    W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
    Int m_meshCount;
    Int m_numTotalsVerts;
};

struct W3DShadowGeometryHelperFrame
{
    W3DShadowGeometry * volatile self;
    int newVertexCount;
    volatile int innerOffset;
};

// The target helper performs the common per-model buffer retention and vertex
// deduplication described by W3DShadowGeometry::initFromHLOD in the donor.
// ?rva000F1018@W3DShadowGeometry@@QAEHPAVMeshModelClass@@HPAV1@@Z present-unmatched
int W3DShadowGeometry::rva000F1018(MeshModelClass * volatile model, int index,
                                  W3DShadowGeometry *parent)
{
    W3DShadowGeometryMesh *entry = &m_meshList[m_meshCount];
    entry->meshRobjIndex = index;
    W3DShadowGeometryHelperFrame frame;
    frame.self = this;

    RetailMeshGeometry *geometry = model->geometry;
    unsigned int flags = geometry->flags;
    if (!(flags & 0x00001000))
        return 0;
    entry->flags = (unsigned char)((flags >> 10) & 1);

    geometry = model->geometry;
    entry->sourceVertexCount = geometry->vertexCount;
    RetailMeshBuffer *vertexBuffer = geometry->vertexBuffer;
    if (vertexBuffer)
        ++vertexBuffer->references;
    entry->vertexBuffer = vertexBuffer;
    entry->vertices = entry->vertexBuffer->vertices;
    entry->numPolygons = geometry->polygonCount;
    ++geometry->polygonBuffer->references;
    entry->polygonBuffer = geometry->polygonBuffer;

    if (entry->sourceVertexCount > MAX_SHADOW_VOLUME_VERTS)
        return 0;

    UnsignedShort vertParent[MAX_SHADOW_VOLUME_VERTS];
    memset(vertParent, -1, sizeof(vertParent));
    frame.newVertexCount = entry->sourceVertexCount;
    index = 0;
    for (int j = 0; j < entry->sourceVertexCount; ++j, index += 12)
    {
        if (vertParent[j] != 0xFFFF)
            continue;

        const Vector3 *v_curr = (const Vector3 *)((const char *)entry->vertices + index);
        int k = j + 1;
        frame.innerOffset = index + 12;
        for (; k < entry->sourceVertexCount; frame.innerOffset += 12, ++k)
        {
            const Vector3 *v_next = (const Vector3 *)((const char *)entry->vertices + frame.innerOffset);
            Vector3 len(*v_curr - *v_next);
            if (len.Length2() == 0.0f)
            {
                vertParent[k] = (UnsignedShort)j;
                --frame.newVertexCount;
            }
        }
        vertParent[j] = (UnsignedShort)j;
    }

    entry->parentVertices = new UnsignedShort[entry->sourceVertexCount];
    memcpy(entry->parentVertices, vertParent,
           sizeof(UnsignedShort) * entry->sourceVertexCount);
    entry->numUniqueVertices = frame.newVertexCount;
    frame.self->m_numTotalsVerts += frame.newVertexCount;
    entry->parentGeometry = parent;
    geometry = model->geometry;
    if (geometry->flags & 0x00000400)
        entry->vertices = 0;
    frame.self->m_numTotalsVerts += frame.newVertexCount;
    ++frame.self->m_meshCount;
    return 1;
}

int W3DShadowGeometry::initFromHLOD(RenderObjClass *robj)
{
    HLodClass *hlod = (HLodClass *)robj;
    m_numTotalsVerts = 0;
    m_meshCount = 0;

    int top = hlod->Get_LOD_Count() - 1;
    for (int i = 0; i < hlod->Get_Lod_Model_Count(top); ++i)
    {
        if (hlod->Peek_Lod_Model(top, i) &&
            hlod->Peek_Lod_Model(top, i)->Class_ID() == 0)
        {
            MeshModelClass *model = hlod->Peek_Lod_Model(top, i)->Get_Model();
            rva000F1018(model, i, this);
        }
    }
    return m_meshCount != 0;
}
