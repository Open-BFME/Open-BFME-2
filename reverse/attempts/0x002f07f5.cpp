// ?rva002F07F5@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.787203 date=2026-10-09
// ?rva002F07F5@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.787203 date=2026-10-09
// cl: /ICode/Libraries/Include /ICode/GameEngine/Source/Common /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Address-derived helper2F07F5..2F0A72 RET8,637B.
// Target first checks2F06A3(Object,current,dest,current); counts list+14
// entries in current footprint, then validates destination footprint and
// rejects when other-item count reaches the old count or a linked owner
// has AI+16C>0. Native bit16 triggers four same-layer neighbor checks.
// ZH checkForMovement supplies footprint/cell-list semantics; this horde
// extension's counters and flags are target facts, not a donor identity.
#include "Lib/Coord3D.h"
typedef int Int;typedef bool Bool;
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
struct ICoord2D {Int x,y;};
struct Rva002E8BCFSrc;
class Rva002E8BCF {public: Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool);Int surfaces;Bool flag4,flag5;Int limit;Bool flagC;};
class Rva002E6DC4 {public: Bool rva002E6DC4(void *,void *);};
class AIUpdateInterface {public: char pad00[0x16C];Int field16C;};
class ThingTemplate {public: char pad00[0x56C];Int priority;char pad570[0x634-0x570];Bool flag634;};
class Object {
public:
 Int rva0028B511() const;Bool rva0028AFBB() const;Object *rva002931F5(Bool);

};
// Object's independently observed prefix: template4,position38,AI258.
struct Rva002F07F5ObjectView {void *vtable;ThingTemplate *templ;char pad08[0x38-8];Coord3D pos;char pad44[0x258-0x44];AIUpdateInterface *ai;};
struct Rva002F07F5Node {Rva002F07F5Node *next;void *prev;Object *obj;};
struct Rva002F07F5CellInfo {char pad00[0x14];Rva002F07F5Node *items;};
class PathfindCell {public: Rva002F07F5CellInfo *info;char pad04[8];unsigned int flags;Int getLayer()const{return (flags>>4)&0x3F;}};
class TerrainLogic {
public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
 S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
 S(40) S(41) S(42) S(43)
#undef S
 virtual Bool slotB0(Object *,Int);
};
extern TerrainLogic *TheTerrainLogic;
void Rva002EBCD6Split(void *,Int *,Int *);
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
Int Rva002E6E6CGet(Int);
class Pathfinder {
public:
 Bool rva002F06A3(Object *,const Coord3D *,const Coord3D *,const Coord3D *);
 Bool rva002F07F5(Object *,const Coord3D *);
 PathfindCell *getCell(PathfindLayerEnum,Int,Int);
};
Bool Pathfinder::rva002F07F5(Object *obj,const Coord3D *dest)
{
 Rva002F07F5ObjectView *view=(Rva002F07F5ObjectView *)obj;
 const Coord3D *from=&view->pos;
 if(!rva002F06A3(obj,from,dest,from))return false;
 Int newCount=0;
 Int below,above;Rva002EBCD6Split(obj,&below,&above);
 Int layers[2];layers[0]=obj->rva0028B511();Int layerCount=1;
 if(!(unsigned char)Rva002E6E6CGet(layers[0]) && TheTerrainLogic->slotB0(obj,layers[0])) {
  layers[1]=1;layerCount=2;
 }
 Int oldCount=0;
 {
  ICoord2D cell;Rva002EBC14Cell(&cell,obj,from);
  Int lastX=cell.x+above;
  for(Int x=cell.x-below;x<lastX;++x) {
   Int firstY=cell.y-below,lastY=cell.y+above;
   for(Int y=firstY;y<lastY;++y)
    for(Int l=0;l<layerCount;++l) {
     PathfindCell *c=getCell((PathfindLayerEnum)layers[l],x,y);
     if(c && c->info)for(Rva002F07F5Node *n=c->info->items;n;n=n->next)if(n->obj!=obj)++oldCount;
    }
  }
 }
 ICoord2D cell;ICoord2D *found=Rva002EBC14Cell(&cell,obj,dest);Int destX=found->x,destY=found->y;
 Int priority=view->templ->priority;Bool flag=view->templ->flag634;AIUpdateInterface *ai=view->ai;
 Rva002E8BCF query((const Rva002E8BCFSrc *)((char *)ai+0x1CC),!flag,priority-1,obj->rva0028AFBB());
 Int lastX=destX+above;
 for(Int x=destX-below;x<lastX;++x) {
  Int firstY=destY-below,lastY=destY+above;
  for(Int y=firstY;y<lastY;++y)
   for(Int l=0;l<layerCount;++l) {
    Int layer=layers[l];PathfindCell *c=getCell((PathfindLayerEnum)layer,x,y);
    if(!c)continue;
    if(c->flags & 0x10000) {
     static Int deltaX[]={-1,1,0,0};static Int deltaY[]={0,0,-1,1};
     for(Int i=0;i<4;++i) {
      PathfindCell *neighbor=getCell((PathfindLayerEnum)layer,x+deltaX[i],y+deltaY[i]);
      if(neighbor && neighbor->getLayer()!=layer)return false;
     }
    }
    Rva002F07F5CellInfo *info=c->info;
    if(info) {
     if(!((Rva002E6DC4 *)this)->rva002E6DC4(&query,c))return false;
     for(Rva002F07F5Node *n=info->items;n;n=n->next) {
      if(n->obj==obj)continue;
      ++newCount;
      if(newCount>=oldCount)return false;
      Object *effective=n->obj->rva002931F5(true);if(!effective)effective=n->obj;
      AIUpdateInterface *other=((Rva002F07F5ObjectView *)effective)->ai;
      if(other && other->field16C>0)return false;
     }
    }
   }
 }
 return true;
}
