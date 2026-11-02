// Target facts (BFME 2 1.06; code addresses are RVAs, tables are VAs):
// Constructors 0x00168F30 and 0x0016A230 install 0x00BD43D0 at +0 and
// 0x00BD43CC at +8. Destructor 0x0016CCC0 restores both at 0x0016CCE3/16CCE9;
// its later 0x00BC650C store at 0x0016CD12 is RefCountClass base teardown.
// RefCountClass constructor 0x00072882 initializes NumRefs +4 to 1 and that
// base table. Both geometry constructors initialize the same count, install
// MultiListObjectClass's 0x00BC5C6C at +8 and clear its node at +0x0C.
// Destructor call 0x0016CD09 passes this+8 to ~MultiListObjectClass 0x006109C0.
// The secondary table has one slot: thunk 0x00169FF0 subtracts 8 from this
// and jumps to geometry's deleting destructor 0x0016D790. The adjacent primary
// table has six slots: Delete_This 0x0006CE57, deleting destructor 0x0016D790,
// Load_W3D 0x0016D810, Compute_Plane_Equations 0x0016A850,
// Compute_Vertex_Normals 0x0016CFC0 and Compute_Bounds 0x0016A9F0.
// ShareBuffer<Vector3i16>'s constructor stores the next table 0x00BD43E8
// at 0x001696A7, bounding the geometry primary table to those six slots.
// Load_W3D returns bool; normal computation takes Vector3* and bool (RET 8).
// Geometry's constructor writes through +0x88; MeshModel constructors
// 0x001727E0/172940 call it and start their own pointer stores at +0x8C.
// The complete geometry extent is 0x8C. The empty W3DMPO base has no vptr.
// Name +0x10 is read by 0x0016A6B0 and set from the header by 0x0016D810;
// user text +0x14 is read by 0x0016A780 and filled by chunk reader 0x0016B0E0.
// Flags +0x18 is masked by 0x0016A850/16A9F0; loader 0x0016D810 copies a
// signed byte SortLevel +0x1C and W3dAttributes dword +0x20. Counts +0x24/28,
// Poly +0x2C, Vertex +0x30 and CullTree +0x88 feed 0x0016AD10's tree builder.
// 0x0016AE70 selects vertex pointers +0x30/34; 0x0016AAE0 selects normals
// +0x38/3C. Reset 0x0016A320 allocates the Vector3 buffers +0x40/44 with
// VertexTangents/VertexBinormals strings. Accessors 0x0016AC00,16A010,16A0C0
// establish planes +0x48, shade indices +0x4C and four ushort bone links per
// vertex +0x50. 0x0016A170 allocates ushort buffer +0x54; 0x0016B1A0 writes
// first-bone/run-length pairs through it. Reset/assignment 0x0016A320/168FE0
// release buffer +0x5C; constructor 0x00169B00 gives its elements stride 16.
// Surface bytes +0x58 are read by 0x0016A220. Bounds 0x0016A9F0 and getters
// 0x001692F0/169370 establish Vector3 min +0x60, max +0x6C, center +0x78
// and float radius +0x84. Copy constructor 0x0016A230 calls assignment
// 0x00168FE0 at 0x0016A302; both and the destructor remain out of line.
// 0x0016B39E sets flag 0x400 inline at +0x18; the integer Set_Flag overload
// uses the same flag operation as Zero Hour's enum-taking inline accessor.
// Rowed accessors: Get_Vertex_Array 0x00709BE0, Get_Vertex_Normal_Array
// 0x0016AB90, Get_Vertex_Shade_Index_Array 0x0016CCB0,
// Get_Vertex_Bone_Links 0x0018C30E, Get_Poly_Surface_Type_Array 0x0016A000,
// Get_Poly_Surface_Type 0x0016A220, Get_Sort_Level 0x00143480,
// Set_Sort_Level 0x006BD4E0, Set_Flag 0x001494B0, Get_Flag 0x000D1AA1,
// rva0016ABC0 0x0016ABC0, rva0016ABE0 0x0016ABE0, rva0018C088 0x0018C088.
// Rowed operations: Compute_Ram_Size 0x0016ADC0, Compute_Plane 0x0016ACC0,
// Cast_Ray 0x0016D7B0, Intersect_OBBox 0x0016D7E0, Scale 0x0016B3F0,
// get_polys 0x000B49A1, cast_ray_brute_force 0x0016CE00,
// intersect_obbox_brute_force 0x0016CD30, read_chunks 0x0016D340,
// read_vertices 0x0016AE70, read_vertex_normals 0x0016AF40,
// read_triangles 0x0016B020, read_vertex_influences 0x0016B1A0,
// read_vertex_shade_indices 0x0016B3C0 and read_aabtree 0x001693A0.
// Set_Name 0x0016A6C0 and Set_User_Text 0x0016A790 replace their buffers.
// Other declarations below use their MeshGeometryClass ledger names; the
// neutral slot34/slot3C/slot54/slot5C names assert offsets only. Zero Hour's
// WW3D2/meshgeometry.h supplies the established member, flag and inline count
// accessor names; WWLib/multilist.h supplies the secondary base declaration.

#pragma once
#ifndef BFME2_WW3D2_MESHGEOMETRYCLASS_H
#define BFME2_WW3D2_MESHGEOMETRYCLASS_H
#define MESHGEOMETRY_H

#include "../WWLib/RefCountData.h"
#include "../WWMath/Vector3Data.h"
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/multilist.h"

template<class T> class ShareBufferClass;
class Vector3i16;
class Vector4;
class PlaneClass;
class AABoxClass;
class SphereClass;
class AABTreeClass;
class ChunkLoadClass;
class RayCollisionTestClass;
class OBBoxIntersectionTestClass;

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
    MeshGeometryClass();
    MeshGeometryClass(const MeshGeometryClass &that);
    virtual ~MeshGeometryClass();
    MeshGeometryClass &operator=(const MeshGeometryClass &that);

    enum FlagsType
    {
        DIRTY_BOUNDS = 0x1,
        DIRTY_PLANES = 0x2,
        DIRTY_VNORMALS = 0x4,
        SORT = 0x10,
        DISABLE_BOUNDING_BOX = 0x20,
        DISABLE_BOUNDING_SPHERE = 0x40,
        DISABLE_PLANE_EQ = 0x80,
        TWO_SIDED = 0x100,
        ALIGNED = 0x200,
        SKIN = 0x400,
        ORIENTED = 0x800,
        CAST_SHADOW = 0x1000,
        PRELIT_MASK = 0xE000,
        PRELIT_VERTEX = 0x2000,
        PRELIT_LIGHTMAP_MULTI_PASS = 0x4000,
        PRELIT_LIGHTMAP_MULTI_TEXTURE = 0x8000,
        ALLOW_NPATCHES = 0x10000
    };

    virtual bool Load_W3D(ChunkLoadClass &cload);
    void Reset_Geometry(int polycount, int vertcount, bool keepAlloc = true);
    const char *Get_Name() const;
    void Set_Name(const char *name);
    const char *Get_User_Text();
    void Set_User_Text(char *text);
    void Set_Flag(FlagsType flag, bool onoff);
    void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
    int Get_Flag(FlagsType flag);
    void Set_Sort_Level(int level);
    int Get_Sort_Level() const;
    int Get_Polygon_Count() const { return PolyCount; }
    int Get_Vertex_Count() const { return VertexCount; }
    int Get_Vertex_Count() { return VertexCount; }
    int Compute_Ram_Size();
    Vector3 *Get_Vertex_Array();
    const Vector3 *Get_Vertex_Normal_Array(bool alternate = false);
    const unsigned long *Get_Vertex_Shade_Index_Array(bool create = true);
    const unsigned short *Get_Vertex_Bone_Links();
    unsigned char *Get_Poly_Surface_Type_Array();
    unsigned char Get_Poly_Surface_Type(int poly_index) const;
    void Compute_Plane(int index, PlaneClass *plane) const;
    void Get_Bounding_Box(AABoxClass *box);
    void Get_Bounding_Sphere(SphereClass *sphere);
    bool Cast_Ray(RayCollisionTestClass &test);
    bool Intersect_OBBox(OBBoxIntersectionTestClass &test);
    void Scale(const Vector3 &scale);
    Vector3 *rva0016ABC0();
    Vector3 *rva0016ABE0();
    int rva0018C088() const;

protected:
    virtual void Compute_Plane_Equations(Vector4 *array);
    virtual void Compute_Vertex_Normals(Vector3 *array, bool alternate);
    virtual void Compute_Bounds(Vector3 *vertices);
    Vector3i16 *get_polys();
    Vector3 *get_vert_normals(bool alternate = false);
    Vector4 *get_planes(bool create = true);
    unsigned long *get_shade_indices(bool create = true);
    unsigned short *get_bone_links(bool create = true);
    unsigned short *get_buffer54(int count);
    void Generate_Culling_Tree();
    bool cast_ray_brute_force(RayCollisionTestClass &test);
    bool intersect_obbox_brute_force(OBBoxIntersectionTestClass &test);
    bool read_chunks(ChunkLoadClass &cload);
    bool read_vertices(ChunkLoadClass &cload, bool alternate);
    bool read_vertex_normals(ChunkLoadClass &cload, bool alternate);
    bool read_triangles(ChunkLoadClass &cload);
    bool read_user_text(ChunkLoadClass &cload);
    bool read_vertex_influences(ChunkLoadClass &cload);
    bool read_vertex_shade_indices(ChunkLoadClass &cload);
    bool read_aabtree(ChunkLoadClass &cload);

public:
    ShareBufferClass<char> *MeshName;
    ShareBufferClass<char> *UserText;
    int Flags;
    char SortLevel;
    unsigned long W3dAttributes;
    int PolyCount;
    int VertexCount;
    ShareBufferClass<Vector3i16> *Poly;
    ShareBufferClass<Vector3> *Vertex;
    ShareBufferClass<Vector3> *slot34;
    ShareBufferClass<Vector3> *VertexNorm;
    ShareBufferClass<Vector3> *slot3C;
    ShareBufferClass<Vector3> *VertexTangents;
    ShareBufferClass<Vector3> *VertexBinormals;
    ShareBufferClass<Vector4> *PlaneEq;
    ShareBufferClass<unsigned long> *VertexShadeIdx;
    ShareBufferClass<unsigned short> *VertexBoneLink;
    ShareBufferClass<unsigned short> *slot54;
    ShareBufferClass<unsigned char> *PolySurfaceType;
    RefCountClass *slot5C;
    Vector3 BoundBoxMin;
    Vector3 BoundBoxMax;
    Vector3 BoundSphereCenter;
    float BoundSphereRadius;
    AABTreeClass *CullTree;
};

typedef char MeshGeometryClass_size_check[(sizeof(MeshGeometryClass) == 0x8C) ? 1 : -1];

#endif
