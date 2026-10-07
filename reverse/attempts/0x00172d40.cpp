// ?Replace_VertexMaterial@MeshModelClass@@QAEXPAVVertexMaterialClass@@0@Z
// partial score=0.98 date=2026-10-07
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME2 mesh-model texture replacement, RVA 0x00172BF0 (329 bytes).
// Derived from EA Zero Hour GeneralsMD WW3D2/meshmdl.cpp (GPL-3.0-or-later).
// Retail keeps the stage/pass/polygon traversal, using owning texture handles.
// Verified layout: polygon count +0x24; current material description +0x94;
// polygon-renderer list +0x9C; description texture arrays +0xC8.
// RefCountPtr is the recovered handle model also used by MaterialInfoClass.
// Return-by-value temporaries release through TextureBaseClass::Release_Ref.
// The complete body and its 52-byte list-query and 31-byte array-query siblings
// place uniquely in retail. Callee identities were audited separately from bytes.
#include "multilist.h"
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr {
public:
    T *p;
    ~RefCountPtr() { if(p) p->Release_Ref(); }
    bool operator==(const RefCountPtr &other) const { return p==other.p; }
};
class VertexMaterialClass;
class DX8PolygonRendererClass;
class DX8FVFCategoryContainer {
public: void Change_Polygon_Renderer_Material(MultiListClass<DX8PolygonRendererClass>&, VertexMaterialClass*, VertexMaterialClass*, unsigned);
    void Change_Polygon_Renderer_Texture(MultiListClass<DX8PolygonRendererClass>&, const RefCountPtr<TextureClass>&, const RefCountPtr<TextureClass>&, unsigned, unsigned);
};
class DX8TextureCategoryClass {
    char gap[0x34];
    DX8FVFCategoryContainer *Container;
public: DX8FVFCategoryContainer *Get_Container() { return Container; }
};
class DX8PolygonRendererClass : public MultiListObjectClass {
    char gap[4];
    DX8TextureCategoryClass *TextureCategory;
public: DX8TextureCategoryClass *Get_Texture_Category() { return TextureCategory; }
};
class MeshMatDescClass {
public:
    int PassCount;
    char gap4[0xa4];
    VertexMaterialClass *Material[4];
    char gapB8[0x10];
    void *TextureArray[4][2];
    void *MaterialArray[4];
    VertexMaterialClass *Peek_Material(int,int) const;
    void Set_Material(int,VertexMaterialClass*,int);
    void Set_Single_Material(VertexMaterialClass*,int);
    void Set_Texture(int,const RefCountPtr<TextureClass>&,int,int);
    void Set_Single_Texture(const RefCountPtr<TextureClass>&,int,int);
};
class MeshModelClass {
    char prefix[0x24];
    int PolygonCount;
    int VertexCount;
    char gap2C[0x68];
    MeshMatDescClass *CurMatDesc;
    char gap98[4];
    MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
public:
    RefCountPtr<TextureClass> Peek_Texture(int,int,int) const;
    RefCountPtr<TextureClass> Peek_Single_Texture(int,int) const;
    int Get_Pass_Count() const { return CurMatDesc->PassCount; }
    int Get_Polygon_Count() const { return PolygonCount; }
    int Get_Vertex_Count() const { return VertexCount; }
    bool Has_Material_Array(int pass) const { return CurMatDesc->MaterialArray[pass]!=0; }
    VertexMaterialClass *Peek_Material(int i,int pass) const { return CurMatDesc->Peek_Material(i,pass); }
    VertexMaterialClass *Peek_Single_Material(int pass) const { return CurMatDesc->Material[pass]; }
    void Set_Material(int i,VertexMaterialClass *v,int pass) { CurMatDesc->Set_Material(i,v,pass); }
    void Set_Single_Material(VertexMaterialClass *v,int pass) { CurMatDesc->Set_Single_Material(v,pass); }
    void Replace_VertexMaterial(VertexMaterialClass*,VertexMaterialClass*);
    bool Has_Texture_Array(int pass,int stage) const { return CurMatDesc->TextureArray[pass][stage]!=0; }
    void Set_Texture(int i,const RefCountPtr<TextureClass>& texture,int pass,int stage) { CurMatDesc->Set_Texture(i,texture,pass,stage); }
    void Set_Single_Texture(const RefCountPtr<TextureClass>& texture,int pass,int stage) { CurMatDesc->Set_Single_Texture(texture,pass,stage); }
    DX8FVFCategoryContainer *Peek_FVF_Category_Container() {
        if(PolygonRendererList.Is_Empty()) return 0;
        DX8PolygonRendererClass *polygon_renderer=PolygonRendererList.Get_Head();
        DX8TextureCategoryClass *texture_category=polygon_renderer->Get_Texture_Category();
        return texture_category->Get_Container();
    }
    void Replace_Texture(const RefCountPtr<TextureClass>&,const RefCountPtr<TextureClass>&);
};

// ZH meshmdl.cpp Replace_VertexMaterial; target199B RET8, confirmed extent.
void MeshModelClass::Replace_VertexMaterial(VertexMaterialClass *vmat,VertexMaterialClass *new_vmat)
{
 for(int pass=0;pass<Get_Pass_Count();++pass) {
  if(Has_Material_Array(pass)) {
   for(int i=0;i<Get_Vertex_Count();++i) {
    if(Peek_Material(i,pass)==vmat) Set_Material(i,new_vmat,pass);
   }
  } else {
   if(Peek_Single_Material(pass)==vmat) Set_Single_Material(new_vmat,pass);
  }
  DX8FVFCategoryContainer *fvf_category=Peek_FVF_Category_Container();
  if(fvf_category) fvf_category->Change_Polygon_Renderer_Material(PolygonRendererList,vmat,new_vmat,pass);
 }
}
