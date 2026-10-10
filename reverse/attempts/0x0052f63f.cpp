// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.7679020463804076 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /I.
// stlport
// NEW native ClassifyWall reconstruction, 0052F63F..00530212, RET8.
// ZH AIPathfind.cpp gives raster/pinch semantics; BFME wall layer/height,
// portal bridge ownership, bookkeeping and diagnostics are target evidence.
#include <new>
#include <set>
#include <vector>
#include "ascii_string.h"
struct ICoord2D{int x,y;};
struct IRegion2D{ICoord2D lo,hi;};
struct BfmeE8{int a,b;};
class Dict;
class Rva0027C36A{public:Rva0027C36A();char bytes[0xa8];};
class PolygonTrigger{public:virtual void *destroy(unsigned);void getBounds(int*);};
class Bridge{public:Bridge(Rva0027C36A&,Dict*,const AsciiString&,PolygonTrigger*);virtual void *destroy(unsigned);Bridge*next;char bytes[0xcc-8];};
class Drawable{public:int rva002725E7(int);int rva002725B1(int);bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);};
struct WallTemplate{char pad[0x64];AsciiString name;};
class Object{public:Drawable*getDrawable()const;char pad0[4];WallTemplate*templ;char pad8[0x74-8];int id;char pad78[0x94-0x78];unsigned status;};
class Rva0036666B{public:bool rva0036666B();};
class Rva0036658B{public:bool rva0036658B(void*,void*);};
class PathfindLayer{public:bool DoBoundsOverlap(const IRegion2D*);void rva003667D4();void AddArea(void*);void allocateCells(const IRegion2D*);char pad[0x38];PolygonTrigger*areas;int height;};
class Rva00366500{public:bool rva00366500(int);bool rva0036652D(int);};
class Rva0052E001{public:bool rva0052E001(bool);};
class PathfindCell{public:bool SetType_Dirty(int);char pad[12];unsigned type:4;unsigned layer:6;unsigned low:6;unsigned pinched:1;unsigned mid:15;};
class PathfindZoneManager{public:void MarkDirty(int,int);};

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Debug{public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual Debug&putFloat(float);virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual Debug&putInt(int);virtual Debug&putText(const char*);virtual void s3C();virtual void s40();virtual void s44();virtual void s48();virtual bool CrashDone(int);virtual void s50();virtual void s54();virtual void s58();virtual void s5C();virtual void SkipNext();virtual void s64();virtual void s68();virtual Debug&CrashBegin(const char*,int,int);
};
static __forceinline Debug &operator<<(Debug &d,float x){return d.putFloat(x);}
static __forceinline Debug &operator<<(Debug &d,int x){return d.putInt(x);}
static __forceinline Debug &operator<<(Debug &d,const char*x){return d.putText(x);}
extern Debug*theDebug;
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
extern "C" double __cdecl fabs(double);
extern "C" __declspec(dllimport)double __cdecl floor(double);
extern "C" __declspec(dllimport)double __cdecl ceil(double);
static __forceinline int float2long(float f){int i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long((float)floor(x))
#define CEIL(x) float2long((float)ceil(x))
class Rva002E713FOwner{public:void rva0052ED74(void*,int);};
class Pathfinder{public:
 void rva0052F63F(Object*,bool);void rva0052ED74(Bridge*,int);bool rva0052E6E6(int,int,PathfindCell*,PolygonTrigger*,int,bool);
 char pad0[12];int allocated;PathfindCell**map;IRegion2D extent;char pad24[0x5c-0x24];Bridge*bridges;PathfindLayer layers[16];PathfindZoneManager zones;
 char pad461[0x1be91-0x461];bool changedLayer;char pad1BE92[0x1beb4-0x1be92];bool changedWall;char pad1BEB5[3];int heightCount;float heights[64];AsciiString names[64];char pad1C0BC[0x1c1c0-0x1c0bc];_STL::set<int>wallIDs;
 float &heightForLayer(int layer){return *((float*)((char*)this+0x1be78)+layer);}
 const AsciiString&nameForLayer(int layer){return names[layer-17];}
};
static __forceinline void deletePoly(PolygonTrigger*p){operator delete(p?p->destroy(0):0);}
void Pathfinder::rva0052F63F(Object*obj,bool insert)
{
 Drawable*drawable=obj->getDrawable();if(!drawable)return;
 static const volatile float tolerance=3.5f;Rva0027C36A data;PolygonTrigger*poly;
 if(insert){
  float h;poly=(PolygonTrigger*)drawable->rva002725E7((int)&h);
  if(poly){
   int layer=2;IRegion2D bounds;poly->getBounds((int*)&bounds);
   for(layer=2;layer<=15;++layer){
    PathfindLayer*entry=&layers[layer];int layerHeight=entry->height;
    if(((Rva0036666B*)entry)->rva0036666B()&&entry->areas&&entry->DoBoundsOverlap(&bounds)&&fabs((float)layerHeight-h)<tolerance)break;
   }
   if(layer<=15){
    if(allocated)layers[layer].rva003667D4();layers[layer].AddArea(poly);
    if(allocated)layers[layer].allocateCells(&extent);poly=0;
   }else{
    for(layer=2;layer<=15;++layer)if(!((Rva0036666B*)&layers[layer])->rva0036666B())break;
    if(layer<=15&&((Rva0036658B*)&layers[layer])->rva0036658B(poly,(void*)layer)&&allocated){layers[layer].allocateCells(&extent);changedLayer=true;}
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
 int layer=1;float closest=1000000.0f;
 for(int i=0;i<heightCount;++i){float distance=(float)fabs(height-heights[i]);if(distance<closest){closest=distance;layer=i+17;}}
 if(closest>tolerance){
  static int count=0;
  if(closest<9.9f&&count<10){
   ++count;
   if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();
    (theDebug->CrashBegin(0,0,0)<<obj->templ->name.str()<<" has a wall height of "<<height<<" but there's already a wall with a height\nof "<<heightForLayer(layer)<<" defined by "<<nameForLayer(layer).str()<<"; separation required "<<tolerance<<"; layer "<<layer).CrashDone(2);
   }
  }
  if(heightCount<64){heights[heightCount]=height;names[heightCount]=obj->templ->name;layer=heightCount+17;++heightCount;}
  else{
   static bool warned=false;
   if(!warned){warned=true;if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();(theDebug->CrashBegin(0,0,0)<<"Ran out of wall entries; too many walls with different heights on map").CrashDone(2);
   }}
  }
 }
 if(height>heightForLayer(layer)){heightForLayer(layer)=height;names[layer-17]=obj->templ->name;}
 IRegion2D world;area->getBounds((int*)&world);
 IRegion2D bounds={{FLOOR(world.lo.x/10)-2,FLOOR(world.lo.y/10)-2},{CEIL(world.hi.x/10)+2,CEIL(world.hi.y/10)+2}};
 if(bounds.lo.x<extent.lo.x)bounds.lo.x=extent.lo.x;if(bounds.lo.y<extent.lo.y)bounds.lo.y=extent.lo.y;
 if(bounds.hi.x>extent.hi.x)bounds.hi.x=extent.hi.x;if(bounds.hi.y>extent.hi.y)bounds.hi.y=extent.hi.y;
 if(insert){
  wallIDs.insert(obj->id);_STL::vector<BfmeE8>changed;
  for(int j=bounds.lo.y;j<=bounds.hi.y;++j)for(int i=bounds.lo.x;i<=bounds.hi.x;++i){
   if(rva0052E6E6(i,j,&map[i][j],area,layer,insert)){BfmeE8 p={i,j};changed.push_back(p);}
  }
  for(int j=bounds.lo.y;j<=bounds.hi.y;++j)for(int i=bounds.lo.x;i<=bounds.hi.x;++i){
   if(map[i][j].layer==layer)map[i][j].pinched=false;
   if(map[i][j].type==0){
    int count=0;for(int k=i-1;k<i+2;++k){if(k<extent.lo.x||k>extent.hi.x)continue;
     for(int l=j-1;l<j+2;++l){if(l<extent.lo.y||l>extent.hi.y)continue;if(k==i&&l==j)continue;
      if(map[k][l].layer!=map[i][j].layer)++count;
     }
    }
    if(count>1)map[i][j].pinched=true;
   }
  }
  for(_STL::vector<BfmeE8>::iterator p=changed.begin();p!=changed.end();++p){
   int i=p->a,j=p->b;if(map[i][j].pinched&&map[i][j].type==0){map[i][j].SetType_Dirty(8);zones.MarkDirty(i,j);}map[i][j].pinched=false;
  }
 }else{
  _STL::set<int>::iterator found=wallIDs.find(obj->id);if(found!=wallIDs.end())wallIDs.erase(found);
  for(int j=bounds.lo.y;j<=bounds.hi.y;++j)for(int i=bounds.lo.x;i<=bounds.hi.x;++i){
   if(map[i][j].pinched){int count=0;int current=map[i][j].layer;
    for(int k=i-1;k<i+2;++k){if(k<extent.lo.x||k>extent.hi.x)continue;
     for(int l=j-1;l<j+2;++l){if(l<extent.lo.y||l>extent.hi.y)continue;if(k==i&&l==j)continue;if(map[k][l].layer!=current)++count;}
    }
    if(count>1)map[i][j].pinched=false;
   }
  }
  for(int j=bounds.lo.y;j<=bounds.hi.y;++j)for(int i=bounds.lo.x;i<=bounds.hi.x;++i){
   if(map[i][j].layer==layer){
    PathfindCell*c=&map[i][j];bool dirty=c->SetType_Dirty(0);dirty|=((Rva0052E001*)c)->rva0052E001(false);dirty|=((Rva00366500*)c)->rva00366500(true);dirty|=((Rva00366500*)c)->rva0036652D(false);
    if(dirty)zones.MarkDirty(i,j);c->pinched=false;
   }
  }
  for(_STL::set<int>::iterator p=wallIDs.begin();p!=wallIDs.end();++p){
   Object*other=TheGameLogic->findObjectByID((ObjectID)*p);if(!other||(other->status&1))continue;
   Drawable*d=other->getDrawable();if(!d)continue;float z;PolygonTrigger*q=(PolygonTrigger*)d->rva002725B1((int)&z);if(!q)continue;
   IRegion2D qb;q->getBounds((int*)&qb);
   int lx=FLOOR(qb.lo.x/10)-2,ly=FLOOR(qb.lo.y/10)-2,hx=CEIL(qb.hi.x/10)+2,hy=CEIL(qb.hi.y/10)+2;
   if(lx<=bounds.hi.x&&hx>=bounds.lo.x&&ly<=bounds.hi.y&&hy>=bounds.lo.y){rva0052F63F(other,true);deletePoly(q);}
  }
 }
 deletePoly(area);
}
