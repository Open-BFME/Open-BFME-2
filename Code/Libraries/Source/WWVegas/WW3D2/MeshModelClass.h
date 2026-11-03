// Target facts (BFME 2 1.06; code addresses are RVAs, tables are VAs):
// Constructors 0x001727E0 and 0x00172940 (copy) call MeshGeometryClass's
// 0x00168F30/0x0016A230, then store their own tables 0x00BD46C4 at +0 and 0x00BD46C0
// at +8; destructor 0x00172AB0 stores the same pair first and ends by calling the
// list destructor 0x00144690 on +0x9C and ~MeshGeometryClass 0x0016CCC0, which
// restores the base tables 0x00BD43D0/0x00BD43CC. The class introduces no virtual
// slot: primary table 0x00BD46C4 has the base's six slots (Delete_This 0x0006CE57,
// deleting destructor 0x00172E50, Load_W3D override 0x0018BA10 and the base's
// 0x0016A850, 0x0016CFC0, 0x0016A9F0); the next word is not code. Secondary table
// 0x00BD46C0 has one slot, thunk 0x00172930 (this-8, jump to 0x00172E50).
// Deleting destructor 0x00172E50 and allocation sites 0x00149D16/0x00149C64 use the
// global operator new/delete (0x0002FDA0/0x0002FD60); both sites push 0xC4: sizeof.
// Constructor stores: +0x8C/+0x90/+0x94/+0x98 cleared, then 0x001728D5/0x001728DB
// store a new 0x118-byte MeshMatDescClass (0x0015B480) at +0x8C and +0x94, and
// 0x001728FD a new 0x38-byte MaterialInfoClass (0x001708D0) at +0x98. Copy
// constructor 0x00172940 copy-constructs +0x90 only when the source has one and
// calls clone_materials 0x001881C0; destructor 0x00172AB0 deletes +0x8C/+0x90
// through ~MeshMatDescClass 0x0015DC40 and releases +0x98 through its slot 0.
// 0x0017282C..0x00172858 inline a GenericMultiListClass at +0x9C (head node
// +0xA0..+0xB0) and install its table 0x00BD34E0, whose destructor 0x00144690 the
// destructors of this class and of DX8TextureCategoryClass (0x00144AF0) call;
// Peek_FVF_Category_Container 0x00172030 reads the head's object as a polygon
// renderer (its +0x0C category, the category's +0x34 container), as Zero Hour's
// MultiListClass<DX8PolygonRendererClass> member does.
// +0xB4/+0xB8 link every instance into a list headed by global 0x00DF6F90:
// constructors store the old head at +0xB8 and the head's address at +0xB4, and
// 0x0017289F points the next node's +0xB4 at this +0xB8; the destructor unlinks it
// at 0x00172B80, and 0x001718E0 walks +0xB8. +0xBC is cleared by both constructors;
// 0x001735F9 news 0x28 bytes, constructs them with 0x0018C54E, stores them at
// +0xBC and calls FXShaderGeometry::Init 0x0018C84E on them; Render_With_FX_Material
// 0x0014A880 calls FXShaderGeometry::Begin_Rendering 0x0018C09B through +0xBC.
// Byte +0xC0 is cleared by both constructors (0x00172876, 0x001729DA).
// Copy constructor, assignment 0x00171E60 and destructor stay out of line.
// Donor names: Zero Hour WW3D2/meshmdl.h (DefMatDesc, AlternateMatDesc, CurMatDesc,
// MatInfo, PolygonRendererList, HasBeenInUse, methods, defaults, friends) and
// WW3D2/dx8list.h (the list's element type); the m_B4/m_B8/m_BC placeholders
// assert offsets and retail types only. Every method below is a ledger row, except
// Peek_Texture, whose retail call target 0x00143560 reverse/symbols.csv names.

#pragma once
#ifndef BFME2_WW3D2_MESHMODELCLASS_H
#define BFME2_WW3D2_MESHMODELCLASS_H

#include "MeshGeometryClass.h"

class MeshMatDescClass;
class MaterialInfoClass;
class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;
class FXShaderGeometry;
class VertexMaterialClass;
class TextureClass;
class ShaderClass;
class HTreeClass;
class MeshLoadContextClass;
class MeshClass;
class MeshDeformSetClass;
class MeshDeformClass;
class DX8SkinFVFCategoryContainer;
class DX8MeshRendererClass;
template<class T> class RefCountPtr;

class MeshModelClass : public MeshGeometryClass
{
public:
    MeshModelClass();
    MeshModelClass(const MeshModelClass &that);
    virtual ~MeshModelClass();
    MeshModelClass &operator=(const MeshModelClass &that);

    void Reset(int polycount, int vertcount, int passcount, bool skinned);
    void Register_For_Rendering();
    void rva001716E0UnregisterMeshModel();
    bool rva00171720();
    void rva00171780();
    int Compute_Ram_Size();

    void Set_Pass_Count(int passes);
    int Get_Pass_Count() const;
    unsigned *Get_Color_Array(int array_index, bool create = true);
    void Set_Single_Material(VertexMaterialClass *vmat, int pass = 0);
    void Set_Single_Texture(const RefCountPtr<TextureClass> &tex, int pass = 0, int stage = 0);
    void Set_Single_Shader(ShaderClass shader, int pass = 0);
    VertexMaterialClass *Get_Single_Material(int pass = 0) const;
    ShaderClass Get_Single_Shader(int pass = 0) const;
    VertexMaterialClass *Peek_Single_Material(int pass = 0) const;
    RefCountPtr<TextureClass> Peek_Single_Texture(int pass = 0, int stage = 0) const;
    void Set_Material(int vidx, VertexMaterialClass *vmat, int pass = 0);
    void Set_Shader(int pidx, ShaderClass shader, int pass = 0);
    void Set_Texture(int pidx, const RefCountPtr<TextureClass> &tex, int pass = 0, int stage = 0);
    bool Has_Material_Array(int pass) const;
    bool Has_Shader_Array(int pass) const;
    bool Has_Texture_Array(int pass, int stage) const;
    ShaderClass Get_Shader(int pidx, int pass = 0) const;
    VertexMaterialClass *Peek_Material(int vidx, int pass = 0) const;
    RefCountPtr<TextureClass> Peek_Texture(int pidx, int pass = 0, int stage = 0) const;
    void Replace_Texture(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &new_texture);
    void Replace_VertexMaterial(VertexMaterialClass *vmat, VertexMaterialClass *new_vmat);

    void Make_Geometry_Unique();
    void Make_UV_Array_Unique(int pass = 0, int stage = 0);
    void Make_Color_Array_Unique(int array_index = 0);

    virtual bool Load_W3D(ChunkLoadClass &cload);

    void Enable_Alternate_Material_Description(bool onoff);
    bool Is_Alternate_Material_Description_Enabled();
    DX8FVFCategoryContainer *Peek_FVF_Category_Container();
    bool Needs_Vertex_Normals();
    void Init_For_NPatch_Rendering();

    void get_deformed_vertices(Vector3 *dst_vert, Vector3 *dst_norm, const HTreeClass *htree);
    void get_deformed_vertices(Vector3 *dst_vert, const HTreeClass *htree);

protected:
    bool read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_per_tri_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_fx_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_material_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_Rva00188AF0(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_dig(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_dcg(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_texture_stage(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_stage_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_Rva00189B50(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_per_face_texcoord_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context);

    void post_process();
    void post_process_fog();
    unsigned int get_sort_flags(int pass) const;
    unsigned int get_sort_flags() const;
    void compute_static_sort_levels();

    void install_materials(MeshLoadContextClass *loadinfo);
    void clone_materials(const MeshModelClass &srcmesh);
    void install_alternate_material_desc(MeshLoadContextClass *context);

public:
    MeshMatDescClass *DefMatDesc;
    MeshMatDescClass *AlternateMatDesc;
    MeshMatDescClass *CurMatDesc;
    MaterialInfoClass *MatInfo;
    MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
    MeshModelClass **m_B4;
    MeshModelClass *m_B8;
    FXShaderGeometry *m_BC;
    bool HasBeenInUse;

    friend class MeshClass;
    friend class MeshDeformSetClass;
    friend class MeshDeformClass;
    friend class MeshLoadContextClass;
    friend class DX8SkinFVFCategoryContainer;
    friend class DX8MeshRendererClass;
    friend class DX8PolygonRendererClass;
};

typedef char MeshModelClass_size_check[(sizeof(MeshModelClass) == 0xC4) ? 1 : -1];

#endif
