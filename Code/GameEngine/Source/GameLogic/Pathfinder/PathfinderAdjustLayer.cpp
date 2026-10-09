// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native2EF2A6..2EF3D9 RET4; existing AdjustLayer callee pin from WB.
// Cell layer differs from Object's old layer: height gate then scan bridges.
// Float threshold independently read as10.0 from nativeBC2428; no global.
// Original field spellings remain inferred; native bytes prove accesses.
#include <math.h>
#include "Lib/Coord3D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
struct ObjWithPos;
class Object {public:int rva0028B511()const;void rva0028B4CE(PathfindLayerEnum);char pad00[0x38];Coord3D position;};
class PathfindCell {public:char pad00[0xC];unsigned flags;int layer()const{return(flags>>4)&0x3F;}int type()const{return flags&0xF;}};
class Rva0036666B {public:bool rva0036666B();};
class TerrainLogic {
public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();
 virtual void slot10();virtual void slot14();virtual void slot18();
 virtual float slot1C(float,float,int,Coord3D *,bool);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {public:void rva002EF2A6(Object *);PathfindCell *Rva002EDF44(ObjWithPos *);void *rva001E3647Pos(int,const Coord3D *);};
void Pathfinder::rva002EF2A6(Object *obj)
{
 int oldLayer=obj->rva0028B511();
 PathfindCell *cell=Rva002EDF44((ObjWithPos *)obj);
 Coord3D pos;pos.x=obj->position.x;pos.y=obj->position.y;pos.z=obj->position.z;
 if(cell && cell->layer()!=oldLayer) {
  float limit=pos.z+10.0f;
  if(TheTerrainLogic->slot1C(pos.x,pos.y,cell->layer(),0,true)>limit)obj->rva0028B4CE((PathfindLayerEnum)cell->layer());
  int i=2;Rva0036666B *layer=(Rva0036666B *)((char *)this+0xE0);
  for(;i<=15;++i,layer=(Rva0036666B *)((char *)layer+0x40)) {
   if(layer->rva0036666B()) {
    PathfindCell *next=(PathfindCell *)rva001E3647Pos(i,&pos);
    if(next && next->layer()==i && next->type()!=5) {
     if(fabs(TheTerrainLogic->slot1C(pos.x,pos.y,i,0,true)-pos.z)<10.0f) {
      obj->rva0028B4CE((PathfindLayerEnum)i);break;
     }
    }
   }
  }
 }
}
