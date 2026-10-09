// ?rva002ED313@Pathfinder@@QAE_NPAVObject@@@Z
// partial score=0.753315 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native2ED313..2ED484 RET4 complete369; existing thiscall Object* pin.
// ZH checkForMovement supplies the rectangular-footprint/cell-list scaffold;
// this native occupancy rule uses template flag122 bit10 and two lists14/20.
// Target x-cell negative -> false; impassable/obstacle cells fail; bit18
// fails for Object flag AFBB. Two supported occupied-cell branches remain
// named by addresses/offsets; no original target method or kind name asserted.
#include "Lib/Coord3D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
struct ICoord2D {int x,y;};
struct RectTemplateView {char pad00[0x122];unsigned char flag122;};
class Object {public:bool rva0028AFBB()const;void *vtable;RectTemplateView *templ;char pad08[0x38-8];Coord3D pos;char pad44[0x74-0x44];int id;};
struct RectNode {RectNode *next;void *previous;Object *object;};
struct RectCellInfo {char pad00[0x14];RectNode *reserved;char pad18[8];RectNode *actual;
 __forceinline Object *find(Object *o)const {for(RectNode *n=reserved;n;n=n->next)if(n->object==o)return n->object;return 0;}
};
class PathfindCell {public:RectCellInfo *info;char pad04[8];unsigned int flags;
 __forceinline bool hasActual()const {if(info)return info->actual!=0;return false;}
 __forceinline bool hasReserved()const {if(info)return info->reserved!=0;return false;}
};
class Rva0052DB11 {public:bool rva0052DB11(int);};
class Rva002EBC34 {public:ICoord2D *rva002EBC34(ICoord2D *,void *,const Coord3D *);};
void Rva002EBCD6Split(void *,int *,int *);
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {public:bool rva002ED313(Object *);PathfindCell *getCell(PathfindLayerEnum,int,int);};
bool Pathfinder::rva002ED313(Object *obj)
{
 ICoord2D cell;((Rva002EBC34 *)this)->rva002EBC34(&cell,obj,&obj->pos);
 int centerX=cell.x;if(centerX<0)return false;
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,&obj->pos);
 int below,above;Rva002EBCD6Split(obj,&below,&above);
 int id=obj->id;
 int maxX=centerX+above;
 for(int x=centerX-below;x<maxX;++x) {
  int firstY=cell.y-below,maxY=cell.y+above;
  for(int y=firstY;y<maxY;++y) {
   PathfindCell *c=getCell(layer,x,y);
   if(!c || (c->flags&0xF)==5)return false;
   if(((unsigned char)(c->flags>>18)&1) && obj->rva0028AFBB())return false;
   if((c->flags&0xF)==4)return false;
   if(c->hasActual() || c->hasReserved()) {
    RectCellInfo *info=c->info;
    if(obj->templ->flag122&0x10) {
     if(info)for(RectNode *n=info->actual;n;n=n->next) {
      Object *other=n->object;
      if(other->id!=id) {Object *reserved=info->find(other);if(reserved && (reserved->templ->flag122&0x10))return false;}
     }
    } else if(((Rva0052DB11 *)c)->rva0052DB11(id))return false;
   }
  }
 }
 return true;
}
