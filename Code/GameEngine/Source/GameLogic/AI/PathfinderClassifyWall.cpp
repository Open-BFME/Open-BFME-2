// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /I.
// stlport
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <new>
#include <set>
#include <vector>
#include "ascii_string.h"
extern "C" void __cdecl free(void*);
// ?ClassifyWall@Pathfinder@@QAEXPAVObject@@_N@Z retail 0x0052F63F..0x00530212 (3027 bytes).
// BFME 2 wall classifier (WB twin Pathfinder::ClassifyWall; called from 0x00530F38 inside
// 0x00530212). Target evidence: on insert it merges the wall's bridge polygon into a free
// or overlapping layer 2..15, matches the wall height against the 64-entry height table
// (layers 17+, tolerance 3.5, debug report under 9.9), rasterises the wall polygon through
// the rowed 0x0052E6E6 and re-pinches the touched cells; on removal it unpinches, resets
// the wall layer's cells and reclassifies every other wall in wallIDs whose cell bounds
// overlap. Locals, loop order and init order follow the WB frame; the m_extent reference
// and the barrier before the dirty test reproduce retail's operand order and spills.

typedef int Int;

#include "../../../Include/GameLogic/Rva0052E02F.h"

class Rva0052E0CE
{
public:
	bool rva0052E0CE(bool value);
};

#include "../../../Include/GameLogic/Rva002E713FOwner.h"

#include "../../../Include/GameLogic/PathfindCell.h"

// Retail inlines these packed-dword (+0x0C) accesses: layer bits 4..9 read as
// an int, pinched bit 16.
static __forceinline Int getCellLayerBits(const PathfindCell *cell)
{
	return (cell->m_0C >> 4) & 0x3F;
}
static __forceinline void setCellPinched(PathfindCell *cell, bool pinch)
{
	if (pinch)
		cell->m_0C |= 0x10000u;
	else
		cell->m_0C &= ~0x10000u;
}

#include "Code/Libraries/Include/Lib/ICoord2D.h"

#include "Code/Libraries/Include/Lib/IRegion2D.h"

struct BfmeE8{int a,b;};
// These are only expanded inline here; bind to the kept retail copies instead of
// emitting this unit's own (bodies verbatim primary).
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<int,int>(int *p,int const &v) { new (p) int(v); } }
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const { return x < y; } }
namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &a,const unsigned int &b) { return a < b ? b : a; } }
// Retail's push_back calls the no-EH provider 0x00057C80; spell its algorithm
// out (as GameLogicInit.cpp does) so this TU's copy is that provider, not an EH copy.
namespace _STL {
template<> inline void vector<BfmeE8>::_M_insert_overflow(
    pointer position, const BfmeE8 &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}
class Dict;
class Rva0027C36A{public:Rva0027C36A();char bytes[0xa8];};
class PolygonTrigger{public:virtual void *destroy(unsigned);void getBounds(IRegion2D*);};
class Bridge{public:Bridge(Rva0027C36A&,Dict*,const AsciiString&,PolygonTrigger*);virtual void *destroy(unsigned);Bridge*next;char bytes[0xcc-8];};
#include "../../../Include/GameClient/Drawable.h"
struct WallTemplate{char pad[0x64];AsciiString name;const AsciiString&getName()const{return name;}};
class Object{public:Drawable*getDrawable()const;const WallTemplate*getTemplate()const{return templ;}char pad0[4];WallTemplate*templ;char pad8[0x74-8];int id;int getID()const{return id;}char pad78[0x94-0x78];unsigned status;};
#include "../../../Include/Common/Rva0036666B.h"
class Rva0036658B{public:bool rva0036658B(void*,void*);};
#include "../../../Include/GameLogic/PathfindLayer.h"
#include "../../../Include/GameLogic/Rva00366500.h"
#include "../../../Include/GameLogic/Rva0052E001.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
#include "../../Common/debug.h"
extern Debug*theDebug;
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
#include <math.h>
static __forceinline int float2long(float f){int i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long(floorf(x))
#define CEIL(x) float2long(ceilf(x))


class Pathfinder
{
public:
	void ClassifyWall(Object *,bool);
	bool rva0052E6E6(int,int,PathfindCell *,PolygonTrigger *,int,bool);
	float &heightForLayer(int layer){return heights[layer-17];}
	const AsciiString &nameForLayer(int layer){return names[layer-17];}

private:
	char m_head[0xC];
	int allocated;
	PathfindCell **m_map;
	IRegion2D m_extent;
	char pad24[0x5C-0x24];Bridge *bridges;PathfindLayer layers[16];PathfindZoneManager zones;
	bool changedWall;char pad1BEB5[3];int heightCount;float heights[64];AsciiString names[64];char pad1C0BC[0x1c1c0-0x1c0bc];_STL::set<int>wallIDs;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
static __forceinline void deletePoly(PolygonTrigger *p){operator delete(p?p->destroy(0):0);}
void Pathfinder::ClassifyWall(Object*obj,bool insert)
{
 const float tolerance=3.5f;
 Int i, j;
 Drawable*drawable=obj->getDrawable();if(!drawable)return;
 Rva0027C36A data;PolygonTrigger*poly;
 if(insert){
  float h;poly=(PolygonTrigger*)drawable->rva002725E7((int)&h);
  if(poly){
   bool merged = false;
   int layer=2;IRegion2D bounds;poly->getBounds(&bounds);
   for(;layer <= 15;layer++){
    PathfindLayer *entry = &layers[layer];
    if(((Rva0036666B*)entry)->rva0036666B() && entry->m_triggers && entry->DoBoundsOverlap(&bounds) && fabs(entry->getHeight()-h)<tolerance){
     if(allocated)layers[layer].rva003667D4();
     layers[layer].AddArea(poly);
     if(allocated)layers[layer].allocateCells(&m_extent);
     poly=0;merged=true;break;
    }
   }
   if(!merged){
    for(layer=2;layer <= 15;++layer){
     const PathfindLayer *entry = &layers[layer];
     if(!((Rva0036666B*)entry)->rva0036666B()){
      if(((Rva0036658B*)&layers[layer])->rva0036658B(poly,(void*)layer)){
       if(allocated){layers[layer].allocateCells(&m_extent);zones.field1BA31=true;}
       break;
      }
      break;
     }
    }
   }
  }
  if(drawable->rva0027267D((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);b->next=bridges;bridges=b;changedWall=true;
  }
  if(drawable->rva002726C3((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);b->next=bridges;bridges=b;changedWall=true;
  }
 }else{
  if(drawable->rva0027267D((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);((Rva002E713FOwner*)this)->rva0052ED74(b,0);operator delete(b?b->destroy(0):0);
  }
  if(drawable->rva002726C3((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);((Rva002E713FOwner*)this)->rva0052ED74(b,0);operator delete(b?b->destroy(0):0);
  }
 }
 float height;PolygonTrigger*area=(PolygonTrigger*)drawable->rva002725B1((int)&height);if(!area)return;
 float closest=1000000.0f;int layer=1;
 for(int i=0;i<heightCount;++i){float distance=fabs(height-heights[i]);if(distance<closest){closest=distance;layer=i+17;}}
 if(closest > tolerance){
  static int count=0;
  if(closest < 9.9f&&count<10){
   ++count;
   if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();
    (theDebug->CrashBegin(0,0,0)<<obj->getTemplate()->getName().str()<<" has a wall height of "<<height<<" but there's already a wall with a height\nof "<<heightForLayer(layer)<<" defined by "<<nameForLayer(layer).str()<<" - maximum delta for considering two walls to\nbe equal is "<<tolerance<<"; needs to be fixed /"<<layer).CrashDone(2);
   }
  }
  if(heightCount < 64){heights[heightCount]=height;names[heightCount]=obj->getTemplate()->getName();layer=heightCount+17;++heightCount;}
  else{
   static bool warned=false;
   if((!warned)){warned=true;if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();(theDebug->CrashBegin(0,0,0)<<"Ran out of wall entries; too many walls with different heights on map").CrashDone(2);
   }}
  }
 }
 if(height>heightForLayer(layer)){heightForLayer(layer)=height;names[layer-17]=obj->getTemplate()->getName();}
 IRegion2D world;area->getBounds(&world);
 IRegion2D cellBounds;
 cellBounds.lo.x=FLOOR(world.lo.x/10)-2;
 cellBounds.lo.y=FLOOR(world.lo.y/10)-2;
 cellBounds.hi.x=CEIL(world.hi.x/10)+2;
 cellBounds.hi.y=CEIL(world.hi.y/10)+2;
 
 const IRegion2D &extent=m_extent;
 if(cellBounds.lo.x<extent.lo.x)cellBounds.lo.x=extent.lo.x;
 if(cellBounds.lo.y<extent.lo.y)cellBounds.lo.y=extent.lo.y;
 if(cellBounds.hi.x>extent.hi.x)cellBounds.hi.x=extent.hi.x;
 if(cellBounds.hi.y>extent.hi.y)cellBounds.hi.y=extent.hi.y;
 if(insert){
  wallIDs.insert(obj->getID());_STL::vector<BfmeE8>changed;
  for(j=cellBounds.lo.y;j <= cellBounds.hi.y;++j)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   if(rva0052E6E6(i,j,&m_map[i][j],area,layer,insert)){BfmeE8 p={i,j};changed.push_back(p);}
  }
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;++j)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   const int current=getCellLayerBits(&m_map[i][j]);
   if(current==layer)setCellPinched(&m_map[i][j], false);
   if(m_map[i][j].getType()==0){
    int count=0;for(int k=i-1;k<i+2;k++){if(k<extent.lo.x||k>extent.hi.x)continue;
     for(int l=j-1;l<j+2;++l){if(l<extent.lo.y||l>extent.hi.y)continue;if(k==i&&j==l)continue;
      if(getCellLayerBits(&m_map[k][l])!=current)++count;
     }
    }
    if(count > 1)setCellPinched(&m_map[i][j], true);
   }
  }
  for(_STL::vector<BfmeE8>::iterator p=changed.begin();p!=changed.end();p++){
   const int i=p->a,j=p->b;if(m_map[i][j].getPinched()&&m_map[i][j].getType()==0){m_map[i][j].SetType_Dirty(8);zones.MarkDirty(i,j);}setCellPinched(&m_map[i][j], false);
  }
 }else{
  _STL::set<int>::iterator found=wallIDs.find(obj->getID());if(found!=wallIDs.end())wallIDs.erase(found);
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;j++)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   if(m_map[i][j].getPinched()){int current=getCellLayerBits(&m_map[i][j]);int count=0;
    for(int k=i-1;k<i+2;k++){if(k<extent.lo.x||k>extent.hi.x)continue;
     for(int l=j-1;l<j+2;l++){if(l<extent.lo.y||l>extent.hi.y)continue;if(k==i&&j==l)continue;if(getCellLayerBits(&m_map[k][l])!=current)++count;}
    }
    if(count > 1)setCellPinched(&m_map[i][j], false);
   }
  }
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;j++)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   PathfindCell*cell=&m_map[i][j];
   if(getCellLayerBits(cell)==layer){
    bool dirty=cell->SetType_Dirty(0);dirty|=((Rva0052E001*)cell)->rva0052E001(false);dirty|=((Rva00366500*)cell)->rva00366500(true);dirty|=((Rva00366500*)cell)->rva0036652D(false);
    _ReadWriteBarrier();
    if(dirty)zones.MarkDirty(i,j);setCellPinched(cell, false);
   }
  }
  for(_STL::set<int>::iterator p=wallIDs.begin();p!=wallIDs.end();++p){
   Object*other=TheGameLogic->findObjectByID((ObjectID)*p);if((!other)||(other->status&1))continue;
   Drawable*otherDrawable=other->getDrawable();if((!otherDrawable))continue;float otherHeight;PolygonTrigger*otherArea=(PolygonTrigger*)otherDrawable->rva002725B1((int)&otherHeight);if(!otherArea)continue;
   IRegion2D qb;otherArea->getBounds(&qb);
   IRegion2D qc;
   qc.lo.x=FLOOR(qb.lo.x/10)-2;
   qc.lo.y=FLOOR(qb.lo.y/10)-2;
   qc.hi.x=CEIL(qb.hi.x/10)+2;
   qc.hi.y=CEIL(qb.hi.y/10)+2;
   if((qc.lo.x<=cellBounds.hi.x&&qc.hi.x>=cellBounds.lo.x&&qc.lo.y<=cellBounds.hi.y&&qc.hi.y>=cellBounds.lo.y)){ClassifyWall(other,true);deletePoly(otherArea);}
  }
 }
 deletePoly(area);
}
