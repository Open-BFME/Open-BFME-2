// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native2EF2A6..2EF3D9 RET4; existing AdjustLayer callee pin from WB.
// Cell layer differs from Object's old layer: height gate then scan bridges.
// Float threshold independently read as10.0 from nativeBC2428; no global.
// Original field spellings remain inferred; native bytes prove accesses.
#include <math.h>
#include "Lib/Coord3D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
struct ObjWithPos;
class Object {public:int rva0028B511()const;void setLayer(PathfindLayerEnum);char pad00[0x38];Coord3D position;};
#include "../../../Include/GameLogic/PathfindCell.h"
#include "../../../Include/Common/Rva0036666B.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/GameLogic/AIPathfind.h"
void Pathfinder::AdjustLayer(Object *obj)
{
 int oldLayer=obj->rva0028B511();
 PathfindCell *cell=Rva002EDF44((ObjWithPos *)obj);
 Coord3D pos;pos.x=obj->position.x;pos.y=obj->position.y;pos.z=obj->position.z;
 if(cell && cell->getLayer()!=oldLayer) {
  float limit=pos.z+10.0f;
  if(TheTerrainLogic->getLayerHeight(pos.x,pos.y,(PathfindLayerEnum)cell->getLayer(),0,true)>limit)obj->setLayer((PathfindLayerEnum)cell->getLayer());
  int i=2;Rva0036666B *layer=(Rva0036666B *)((char *)this+0xE0);
  for(;i<=15;++i,layer=(Rva0036666B *)((char *)layer+0x40)) {
   if(layer->rva0036666B()) {
    PathfindCell *next=(PathfindCell *)rva001E3647Pos(i,&pos);
    if(next && next->getLayer()==i && next->getType()!=PathfindCell::CELL_BRIDGE_IMPASSABLE) {
     if(fabs(TheTerrainLogic->getLayerHeight(pos.x,pos.y,(PathfindLayerEnum)i,0,true)-pos.z)<10.0f) {
      obj->setLayer((PathfindLayerEnum)i);break;
     }
    }
   }
  }
 }
}
