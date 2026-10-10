// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.7427084405558415 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 575ba2b04 W3DTreeBufferRva00734270.cpp and ZH loadTreesInVertexAndIndexBuffers
// provide the update/alpha/locked-buffer semantics. Target EBFD1..EC67F
// independently supplies vector prefixes, E8 record stride, 2C output stride,
// composed scale/postMul/offset transform, extra C4 flag and fade flag40.
#include "vector3.h"
#include "vector2.h"
#include "matrix3d.h"
class VertexBufferClass {public:class WriteLockClass {public:
 WriteLockClass(VertexBufferClass*,int);~WriteLockClass();void *Get_Vertex_Array(){return vertices;}
 private:VertexBufferClass *buffer;void *vertices;int flags;
};};
class IndexBufferClass {public:class WriteLockClass {public:
 WriteLockClass(IndexBufferClass*,int);~WriteLockClass();unsigned short*Get_Index_Array(){return indices;}
 private:IndexBufferClass *buffer;unsigned short *indices;int flags;
};};
struct TreeVertex {float x,y,z,nx,ny,nz;unsigned diffuse;float u,v,u2,v2;};
struct TreeModelVertices {char p[0xC];Vector3 *vertices;};
struct TreeTriangle {unsigned short I,J,K;};
template<class T>struct TreeArray {char p[0xC];T *array;};
class MeshMatDescClass {public:Vector2*Get_UV_Array(int,int);char p[0xC];int uvCount;TreeArray<Vector2>*uv;char p14[0x50-0x14];TreeArray<unsigned>*colors;
 __forceinline Vector2*GetUV(){if(uvCount)return Get_UV_Array(0,0);if(uv)return uv->array;return 0;}
 __forceinline unsigned*GetColor(){if(colors)return colors->array;return 0;}
};
class MeshGeometryClass {public:const Vector3*Get_Vertex_Normal_Array(bool);};
struct TreeModel:MeshGeometryClass {char p[0x24];int polys,count;TreeArray<TreeTriangle>*poly;TreeModelVertices *vertices;char p34[0x94-0x34];MeshMatDescClass *material;
 int Get_Vertex_Count()const{return count;}Vector3*Get_Vertex_Array()const{return vertices->vertices;}
 int Get_Polygon_Count()const{return polys;}TreeTriangle*Get_Polygon_Array()const{return poly->array;}
 __forceinline Vector2*GetUV(){return material->GetUV();}__forceinline unsigned*GetColor(){return material->GetColor();}
};
class TreeMesh {char p[0xC4];TreeModel *model;public:TreeModel*Peek_Model()const{return model;}};
struct TreeFadeData {char p[0x54];bool noSway;char p55[3];int step;};
struct TreeType {TreeMesh *mesh;Vector3 offset;char p10[0x10];const TreeFadeData *data;float uScale,vScale,shadowUScale,shadowVScale,uOrigin,vOrigin,shadowUOrigin,shadowVOrigin;char p44[0x5C-0x44];};
struct TreeRecord {
 Vector3 location;float scale;Matrix3D transform;int type;bool visible;char p45[0x60-0x45];int sway;
 int firstVertex,buffer;char p6C[0x80-0x6C];int state;char p84[0x90-0x84];Matrix3D world;
 char pC0[4];bool flagC4;char pC5[3];int hidden;char pCC[0xE0-0xCC];int alpha,targetAlpha;
};
template<class T>struct TreeVector {T *start,*finish,*end;T&operator[](unsigned i){return start[i];}unsigned size()const{return finish-start;}};
class GlobalData;extern GlobalData *TheGlobalData;struct TreeGlobalFade {char p[0x40];bool enabled;};
class Rva000EC9C6 {public:void rva000EB6BB();
 private:void *vptr;TreeVector<VertexBufferClass*> vertex;TreeVector<int> vertexCounts;TreeVector<class IndexBufferClass*> index;TreeVector<int> indexCounts;
 char p34[0x5C0-0x34];TreeRecord trees[1200];int count;bool dirty;char p44545[0xF];bool initialized;char p44555[3];
 TreeType types[64];int typeCount;char p45C5C[4];int step;bool alphaChanged;
};
typedef char CheckTreeRecord[(sizeof(TreeRecord)==0xE8)?1:-1];
typedef char CheckTreeType[(sizeof(TreeType)==0x5C)?1:-1];
void Rva000EC9C6::rva000EB6BB(){
 if(!initialized||!index[0]||!vertex[0]||!dirty)return;
 for(int i=0;i<count;++i)trees[i].buffer=-1;
 int curTree=0;
 for(unsigned b=0;b<vertex.size();++b){
  vertexCounts[b]=0;indexCounts[b]=0;
  if(curTree>=count)break;
  IndexBufferClass::WriteLockClass indexLock(index[b],0x2000);
  VertexBufferClass::WriteLockClass vertexLock(vertex[b],0x2000);
  unsigned short *curIb=indexLock.Get_Index_Array();
  TreeVertex *curVb=(TreeVertex*)vertexLock.Get_Vertex_Array();
  for(;curTree<count;curTree+=step){
   int type=trees[curTree].type;
   if(type<0||!trees[curTree].visible||trees[curTree].hidden)continue;
   float scale=trees[curTree].scale;Vector3 location=trees[curTree].location;
   if(!types[type].mesh)continue;
   Matrix3D transform;
   if(trees[curTree].state||trees[curTree].flagC4)transform=trees[curTree].world;
   else transform.Set(location);
   transform.Scale(scale);transform.postMul(trees[curTree].transform);transform.Translate(types[type].offset);
   int startVertex=vertexCounts[b];trees[curTree].firstVertex=startVertex;trees[curTree].buffer=b;
   int numVertex=types[type].mesh->Peek_Model()->Get_Vertex_Count();
   Vector3 *pVert=types[type].mesh->Peek_Model()->Get_Vertex_Array();
   if(vertexCounts[b]+numVertex>=30000)break;
   int numIndex=types[type].mesh->Peek_Model()->Get_Polygon_Count();
   const TreeTriangle*pPoly=types[type].mesh->Peek_Model()->Get_Polygon_Array();
   if(indexCounts[b]+3*numIndex>=60000)break;
   const Vector2*uvs=types[type].mesh->Peek_Model()->GetUV();
   const Vector3*normals=types[type].mesh->Peek_Model()->Get_Vertex_Normal_Array(false);
   const unsigned*colors=types[type].mesh->Peek_Model()->GetColor();
   float uScale=types[type].uScale,vScale=types[type].vScale,uOrigin=types[type].uOrigin,vOrigin=types[type].vOrigin;
   for(int j=0;j<numVertex;++j){
    Matrix3D::Transform_Vector(transform,pVert[j],(Vector3*)curVb);
    if(normals)*(Vector3*)&curVb->nx=normals[j];else{curVb->nx=0;curVb->ny=0;curVb->nz=1;}
    if(colors)curVb->diffuse=(colors[j]&0xFFFFFF)|(trees[curTree].alpha<<24);
    else curVb->diffuse=0xFFFFFF|(trees[curTree].alpha<<24);
    float U=uvs[j].U,V=uvs[j].V;
    if(U>1)U=1;if(U<0)U=0;if(V>1)V=1;if(V<0)V=0;
    curVb->u=U*uScale+uOrigin;curVb->v=V*vScale+vOrigin;
    curVb->u2=types[trees[curTree].type].data->noSway?0:trees[curTree].sway;
    curVb->v2=location.Z;++curVb;
   }
   vertexCounts[b]+=numVertex;
   for(int j=0;j<numIndex;++j){*curIb++=startVertex+pPoly[j].I;*curIb++=startVertex+pPoly[j].J;*curIb++=startVertex+pPoly[j].K;}
   indexCounts[b]+=3*numIndex;
  }
 }
}
