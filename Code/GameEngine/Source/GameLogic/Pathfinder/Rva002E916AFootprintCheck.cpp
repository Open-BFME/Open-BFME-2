// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002E916A@Rva002E7388Owner@@QAE_NHH@Z
// Native 2E916A..2E931F (437B, RET8) owns a 0x30-byte destination-check functor
// (fields set by the matched 2E7388 setter). WB D3CDE0 twin; BFME1/ZH Pathfinder
// checkDestination is the semantic guide: every footprint cell around (x,y)
// must exist, not be blocked (flags bit16), match the requested layer (layer 1
// or a 2E6E8A/1E3679 layer only over layer-16 cells), pass the movement check
// 2E6DC4, and its centre ground height (cell*10 + 5, through a Coord3D local
// as in the WB twin) must stay within 10 of the first cell's. Then the centre
// is stored and, for a 2E6E6C layer whose skipped cell differs, the 2E8145
// line walk must not hit. The height delta uses the float <math.h> fabs
// overload (retail compares the CRT fabs result without a float narrowing).
// Field names remain structural.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// class-gate: allow ICoord2D TU-local view: the canonical header lacks the ICoord2DBase base and operator!=, and retail calls the rowed out-of-line ICoord2D::operator!= at 0x00004CC9.
struct ICoord2DBase
{
public:
	int x; // +0x00
	int y; // +0x04
};
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
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};
int Rva002E6E8AGet(int);
bool Rva001E3679(int);
int isGroundOrBridgeLayer(int);
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
   Coord3D pos;
   pos.x=cx*10+5.0f;
   pos.y=cy*10+5.0f;
   float h=TheTerrainLogic->height(pos.x,pos.y,cellLayer,0,true);
   if(first){initialHeight=h;first=false;}
   else if(fabs(h-initialHeight)>10.0f)return false;
  }
 }
 current.x=x;current.y=y;
 int requested=requestedLayer;
 if((unsigned char)isGroundOrBridgeLayer(requested)) {
  const ICoord2D *skip=&skipped;
  if(current!=*skip) {
   Rva002E8145Info info;info.opaque=(int)pathfinder;info.skipX=skip->x;info.skipY=skip->y;
   if(pathfinder->rva002E8145(&current,skip,(PathfindLayerEnum)requested,&info))return false;
  }
 }
 return true;
}
