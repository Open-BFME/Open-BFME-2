// ?Generate_Texture_Categories@DX8FVFCategoryContainer@@IAEXAAVVertex_Split_Table@@I@Z
// partial score=0.94 date=2026-10-08
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
 RefCountPtr();
 RefCountPtr(const RefCountPtr &v) : Referent(v.Referent) { if(Referent) ++Referent->refs; }
 ~RefCountPtr();
 T *Peek_Referent() const {return Referent;}
 RefCountPtr &operator=(const RefCountPtr &v) { if(v.Referent) ++v.Referent->refs; if(Referent) Referent->Release_Ref(); Referent=v.Referent; return *this; }
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
 unsigned passes; char pad[0xA8-4];
 unsigned Get_Pass_Count() const {return passes;} VertexMaterialClass *single[16]; void *arrays[4];
 VertexMaterialClass *Peek_Material(int,int) const;
 bool Has_Material_Array(int p) const { return arrays[p]!=0; }
 VertexMaterialClass *Peek_Single_Material(int p) const {return single[p];}
};
class MeshModelClass {
public:
 char pad[0x2c]; PolygonBuffer *polygons; char pad30[0x94-0x30]; MeshMatDescClass *descriptor;
 unsigned Get_Pass_Count() const {return descriptor->Get_Pass_Count();}
 bool Has_Material_Array(int p) const { return descriptor->Has_Material_Array(p); }
 const TriIndex *Get_Polygon_Array() const { return polygons->data; }
 VertexMaterialClass *Peek_Material(int i,int p) const { return descriptor->Peek_Material(i,p); }
 VertexMaterialClass *Peek_Single_Material(int p) const { return descriptor->Peek_Single_Material(p); }
};
class Vertex_Split_Table {
public:
 MeshModelClass *model; bool npatch; unsigned count; TriIndex *polygons;
 unsigned Get_Polygon_Count() const {return count;}
 unsigned Get_Pass_Count() const {return model->Get_Pass_Count();}
 MeshModelClass *Get_Mesh_Model_Class() {return model;}
 unsigned short *Get_Polygon_Array(unsigned) { return (unsigned short *)polygons; }
 RefCountPtr<TextureClass> Peek_Texture(unsigned,unsigned,unsigned);
 ShaderClass Peek_Shader(unsigned,unsigned);
 VertexMaterialClass *Peek_Material(unsigned index,unsigned pass) {
  
  if(model->Has_Material_Array(pass)) return model->Peek_Material(model->Get_Polygon_Array()[index][0],pass);
  return model->Peek_Single_Material(pass);
 }
};
class IndexBufferClass { public: virtual ~IndexBufferClass(); char pad[20]; };
class SortingIndexBufferClass:public IndexBufferClass {public: SortingIndexBufferClass(unsigned short);};
class DX8IndexBufferClass:public IndexBufferClass {public: enum UsageType {USAGE_DEFAULT=0,USAGE_NPATCHES=4}; DX8IndexBufferClass(unsigned,UsageType);};
class DX8Caps {public: char pad[0x13b]; bool npatches; bool Support_NPatches() const {return npatches;}};
class DX8Wrapper {private:static DX8Caps *CurrentCaps; public:static DX8Caps *Get_Current_Caps() {return CurrentCaps;}};
class WW3D {private:static unsigned NPatchesLevel; public:static unsigned Get_NPatches_Level(){return NPatchesLevel;}};
class BfmeHandleCX;
struct Textures_Material_And_Shader_Booking_Struct {
 RefCountPtr<TextureClass> textures[2][64]; VertexMaterialClass *materials[64]; ShaderClass shaders[64]; unsigned count;
 Textures_Material_And_Shader_Booking_Struct():count(0) {for(int i=0;i<64;++i) materials[i]=0;}
 bool Add_Textures_Material_And_Shader(BfmeHandleCX*,VertexMaterialClass*,ShaderClass);
};
class DX8FVFCategoryContainer {
public:
 virtual ~DX8FVFCategoryContainer(); char pad[0xd0-4]; IndexBufferClass *index_buffer; unsigned used_indices; char pade4[0xe4-0xd8]; bool sorting;
protected:
 void Insert_To_Texture_Category(Vertex_Split_Table&,TextureClass**,VertexMaterialClass*,ShaderClass,int,unsigned);
 void Generate_Texture_Categories(Vertex_Split_Table&,unsigned);
};
void DX8FVFCategoryContainer::Generate_Texture_Categories(Vertex_Split_Table& split_table,unsigned vertex_offset) {
 int polygon_count=split_table.Get_Polygon_Count();
 int index_count=polygon_count*3*split_table.Get_Pass_Count();
 if(!index_buffer) {
  int ib_size=12000; if(ib_size<index_count) ib_size=index_count;
  if(sorting) index_buffer=new SortingIndexBufferClass(ib_size);
  else index_buffer=new DX8IndexBufferClass(ib_size,(DX8Wrapper::Get_Current_Caps()->Support_NPatches() && WW3D::Get_NPatches_Level()>1)?DX8IndexBufferClass::USAGE_NPATCHES:DX8IndexBufferClass::USAGE_DEFAULT);
 }
 for(unsigned pass=0;pass<split_table.Get_Pass_Count();++pass) {
  Textures_Material_And_Shader_Booking_Struct booking;
  for(int i=0;i<polygon_count;++i) {
   RefCountPtr<TextureClass> textures[2];
   for(int stage=0;stage<2;++stage) textures[stage]=split_table.Peek_Texture(i,pass,stage);
   VertexMaterialClass *mat=split_table.Peek_Material(i,pass);
   ShaderClass shader=split_table.Peek_Shader(i,pass);
   if(!booking.Add_Textures_Material_And_Shader(reinterpret_cast<BfmeHandleCX*>(textures),mat,shader))continue;
   Insert_To_Texture_Category(split_table,reinterpret_cast<TextureClass**>(textures),mat,shader,pass,vertex_offset);
  }
 }
}

