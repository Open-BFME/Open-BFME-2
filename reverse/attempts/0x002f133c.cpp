// ?rva002F133C@Rva002F2865Host@@QAEHPAD0H@Z
// partial score=0.772213 date=2026-10-09
// cl: /ICode/Libraries/Include /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native2F133C..2F14F9 RET12 complete445. Existing Rva002F2865Host pin
// spelling/signature retained for its rowed forwarder. Both pointer args are
// decoded from target accesses; final integer argument carries an ID buffer.
// Target scans footprint perimeter (not a line walk), at most16 distinct IDs.
// ZH pathfinder footprint and cell occupancy supply semantic context; this
// target extension and visit stamp are native facts; no original name claimed.
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
struct ICoord2D {int x,y;};
class Object {public:int rva0028B511()const;bool rva002E6B89();char pad00[0x74];ObjectID id;};
struct CellObjectNode {CellObjectNode *next;void *previous;Object *object;};
struct PerimeterCellInfo {char pad00[0x20];CellObjectNode *items;int word24;ObjectID fallbackID;};
class PathfindCell {public:PerimeterCellInfo *info;};
class TerrainLogic {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual bool slotB0(Object *,int);
};
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern int g_Va00DFECD0; // existing rowed Object visit-stamp provider owns this.
void Rva002EBCD6Split(void *,int *,int *);
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
int Rva002E6E6CGet(int);
class Rva002F2865Host {public:int rva002F133C(char *,char *,int);};
class Pathfinder {public:PathfindCell *getCell(PathfindLayerEnum,int,int);};
int Rva002F2865Host::rva002F133C(char *record,char *destination,int output)
{
 Object *obj=(Object *)record;ObjectID *ids=(ObjectID *)output;
 ICoord2D center;Rva002EBC14Cell(&center,obj,(const Coord3D *)destination);
 int below,above;Rva002EBCD6Split(obj,&below,&above);
 int layers[2];layers[0]=obj->rva0028B511();int layerCount=1;
 if(!(unsigned char)Rva002E6E6CGet(layers[0]) && TheTerrainLogic->slotB0(obj,layers[0])) {layers[1]=1;layerCount=2;}
 int count=0;++g_Va00DFECD0;obj->rva002E6B89();
 int firstX=center.x-below-1,lastX=center.x+above;
 int x=firstX;if(x<lastX+1) {
 int oldY=center.y;center.y-=below+1;int lastY=oldY+above+1;
 do {
  int step=1;if(x!=firstX && x!=lastX)step=below+above+1;
  for(int y=center.y;y<lastY;y+=step)
   for(int l=0;l<layerCount;++l) {
    PathfindCell *cell=((Pathfinder *)this)->getCell((PathfindLayerEnum)layers[l],x,y);
    if(cell && cell->info) {
     CellObjectNode *n;
     for(n=cell->info->items;n;n=n->next) {
      Object *other=n->object;
      if(!other->rva002E6B89()) {ids[count++]=other->id;if(count==16)return count;}
     }
     if(cell->info->items==n) {
      PerimeterCellInfo *info=cell->info;
      Object *other=TheGameLogic->findObjectByID(info?info->fallbackID:INVALID_OBJECT_ID);
      if(other && !other->rva002E6B89()) {ids[count++]=other->id;if(count==16)return count;}
     }
    }
   }
 }while(++x<lastX+1);
 }
 return count;
}
