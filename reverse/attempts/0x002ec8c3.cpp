// ?_GetOverlapUnits@Pathfinder@@QAEHPAVObject@@PBUCoord3D@@PAH@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /ICode/Libraries/Include/Lib
// Native2EC8C3..2EC9E1 RET12 and WB D3AF90 identify _GetOverlapUnits.
#include "Coord3D.h"
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND=1 };
struct ICoord2D { int x,y; };
class Object { public: int rva0028B511() const; bool rva002E6B89(); int getID() const { return *(const int *)((const char *)this+0x74); } };
struct PathCollisionNode { PathCollisionNode *next; void *word4; Object *object; };
struct PathCollisionInfo { char prefix[0x20]; PathCollisionNode *occupants; };
class PathfindCell { public: PathCollisionInfo *info; };
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva002EBCD6Split(void *,int *,int *);
int Rva002E6E6CGet(int);
extern int g_Va00DFECD0;
template<int N> class OverlapSlots: public OverlapSlots<N-1> { public: virtual void slot(OverlapSlots<N> *); };
template<> class OverlapSlots<0> {};
class TerrainLogic: public OverlapSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
extern TerrainLogic *TheTerrainLogic;
class Pathfinder {
public:
 int _GetOverlapUnits(Object *,const Coord3D *,int *);
 PathfindCell *getCell(PathfindLayerEnum,int,int);
};
int Pathfinder::_GetOverlapUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)Rva002E6E6CGet(layers[0]) && TheTerrainLogic->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathfindCell *c=getCell((PathfindLayerEnum)layers[k],x,y);
    if(c && c->info) {
     for(PathCollisionNode *node=c->info->occupants;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
    }
   }
  }
 }
 return count;
}

