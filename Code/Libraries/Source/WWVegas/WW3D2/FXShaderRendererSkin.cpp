// cl: /O1 /arch:SSE /G7 /EHsc /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// FXShaderRenderer software-skinning helper, retail 0x00173C04 (500 B,
// thiscall RET 8). Called once by FlushSoftwareSkinnedRenderingTasks
// (0x001749D7: ECX = renderer, pushes output vertices then mesh).
//
// Target evidence: the WorldBuilder twin 0x00A224A0 (unoptimised build of
// the same source) gives the statements literally: two function-local
// static DynamicVectorClass<Vector3> caches (guard 0x00DF6FC8 bits 1/2,
// retail objects 0x00DF6FB0 / 0x00DF6F98, ctor (0,0)), mesh->Peek_Model(),
// mmc->Get_Vertex_Count(), the skin statistics record, the two Length() <
// count Resize calls, &buffer[0] cursors, mmc->Get_UV_Array_By_Index(0/1),
// mmc->Get_Color_Array(0,false), mesh->Get_Deformed_Vertices(loc,norm) and
// the per-vertex copy loop using Vector3/Vector2 operator[]. The FuncInfo
// at 0x00D0C7D0 has five unwind states: the two static guards plus three
// dead states, the inlined create-paths of the two UV and the colour
// accessors (new UVBufferClass / new ShareBufferClass<unsigned>).
// MeshMatDescClass::Get_UV_Array stays an out-of-line call (0x000D1F1A):
// it is a header inline one level deeper than the inliner expands here,
// and keeping its body visible is what lets the optimiser keep CurMatDesc
// in ESI across it (retail reloads only legacy +0x0C).
//
// Donor (semantic guide): Zero Hour / BFME1 dx8renderer.cpp,
// DX8SkinFVFCategoryContainer::Render vertex-copy block. BFME differences
// from target bytes: default diffuse 0xFFFFFFFF (donor 0), legacy-UV
// fallback in MeshMatDescClass::Get_UV_Array_By_Index.
// The method name is address-derived; the mesh class is the address-derived
// view the caller already uses, a MeshClass by its Get_Deformed_Vertices call.

class Vector3
{
public:
    float &operator[](int i) { return (&X)[i]; }
    const float &operator[](int i) const { return (&X)[i]; }
    float X, Y, Z;
};

#include "../../../../../reference/shims/wwmath/Vector2.h"

// WWLib vector.h (BFME1 game/Libraries/Source/WWVegas/WWLib).
template<class T> class VectorClass
{
public:
    VectorClass(int size = 0, T const *array = 0);
    virtual ~VectorClass();
    virtual bool operator==(const VectorClass<T> &) const;
    virtual bool Resize(int newsize, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *ptr);
    virtual int ID(T const &ptr);
    T &operator[](int index) { return Vector[index]; }
    int Length() const { return VectorMax; }
protected:
    T *Vector;
    int VectorMax;
    bool IsValid;
    bool IsAllocated;
    bool VectorClassPad[2];
};

template<class T> class DynamicVectorClass : public VectorClass<T>
{
public:
    DynamicVectorClass(unsigned size = 0, T const *array = 0);
    virtual ~DynamicVectorClass();
    virtual bool Resize(int newsize, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *ptr);
    virtual int ID(T const &ptr);
protected:
    int ActiveCount;
    int GrowthStep;
};

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
    : VectorClass<T>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

template<class T>
bool DynamicVectorClass<T>::Resize(int newsize, T const *array)
{
    if (VectorClass<T>::Resize(newsize, array)) {
        if (Length() < ActiveCount) ActiveCount = Length();
        return(true);
    }
    return(false);
}

#include "../WWLib/RefCountData.h"

template <class T> class ShareBufferClass : public RefCountClass
{
public:
    ShareBufferClass(int count, const char *msg, int alignment = 0);
    // Rowed per instantiation (Vector2 0x000D1DC8); this unit only calls it.
    virtual ~ShareBufferClass();
    T *Get_Array() { return m_array; }
protected:
    T *m_rawBuffer; // +0x08
    T *m_array;     // +0x0C
    int m_count;    // +0x10
    int m_alignment; // +0x14
};

class UVBufferClass : public ShareBufferClass<Vector2>
{
public:
    UVBufferClass(int count, const char *msg) : ShareBufferClass<Vector2>(count, msg), m_crc(0xFFFFFFFF) {}
    // Rowed at 0x000D2118 (UVBufferClassDtor.cpp); this unit only calls it.
    virtual ~UVBufferClass();
private:
    unsigned m_crc; // +0x18
};

// Layout as the rowed MeshMatDescClass accessor units read it
// (MeshMatDescGetUVArrayByIndex.cpp, MeshMatDescGetUVArrayRva000D1F1A.cpp,
// MeshMatDescClassGetColorArray.cpp).
class MeshMatDescClass
{
public:
    Vector2 *Get_UV_Array(int pass, int stage);
    Vector2 *Get_UV_Array_By_Index(int index, bool create);
    unsigned *Get_Color_Array(int index, bool create);
private:
    int m_passCount;   // +0x00
    int m_vertexCount; // +0x04
    int m_polyCount;   // +0x08
    int m_unknown0C;   // +0x0C legacy UV source
    UVBufferClass *m_uv[8];        // +0x10
    int m_uvSource[4][2];          // +0x30
    ShareBufferClass<unsigned> *m_colorArray[2]; // +0x50
};

inline Vector2 *MeshMatDescClass::Get_UV_Array(int pass, int stage)
{
    if (m_uvSource[pass][stage] == -1) {
        return 0;
    }
    if (m_uv[m_uvSource[pass][stage]] != 0) {
        return m_uv[m_uvSource[pass][stage]]->Get_Array();
    }
    return 0;
}

inline Vector2 *MeshMatDescClass::Get_UV_Array_By_Index(int index, bool create)
{
    if (create && !m_uv[index])
        m_uv[index] = new UVBufferClass(m_vertexCount, "MeshMatDescClass::UV");
    if (!create && m_unknown0C != 0 && index < 2)
        return Get_UV_Array(0, index);
    if (m_uv[index])
        return m_uv[index]->Get_Array();
    return 0;
}

inline unsigned *MeshMatDescClass::Get_Color_Array(int index, bool create)
{
    if (create && !m_colorArray[index]) {
        m_colorArray[index] = new ShareBufferClass<unsigned>(m_vertexCount, "MeshMatDescClass::ColorArray");
    }
    if (m_colorArray[index]) {
        return m_colorArray[index]->Get_Array();
    }
    return 0;
}

class MeshModelClass
{
public:
    int Get_Vertex_Count() { return VertexCount; }
    const Vector2 *Get_UV_Array_By_Index(int index) { return CurMatDesc->Get_UV_Array_By_Index(index, false); }
    unsigned *Get_Color_Array(int array_index, bool create = true) { return CurMatDesc->Get_Color_Array(array_index, create); }
private:
    char m_pad00[0x28];
    int VertexCount;                // +0x28
    char m_pad2C[0x94 - 0x2C];
    MeshMatDescClass *CurMatDesc;   // +0x94
};

class MeshClass
{
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void vf0C(); virtual void vf10(); virtual void vf14();
    virtual void vf18(); virtual void vf1C(); virtual void vf20();
    virtual void vf24();
    virtual int Get_Num_Polys();    // slot +0x28
    MeshModelClass *Peek_Model() { return Model; }
    void Get_Deformed_Vertices(Vector3 *dst_vert, Vector3 *dst_norm);
private:
    char m_pad04[0xC4 - 4];
    MeshModelClass *Model;          // +0xC4
};

class Rva0017368AMesh : public MeshClass
{
public:
    Rva0017368AMesh **Get_State() { return m_state; }
    void Set_Offset(int offset) { m_vertexOffset = offset; }
private:
    char m_pad0C8[0x300 - 0xC8];
    int m_vertexOffset;              // +0x300
    char m_pad304[0x310 - 0x304];
    Rva0017368AMesh **m_state;       // +0x310
};

namespace Debug_Statistics { void Record_DX8_Skin_Polys_And_Vertices(int polys, int verts); }

struct VertexFormatXYZNDUV2
{
    float x, y, z;
    float nx, ny, nz;
    unsigned diffuse;
    float u1, v1;
    float u2, v2;
};

struct Rva0017368ATask
{
    Rva0017368AMesh *Get_Mesh() { return mesh; }
    Rva0017368AMesh *mesh;
    char unknown[28];
};

unsigned Rva001736A7Compare(const Rva0017368ATask &a, const Rva0017368ATask &b);
// 0x00174870 is rowed as the STLport sort over these 32-byte records with a
// bool comparator (stlport_bfmeassignrecord32_sort.cpp), as
// FXShaderRendererFlushRenderingTasks.cpp calls it.
struct BfmeAssignRecord32;
namespace _STL {
template<class It, class Cmp> void sort(It first, It last, Cmp comp);
}
typedef bool (*BfmeAssignRecord32Less)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);

class DynamicVBAccessClass
{
public:
    DynamicVBAccessClass(unsigned type, unsigned format_index, unsigned short vertex_count, unsigned declaration);
    ~DynamicVBAccessClass();

    class WriteLock
    {
    public:
        WriteLock(DynamicVBAccessClass *vb);
        ~WriteLock();
        VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return (VertexFormatXYZNDUV2 *)m_data; }
    private:
        DynamicVBAccessClass *m_owner;
        void *m_data;
        int m_guard;
    };

private:
    const void *m_format;
    unsigned m_type, m_formatIndex, m_declaration;
    unsigned short m_vertexCount, m_vertexOffset;
    void *m_buffer;
};

#include "DX8WrapperClass.h"

#include "Rva00DF6F94GapFillerContext.h"

class FXShaderRenderer
{
public:
    void PerformRendering(int begin, int end);	// 0x0017438B (WB PerformRendering)
    void FlushSoftwareSkinnedRenderingTasks();
    void rva00173C04(Rva0017368AMesh *mesh, void *dest_verts);
private:
    char m_pad00[0x0C];
    struct TaskList
    {
        bool empty() const { return m_begin == m_end; }
        Rva0017368ATask *begin() { return m_begin; }
        Rva0017368ATask *end() { return m_end; }
        Rva0017368ATask *m_begin;
        Rva0017368ATask *m_end;
    } m_tasks; // +0x0C
};

typedef char Rva00173C04CacheSize[(sizeof(DynamicVectorClass<Vector3>) == 24) ? 1 : -1];
typedef char Rva00173C04VertexSize[(sizeof(VertexFormatXYZNDUV2) == 44) ? 1 : -1];

void FXShaderRenderer::rva00173C04(Rva0017368AMesh *mesh, void *dest_verts)
{
    static DynamicVectorClass<Vector3> _TempVertexBuffer;
    static DynamicVectorClass<Vector3> _TempNormalBuffer;

    MeshModelClass *mmc = mesh->Peek_Model();
    int mesh_vertex_count = mmc->Get_Vertex_Count();
    Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Get_Num_Polys(), mesh_vertex_count);

    if (_TempVertexBuffer.Length() < mesh_vertex_count) _TempVertexBuffer.Resize(mesh_vertex_count);
    if (_TempNormalBuffer.Length() < mesh_vertex_count) _TempNormalBuffer.Resize(mesh_vertex_count);

    Vector3 *loc = &(_TempVertexBuffer[0]);
    Vector3 *norm = &(_TempNormalBuffer[0]);
    const Vector2 *uv0 = mmc->Get_UV_Array_By_Index(0);
    const Vector2 *uv1 = mmc->Get_UV_Array_By_Index(1);
    const unsigned *diffuse = mmc->Get_Color_Array(0, false);

    VertexFormatXYZNDUV2 *verts = (VertexFormatXYZNDUV2 *)dest_verts;

    mesh->Get_Deformed_Vertices(loc, norm);

    for (int v = 0; v < mesh_vertex_count; ++v) {
        verts[v].x = (*loc)[0];
        verts[v].y = (*loc)[1];
        verts[v].z = (*loc)[2];
        verts[v].nx = (*norm)[0];
        verts[v].ny = (*norm)[1];
        verts[v].nz = (*norm)[2];
        if (diffuse) {
            verts[v].diffuse = *diffuse++;
        }
        else {
            verts[v].diffuse = 0xFFFFFFFF;
        }
        if (uv0) {
            verts[v].u1 = (*uv0)[0];
            verts[v].v1 = (*uv0)[1];
            uv0++;
        }
        else {
            verts[v].u1 = 0.0f;
            verts[v].v1 = 0.0f;
        }
        if (uv1) {
            verts[v].u2 = (*uv1)[0];
            verts[v].v2 = (*uv1)[1];
            uv1++;
        }
        else {
            verts[v].u2 = 0.0f;
            verts[v].v2 = 0.0f;
        }
        loc++;
        norm++;
    }
}

// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ @0x001748E8
void FXShaderRenderer::FlushSoftwareSkinnedRenderingTasks()
{
    if (m_tasks.empty())
        return;

    _STL::sort((BfmeAssignRecord32 *)m_tasks.begin(), (BfmeAssignRecord32 *)m_tasks.end(), (BfmeAssignRecord32Less)&Rva001736A7Compare);

    int verticesToSkin = 0;
    for (Rva0017368ATask *it = m_tasks.begin(); it != m_tasks.end(); ++it) {
        Rva0017368AMesh *mesh = it->Get_Mesh();
        if (mesh->Get_State()) {
            if (*mesh->Get_State() == 0) {
                *mesh->Get_State() = mesh;
                verticesToSkin += mesh->Peek_Model()->Get_Vertex_Count();
            }
        } else {
            verticesToSkin += mesh->Peek_Model()->Get_Vertex_Count();
        }
    }

    Rva0017368ATask *batchStart = m_tasks.begin();
    while (batchStart != m_tasks.end()) {
        Rva0017368ATask *task = batchStart;
        int budget = verticesToSkin;
        if (budget > 0xFFFF)
            budget = 0xFFFF;
        DynamicVBAccessClass vb(2, 5, (unsigned short)budget, 0);
        {
            DynamicVBAccessClass::WriteLock lock(&vb);
            VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();
            int used = 0;
            int offset = 0;
            for (; task != m_tasks.end(); ++task) {
                Rva0017368AMesh *mesh = task->Get_Mesh();
                if (!mesh->Get_State() || mesh == *mesh->Get_State()) {
                    if (mesh->Peek_Model()->Get_Vertex_Count() + used > budget)
                        break;
                    rva00173C04(mesh, verts + used);
                    offset = used;
                    used += mesh->Peek_Model()->Get_Vertex_Count();
                }
                mesh->Set_Offset(offset);
            }
            verticesToSkin -= used;
        }
        DX8Wrapper::Set_Vertex_Buffer(vb);
        PerformRendering((int)batchStart, (int)task);
        batchStart = task;
    }
    ((Rva00DF6F94GapFillerContext *)this)->rva00174350();
}
