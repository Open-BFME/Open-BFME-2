// ?rva0016E450@Rva0016E450Source@@QAEPAXPAH@Z
// partial score=0.7 date=2026-10-08
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Whole retail GetEdges:16E450..16EAEC,1692B,RET4. WB A0F6A0,
// meshgeometry.cpp1944 proves vertex welding, directed edge pairing and
// all three geometry diagnostics. Existing address-derived call view retained.
// Scratch reconstruction: template callee folds still require verification.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <vector>
#include <hash_map>
struct Gen_p12pod { int a[3]; };
inline bool compare_tail(const Gen_p12pod &a,const Gen_p12pod &b) {
 const int a1=a.a[1]; return b.a[1]>a1 || (!(b.a[1]<a1)&&a.a[2]<b.a[2]);
}
inline bool operator<(const Gen_p12pod &a,const Gen_p12pod &b) {
 const int a0=a.a[0]; return b.a[0]>a0 || (!(b.a[0]<a0)&&compare_tail(a,b));
}
namespace _STL {
template<class T,class L,class R>
static inline bool operator==(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b)
 { return a._M_node==b._M_node; }
}
typedef _STL::pair<int,int> Rva00928590Key;
struct Rva00928590Hash {
 unsigned operator()(const Rva00928590Key &key)const {
  return (static_cast<unsigned>(key.second)<<16)+static_cast<unsigned>(key.first);
 }
};
struct Rva00928590Eq {
 bool operator()(const Rva00928590Key&a,const Rva00928590Key&b)const
 { return a.first==b.first&&a.second==b.second; }
};
typedef _STL::hash_map<Rva00928590Key,int,Rva00928590Hash,Rva00928590Eq,
 _STL::allocator<_STL::pair<const Rva00928590Key,int> > > EdgeMap;
class Rva0016E400 {
public:
 Rva0016E400();
 EdgeMap table;
};
struct MeshGeometrySlot64Element_00923F70 { unsigned char Data[16]; };
template<class T> class ShareBufferClass {
public:
 void Resize(int);
 void *vptr;
 int references;
 T *RawBuffer,*Array;
 int Count,Alignment;
};
struct EdgeRecord { int vertex1,vertex2,triangle1,triangle2; };
struct VertexPosition { float x,y,z; };
struct TriangleIndices { unsigned short vertex[3]; };
class Debug {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual void slot30(); virtual void slot34(); virtual Debug &slot38(const char *);
 virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual void slot4c(int); virtual void slot50(); virtual void slot54(); virtual void slot58();
 virtual void slot5c(); virtual void slot60(); virtual void slot64(); virtual void slot68();
 virtual Debug &slot6c(int,int,int);
};
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int);
#define GEOMETRY_REPORT(message) if(bfmeRva000387C0()) { _bfme_debugRecordCallsite(1); theDebug->slot60(); theDebug->slot6c(0,0,0).slot38("Geometry for model ").slot38(MeshName?MeshName->Array:0).slot38(message).slot4c(2); }
class Rva0016E450Source {
public:
 void *rva0016E450(int *edgeCount);
 char prefix[0x10];
 ShareBufferClass<char> *MeshName;
 char gap14[0x24-0x14];
 int PolyCount,VertexCount;
 ShareBufferClass<TriangleIndices> *Polys;
 ShareBufferClass<VertexPosition> *Vertices;
 char gap34[0x5c-0x34];
 ShareBufferClass<MeshGeometrySlot64Element_00923F70> *Edges;
};
void *Rva0016E450Source::rva0016E450(int *edgeCount)
{
 if(!Edges||!PolyCount||!VertexCount) { *edgeCount=0; return 0; }
 if(Edges->Count) { *edgeCount=Edges->Count; return Edges->Array; }
 Edges->Resize(PolyCount*3/2);
 EdgeRecord *output=(EdgeRecord*)Edges->Array;
 _STL::vector<int> vertexMap;
 {
  _STL::map<Gen_p12pod,int> welded;
  VertexPosition *vertices=Vertices->Array;
  for(int i=0;i<VertexCount;++i) {
   int x=int(float(int(vertices[i].x*100.0f)));
   int y=int(float(int(vertices[i].y*100.0f)));
   int z=int(float(int(vertices[i].z*100.0f)));
   Gen_p12pod key={x,y,z};
   _STL::map<Gen_p12pod,int>::iterator found=welded.find(key);
   if(found==welded.end()) {
    int id=welded.size();
    vertexMap.push_back(id);
    Gen_p12pod keyForInsert={x,y,z};
    welded[keyForInsert]=id;
   } else vertexMap.push_back(found->second);
  }
 }
 Rva0016E400 edgeTable;
 TriangleIndices *polys=Polys->Array;
 bool warned=false;
 for(int i=0;i<PolyCount;++i) {
  for(int j=0;j<3;++j) {
   int a=vertexMap[polys[i].vertex[j]];
   int b=vertexMap[polys[i].vertex[(j+1)%3]];
   if(a>b) {
    Rva00928590Key key(a,b);
    if(!warned&&edgeTable.table.find(key)!=edgeTable.table.end()) {
     GEOMETRY_REPORT(" shares an edge with more than two triangles, this will cause shadow bugs.");
     warned=true;
    }
    edgeTable.table[key]=i;
   }
  }
 }
 polys=Polys->Array;
 int count=0;
 warned=false;
 for(int i=0;i<PolyCount;++i) {
  for(int j=0;j<3;++j) {
   int a=vertexMap[polys[i].vertex[j]];
   int b=vertexMap[polys[i].vertex[(j+1)%3]];
   if(a<b) {
    Rva00928590Key key(b,a);
    EdgeMap::iterator found=edgeTable.table.find(key);
    if(found==edgeTable.table.end()) {
     if(!warned) {
      GEOMETRY_REPORT(" contains at least one triangle that doesn't share an edge with another triangle.\nShadow bugs will occur.");
      warned=true;
     }
    } else if(count>=Edges->Count) warned=true;
    else {
     output->vertex1=polys[i].vertex[j];
     output->vertex2=polys[i].vertex[(j+1)%3];
     output->triangle1=i;
     output->triangle2=found->second;
     ++output;
     ++count;
    }
   }
  }
 }
 if(count!=PolyCount*3/2||warned) {
  GEOMETRY_REPORT(" is not a valid shadow caster, it may contain T-junctions or not be closed. Shadow bugs are more than likely.");
  if(count==0) { output->vertex1=0; output->vertex2=0; output->triangle1=0; output->triangle2=0; count=1; }
  Edges->Resize(count);
 }
 *edgeCount=Edges->Count;
 return Edges->Array;
}
