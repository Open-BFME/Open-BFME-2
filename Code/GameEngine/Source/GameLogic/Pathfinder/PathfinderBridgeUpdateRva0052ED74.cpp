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
// Ground setters precede the dirty test; the other-cell connection follows it.
// math.h's float fabs keeps the 15.0f tolerance compare a four-byte load.
#include "Lib/Coord3D.h"
#include "Lib/Region2D.h"
#include "../../Common/GameLogicObjectLookupView.h"
static __forceinline float bridgeDelta(float a,float b){return (float)(a-b);}
// Keep math.h's unused out-of-line floorf copy local.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
static __forceinline int float2long(float f){int i;__asm{fld f
 fistp i}return i;}
#define FLOOR(x) float2long((float)floor(x))
#define CEIL(x) float2long((float)ceil(x))
struct BridgeBounds {struct {float x,y;}lo,hi;BridgeBounds(const BridgeBounds &r){lo.x=r.lo.x;lo.y=r.lo.y;hi.x=r.hi.x;hi.y=r.hi.y;}~BridgeBounds(){}};
class Rva0027C36A {public:Rva0027C36A();Rva0027C36A &operator=(const Rva0027C36A &);Coord3D from,to;char rest[0xA8-24];};
class Bridge {public:virtual ~Bridge();Bridge *next;int word8;Rva0027C36A info;BridgeBounds bounds;bool isPointOnBridge(const Coord3D *loc);float getBridgeHeight(const Coord3D *loc,Coord3D *normal);bool isCellOnEnd(const Region2D *cellBounds);};
struct CellOwnerInfo{char pad[0x28];int owner;};
struct Rva0052DFB1Arg;
class PathfindCell {public:int getOwner()const{return info?info->owner:0;}int getType()const{return type;}int getLayer()const{return layer;}int getObstacleID()const{return info?info->owner:0;}void setPinched(bool p){pinched=p;}bool rva0052DFB1(const Rva0052DFB1Arg *arg);CellOwnerInfo *info;char pad[8];unsigned int type:4,layer:6,unused:6,pinched:1,rest:15;bool SetType_Dirty(int);};
// cl evaluates the calls of an ORed setter chain by a key built from each call's
// constant argument and its callee's declaration position (larger constants and
// later declarations first). Retail's four orders need connect declared just
// after SetType_Dirty and before layer, and E0A1 declared well after both.
class Rva00366500{public:bool rva0036652D(int);bool rva00366500(int);};
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
bool Rva001E3679(int);
#include "../../../Include/GameLogic/PathfindLayer.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/GameLogic/Rva0052E001.h"
class Object;
struct Rva002ED236Pos {float x,y,z;Rva002ED236Pos(const Coord3D &p){x=p.x;y=p.y;z=p.z;}~Rva002ED236Pos(){}};
enum PathfindLayerEnum {GROUND=1};
#include "../../../Include/GameLogic/AIPathfind.h"
extern GameLogic *TheGameLogic;
class Rva0052E0A1{public:bool rva0052E0A1(int v);};
// Native 0052E914..0052ED74, RET28. WB12DE080 gives each ORed setter condition; the
// other-cell connection follows the dirty test. Corners follow ZH classifyLayerMapCell.
/**
 * Classify the given map cell as clear, or not, etc.
 */
void Pathfinder::rva0052E914(int i,int j,PathfindCell *cell,Bridge *theBridge,bool flag,PathfindCell *otherCell,float height)
{
	Coord3D topLeftCorner, bottomRightCorner;
	topLeftCorner.y=(float)(j*10);bottomRightCorner.y=topLeftCorner.y+10.0f;
	topLeftCorner.x=(float)(i*10);bottomRightCorner.x=topLeftCorner.x+10.0f;
	topLeftCorner.z=0;bottomRightCorner.z=0;
	int bridgeCount=0;Coord3D pt;
	if(theBridge->isPointOnBridge(&topLeftCorner))bridgeCount++;
	pt=topLeftCorner;pt.y=bottomRightCorner.y;
	if(theBridge->isPointOnBridge(&pt))bridgeCount++;
	if(theBridge->isPointOnBridge(&bottomRightCorner))bridgeCount++;
	pt=topLeftCorner;pt.x=bottomRightCorner.x;
	if(theBridge->isPointOnBridge(&pt))bridgeCount++;
	if(flag){
		if(bridgeCount!=0&&cell->getType()==4){
			Object *obj=TheGameLogic->findObjectByID((ObjectID)cell->getObstacleID());
			if(obj){cell->rva0052DFB1((const Rva0052DFB1Arg*)obj);m_zoneManager.MarkDirty(i,j);}
		}
		if(bridgeCount>0){if(((Rva0052E001*)cell)->rva0052E001(true))m_zoneManager.MarkDirty(i,j);}
		if(bridgeCount==4){
			if(((Rva00366500*)cell)->rva00366500(0x10)|((Rva0052E0A1*)cell)->rva0052E0A1(0)|((Rva00366500*)cell)->rva0036652D(0)|cell->SetType_Dirty(0))m_zoneManager.MarkDirty(i,j);
			cell->setPinched(false);
			return;
		}
		if(bridgeCount==0)return;
		// check against the end lines.
		Region2D cellBounds;
		cellBounds.lo.x=topLeftCorner.x;cellBounds.lo.y=topLeftCorner.y;
		cellBounds.hi.x=bottomRightCorner.x;cellBounds.hi.y=bottomRightCorner.y;
		float wallHeight=GetWallHeight((PathfindLayerEnum)cell->getLayer(),&topLeftCorner,0);
		float bridgeHeight=theBridge->getBridgeHeight(&topLeftCorner,0);
		if(theBridge->isCellOnEnd(&cellBounds)){
			if(otherCell&&fabs(bridgeHeight-height)<15.0f){
				if(((Rva00366500*)cell)->rva00366500(0x10)|((Rva00366500*)cell)->rva0036652D(otherCell->getLayer())|cell->SetType_Dirty(0)|((Rva0052E0A1*)cell)->rva0052E0A1(0))m_zoneManager.MarkDirty(i,j);
				((Rva00366500*)otherCell)->rva0036652D(cell->getLayer());
				otherCell->SetType_Dirty(0);
			}else if(fabs(wallHeight-bridgeHeight)<15.0f){
				if(cell->SetType_Dirty(0)|((Rva00366500*)cell)->rva0036652D(0x10)|((Rva0052E0A1*)cell)->rva0052E0A1(0))m_zoneManager.MarkDirty(i,j);
			}else{
				if(((Rva00366500*)cell)->rva00366500(0x10)|((Rva0052E0A1*)cell)->rva0052E0A1(0)|((Rva00366500*)cell)->rva0036652D(0)|cell->SetType_Dirty(0))m_zoneManager.MarkDirty(i,j);
				cell->setPinched(false);
			}
		}else{
			// it's off the bridge.
			if(((Rva00366500*)cell)->rva00366500(0x10)|((Rva00366500*)cell)->rva0036652D(0)|cell->SetType_Dirty(5))m_zoneManager.MarkDirty(i,j);
		}
		return;
	}
	if(bridgeCount!=0){
		if(((Rva0052E001*)cell)->rva0052E001(false))m_zoneManager.MarkDirty(i,j);
		int count=0;int maxLayer=1;
		for(int x=i-1;x<i+2;x++){
			if(x<m_extent.lo.x||x>m_extent.hi.x)continue;
			for(int y=j-1;y<j+2;y++){
				if(y<m_extent.lo.y||y>m_extent.hi.y)continue;
				if(x==i&&j==y)continue;
				int layer=m_map[x][y].getLayer();
				if(layer>0x10){count++;maxLayer=layer;}
			}
		}
		int layer=cell->getLayer();
		if(layer==0x10){
			if(bridgeCount!=4&&count>=3) ((Rva00366500*)cell)->rva00366500(maxLayer);
			else{((Rva00366500*)cell)->rva00366500(1);cell->SetType_Dirty(0);}
			m_zoneManager.MarkDirty(i,j);
		}else if(layer!=1){
			if(cell->SetType_Dirty(5))m_zoneManager.MarkDirty(i,j);
		}
		if(((Rva00366500*)cell)->rva0036652D(0))m_zoneManager.MarkDirty(i,j);
	}else if(cell->getType()==2){
		cell->SetType_Dirty(0);
		m_zoneManager.MarkDirty(i,j);
	}
}
int BridgeUpdateNeighborX[8]={-1,1,0,0,-1,1,-1,1};
int BridgeUpdateNeighborY[8]={0,0,-1,1,-1,-1,1,1};
class Rva002E713FOwner {public:
 void rva0052ED74(void *,int);
 char pad00[0x10];PathfindCell **map;int loX,loY,hiX,hiY;char pad24[0x5C-0x24];Bridge *bridges;
 PathfindLayer layers[16];PathfindZoneManager zones;bool changed;
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
    for(int neighborIndex=0;neighborIndex<8;++neighborIndex){
     PathfindCell *near=&map[i+BridgeUpdateNeighborX[neighborIndex]][j+BridgeUpdateNeighborY[neighborIndex]];
     if(near->layer!=16 && near->type!=5 && near->layer==1 && near->getOwner()==0){
      if(near->SetType_Dirty(2))zones.MarkDirty(i+BridgeUpdateNeighborX[neighborIndex],j+BridgeUpdateNeighborY[neighborIndex]);
     }
    }
   }
  }
 }
}
