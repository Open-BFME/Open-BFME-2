// Target facts: MeshMatDescClass is a plain class with no bases or virtual functions. Constructors RVA 0x0015B480 and 0x0015DD10 and destructor RVA 0x0015DC40 never store a vptr; +0 is PassCount (1 at 0x0015B4B6), not a table. MeshModelClass allocates 0x118 bytes at 0x001728A9 and calls 0x0015B480 at 0x001728C5. Compute_Ram_Size (0x0015CAE0) starts with 0x118. The constructors initialize counts at +0/+4/+8, the owned state pointer at +0x0C, eight UV pointers at +0x10, UVSource[4][2] at +0x30, two color buffers at +0x50, source arrays at +0x58/+0x68, eight four-byte texture handles at +0x78, four shaders at +0x98, materials at +0xA8, references at +0xB8, TextureArray[4][2] at +0xC8, MaterialArray[4] at +0xE8, ShaderArray[4] at +0xF8 and references at +0x108 (0x0015B4B6..0x0015B58B). No original name is established for +0x0C/+0xB8/+0x108.
// Target facts: destructor 0x0015DC40 calls Reset (0x0015D140), then destroys eight handles at +0x78 with stride 4 and RefCountPtr<TextureClass> destructor 0x0017098D (0x0015DC70..0x0015DC85). The constructor uses the same stride, count and destructor at 0x0015B49C..0x0015B4C5. Copy constructor 0x0015DD10 calls assignment 0x0015D800 at 0x0015DE24. Get_UV_Array 0x000D1F1A proves UVSource/+0x30 and UV/+0x10; Get_Color_Array 0x000D1FBD proves +0x50; Get_DCG_Source 0x00188020 proves +0x58; Get_Shader 0x0015B6C0 proves +0x98/+0xF8; Peek_Material 0x0015A8E0 proves +0xA8/+0xE8; Get_Texture_Array 0x0015D360 indexes +0xC8 as two stages per pass. The +0xCC access in Compute_Ram_Size 0x0015CB7B is stage 1 of that array, not a separate field. Get_Rva0015B7A0 (0x0015B7A0) creates a reference-counted buffer in +0x108; read_Rva00188AF0 tests +0xB8/+0x108 at 0x00188B06/0x00188B10. Store_Pass0_State (0x0015D5B0) allocates 16 bytes and stores the pointer at +0x0C (0x0015D5F1..0x0015D610).
// Target facts: Get_Single_Material follows Zero Hour's inline Add_Ref and return of Material[pass]; the Collect_Materials row 0x001703D0 uses this sequence for single materials at 0x001704C0..0x001704D3. Out-of-line rows: Reset 0x0015D140; Init_Alternate 0x0015A1B0; Is_Empty 0x0015A6C0; Store_Pass0_State 0x0015D5B0; Get_UV_Array_Count 0x00143340; Install_UV_Array 0x0015B960; Set_UV_Source 0x0015A040; Get_UV_Array_By_Index 0x000D1F40; rva00188010 0x00188010; Set_Single_Material 0x0015A760; Set_Single_Texture 0x0015A7A0; Set_Single_Shader 0x0015A7E0; Peek_Single_Material 0x002C8ECF; Get_Single_Texture 0x0015A180; Peek_Single_Texture 0x000D2026; Get_Single_Shader 0x00143370; Set_Material 0x0015D2A0; Set_Texture 0x0015DCC0; Set_Shader 0x0015DCA0; Get_Texture 0x0015A910; Has_UV 0x00187F50; Has_Color_Array 0x00187F70; Has_Texture_Data 0x00187F80; Has_Shader_Data 0x00187FB0; Has_Material_Data 0x00187FE0; Has_Texture_Array 0x001433D0; Has_Shader_Array 0x001433B0; Get_Material_Array 0x0015B700; Get_Shader_Array 0x0015D450; Make_UV_Array_Unique 0x0015D510; Make_Color_Array_Unique 0x0015B840; Post_Load_Process 0x0015BB00; Do_Mappers_Need_Normals 0x0015A9F0; Configure_Material 0x0015A990; Disable_Backface_Culling 0x00188670; Set_Single_Rva0015A800 0x0015A800; Set_Rva0015D300 0x0015D300; rva0015B8C0 0x0015B8C0. The ledger supplies the out-of-line method names and signatures declared below, including the nonvirtual destructor, copy and assignment. Zero Hour GeneralsMD WW3D2/meshmatdesc.h supplies the common field names, dimensions and count/source accessor names; its W3DMPO base and raw texture API do not describe BFME2. Neutral field names retain the retail-only state and reference buffers.

#pragma once
#ifndef __BFME2_MESHMATDESCCLASS_H_
#define __BFME2_MESHMATDESCCLASS_H_

#include "ShaderClass.h"
#include "VertexMaterialClass.h"
#include "../../../../../reference/shims/bfmestreak/ref_ptr.h"

class MeshModelClass;
class MeshMatDescRendererState;
class Vector2;
class TextureClass;
class UVBufferClass;
class TexBufferClass;
class MatBufferClass;
class OpaqueRefBuffer;
template <class T> class ShareBufferClass;

class MeshMatDescClass
{
public:
    enum { MAX_PASSES = 4, MAX_TEX_STAGES = 2, MAX_COLOR_ARRAYS = 2, MAX_UV_ARRAYS = 8 };

    MeshMatDescClass();
    MeshMatDescClass(const MeshMatDescClass &that);
    ~MeshMatDescClass();
    MeshMatDescClass &operator=(const MeshMatDescClass &that);
    void Reset(int polycount, int vertcount, int passcount);
    void Init_Alternate(MeshMatDescClass &default_desc, MeshMatDescClass &alternate_desc);
    bool Is_Empty();
    int Compute_Ram_Size();
    void Store_Pass0_State(bool store);

    void Set_Pass_Count(int count) { PassCount = count; }
    int Get_Pass_Count() const { return PassCount; }
    void Set_Vertex_Count(int count) { VertexCount = count; }
    int Get_Vertex_Count() const { return VertexCount; }
    void Set_Polygon_Count(int count) { PolyCount = count; }
    int Get_Polygon_Count() const { return PolyCount; }

    Vector2 *Get_UV_Array(int pass, int stage);
    Vector2 *Get_UV_Array_By_Index(int index, bool create = true);
    int Get_UV_Array_Count();
    void Install_UV_Array(int pass, int stage, Vector2 *uvs, int count);
    void Set_UV_Source(int pass, int stage, int sourceindex);
    int Get_UV_Source(int pass, int stage) { return UVSource[pass][stage]; }
    unsigned *Get_Color_Array(int index, bool create = true);
    VertexMaterialClass::ColorSourceType Get_DCG_Source(int pass);
    void Set_DCG_Source(int pass, VertexMaterialClass::ColorSourceType source) { DCGSource[pass] = source; }
    void Set_DIG_Source(int pass, VertexMaterialClass::ColorSourceType source) { DIGSource[pass] = source; }
    VertexMaterialClass::ColorSourceType Get_DIG_Source(int pass) { return DIGSource[pass]; }
    void rva00188010(int pass, int value);

    void Set_Single_Material(VertexMaterialClass *material, int pass = 0);
    void Set_Single_Texture(const RefCountPtr<TextureClass> &texture, int pass = 0, int stage = 0);
    void Set_Single_Shader(ShaderClass shader, int pass = 0);
    VertexMaterialClass *Get_Single_Material(int pass = 0) const { if (Material[pass]) Material[pass]->Add_Ref(); return Material[pass]; }
    VertexMaterialClass *Peek_Single_Material(int pass = 0) const;
    RefCountPtr<TextureClass> Get_Single_Texture(int pass = 0, int stage = 0) const;
    RefCountPtr<TextureClass> Peek_Single_Texture(int pass = 0, int stage = 0) const;
    ShaderClass Get_Single_Shader(int pass = 0) const;
    void Set_Material(int index, VertexMaterialClass *material, int pass = 0);
    void Set_Texture(int index, const RefCountPtr<TextureClass> &texture, int pass = 0, int stage = 0);
    void Set_Shader(int index, ShaderClass shader, int pass = 0);
    VertexMaterialClass *Peek_Material(int index, int pass = 0) const;
    RefCountPtr<TextureClass> Get_Texture(int index, int pass = 0, int stage = 0) const;
    ShaderClass Get_Shader(int index, int pass = 0) const;

    bool Has_UV(int pass, int stage);
    bool Has_Color_Array(int index);
    bool Has_Texture_Data(int pass, int stage) const;
    bool Has_Shader_Data(int pass);
    bool Has_Material_Data(int pass);
    bool Has_Texture_Array(int pass, int stage) const;
    bool Has_Shader_Array(int pass) const;
    bool Has_Material_Array(int pass) const { return MaterialArray[pass] != 0; }
    bool Has_Rva00188AF0_Data(int pass) { return field_B8[pass] != 0 || field_108[pass] != 0; }
    TexBufferClass *Get_Texture_Array(int pass, int stage, bool create = true);
    MatBufferClass *Get_Material_Array(int pass, bool create = true);
    ShaderClass *Get_Shader_Array(int pass, bool create = true);
    void Make_UV_Array_Unique(int pass, int stage);
    void Make_Color_Array_Unique(int index);
    void Post_Load_Process(bool enable_lighting = true, MeshModelClass *parent = 0);
    bool Do_Mappers_Need_Normals();
    void Set_Single_Rva0015A800(void *entry, int pass);
    void Set_Rva0015D300(int index, void *entry, int pass);
    OpaqueRefBuffer *Get_Rva0015B7A0(int pass, bool create);
    void rva0015B8C0();

protected:
    void Configure_Material(VertexMaterialClass *material, int pass, bool lighting_enabled);
    void Disable_Backface_Culling();

public:
    int PassCount;
    int VertexCount;
    int PolyCount;
    MeshMatDescRendererState *field_0C;
    UVBufferClass *UV[MAX_UV_ARRAYS];
    int UVSource[MAX_PASSES][MAX_TEX_STAGES];
    ShareBufferClass<unsigned> *ColorArray[MAX_COLOR_ARRAYS];
    VertexMaterialClass::ColorSourceType DCGSource[MAX_PASSES];
    VertexMaterialClass::ColorSourceType DIGSource[MAX_PASSES];
    RefCountPtr<TextureClass> Texture[MAX_PASSES][MAX_TEX_STAGES];
    ShaderClass Shader[MAX_PASSES];
    VertexMaterialClass *Material[MAX_PASSES];
    RefCountClass *field_B8[MAX_PASSES];
    TexBufferClass *TextureArray[MAX_PASSES][MAX_TEX_STAGES];
    MatBufferClass *MaterialArray[MAX_PASSES];
    ShareBufferClass<ShaderClass> *ShaderArray[MAX_PASSES];
    OpaqueRefBuffer *field_108[MAX_PASSES];
};

typedef char MeshMatDescClassSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

#endif
