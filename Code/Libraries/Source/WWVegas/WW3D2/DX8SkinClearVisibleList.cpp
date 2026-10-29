// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WW3D2 /ICode
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp,
// DX8SkinFVFCategoryContainer::clearVisibleSkinList. Target evidence: matched
// Reset at 0x1444B0 calls this helper; retail fields are head+F0, tail+F4,
// vertex count+E8 and mesh next-visible+304. Ghidra's 67-byte extent is three
// bytes short of the full ret-terminated body; retail returns at 0x143CA5 and
// the following CC starts at 0x143CA6.
// ZH dx8renderer.cpp Render semantic source; BFME1 revision9cbfb551fe20.
// WB9DAE60 names target148520 and source1383..1527. Native full1400B
// ends148A98 after dynamicVB cleanup13A780 (queue1379 cuts the call).
// CurMatDesc is +0x94.
// Queue-drain spelling follows the EA donor; see skin-render-00148520-20261019.md.
#include <stddef.h>
#include "vector3.h"
#include "vector2.h"
#include "vector.h"
#include "multilist.h"

// Bind the out-of-line vector members to their rowed providers.
template <> VectorClass<Vector3>::VectorClass(int, const Vector3 *);
// Declaring the dtor only stops cl synthesizing this unit's copy of the scalar
// deleting destructor; retail's is 0x000F1CF7.
template <> VectorClass<Vector3>::~VectorClass();
template <> bool VectorClass<Vector3>::operator==(VectorClass<Vector3> const &) const;
// Define the destructor here, in the default context, as mesh.cpp/collect.cpp emit it.
template <> inline DynamicVectorClass<Vector3>::~DynamicVectorClass() {}
template <> bool VectorClass<Vector3>::Resize(int, const Vector3 *);
template <> __declspec(dllimport) __forceinline DynamicVectorClass<Vector3>::DynamicVectorClass(unsigned size, const Vector3 *array)
    : VectorClass<Vector3>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
// Render inlines DynamicVectorClass<Vector3>::Resize, but retail's out-of-line
// body is the size-optimised 0x000F0CF9 (FXShaderRendererSkin.cpp emits it):
// expand the stock body here without emitting a copy.
template <> __declspec(dllimport) __forceinline bool DynamicVectorClass<Vector3>::Resize(int newsize, Vector3 const *array)
{
	if (VectorClass<Vector3>::Resize(newsize, array)) {
		if (Length() < ActiveCount) ActiveCount = Length();
		return(true);
	}
	return(false);
}

// BFME's aligned-buffer layout; destruction binds the rowed providers.
// Render expands the aligned-buffer constructor in its unwind graph.
// Retail's DynamicVectorClass<Vector3> deleting destructor is the size-optimised
// FXShaderRendererSkin.cpp body; this TU emits its copy in RefCountClass's context.
#pragma optimize("s", on)
class RefCountClass
{
public:
    RefCountClass() : NumRefs(1) {}
    virtual void Delete_This();
protected:
    virtual ~RefCountClass();
private:
    int NumRefs;
};

#pragma optimize("", on)

template <class T> class ShareBufferClass : public RefCountClass
{
public:
    ShareBufferClass(int count, const char *msg, int alignment = 0);
    virtual ~ShareBufferClass();
    T *Get_Array() { return Array; }
protected:
    T *RawBuffer;
    T *Array;
    int Count;
    int Alignment;
};

// The inlined allocation path retains Render's native unwind states.
template <> __declspec(dllimport) __forceinline
ShareBufferClass<unsigned>::ShareBufferClass(int count, const char *msg, int alignment)
    : Count(count), Alignment(alignment)
{
    if (Alignment == 0) {
        RawBuffer = new unsigned[Count];
        Array = RawBuffer;
    } else {
        RawBuffer = (unsigned *)new char[Count * sizeof(unsigned) + Alignment];
        Array = (unsigned *)(((unsigned int)RawBuffer + Alignment - 1) & ~(Alignment - 1));
    }
}

class UVBufferClass : public ShareBufferClass<Vector2>
{
public:
    UVBufferClass(int count, const char *msg);
private:
    unsigned CRC;
public:
	~UVBufferClass();
};

// Layout as FXShaderRendererSkin.cpp reads it; +0x0C is BFME's legacy UV source.
class MeshMatDescClass
{
public:
    // Render expands these accessors; their out-of-line bodies have rowed owners.
    __declspec(dllimport) __forceinline Vector2 *Get_UV_Array(int pass, int stage);
    __declspec(dllimport) __forceinline Vector2 *Get_UV_Array_By_Index(int index, bool create);
    unsigned *Get_Color_Array(int index, bool create);
    int PassCount;
    int VertexCount;
    int PolyCount;
    int LegacyUVSource;
    UVBufferClass *UV[8];
    int UVSource[4][2];
    ShareBufferClass<unsigned> *ColorArray[2];
};

__declspec(dllimport) __forceinline Vector2 *MeshMatDescClass::Get_UV_Array(int pass, int stage)
{
    if (UVSource[pass][stage] == -1) {
        return NULL;
    }
    if (UV[UVSource[pass][stage]] != NULL) {
        return UV[UVSource[pass][stage]]->Get_Array();
    }
    return NULL;
}

__declspec(dllimport) __forceinline Vector2 *MeshMatDescClass::Get_UV_Array_By_Index(int index, bool create)
{
    if (create && !UV[index]) {
        UV[index] = new UVBufferClass(VertexCount, "MeshMatDescClass::UV");
    }
    if (!create && LegacyUVSource != 0 && index < 2) {
        return Get_UV_Array(0, index);
    }
    if (UV[index] != NULL) {
        return UV[index]->Get_Array();
    }
    return NULL;
}

inline unsigned *MeshMatDescClass::Get_Color_Array(int index, bool create)
{
    if (create && !ColorArray[index]) {
        ColorArray[index] = new ShareBufferClass<unsigned>(VertexCount, "MeshMatDescClass::ColorArray");
    }
    if (ColorArray[index]) {
        return ColorArray[index]->Get_Array();
    }
    return NULL;
}

// Polygon count +0x24 and vertex count +0x28 as in Zero Hour's MeshGeometryClass; Check_If_Mesh_Fits
// reads the pass count through CurMatDesc +0x94 (BFME1's image reads the pair at +0x9C/+0x24).
class MeshModelClass
{
public:
    unsigned char pad[0x24];
    int PolygonCount;
    int VertexCount;
    unsigned char pad1[0x94 - 0x2C];
    MeshMatDescClass *CurMatDesc;
    __declspec(dllimport) __forceinline const Vector2 *Get_UV_Array_By_Index(int index)
    { return CurMatDesc->Get_UV_Array_By_Index(index, false); }
    unsigned *Get_Color_Array(int array_index, bool create = true)
    { return CurMatDesc->Get_Color_Array(array_index, create); }
    int Get_Vertex_Count() const
    { return VertexCount; }
    int Get_Pass_Count() const
    { return CurMatDesc->PassCount; }
    int Get_Polygon_Count() const
    { return PolygonCount; }
};

// Mesh vtable slots +0x28 (Get_Num_Polys) and +0x64 (Get_Alpha); +0x310 is the
// skin anchor slot Render shares between meshes of one deformation.
class MeshClass
{
public:
    virtual void vt0(); virtual void vt4(); virtual void vt8(); virtual void vtC();
    virtual void vt10(); virtual void vt14(); virtual void vt18(); virtual void vt1C();
    virtual void vt20(); virtual void vt24();
    virtual int Get_Num_Polys() const;
    virtual void vt2C(); virtual void vt30(); virtual void vt34(); virtual void vt38();
    virtual void vt3C(); virtual void vt40(); virtual void vt44(); virtual void vt48();
    virtual void vt4C(); virtual void vt50(); virtual void vt54(); virtual void vt58();
    virtual void vt5C(); virtual void vt60();
    virtual float Get_Alpha() const;
    MeshModelClass *Peek_Model() { return Model; }
    int Get_Base_Vertex_Offset() { return BaseVertexOffset; }
    void Set_Base_Vertex_Offset(unsigned offset) { BaseVertexOffset = offset; }
    MeshClass *Peek_Next_Visible_Skin() { return NextVisibleSkin; }
    void Set_Next_Visible_Skin(MeshClass *next) { NextVisibleSkin = next; }
    MeshClass **Get_Anchor() { return Anchor; }
    void Get_Deformed_Vertices(Vector3 *dst_vert, Vector3 *dst_norm);
private:
    char pad[0xC4 - 4];
    MeshModelClass *Model;
    char gapC8[0x238];
    unsigned BaseVertexOffset;
    MeshClass *NextVisibleSkin;
    char gap308[8];
    MeshClass **Anchor;
};

struct VertexFormatXYZNDUV2
{
    float x, y, z;
    float nx, ny, nz;
    unsigned diffuse;
    float u1, v1;
    float u2, v2;
};

class DynamicVBAccessClass
{
public:
    DynamicVBAccessClass(unsigned type, unsigned fvf, unsigned short vertex_count, unsigned declaration);
    ~DynamicVBAccessClass();
    class WriteLock
    {
    public:
        WriteLock(DynamicVBAccessClass *vb);
        ~WriteLock();
        VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() const { return Vertices; }
    private:
        void *Owner;
        VertexFormatXYZNDUV2 *Vertices;
        char Locked;
    };
private:
    void *FVFInfo;
    unsigned Type, Index, Declaration;
    unsigned short VertexCount, VertexBufferOffset;
    void *VertexBuffer;
};

class VertexBufferClass;

// Only the index count matters here: BFME's is a full unsigned at +0x0C (the
// retail compare is unsigned), where Zero Hour's header has an unsigned short.
class IndexBufferClass
{
public:
    unsigned char pad[0x0C];
    unsigned index_count;
    unsigned Get_Index_Count() const
    { return index_count; }
};

class DX8Wrapper
{
public:
    static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass &vba);
    static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
};

namespace Debug_Statistics { void Record_DX8_Skin_Polys_And_Vertices(int polys, int vertices); }

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
    void Render();
};

class MaterialPassClass;

// Add_Visible_Material_Pass is rowed at 0x00144CB0 in DX8RigidDelayedMaterialPass.cpp.
class DX8FVFCategoryContainer
{
public:
    virtual ~DX8FVFCategoryContainer();
    void Add_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
protected:
    bool Render_Procedural_Material_Passes();
    char pad[4];
    MultiListClass<DX8TextureCategoryClass> texture_category_list[4];
    MultiListClass<DX8TextureCategoryClass> visible_texture_category_list[4];
    void *visible_matpass_head;
    void *visible_matpass_tail;
    IndexBufferClass *index_buffer;	// +0xD0
    unsigned used_indices;			// +0xD4
    unsigned FVF;
    unsigned passes;				// +0xDC
    unsigned dynamic_fvf_type;
    bool sorting;					// +0xE4
    bool AnythingToRender;			// +0xE5
};

class DX8SkinFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
    virtual void Render();
    virtual void Add_Mesh(MeshModelClass *mmc);
    virtual void Log(bool only_visible);
    virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);
    virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
    void Add_Visible_Skin(MeshClass *mesh);
private:
    void clearVisibleSkinList();
    unsigned VisibleVertexCount;	// +0xE8
    unsigned VisibleSkinCount;		// +0xEC
    MeshClass *VisibleSkinHead;		// +0xF0
    MeshClass *VisibleSkinTail;		// +0xF4
};

typedef char CurMatDescOffset[(offsetof(MeshModelClass, CurMatDesc) == 0x94) ? 1 : -1];
typedef char PolygonCountOffset[(offsetof(MeshModelClass, PolygonCount) == 0x24) ? 1 : -1];
typedef char ContainerBaseSize[(sizeof(DX8FVFCategoryContainer) == 0xE8) ? 1 : -1];
typedef char MeshSize[(sizeof(MeshClass) == 0x314) ? 1 : -1];

void DX8SkinFVFCategoryContainer::clearVisibleSkinList()
{
    while (VisibleSkinHead != NULL) {
        MeshClass *next = VisibleSkinHead->Peek_Next_Visible_Skin();
        VisibleSkinHead->Set_Next_Visible_Skin(NULL);
        VisibleSkinHead = next;
    }
    VisibleSkinHead = NULL;
    VisibleSkinTail = NULL;
    VisibleVertexCount = 0;
    VisibleSkinCount = 0;
}

void DX8SkinFVFCategoryContainer::Add_Visible_Skin(MeshClass *mesh)
{
    if (mesh->Peek_Next_Visible_Skin() != NULL || mesh == VisibleSkinTail)
        return;
    if (VisibleSkinHead == NULL)
        VisibleSkinTail = mesh;
    mesh->Set_Next_Visible_Skin(VisibleSkinHead);
    VisibleSkinHead = mesh;
    VisibleVertexCount += mesh->Peek_Model()->Get_Vertex_Count();
}

// ?Check_If_Mesh_Fits@DX8SkinFVFCategoryContainer@@UAE_NPAVMeshModelClass@@@Z
// Retail 0x00143C20, 54 bytes: slot 4 of the container vtable 0x007D3544, in
// Zero Hour's DX8FVFCategoryContainer order (~, Render, Add_Mesh, Log,
// Check_If_Mesh_Fits, then the two Delayed passes; the rigid container's table
// just before it has the same shape). Aligning that table against lotrbfme.exe
// names this slot DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits, and the body
// sits right before the rowed clearVisibleSkinList. It is Zero Hour's body
// minus the gap-filler branch, which BFME's skin container does not have
// (BFME1 matched the same shape at 55 bytes).
bool DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits(MeshModelClass* mmc)
{
    if (!index_buffer) return true;	// No IB created - mesh will fit as a new ib will be created when inserting
    int required_polygons=mmc->Get_Polygon_Count();

    if ((required_polygons*3*mmc->Get_Pass_Count())<=index_buffer->Get_Index_Count()-used_indices) {
        return true;
    }
    return false;
}

// ?Add_Delayed_Visible_Material_Pass@DX8SkinFVFCategoryContainer@@UAEXPAVMaterialPassClass@@PAVMeshClass@@@Z
// retail 0x001460B0 (vtable slot 5): Zero Hour's dx8renderer.h inline, a tail jump to Add_Visible_Material_Pass.
// Select-any like the header copies other units emit; the anchor below keeps this noinline body emitted.
__declspec(noinline) inline void DX8SkinFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    Add_Visible_Material_Pass(pass, mesh);
}

// ?bfmeAnchorSkinAddDelayedVisibleMaterialPass absent-from-retail
void bfmeAnchorSkinAddDelayedVisibleMaterialPass(DX8SkinFVFCategoryContainer *container, MaterialPassClass *pass, MeshClass *mesh)
{
    container->DX8SkinFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(pass, mesh);
}

// Retail 0x00148520, vtable 0x00BD3544 slot 1. BFME adds the anchor slot: a mesh whose
// anchor already holds a rendered mesh reuses that mesh's vertex offset instead of skinning.
void DX8SkinFVFCategoryContainer::Render()
{
    static DynamicVectorClass<Vector3> _TempVertexBuffer;
    static DynamicVectorClass<Vector3> _TempNormalBuffer;

    if (!AnythingToRender) {
        return;
    }
    AnythingToRender=false;

    DX8Wrapper::Set_Vertex_Buffer((const VertexBufferClass *)NULL, 0);	// Free up the reference to the current vertex buffer
                                                                        // (in case it is the dynamic, which may have to be resized)

    //'Generals' customization to allow more than 65535 vertices
    unsigned int maxVertexCount=VisibleVertexCount;
    if (maxVertexCount > 65535)
    {	//clamp vertex count to maximum size that can be indexed by 16-bit index
        maxVertexCount = 65535;
    }

    DynamicVBAccessClass vb(sorting ? 3 : 2, 5, maxVertexCount, 0);

    unsigned int renderedVertexCount=0;

    MeshClass * mesh = VisibleSkinHead;
    MeshClass * remainingMesh = VisibleSkinHead;
    while (renderedVertexCount < VisibleVertexCount)
    {	mesh = remainingMesh;
        {	DynamicVBAccessClass::WriteLock l(&vb);
            VertexFormatXYZNDUV2 * dest_verts = l.Get_Formatted_Vertex_Array();
            unsigned vertex_offset=0;
            remainingMesh = NULL;

            while (mesh != NULL) {

                MeshModelClass * mmc = mesh->Peek_Model();
                int mesh_vertex_count=mmc->Get_Vertex_Count();
                //'Generals' mod to deal with cases where not all meshes fit in VB.
                if (vertex_offset+mesh_vertex_count > maxVertexCount || remainingMesh)
                {	//flag mesh so we know it didn't fit in the vertex buffer
                    mesh->Set_Base_Vertex_Offset(65535);
                    if (remainingMesh == NULL)
                        remainingMesh = mesh;	//start of meshes that didn't fit in buffer
                    mesh = mesh->Peek_Next_Visible_Skin();	//skip rendering this mesh
                    continue;
                }

                if (mesh->Get_Anchor() && *mesh->Get_Anchor()) {
                    Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);
                    mesh->Set_Base_Vertex_Offset((*mesh->Get_Anchor())->Get_Base_Vertex_Offset());
                    mesh = mesh->Peek_Next_Visible_Skin();
                    renderedVertexCount += mesh_vertex_count;
                    continue;
                }

        // If this assert hits, a skinned mesh has probably been added to the scene more than once.
        // Example: A skinned mesh was added to the scene then it was attached to a bone without being removed from the scene.
                Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);

                if (_TempVertexBuffer.Length() < mesh_vertex_count) _TempVertexBuffer.Resize(mesh_vertex_count);
                if (_TempNormalBuffer.Length() < mesh_vertex_count) _TempNormalBuffer.Resize(mesh_vertex_count);

                Vector3* loc=&(_TempVertexBuffer[0]);
                Vector3* norm=&(_TempNormalBuffer[0]);
                const Vector2* uv0=mmc->Get_UV_Array_By_Index(0);
                const Vector2* uv1=mmc->Get_UV_Array_By_Index(1);
                const unsigned* diffuse=mmc->Get_Color_Array(0,false);

                VertexFormatXYZNDUV2* verts=dest_verts+vertex_offset;

                mesh->Get_Deformed_Vertices(loc,norm);

                for (int v=0;v<mesh_vertex_count;++v) {
                    verts[v].x=(*loc)[0];
                    verts[v].y=(*loc)[1];
                    verts[v].z=(*loc)[2];
                    verts[v].nx=(*norm)[0];
                    verts[v].ny=(*norm)[1];
                    verts[v].nz=(*norm)[2];
                    if (diffuse) {
                        verts[v].diffuse=*diffuse++;
                    }
                    else {
                        verts[v].diffuse=0;
                    }
                    if (uv0) {
                        verts[v].u1=(*uv0)[0];
                        verts[v].v1=(*uv0)[1];
                        uv0++;
                    }
                    else {
                        verts[v].u1=0.0f;
                        verts[v].v1=0.0f;
                    }
                    if (uv1) {
                        verts[v].u2=(*uv1)[0];
                        verts[v].v2=(*uv1)[1];
                        uv1++;
                    }
                    else {
                        verts[v].u2=0.0f;
                        verts[v].v2=0.0f;
                    }

                    loc++;
                    norm++;
                }

                float alpha = mesh->Get_Alpha();
                if (alpha < 1.0f) {
                    unsigned int alpha_bits = (unsigned int)(255.0f * alpha);
                    alpha_bits <<= 24;
                    for (int v=0;v<mesh_vertex_count;++v) {
                        verts[v].diffuse = (verts[v].diffuse & 0x00FFFFFF) | alpha_bits;
                    }
                }

                mesh->Set_Base_Vertex_Offset(vertex_offset);
                if (mesh->Get_Anchor()) {
                    *mesh->Get_Anchor() = mesh;
                }
                vertex_offset+=mesh_vertex_count;
                renderedVertexCount += mesh_vertex_count;

                mesh = mesh->Peek_Next_Visible_Skin();
            }	//while
        }//lock

        DX8Wrapper::Set_Vertex_Buffer(vb);
        DX8Wrapper::Set_Index_Buffer(index_buffer,0);

        //Flush the meshes which fit in the vertex buffer, applying all texture variations
        for (unsigned pass=0;pass<passes;++pass) {
            MultiListIterator<DX8TextureCategoryClass> it(&visible_texture_category_list[pass]);
            while (!it.Is_Done()) {
                it.Peek_Obj()->Render();
                it.Next();
            }
        }

        Render_Procedural_Material_Passes();

        for (MeshClass *m = VisibleSkinHead; m != NULL; m = m->Peek_Next_Visible_Skin()) {
            if (m->Get_Anchor()) {
                *m->Get_Anchor() = NULL;
            }
        }
    }//while

    //remove all the rendered data from queues
    for (unsigned pass=0;pass<passes;++pass) {
        while (DX8TextureCategoryClass * tex = visible_texture_category_list[pass].Remove_Head()) {
        }
    }

    clearVisibleSkinList();
}
