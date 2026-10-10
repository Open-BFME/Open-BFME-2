// ?rva000EBFD1@Rva000EC9C6@@QAEXXZ
// partial score=0.66993480156173 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 575ba2b04 W3DTreeBufferRva00734270.cpp and ZH updateVertexBuffer
// provide the update/alpha/locked-buffer semantics. Target EBFD1..EC67F
// independently supplies vector prefixes, E8 record stride, 2C output stride,
// composed scale/postMul/offset transform, extra C4 flag and fade flag40.
#include "vector3.h"
#include "matrix3d.h"
class VertexBufferClass {public:class WriteLockClass {public:
 WriteLockClass(VertexBufferClass*,int);~WriteLockClass();void *Get_Vertex_Array(){return vertices;}
 private:VertexBufferClass *buffer;void *vertices;int flags;
};};
struct TreeVertex {float x,y,z,nx,ny,nz;unsigned diffuse;float u,v,u2,v2;};
struct TreeModelVertices {char p[0xC];Vector3 *vertices;};
struct TreeModel {char p[0x28];int count;char p2[4];TreeModelVertices *vertices;int Get_Vertex_Count()const{return count;}Vector3*Get_Vertex_Array()const{return vertices->vertices;}};
class TreeMesh {char p[0xC4];TreeModel *model;public:TreeModel*Peek_Model()const{return model;}};
struct TreeFadeData {char p[0x58];int step;};
struct TreeType {TreeMesh *mesh;Vector3 offset;char p10[0x10];const TreeFadeData *data;char p24[0x5C-0x24];};
struct TreeRecord {
 Vector3 location;float scale;Matrix3D transform;int type;bool visible;char p45[0x64-0x45];
 int firstVertex,buffer;char p6C[0x80-0x6C];int state;char p84[0x90-0x84];Matrix3D world;
 char pC0[4];bool flagC4;char pC5[3];int hidden;char pCC[0xE0-0xCC];int alpha,targetAlpha;
};
template<class T>struct TreeVector {T *start,*finish,*end;T&operator[](unsigned i){return start[i];}unsigned size()const{return finish-start;}};
class GlobalData;extern GlobalData *TheGlobalData;struct TreeGlobalFade {char p[0x40];bool enabled;};
class Rva000EC9C6 {public:void rva000EBFD1();
 private:void *vptr;TreeVector<VertexBufferClass*> vertex;char p10[0x1C-0x10];TreeVector<void*> index;TreeVector<int> indexCounts;
 char p34[0x5C0-0x34];TreeRecord trees[1200];int count;char p44544[0x10];bool initialized;char p44555[3];
 TreeType types[64];int typeCount;char p45C5C[4];int step;bool alphaChanged;
};
typedef char CheckTreeRecord[(sizeof(TreeRecord)==0xE8)?1:-1];
typedef char CheckTreeType[(sizeof(TreeType)==0x5C)?1:-1];
void Rva000EC9C6::rva000EBFD1(){
 if(!initialized || !index[0] || !vertex[0])return;
 for(unsigned b=0;b<vertex.size();++b){
  if(indexCounts[b]==0)break;
  VertexBufferClass::WriteLockClass lock(vertex[b],0);
  TreeVertex *vb=(TreeVertex*)lock.Get_Vertex_Array();
  for(int i=0;i<count;i+=step){
   if(trees[i].buffer!=(int)b)continue;
   int type=trees[i].type;if(type<0)continue;
   int alpha=trees[i].alpha;
   if(trees[i].state==0 && alpha==trees[i].targetAlpha && !trees[i].flagC4)continue;
   if(((TreeGlobalFade*)TheGlobalData)->enabled && alpha!=trees[i].targetAlpha){
    int target=trees[i].targetAlpha;
    if(alpha>target){alpha-=types[type].data->step;if(alpha<target)alpha=target;}
    else{alpha+=types[type].data->step;if(alpha>target)alpha=target;}
    trees[i].alpha=alpha;
   }
   if(!trees[i].visible || trees[i].hidden)continue;
   float scale=trees[i].scale;Vector3 location=trees[i].location;
   if(!types[type].mesh)type=0;
   Matrix3D transform;
   if(trees[i].state || trees[i].flagC4)transform=trees[i].world;
   else {transform.Set(location);}
   transform[1][0] *= scale;transform[0][0] *= scale;transform[2][0] *= scale;transform[1][1] *= scale;transform[0][1] *= scale;transform[2][1] *= scale;transform[1][2] *= scale;transform[0][2] *= scale;transform[2][2] *= scale;
   transform.postMul(trees[i].transform);
   transform.Translate(types[type].offset);
   TreeVertex *cur=vb+trees[i].firstVertex;
   int n=types[type].mesh->Peek_Model()->Get_Vertex_Count();
   Vector3 *vertices=types[type].mesh->Peek_Model()->Get_Vertex_Array();
   for(int j=0;j<n;++j){
    Matrix3D::Transform_Vector(transform,vertices[j],(Vector3*)cur);
    cur->diffuse=(cur->diffuse&0x00FFFFFF)|(alpha<<24);
    ++cur;
   }
  }
 }
}
