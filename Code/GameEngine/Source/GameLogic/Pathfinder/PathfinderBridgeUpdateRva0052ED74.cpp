// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// Native 0052ED74..0052F294, 1312B, RET8. Neutral shared receiver and
// existing int-word ABI come from rowed 0052F294; retail tests the flag byte.
// WB12DD670 corroborates the bridge-bounds removal and raised-wall endpoint
// handling. ZH AIPathfind.cpp bridge routines are semantic leads; BFME2's
// receiver +10 map, +5C bridge chain, +60 stride40 layers, +460 zones and
// +1BEB4 dirty flag are independently measured in retail and matched neighbours.
// Bridge record +C uses rowed A8 constructor/assignment; bounds are at +B4.
// The existing Rva002ED236Pos argument view preserves the callee-destroyed
// by-value float copy. Explicit float subtraction restores native fabs-call
// scheduling without changing the mathematical operation.
// Full neighbor arrays are read independently from retail DD1A3C/DD1A5C;
// original identifiers are unknown. Data rows verify all 32 bytes of each.
#include "Lib/Coord3D.h"
static __forceinline float bridgeDelta(float a,float b){return (float)(a-b);}
extern "C" double __cdecl fabs(double);
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
static __forceinline int float2long(float f){int i;__asm{fld f
 fistp i}return i;}
#define FLOOR(x) float2long((float)floor(x))
#define CEIL(x) float2long((float)ceil(x))
struct BridgeBounds {struct {float x,y;}lo,hi;BridgeBounds(const BridgeBounds &r){lo.x=r.lo.x;lo.y=r.lo.y;hi.x=r.hi.x;hi.y=r.hi.y;}~BridgeBounds(){}};
class Rva0027C36A {public:Rva0027C36A();Rva0027C36A &operator=(const Rva0027C36A &);Coord3D from,to;char rest[0xA8-24];};
class Bridge {public:virtual ~Bridge();Bridge *next;int word8;Rva0027C36A info;BridgeBounds bounds;};
struct CellOwnerInfo{char pad[0x28];int owner;};
class PathfindCell {public:int getOwner()const{return info?info->owner:0;}bool SetType_Dirty(int);CellOwnerInfo *info;char pad[8];unsigned int type:4,layer:6,rest:22;};
struct ICoord2D{int x,y;};
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
bool Rva001E3679(int);
class PathfindLayer {public:PathfindCell *getCell(int,int);void AddWallConnectCell(const ICoord2D *);char pad[0x3C];int height;};
class PathfindZoneManager{public:void MarkDirty(int,int);char pad[4];};
class Object;
struct Rva002ED236Pos {float x,y,z;Rva002ED236Pos(const Coord3D &p){x=p.x;y=p.y;z=p.z;}~Rva002ED236Pos(){}};
enum PathfindLayerEnum {GROUND=1};
class Pathfinder {public:PathfindLayerEnum rva002ED236(Object *,Rva002ED236Pos);void rva0052E914(int,int,PathfindCell *,Bridge *,bool,PathfindCell *,float);};
int BridgeUpdateNeighborX[8]={-1,1,0,0,-1,1,-1,1};
int BridgeUpdateNeighborY[8]={0,0,-1,1,-1,-1,1,1};
class Rva002E713FOwner {public:
 void rva0052ED74(void *,int);
 char pad00[0x10];PathfindCell **map;int loX,loY,hiX,hiY;char pad24[0x5C-0x24];Bridge *bridges;
 PathfindLayer layers[16];PathfindZoneManager zones;char pad464[0x1BEB4-0x464];bool changed;
};
void Rva002E713FOwner::rva0052ED74(void *opaque,int flags)
{
 Bridge *bridge=(Bridge *)opaque;
#define update (*(bool *)&flags)
 BridgeBounds bounds=bridge->bounds;
 if(!update){
  Bridge *previous=0;
  for(Bridge *node=bridges;node;){
   Bridge *next=node->next;BridgeBounds other=node->bounds;
   if(fabs(bridgeDelta(other.lo.x,bounds.lo.x))<1.0f && fabs(bridgeDelta(other.lo.y,bounds.lo.y))<1.0f && fabs(bridgeDelta(other.hi.x,bounds.hi.x))<1.0f && fabs(bridgeDelta(other.hi.y,bounds.hi.y))<1.0f){
    if(previous)previous->next=next;else bridges=next;
    node->next=0;::delete node;
   }else previous=node;
   node=next;
  }
 }
 int first=1,second=1,actualFirst=1,actualSecond=1;
 if(update){
  Rva0027C36A info;info=bridge->info;
  actualFirst=first=((Pathfinder *)this)->rva002ED236(0,info.from);
  if(Rva001E3679(first)){ICoord2D cell;layers[first].AddWallConnectCell(Rva002E7875WorldToCell(&cell,true,&info.from));}else first=1;
  actualSecond=second=((Pathfinder *)this)->rva002ED236(0,info.to);
  if(Rva001E3679(second)){ICoord2D cell;layers[second].AddWallConnectCell(Rva002E7875WorldToCell(&cell,true,&info.to));}else second=1;
 }
 int lx=FLOOR((bounds.lo.x-.1f)*.1f),ly=FLOOR((bounds.lo.y-.1f)*.1f);
 int hx=CEIL((bounds.hi.x+.1f)*.1f),hy=CEIL((bounds.hi.y+.1f)*.1f);
 lx-=2;ly-=2;hx+=2;hy+=2;
 if(lx<loX)lx=loX;if(ly<loY)ly=loY;if(hx>hiX)hx=hiX;if(hy>hiY)hy=hiY;
 if(changed || !update || Rva001E3679(first) || Rva001E3679(second)){
  for(int i=lx;i<=hx;++i)for(int j=ly;j<=hy;++j){
   PathfindCell *other=0;float height=0;
   if(first!=1){other=layers[first].getCell(i,j);height=(float)layers[first].height;}
   if(!other && second!=1){other=layers[second].getCell(i,j);height=(float)layers[second].height;}
   ((Pathfinder *)this)->rva0052E914(i,j,&map[i][j],bridge,update,other,height);
  }
 }
 if(update && (first!=1||second!=1) && actualFirst!=1 && actualSecond!=1){
  for(int i=lx+1;i<=hx-1;++i)for(int j=ly+1;j<=hy-1;++j){
   PathfindCell *cell=&map[i][j];
   if(cell->layer==16 && cell->type!=5){
    for(int n=0;n<8;++n){
     PathfindCell *near=&map[i+BridgeUpdateNeighborX[n]][j+BridgeUpdateNeighborY[n]];
     if(near->layer!=16 && near->type!=5 && near->layer==1 && near->getOwner()==0){
      if(near->SetType_Dirty(2))zones.MarkDirty(i+BridgeUpdateNeighborX[n],j+BridgeUpdateNeighborY[n]);
     }
    }
   }
  }
 }
}
