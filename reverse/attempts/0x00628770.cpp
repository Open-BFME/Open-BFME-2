// ?GetObjectsInRange@PartitionManagerImpl@@QAE?AUBfmeWideResult@@PBMMPBURva009F4130Range@@HPAVRva009F2AB0Mask@@H@Z
// partial score=1.0 date=2026-10-10
// cl: /O2 /Ob1 /G6 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
struct Rva009F39F0Payload { void *start, *finish, *end, *cursor; int refs; Rva009F39F0Payload():start(0),finish(0),end(0){} };
struct Rva009F39F0Result { Rva009F39F0Payload *value; Rva009F39F0Result(); };
#include "PartitionRangeQueryCallView.h"
__declspec(noinline) BfmeWideResult::BfmeWideResult() {
    m_value = new Rva009F39F0Payload;
    ((Rva009F39F0Payload *)m_value)->refs=1;
    ((Rva009F39F0Payload *)m_value)->cursor=((Rva009F39F0Payload *)m_value)->start;
}
__forceinline BfmeWideResult::BfmeWideResult(const BfmeWideResult &other) : m_value(other.m_value) {
    ++((Rva009F39F0Payload *)m_value)->refs;
}
__forceinline BfmeWideResult::~BfmeWideResult() {
    --((Rva009F39F0Payload *)m_value)->refs;
    if (((Rva009F39F0Payload *)m_value)->refs==0) {
        Rva009F39F0Payload *payload=(Rva009F39F0Payload *)m_value;
        if (payload->start) _STL::free(payload->start);
        ::operator delete(payload);
    }
}
struct Rva009F4130Range { float x0,y0,z0,x1,y1; };
struct Rva009F4130NodeList { int count; void *head; };
class BfmeThingEQ;
class Rva009F2AB0Mask { public: int getMask(); };
class BfmeHostER { public: unsigned bfmeIndexER(float); };
class BfmeHostES { public: unsigned bfmeIndexES(float); };
class BfmeThingVJX { public: void bfmeGoVJX(int); };
typedef float (__cdecl *Rva009F4130Distance)(void *,void *,float);
// The target's mutable five-entry callback table at VA DD7EC0. These
// declarations retain each provider's rowed ABI; the common pointer view is
// only the query helper's table consumption, not a new provider signature.
struct Coord2DBase; class Rva009F4070PositionProvider;
struct Coord3DBase; class Rva009F40A0PositionProvider;
struct Coord3D; class Object; class BfmePosEJ; class BfmeObjEJ;
class Rva009F66F0Provider;
float Rva009F4070DistanceSquared(const Coord2DBase *, Rva009F4070PositionProvider *);
float bfmeSignedEJ(const BfmePosEJ *, BfmeObjEJ *);
float Rva009F40A0DistanceSquared(const Coord3DBase *, Rva009F40A0PositionProvider *);
float distCalcProc_BoundaryAndBoundary_3D(const Coord3D *, const Object *, int);
float Rva009F66F0(const Coord3D *, Rva009F66F0Provider *, float);
Rva009F4130Distance g_partitionDistance[5] = {
 (Rva009F4130Distance)Rva009F4070DistanceSquared,
 (Rva009F4130Distance)bfmeSignedEJ,
 (Rva009F4130Distance)Rva009F40A0DistanceSquared,
 (Rva009F4130Distance)distCalcProc_BoundaryAndBoundary_3D,
 (Rva009F4130Distance)Rva009F66F0
};
struct PartitionTreeView { Rva009F4130NodeList *begin, *end, *capacity; };
class PartitionManagerImpl {
public:
    int prefix[6]; _STL::vector<Rva009F4130NodeList> trees[21];
    void *head; float scale; int size;
    BfmeWideResult GetObjectsInRange(const float *,float,const Rva009F4130Range *,int,Rva009F2AB0Mask *,int);
    void _GetObjectsInRange(Rva009F39F0Result *,Rva009F4130NodeList *,unsigned,int,int,int,int,int,int,int,void *,float,const Rva009F4130Range *,Rva009F4130Distance,BfmeThingEQ *);
};
// WB1681FF0 and the native 525-byte body; BFME 1's result lifetime is retained.
BfmeWideResult PartitionManagerImpl::GetObjectsInRange(const float *position,float radius,const Rva009F4130Range *bounds,int distanceType,Rva009F2AB0Mask *filter,int sort)
{
    BfmeWideResult result;
    if (distanceType!=0 && distanceType!=2 && distanceType!=1 && distanceType!=3 && distanceType!=4) distanceType=0;
    unsigned mask=filter ? filter->getMask()*2+1 : ~0u;
    int xmin,xmax,ymin,ymax;
    if (position) {
        xmin=((BfmeHostER *)this)->bfmeIndexER(position[0]-radius);
        xmax=((BfmeHostER *)this)->bfmeIndexER(position[0]+radius);
        ymin=((BfmeHostES *)this)->bfmeIndexES(position[1]-radius);
        ymax=((BfmeHostES *)this)->bfmeIndexES(position[1]+radius);
    } else {
        xmin=((BfmeHostER *)this)->bfmeIndexER(bounds->x0);
        xmax=((BfmeHostER *)this)->bfmeIndexER(bounds->x1);
        ymin=((BfmeHostES *)this)->bfmeIndexES(bounds->y0);
        ymax=((BfmeHostES *)this)->bfmeIndexES(bounds->y1);
    }
    radius*=radius;
    _STL::vector<Rva009F4130NodeList> *tree=trees;
    for (int remaining=21;remaining;--remaining,++tree,mask>>=1) {
        if (mask&1) _GetObjectsInRange((Rva009F39F0Result *)&result,tree->begin(),trees[0].size()/4,xmin,ymin,xmax,ymax,0,0,size,(void *)position,radius,bounds,g_partitionDistance[distanceType],(BfmeThingEQ *)filter);
    }
    if (sort) ((BfmeThingVJX *)&result)->bfmeGoVJX(sort);
    return result;
}
