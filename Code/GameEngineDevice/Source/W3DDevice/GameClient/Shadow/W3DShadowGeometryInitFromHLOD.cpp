// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Target method identity comes from the Zero Hour W3DVolumetricShadow donor and
// the retail HLOD vtable calls.  BFME2 splits per-mesh population into
// initFromMesh (0x000F1018); its object offsets are read from retail.
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
    void Release_Ref() { if (--references == 0) Delete_This(); }
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


// Target layout view: W3DShadowGeometry+0x10 contains one buffer pointer;
// retail uses it as [buffer + 8] and falls back to the rowed empty string.
class Rva000055F5StringView
{
public:
    Rva000055F5StringView &rva000055F5(const char *value);
    const char *Peek_Buffer() const
    {
        return m_buffer ? (const char *)m_buffer + 8 : "";
    }
private:
    char *m_buffer;
};

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
    virtual const char *Get_Key();
    W3DShadowGeometry();
    int initFromHLOD(RenderObjClass *robj);
    int initFromMesh(RenderObjClass *robj, int mesh_index, W3DShadowGeometry *parent_geometry);
    void Set_Name(const char *value) { nameStorage.rva000055F5(value); }
    const char *Get_Name() const { return nameStorage.Peek_Buffer(); }
private:
    Rva000055F5StringView nameStorage;
    W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
    Int m_meshCount;
    Int m_numTotalsVerts;
};

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
            initFromMesh((RenderObjClass *)model, i, this);
        }
    }
    return m_meshCount != 0;
}


class W3DShadowGeometryManager
{
public:
    int Load_Geom(RenderObjClass *robj, const char *name);
    W3DShadowGeometry *Peek_Geom(const char *name);
    int Add_Geom(W3DShadowGeometry *geometry);
};

// Zero Hour donor W3DShadowGeometryManager::Load_Geom with BFME2's target
// class id and per-mesh helper calls. The target direct-call addresses below
// are pinned from this function's retail REL32s.
int W3DShadowGeometryManager::Load_Geom(RenderObjClass *robj, const char *name)
{
    bool result = false;
    W3DShadowGeometry *newgeom = new W3DShadowGeometry;
    if (newgeom == 0)
        goto Error;

    newgeom->Set_Name(name);
    int classId = robj->Class_ID();
    if (classId != 0)
    {
        if (classId == 25)
            result = newgeom->initFromHLOD(robj);
    }
    else
        result = newgeom->initFromMesh((RenderObjClass *)robj->Get_Model(), -1, newgeom);

    if (result != true)
    {
        newgeom->Release_Ref();
        goto Error;
    }
    if (Peek_Geom(newgeom->Get_Name()) != 0)
    {
        newgeom->Release_Ref();
        goto Error;
    }
    Add_Geom(newgeom);
    newgeom->Release_Ref();
    return 0;

Error:
    return 1;
}
