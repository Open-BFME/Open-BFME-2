// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// MeshGeometryClass::Get_Edges, retail 0x0016E450..0x0016EAEC (1692 B, ret 4).
// Identity: WorldBuilder 0x00A0F6A0 MeshGeometryClass::GetEdges (meshgeometry.cpp:1944
// assert) and the three shadow-caster geometry reports. Its own unit because the
// body needs STLport containers with /EHs, which meshgeometry.cpp does not build with.
// The map<,int>/vector<int> growth calls fold into the /O1 copies rowed by
// UnsignedSetHelpersBFME2.cpp (0x004DFCB0, 0x002DFCF6, 0x0007E48F).
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <vector>
#include <hash_map>
// Suppress this TU's non-retail copy of ??A?$map@UGen_p12pod@@HU?$less@UGen_p12pod@@@_STL@@V?$allocator@U?$pair@$$CBUGen_p12pod@@H:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_p12pod;
namespace _STL { template <> int & map<Gen_p12pod,int,less<Gen_p12pod>,allocator<pair<Gen_p12pod const ,int> > >::operator[](Gen_p12pod const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAPAXIPAX@_STL@@YAPAPAXPAPAXIABQAXABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * __uninitialized_fill_n<void * *,unsigned int,void *>(void * *,unsigned int,void * const &,__true_type const &); }
// Suppress this TU's non-retail copy of ??$advance@PBIH@_STL@@YAXAAPBIH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void advance<unsigned int const *,int>(unsigned int const * &,int); }
// Suppress this TU's non-retail copy of ?get_allocator@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBE?AV?$allocator@PAX@2@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> allocator<void *> vector<void *,allocator<void *> >::get_allocator() const; }
// Bucket access stays inline, as in RvaHashIndex00928620.cpp, so _M_insert is retail's copy.
namespace _STL { template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return _M_start; } }
namespace _STL { template <> __declspec(dllimport) __forceinline void *&vector<void *>::operator[](unsigned int n) { return *(begin() + n); } }
namespace _STL {
template <> __declspec(dllimport) __forceinline
_STLP_alloc_proxy<int *, int, allocator<int> >::_STLP_alloc_proxy(const allocator<int> &a, int *p)
    : allocator<int>(a), _M_data(p) {}
template <> __declspec(dllimport) __forceinline
_Vector_base<int, allocator<int> >::_Vector_base(const allocator<int> &a)
    : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
}
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@UGen_p12pod@@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Select1st@U?$p:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_p12pod;
namespace _STL { template <> _Rb_tree_iterator<pair<Gen_p12pod const ,int>,_Nonconst_traits<pair<Gen_p12pod const ,int> > > _Rb_tree<Gen_p12pod,pair<Gen_p12pod const ,int>,_Select1st<pair<Gen_p12pod const ,int> >,less<Gen_p12pod>,allocator<pair<Gen_p12pod const ,int> > >::insert_unique(_Rb_tree_iterator<pair<Gen_p12pod const ,int>,_Nonconst_traits<pair<Gen_p12pod const ,int> > >,pair<Gen_p12pod const ,int> const &); }
// Suppress this TU's non-retail copy of ??$fill_n@PAPAXIPAX@_STL@@YAPAPAXPAPAXIABQAX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * fill_n<void * *,unsigned int,void *>(void * *,unsigned int,void * const &); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,allocator<void *> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??$__advance@PBIH@_STL@@YAXAAPBIHABUrandom_access_iterator_tag@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,random_access_iterator_tag const &); }
struct VertexPosition { float x,y,z; };
struct Gen_p12pod {
 Gen_p12pod(const VertexPosition &vertexPosition) { a[0]=int(vertexPosition.x); a[1]=int(vertexPosition.y); a[2]=int(vertexPosition.z); }
 int a[3];
};
inline bool compare_tail(const Gen_p12pod &gen_p12pod,const Gen_p12pod &b) {
 const int a1=gen_p12pod.a[1]; return b.a[1]>a1 || (!(b.a[1]<a1)&&gen_p12pod.a[2]<b.a[2]);
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
namespace _STL {
template <> void hashtable<pair<const Rva00928590Key, int>, Rva00928590Key,
    Rva00928590Hash, _Select1st<pair<const Rva00928590Key, int> >,
    Rva00928590Eq, allocator<pair<const Rva00928590Key, int> > >::resize(unsigned int);
}
class Rva0016E400 {
public:
 Rva0016E400();
 EdgeMap table;
};
struct MeshGeometrySlot64Element_00923F70 { unsigned char Data[16]; };
template<class T> class ShareBufferClass {
public:
 void Resize(int);
 T *Get_Array() { return Array; }
 int Get_Count() { return Count; }
 void *vptr;
 int references;
 T *RawBuffer,*Array;
 int Count,Alignment;
};
struct EdgeRecord { int vertex1,vertex2,triangle1,triangle2; };
struct TriangleIndices {
 unsigned short vertex[3];
 unsigned short &operator[](int n) { return vertex[n]; }
};
#include "../../../../GameEngine/Source/Common/debug.h"
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int);
#define GEOMETRY_REPORT(message) if(bfmeRva000387C0()) { _bfme_debugRecordCallsite(1); theDebug->SkipNext(); (theDebug->CrashBegin(0, 0, 0) << "Geometry for model " << Get_Name() << message).CrashDone(2); }
class Rva0016E450Source {
public:
 void *GetEdges(int *edgeCount);
 const char *Get_Name() { return MeshName ? MeshName->Get_Array() : 0; }
 char prefix[0x10];
 ShareBufferClass<char> *MeshName;
 char gap14[0x24-0x14];
 int PolyCount,VertexCount;
 ShareBufferClass<TriangleIndices> *Polys;
 ShareBufferClass<VertexPosition> *Vertices;
 char gap34[0x5c-0x34];
 ShareBufferClass<MeshGeometrySlot64Element_00923F70> *Edges;
};
// Welds vertices on positions quantized to 1/100, pairs each directed edge with its
// reverse through a hash table and caches the edge list; the three reports flag meshes unfit for shadows.
void *Rva0016E450Source::GetEdges(int *edgeCount)
{
 if(!Edges||!PolyCount||!VertexCount) { *edgeCount=0; return 0; }
 if(Edges->Get_Count()) { *edgeCount=Edges->Get_Count(); return Edges->Get_Array(); }
 Edges->Resize(PolyCount*3/2);
 EdgeRecord *edge=(EdgeRecord*)Edges->Get_Array();
 _STL::vector<int> vertexMap;
 {
  _STL::map<Gen_p12pod,int> welded;
  VertexPosition *vertex=Vertices->Get_Array();
  for(int i=0;i<VertexCount;i++,vertex++) {
   VertexPosition pos;
   pos.x=int(vertex->x*100.0f);
   pos.y=int(vertex->y*100.0f);
   pos.z=int(vertex->z*100.0f);
   _STL::map<Gen_p12pod,int>::iterator found=welded.find(Gen_p12pod(pos));
   if(found==welded.end()) {
    vertexMap.push_back(welded.size());
    welded[Gen_p12pod(pos)]=welded.size();
   } else vertexMap.push_back(found->second);
  }
 }
 Rva0016E400 edgeTable;
 TriangleIndices *poly=Polys->Get_Array();
 bool shared=false;
 for(int i=0;i<PolyCount;i++,poly++) {
  for(int j=0;j<3;j++) {
   if(vertexMap[(*poly)[j]]>vertexMap[(*poly)[(j+1)%3]]) {
    Rva00928590Key key(vertexMap[(*poly)[j]],vertexMap[(*poly)[(j+1)%3]]);
    if(!shared&&edgeTable.table.find(key)!=edgeTable.table.end()) {
     GEOMETRY_REPORT(" shares an edge with more than two triangles, this will cause shadow bugs.");
     shared=true;
    }
    edgeTable.table[key]=i;
   }
  }
 }
 int count=0;
 bool unpaired=false;
 poly=Polys->Get_Array();
 for(int i=0;i<PolyCount;i++,poly++) {
  for(int j=0;j<3;j++) {
   if(vertexMap[(*poly)[j]]<vertexMap[(*poly)[(j+1)%3]]) {
    Rva00928590Key key(vertexMap[(*poly)[(j+1)%3]],vertexMap[(*poly)[j]]);
    EdgeMap::iterator found=edgeTable.table.find(key);
    if(found==edgeTable.table.end()) {
     if(!unpaired) {
      GEOMETRY_REPORT(" contains at least one triangle that doesn't share an edge with another triangle.\nShadow bugs will occur.");
      unpaired=true;
     }
    } else if(count>=Edges->Get_Count()) unpaired=true;
    else {
     edge->vertex1=(*poly)[j];
     edge->vertex2=(*poly)[(j+1)%3];
     edge->triangle1=i;
     edge->triangle2=found->second;
     edge++;
     count++;
    }
   }
  }
 }
 if(count!=PolyCount*3/2||unpaired) {
  GEOMETRY_REPORT(" is not a valid shadow caster, it may contain T-junctions or not be closed. Shadow bugs are more than likely.");
  if(count==0) { edge->triangle2=0; edge->triangle1=0; edge->vertex2=0; edge->vertex1=0; count++; }
  Edges->Resize(count);
 }
 *edgeCount=Edges->Get_Count();
 return Edges->Get_Array();
}
