// ?Add_Mesh@DX8RigidFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z
// partial score=0.749838943 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Semantic donor ZH dx8renderer.cpp Add_Mesh, BFME1 revision9cbfb551fe20.
// WB9D97D0 confirms target148180 identity and source1010..1024. Native
//148180..148517 RET4 proves extended96B FVF descriptor, vertex bufferE8,
//used verticesEC, FVF D8, sortingE4; all called providers already matched.
#include <new>
struct Vector2 {float X,Y;};
struct Vector3 {float X,Y,Z;Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}};
struct S2Buffer {char pad[12];void *Data;};
struct S2MaterialDesc {char pad[12];unsigned UVCount;S2Buffer *UV[8];int UVIndex[2];char gap[0x18];S2Buffer *Colors[2];};
class BfmeC998 {public:int bfmeGo998C(int);};
class MeshModelClass {
public:
 char pad[0x28];unsigned vertex_count;S2Buffer *polygons,*vertices;char gap34[0x60];S2MaterialDesc *descriptor;
 unsigned Get_Vertex_Count()const{return vertex_count;}
 const Vector3*Get_Vertex_Array()const{return (Vector3*)vertices->Data;}
 const Vector3*Get_Vertex_Normal_Array(unsigned n)const{return (Vector3*)((BfmeC998*)this)->bfmeGo998C(n);}
 const unsigned *Get_Color_Array(unsigned n)const{S2Buffer*b=descriptor->Colors[n];return b?(unsigned*)b->Data:0;}
 const Vector2*Get_UV_Array_By_Index(int n)const {
  S2MaterialDesc *d=descriptor;
  if(d->UVCount && n<2){int i=d->UVIndex[n];if(i!=-1){S2Buffer*b=d->UV[i];if(b)return (Vector2*)b->Data;}return 0;}
  S2Buffer*b=d->UV[n];if(b)return (Vector2*)b->Data;return 0;
 }
};
class Vertex_Split_Table {
public:
 MeshModelClass *model;bool npatch;unsigned count;void *polygons;bool allocated;
 Vertex_Split_Table(MeshModelClass*);
 ~Vertex_Split_Table(){if(allocated)delete[](unsigned short*)polygons;}
 unsigned Get_Vertex_Count()const{return model->Get_Vertex_Count();}
 const Vector3 *Get_Vertex_Array()const{return model->Get_Vertex_Array();}
 const Vector3 *Get_Vertex_Normal_Array(unsigned n)const{return model->Get_Vertex_Normal_Array(n);}
 const unsigned*Get_Color_Array(unsigned n)const{return model->Get_Color_Array(n);}
 const Vector2*Get_UV_Array(int n)const{return model->Get_UV_Array_By_Index(n);}
};
struct S2FVFInfo {
 unsigned fvf;bool basis;unsigned count,stride,location,extension,normal,extensionEnd,blend,tex[8],diffuse,specular,basisOffset,basisSecond,basisEnd,extensionData,formatIndex;
 unsigned Get_FVF_Size()const{return stride;}unsigned Get_Location_Offset()const{return location;}unsigned Get_Normal_Offset()const{return normal;}
 unsigned Get_Diffuse_Offset()const{return diffuse;}unsigned Get_Specular_Offset()const{return specular;}unsigned Get_Tex_Offset(unsigned n)const{return tex[n];}
};
class BfmeDynamicVBBase {public:virtual ~BfmeDynamicVBBase();char pad[16];S2FVFInfo *format;char tail[4];const S2FVFInfo&FVF_Info()const{return *format;}};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {public:BfmeDynamicSortingVB(unsigned short);void *buffer;};
class BfmeDynamicNativeVB:public BfmeDynamicVBBase {public:BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);void *buffer;};
class VertexBufferClass {public:class AppendLockClass {public: void *owner,*vertices;char lock;AppendLockClass(VertexBufferClass*,unsigned,unsigned,int);~AppendLockClass();void *Get_Vertex_Array()const{return vertices;}};};
class DX8Caps {public:char pad[0x13b];bool npatches;bool Support_NPatches()const{return npatches;}};
class DX8Wrapper {public:static DX8Caps *Get_Current_Caps(){return CurrentCaps;}private:static DX8Caps *CurrentCaps;};
class WW3D {public:static unsigned Get_NPatches_Level(){return NPatchesLevel;}private:static unsigned NPatchesLevel;};
class DX8FVFCategoryContainer {
public:
 virtual ~DX8FVFCategoryContainer();char pad[0xD0-4];void *index;unsigned used_indices,FVF;char gapDC[8];bool sorting;
 void Generate_Texture_Categories(Vertex_Split_Table&,unsigned);
};
class DX8RigidFVFCategoryContainer:public DX8FVFCategoryContainer {
public:
 BfmeDynamicVBBase*vertex_buffer;unsigned used_vertices;
 virtual void Add_Mesh(MeshModelClass*);
};
typedef char FVFSize[(sizeof(S2FVFInfo)==96)?1:-1];
typedef char BaseSize[(sizeof(DX8FVFCategoryContainer)==0xe8)?1:-1];
typedef char VBSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
void DX8RigidFVFCategoryContainer::Add_Mesh(MeshModelClass* mmc_) {
 Vertex_Split_Table split_table(mmc_);
 int needed_vertices=split_table.Get_Vertex_Count();
 if(!vertex_buffer){
  int vb_size=4000;if(vb_size<needed_vertices)vb_size=needed_vertices;
  if(sorting)vertex_buffer=new BfmeDynamicSortingVB(vb_size);
  else vertex_buffer=new BfmeDynamicNativeVB(FVF,vb_size,(DX8Wrapper::Get_Current_Caps()->Support_NPatches() && WW3D::Get_NPatches_Level()>1)?4:0,0);
 }
 VertexBufferClass::AppendLockClass l((VertexBufferClass*)vertex_buffer,used_vertices,split_table.Get_Vertex_Count(),0);
 const Vector3 *locs=split_table.Get_Vertex_Array();
 const S2FVFInfo fi=vertex_buffer->FVF_Info();
 unsigned char *vb=(unsigned char*)l.Get_Vertex_Array();
 unsigned i=0;
 const Vector3 *norms=split_table.Get_Vertex_Normal_Array(i);
 const unsigned *diffuse=split_table.Get_Color_Array(0);
 const unsigned *specular=split_table.Get_Color_Array(1);
 for(;i<split_table.Get_Vertex_Count();++i){
  *(Vector3*)(vb+fi.Get_Location_Offset())=locs[i];
  if((FVF&0x10)==0x10 && norms)*(Vector3*)(vb+fi.Get_Normal_Offset())=norms[i];
  if((FVF&0x40)==0x40){if(diffuse)*(unsigned*)(vb+fi.Get_Diffuse_Offset())=diffuse[i];else *(unsigned*)(vb+fi.Get_Diffuse_Offset())=0xFFFFFFFF;}
  if((FVF&0x80)==0x80){if(specular)*(unsigned*)(vb+fi.Get_Specular_Offset())=specular[i];else *(unsigned*)(vb+fi.Get_Specular_Offset())=0xFFFFFFFF;}
  vb+=fi.Get_FVF_Size();
 }
 int uvcount=(FVF>>8)&15;
 for(int j=0;j<uvcount;++j){
  unsigned char *vb=(unsigned char*)l.Get_Vertex_Array();
  const Vector2 *uvs=split_table.Get_UV_Array(j);
  if(uvs)for(;i<split_table.Get_Vertex_Count();++i){*(Vector2*)(vb+fi.Get_Tex_Offset(j))=uvs[i];vb+=fi.Get_FVF_Size();}
 }
 Generate_Texture_Categories(split_table,used_vertices);
 used_vertices+=needed_vertices;
}
