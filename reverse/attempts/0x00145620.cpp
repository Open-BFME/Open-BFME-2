// ?Add_Mesh@DX8TextureCategoryClass@@QAEIAAVVertex_Split_Table@@IIPAVIndexBufferClass@@I@Z
// partial score=0.99 date=2026-10-08
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Semantic guide: ZH dx8renderer.cpp Add_Mesh. BFME2 target 145620..145A65.
#include <new>
class MultiListObjectClass { public: virtual ~MultiListObjectClass(); void *ListNode; };
class GenericMultiListClass {
public: virtual ~GenericMultiListClass();
protected: bool Internal_Add_Tail(MultiListObjectClass *, bool);
public:
 char Head[20];
};
class TextureClass { public: virtual void Delete_This(); unsigned short refs; void Release_Ref(); };
template<class T> class RefCountPtr {
public:
 T *Referent;
 RefCountPtr() : Referent(0) {}
 RefCountPtr(const RefCountPtr &v) : Referent(v.Referent) { if(Referent) ++Referent->refs; }
 ~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
 T *Peek_Referent() const {return Referent;}
 bool operator==(const RefCountPtr &rhs) const {return Referent==rhs.Referent;}
};
class ShaderClass {
public:
 unsigned ShaderBits;
 ShaderClass() : ShaderBits(0x10441b) {}
 ShaderClass(const ShaderClass &s) : ShaderBits(s.ShaderBits) {}
 bool operator==(const ShaderClass &s) { return ShaderBits == s.ShaderBits; }
};
class VertexMaterialClass {
public:
 char pad[0x64]; mutable unsigned crc; mutable bool dirty;
 unsigned long Get_CRC() const { if(dirty) { crc=Compute_CRC(); dirty=false; } return crc; }
private: unsigned long Compute_CRC() const;
};
typedef unsigned short TriIndex[3];
struct PolygonBuffer { char pad[12]; TriIndex *data; };
class MeshMatDescClass {
public:
 char pad[0xA8]; VertexMaterialClass *single[16]; void *arrays[4];
 VertexMaterialClass *Peek_Material(int,int) const;
 bool Has_Material_Array(int p) const { return arrays[p]!=0; }
 VertexMaterialClass *Peek_Single_Material(int p) const {return single[p];}
};
class MeshModelClass {
public:
 char pad[0x2c]; PolygonBuffer *polygons; char pad30[0x94-0x30]; MeshMatDescClass *descriptor;
 bool Has_Material_Array(int p) const { return descriptor->Has_Material_Array(p); }
 const TriIndex *Get_Polygon_Array() const { return polygons->data; }
 VertexMaterialClass *Peek_Material(int i,int p) const { return descriptor->Peek_Material(i,p); }
 VertexMaterialClass *Peek_Single_Material(int p) const { return descriptor->Peek_Single_Material(p); }
};
class Vertex_Split_Table {
public:
 MeshModelClass *model; bool npatch; unsigned count; TriIndex *polygons;
 unsigned Get_Polygon_Count() const {return count;}
 MeshModelClass *Get_Mesh_Model_Class() {return model;}
 unsigned short *Get_Polygon_Array(unsigned) { return (unsigned short *)polygons; }
 RefCountPtr<TextureClass> Peek_Texture(unsigned,unsigned,unsigned);
 ShaderClass Peek_Shader(unsigned,unsigned);
 VertexMaterialClass *Peek_Material(unsigned index,unsigned pass) {
  
  if(model->Has_Material_Array(pass)) return model->Peek_Material(model->Get_Polygon_Array()[index][0],pass);
  return model->Peek_Single_Material(pass);
 }
};
class IndexBufferClass {
public:
 class AppendLockClass {
 public:
  IndexBufferClass *buffer; unsigned short *indices; char deviceLock;
  AppendLockClass(IndexBufferClass*,unsigned,unsigned,int);
  ~AppendLockClass();
  unsigned short *Get_Index_Array() const {return indices;}
 };
};
class DX8TextureCategoryClass;
class DX8PolygonRendererClass : public MultiListObjectClass {
public:
 DX8PolygonRendererClass(unsigned,MeshModelClass*,DX8TextureCategoryClass*,unsigned,unsigned,bool,unsigned);
 MeshModelClass *model; DX8TextureCategoryClass *category;
 unsigned indexOffset,vertexOffset,indexCount,minIndex,range,firstPolygon,polygonRange;
 bool strip; unsigned pass;
 void Set_Vertex_Index_Range(unsigned mn,unsigned rng,unsigned first,unsigned polys) {
  range=rng; minIndex=mn; firstPolygon=first; polygonRange=polys;
 }
};
template<class T> class MultiListClass : public GenericMultiListClass {
public:
 bool Add_Tail(T *p,bool onlyOnce=true) { return Internal_Add_Tail(p,onlyOnce); }
};
class DX8TextureCategoryClass : public MultiListObjectClass {
public:
 unsigned Add_Mesh(Vertex_Split_Table&,unsigned,unsigned,IndexBufferClass*,unsigned);
 int pass; RefCountPtr<TextureClass> textures[2]; ShaderClass shader;
 VertexMaterialClass *material; MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
 void *container, *tasks;
 const RefCountPtr<TextureClass>& Peek_Texture(unsigned s) const { return textures[s]; }
};
inline static bool Equal_Material(const VertexMaterialClass *a,const VertexMaterialClass *b) {
 int ca=a?a->Get_CRC():0, cb=b?b->Get_CRC():0;
 return ca==cb;
}
unsigned DX8TextureCategoryClass::Add_Mesh(Vertex_Split_Table &split_table,unsigned vertex_offset,
 unsigned index_offset,IndexBufferClass *index_buffer,unsigned pass)
{
 int poly_count=split_table.Get_Polygon_Count();
 unsigned index_count=0, polygons=0;
 for(int i=0;i<poly_count;++i) {
  bool all_textures_same=true;
  for(unsigned stage=0;stage<2;++stage)
   all_textures_same=all_textures_same && (split_table.Peek_Texture(i,pass,stage)==Peek_Texture(stage));
  VertexMaterialClass *mat=split_table.Peek_Material(i,pass);
  ShaderClass shd=split_table.Peek_Shader(i,pass);
  if(all_textures_same && Equal_Material(mat,material) && shd==shader) ++polygons;
 }
 if(polygons) {
  index_count=polygons*3;
  bool stripify=false;
  const TriIndex *src_indices=(const TriIndex*)split_table.Get_Polygon_Array(pass);
  DX8PolygonRendererClass *p_renderer=new DX8PolygonRendererClass(index_count,
   split_table.Get_Mesh_Model_Class(),this,vertex_offset,index_offset,stripify,pass);
  PolygonRendererList.Add_Tail(p_renderer);
  IndexBufferClass::AppendLockClass l(index_buffer,index_offset,index_count,0);
  unsigned short *dst_indices=l.Get_Index_Array();
  unsigned short vmin=0xffff,vmax=0,firstPolygon=0xffff,lastPolygon=0;
  for(int i=0;i<poly_count;++i) {
   bool all_textures_same=true;
   for(unsigned stage=0;stage<2;++stage)
    all_textures_same=all_textures_same && (split_table.Peek_Texture(i,pass,stage)==Peek_Texture(stage));
   VertexMaterialClass *mat=split_table.Peek_Material(i,pass);
   ShaderClass shd=split_table.Peek_Shader(i,pass);
   if(all_textures_same && Equal_Material(mat,material) && shd==shader) {
    if(firstPolygon==0xffff) firstPolygon=(unsigned short)i;
    lastPolygon=(unsigned short)i;
    unsigned short idx;
    idx=(unsigned short)(src_indices[i][0]+vertex_offset);
    vmin=vmin<idx?vmin:idx; vmax=vmax>idx?vmax:idx; *dst_indices++=idx;
    idx=(unsigned short)(src_indices[i][1]+vertex_offset);
    vmin=vmin<idx?vmin:idx; vmax=vmax>idx?vmax:idx; *dst_indices++=idx;
    idx=(unsigned short)(src_indices[i][2]+vertex_offset);
    vmin=vmin<idx?vmin:idx; vmax=vmax>idx?vmax:idx; *dst_indices++=idx;
   }
  }
  p_renderer->Set_Vertex_Index_Range(vmin,vmax-vmin+1,firstPolygon,lastPolygon-firstPolygon+1);
 }
 return index_count;
}







