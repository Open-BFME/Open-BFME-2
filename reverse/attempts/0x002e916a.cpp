// ?rva002E916A@Rva002E7388Owner@@QAE_NHH@Z
// partial score=0.9424238913 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native 2E916A..2E931F owns a 0x30-byte destination-check functor.
// BFME1/ZH Pathfinder checkDestination is the semantic guide to footprint,
// layers and height variation; target-specific endpoints and excluded-cell
// line walk come from this complete native boundary and WB D3CDE0.
// Field names remain structural. 2E7388 setter independently establishes
// field offsets; no new source name, type or storage ownership is inferred.
#include <math.h>
struct ICoord2DBase {int x,y;};
struct ICoord2D:public ICoord2DBase {bool operator!=(const ICoord2DBase&)const;};
enum PathfindLayerEnum { LAYER_INVALID=0 };
class PathfindCell {public: void*info;char unknown04[8];unsigned flags; };
struct Rva002E8145Info {int opaque,skipX,skipY;};
class Rva002E7388Owner;
class Pathfinder {
public:PathfindCell *getCell(PathfindLayerEnum,int,int);
private:friend class Rva002E7388Owner;
 int rva002E8145(const ICoord2D*,const ICoord2D*,PathfindLayerEnum,Rva002E8145Info*);
};
class Rva002E6DC4 {public:bool rva002E6DC4(void*,void*);};
int Rva002E6E8AGet(int);
bool Rva001E3679(int);
int Rva002E6E6CGet(int);
class TerrainLogic {
public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();
 virtual float height(float,float,int,void*,bool);
};
extern TerrainLogic *TheTerrainLogic;
class Rva002E7388Owner {
public:bool rva002E916A(int x,int y);
private:Pathfinder*pathfinder;void*movementInfo;ICoord2D current;int layer,requestedLayer;ICoord2D skipped;int radiusBefore,radiusAfter;void*object;bool state;
};
bool Rva002E7388Owner::rva002E916A(int x,int y)
{
 bool first=true;
 float initialHeight=0.0f;
 for(int cx=x-radiusBefore;cx<x+radiusAfter;++cx) {
  for(int cy=y-radiusBefore;cy<y+radiusAfter;++cy) {
   PathfindCell*cell=pathfinder->getCell((PathfindLayerEnum)layer,cx,cy);
   if(!cell)return false;
   unsigned flags=cell->flags;
   int cellLayer=(flags>>4)&0x3f;
   if((unsigned char)(flags>>16)&1)return false;
   if(requestedLayer!=cellLayer) {
    if(requestedLayer==1) {if(cellLayer!=16)return false;}
    else if(requestedLayer==16) {}
    else if((unsigned char)Rva002E6E8AGet(requestedLayer)||Rva001E3679(requestedLayer)) {if(cellLayer!=16)return false;}
   }
   if(!((Rva002E6DC4*)pathfinder)->rva002E6DC4(movementInfo,cell))return false;
   float h=TheTerrainLogic->height(float(cx*10)+5.0,float(cy*10)+5.0,cellLayer,0,true);
   if(first){initialHeight=h;first=false;}
   else if((float)fabs((double)(h-initialHeight))>10.0f)return false;
  }
 }
 current.x=x;current.y=y;
 const ICoord2D *skip=&skipped;
 int requested=requestedLayer;
 if((unsigned char)Rva002E6E6CGet(requested)&&current!=*skip) {
  Rva002E8145Info info;info.opaque=(int)pathfinder;info.skipX=skip->x;info.skipY=skip->y;
  if(pathfinder->rva002E8145(&current,skip,(PathfindLayerEnum)requested,&info))return false;
 }
 return true;
}
